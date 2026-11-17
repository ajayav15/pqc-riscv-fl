#!/bin/bash
# sequential leakage campaigns for the additional gadgets and the delay-variation study
# usage: run_new.sh <job>
cd /home/claude/pqc-riscv-fl
L=sim/leak
rtl() {  # tag targets
  for t in ${2//,/ }; do
    (cd $L/$1/t$t && ../../../objl2_ise/vsoc +fw=fw.hex +maxcyc=4000000000 > run.log 2>&1)
    python3 analysis/tvla2.py $1 rtl $t > $L/$1/t$t/tvla_rtl.txt 2>&1
    rm -f $L/$1/t$t/leak.bin $L/$1/t$t/leakpc.txt
    echo "$(date +%T) rtl $1 t$t done"
  done
}
gs() {   # tag targets [extra gsim args]
  local tag=$1 tg=$2; shift 2
  for t in ${tg//,/ }; do
    (cd $L/$tag/t$t && ../../../gsim/gsim ../../../gsim/soc.gnl fw.hex -o gleak.bin -maxcyc 4000000000 "$@" > grun.log 2>&1)
    python3 analysis/tvla2.py $tag gsim $t > $L/$tag/t$t/tvla_gsim.txt 2>&1
    echo "$(date +%T) gsim $tag t$t done"
  done
}
B="python3 analysis/leak_campaign.py build"
case $1 in
  J1) $B n2a v2 20000 1 2 1 21 6,7,8,9 8; $B n2z v2z 4000 1 2 1 21 6,7,8,9 8
      rtl n2a 9,6,7,8; rtl n2z 9,6,7,8 ;;
  J1b) $B n2z v2z 4000 1 2 1 21 6,7,8,9 8
      rtl n2a 6,7,8; rtl n2z 9,6,7,8 ;;
  J2) $B gn9 v2 2000 1 2 1 21 9 8; $B gn2 v2 1000 1 2 1 21 6,7 8
      gs gn9 9; gs gn2 6 ;;
  J2b) gs gn2 7 ;;
  J3) $B n2b v2 20000 1 2 1 23 6,7,8,9 8; rtl n2b 9,6,7,8 ;;
  J4) $B gn2z v2z 400 1 2 1 21 6,7,9 8; gs gn2z 9,6,7
      $B gpz v2z 500 1 2 1 31 0,4 8; gs gpz 0,4 -pvar 0.1 31 ;;
  J5) $B gp v2 2000 1 2 1 31 0,4 8; gs gp 0,4 -pvar 0.1 31 ;;
esac
echo "$(date +%T) $1 ALLDONE"
