/* Cycle cost and functional check of the on-node detector (detector.c):
 * runs the exported window stream, prints each int8 logit next to the Python
 * reference and the per-window cycle count. */
#include <stdint.h>
#include "platform.h"
#ifdef DET_VEC_FILE
#include DET_VEC_FILE
#else
#include "det_vectors.h"
#endif
int32_t det_window(const int16_t *x, int32_t log_rate_q12, int32_t reject);
int main(void)
{
    unsigned i, agree = 0;
    uint32_t cyc = 0, cmax = 0;
    OUT_MARK = 1;
    for (i = 0; i < DET_NVEC; i++) {
        uint32_t t = rdcycle();
        int32_t s = det_window(det_x[i], det_lograte_q12, 0);
        t = rdcycle() - t;
        cyc += t; if (t > cmax) cmax = t;
        agree += ((s > 0) == (det_ref[i] > 0));
        pf_puts("w"); pf_putu(i); pf_puts(" lbl="); pf_putu(det_lbl[i]);
        pf_puts(" c="); pf_puts(s < 0 ? "-" : ""); pf_putu((uint32_t)(s < 0 ? -s : s));
        pf_puts(" py="); pf_puts(det_ref[i] < 0 ? "-" : ""); pf_putu((uint32_t)(det_ref[i] < 0 ? -det_ref[i] : det_ref[i]));
        pf_puts(" cyc="); pf_putu(t); pf_puts("\n");
    }
    OUT_MARK = 0;
    pf_kv("det_agree", agree);
    pf_kv("det_n", DET_NVEC);
    pf_kv("det_avg_cycles", cyc / DET_NVEC);
    pf_kv("det_max_cycles", cmax);
#ifdef DET_PROF
    { extern uint32_t det_prof[8]; unsigned k; for (k = 0; k < 7; k++) { pf_puts("prof"); pf_putu(k); pf_puts("="); pf_putu(det_prof[k] / DET_NVEC); pf_puts("\n"); } }
#endif
    pf_puts("DONE\n");
    pf_exit(0);
    return 0;
}
