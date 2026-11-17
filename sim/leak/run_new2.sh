#!/bin/bash
# second queue: gate-level controls, delay-variation study, second compression gadget
cd /home/claude/pqc-riscv-fl
L=sim/leak
gs() {   # tag targets [extra gsim args]
  local tag=$1 tg=$2; shift 2
  for t in ${tg//,/ }; do
    (cd $L/$tag/t$t && ../../../gsim/gsim ../../../gsim/soc.gnl fw.hex -o gleak.bin -maxcyc 4000000000 "$@" > grun.log 2>&1)
    python3 analysis/tvla2.py $tag gsim $t > $L/$tag/t$t/tvla_gsim.txt 2>&1
    echo "$(date +%T) gsim $tag t$t done"
  done
}
rtl() {
  for t in ${2//,/ }; do
    (cd $L/$1/t$t && ../../../objl2_ise/vsoc +fw=fw.hex +maxcyc=4000000000 > run.log 2>&1)
    python3 analysis/tvla2.py $1 rtl $t > $L/$1/t$t/tvla_rtl.txt 2>&1
    rm -f $L/$1/t$t/leak.bin $L/$1/t$t/leakpc.txt
    echo "$(date +%T) rtl $1 t$t done"
  done
}
B="python3 analysis/leak_campaign.py build"
case $1 in
  K7)  gs gn2 7 ;;
  KZ)  $B gn2z v2z 400 1 2 1 21 6,7,9 8; gs gn2z 9,6,7 ;;
  KPZ) $B gpz v2z 300 1 2 1 31 0,4 8; gs gpz 0,4 -pvar 0.1 31 ;;
  KP0) $B gp v2 1000 1 2 1 31 0,4 8; gs gp 0 -pvar 0.1 31 ;;
  KP4) gs gp 4 -pvar 0.1 31 ;;
  KR2) $B n2b v2 20000 1 2 1 23 6,7,8,9 8; rtl n2b 9,6,7,8 ;;
esac
echo "$(date +%T) $1 ALLDONE"
