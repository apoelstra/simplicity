#ifndef SIMPLICITY_TAG_H
#define SIMPLICITY_TAG_H

#include <string.h>
#include "sha256/compression.h"
#include "sha256.h"
#include "ascii.h"

/* Compute the SHA-256 tagged initial value from a string.
 * This tagged initial value is the midstate generated by compression one block consisting of two copies of the SHA-256 hash of
 * 'tagName'.
 * The 'tagName' is not expected to be 'NULL' terminated.
 * This function should only be called through the 'MK_TAG' macro.
 *
 * Precondition: NULL != midstate;
 *               unsigned char tagName[len];
 */
static inline void mkTag(sha256_midstate* midstate, const unsigned char* tagName, const size_t len) {
  uint32_t block[16];
  {
    sha256_context ctx = sha256_init(block);
    sha256_uchars(&ctx, tagName, len);
    sha256_finalize(&ctx);
  }

  memcpy(block + 8, block, 8*sizeof(uint32_t));

  sha256_iv(midstate->s);
  sha256_compression(midstate->s, block);
}

/* The length of a string literal is one less than its sizeof due to the terminating 'NULL' character. */
#define LENGTH_OF(s) (sizeof("" s) - 1)

/* MK_TAG(midstate, s) takes a string literal, 's', and fills in the 'tagName' and 'len' arguments of 'mkTag' appropriately. */
#define MK_TAG(midstate, s) (mkTag((midstate), (unsigned char []){"" s}, LENGTH_OF(s)))

#endif
