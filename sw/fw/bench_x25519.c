/* classical baseline: X25519 ECDH (Monocypher, portable C) on the same core */
#include <stdint.h>
#include "monocypher.h"
#include "platform.h"
int main(void)
{
    uint8_t ska[32], skb[32], pka[32], pkb[32], s1[32], s2[32];
    uint32_t t, i;
    for (i = 0; i < 32; i++) { ska[i] = (uint8_t)(i * 13 + 5); skb[i] = (uint8_t)(i * 29 + 3); }
    t = rdcycle(); crypto_x25519_public_key(pka, ska); pf_kv("x25519_keygen", rdcycle() - t);
    crypto_x25519_public_key(pkb, skb);
    t = rdcycle(); crypto_x25519(s1, ska, pkb);        pf_kv("x25519_shared", rdcycle() - t);
    crypto_x25519(s2, skb, pka);
    for (i = 0, t = 0; i < 32; i++) t |= (uint32_t)(s1[i] ^ s2[i]);
    pf_kv("x25519_match", t == 0);
    pf_puts("DONE\n");
    pf_exit(0);
    return 0;
}
