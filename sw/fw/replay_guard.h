#pragma once
#include <stdint.h>
#ifndef RG_N
#define RG_N 8
#endif
enum { RG_FRESH = 0, RG_RESEND = 1, RG_NEAR = 2 };
extern unsigned rg_last_matches;
int replay_guard(const uint8_t *ct, unsigned ctlen, uint8_t ss_cached[32]);
void replay_guard_store(const uint8_t ss[32]);
