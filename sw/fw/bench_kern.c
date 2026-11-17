/* RTL kernel benchmark: NTT / INTT / basemul_acc cycle counts and a checksum,
 * for baseline (reference C) and ISE builds, with mitigation off and on.
 * Avoids Keccak so it completes quickly under cycle-accurate RTL simulation.
 * Full-KEM functional correctness is established separately by the native
 * cross-check (bench.c: matching KAT FNV and shared secret). */
#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "platform.h"
#ifdef USE_ISE
#include "ise.h"
#include "ise_poly.h"
#endif

#include <stddef.h>
static uint64_t rs = 0x243F6A8885A308D3ull;
static uint32_t xr(void){ rs^=rs<<13; rs^=rs>>7; rs^=rs<<17; return (uint32_t)rs; }
void randombytes(uint8_t *o, size_t n){ for(size_t i=0;i<n;i++) o[i]=(uint8_t)xr(); }
static uint16_t uq(void){ uint32_t r; do r=xr()&0xFFFu; while(r>=KYBER_Q); return (uint16_t)r; }
static uint32_t fnv(const void*p,unsigned n,uint32_t h){const uint8_t*b=p;for(unsigned i=0;i<n;i++){h^=b[i];h*=16777619u;}return h;}

static poly a; static polyvec pa, pb; static poly acc;

static void fill(void){
  unsigned i,j;
  for(j=0;j<KYBER_N;j++) a.coeffs[j]=(int16_t)uq();
  for(i=0;i<KYBER_K;i++) for(j=0;j<KYBER_N;j++){ pa.vec[i].coeffs[j]=(int16_t)uq(); pb.vec[i].coeffs[j]=(int16_t)uq(); }
}

static void suite(const char*tag){
  uint32_t t,h=2166136261u; unsigned j;
  pf_puts(tag);
  rs=0x243F6A8885A308D3ull;   /* identical inputs across runs: result is an invariant */
  fill();
  t=rdcycle(); poly_ntt(&a);                              pf_kv("ntt",rdcycle()-t);
  h=fnv(a.coeffs,sizeof a.coeffs,h);
  t=rdcycle(); poly_invntt_tomont(&a);                    pf_kv("invntt",rdcycle()-t);
  h=fnv(a.coeffs,sizeof a.coeffs,h);
  for(j=0;j<KYBER_K;j++){ poly_ntt(&pa.vec[j]); poly_ntt(&pb.vec[j]); }
  t=rdcycle(); polyvec_basemul_acc_montgomery(&acc,&pa,&pb); pf_kv("basemul_acc",rdcycle()-t);
  h=fnv(acc.coeffs,sizeof acc.coeffs,h);
  pf_kx("kern_fnv",h);
}

int main(void){
#ifdef USE_ISE
  suite("[ise]\n");
  KSEED(0x1234567u);
  KCFG(CFG_DUMMY|CFG_SHUFFLE|CFG_DVFS|CFG_TH(8)|CFG_MASK(3));
  ise_sw_shuffle=1;
  suite("[ise_mitig]\n");
  { uint32_t d; KSTAT(d); pf_kv("dummy_ops",d); }
  KCFG(0); ise_sw_shuffle=0;
#else
  suite("[ref]\n");
#endif
  pf_puts("DONE\n"); pf_exit(0); return 0;
}
