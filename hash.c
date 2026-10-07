#include "hash.h"
#include <stdint.h>

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value

    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);
            unsigned char old_A = A;
            A = ((A + msg[i]) ^ B) | C;
            B = (D << 1) ^ E;
            E = (g + old_A) & D;
            D = (A ^ B) >> 2;
            C = (C + E) ^ A;
            A = D + B;
            B = B * D;
        }
    }

    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    
    return digest;
}
#define SSHA2_DIGEST_SIZE 20
typedef struct {
    unsigned char bytes[SSHA2_DIGEST_SIZE];
} Digest;

static void ssha2_init_state(uint32_t* A, uint32_t* B, uint32_t* C,
    uint32_t* D, uint32_t* E)
{
    *A = 0x67452301u;
    *B = 0xEFCDAB89u;
    *C = 0x98BADCFEu;
    *D = 0x10325476u;
    *E = 0xC3D2E1F0u;
}

Digest SSHA2(const unsigned char* msg, size_t length)
{
    uint32_t A, B, C, D, E;
    ssha2_init_state(&A, &B, &C, &D, &E);

    for (size_t i = 0; i < length; ++i) {
        uint32_t t1 = A >> 2;        // >>2 block
        uint32_t t2 = B >> 1;        // >>1 block
        uint32_t t3 = t1 & t2;       // & block
        uint32_t t4 = C ^ D;         // ^ block
        uint32_t t5 = t3 | t4;       // | block
        uint32_t t6 = t5 + msg[i];   // + block with msg[i]

        // Rotate the registers A–E as in the diagram
        uint32_t newA = t6;
        uint32_t newB = A;
        uint32_t newC = B;
        uint32_t newD = C;
        uint32_t newE = D;

        A = newA;
        B = newB;
        C = newC;
        D = newD;
        E = newE;
    }

    Digest digest;

    // Pack A, B, C, D, E into 20-byte digest (big-endian)
    digest.bytes[0] = (unsigned char)((A >> 24) & 0xFF);
    digest.bytes[1] = (unsigned char)((A >> 16) & 0xFF);
    digest.bytes[2] = (unsigned char)((A >> 8) & 0xFF);
    digest.bytes[3] = (unsigned char)(A & 0xFF);

    digest.bytes[4] = (unsigned char)((B >> 24) & 0xFF);
    digest.bytes[5] = (unsigned char)((B >> 16) & 0xFF);
    digest.bytes[6] = (unsigned char)((B >> 8) & 0xFF);
    digest.bytes[7] = (unsigned char)(B & 0xFF);

    digest.bytes[8] = (unsigned char)((C >> 24) & 0xFF);
    digest.bytes[9] = (unsigned char)((C >> 16) & 0xFF);
    digest.bytes[10] = (unsigned char)((C >> 8) & 0xFF);
    digest.bytes[11] = (unsigned char)(C & 0xFF);

    digest.bytes[12] = (unsigned char)((D >> 24) & 0xFF);
    digest.bytes[13] = (unsigned char)((D >> 16) & 0xFF);
    digest.bytes[14] = (unsigned char)((D >> 8) & 0xFF);
    digest.bytes[15] = (unsigned char)(D & 0xFF);

    digest.bytes[16] = (unsigned char)((E >> 24) & 0xFF);
    digest.bytes[17] = (unsigned char)((E >> 16) & 0xFF);
    digest.bytes[18] = (unsigned char)((E >> 8) & 0xFF);
    digest.bytes[19] = (unsigned char)(E & 0xFF);

    return digest;
}






int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}