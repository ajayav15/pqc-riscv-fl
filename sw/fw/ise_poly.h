#pragma once
#include <stdint.h>
#include "poly.h"
#include "polyvec.h"
extern volatile uint32_t ise_sw_shuffle;
void ise_ntt(int16_t r[256]);
void ise_invntt(int16_t r[256]);
void ise_polyvec_basemul_acc(poly *r, const polyvec *a, const polyvec *b);
