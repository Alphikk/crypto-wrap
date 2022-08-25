#ifndef ENCRYPT_H
#define ENCRYPT_H



#ifdef __cplusplus

extern "C" {

#endif


#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>

#include "general.h"


int encrypt_aes_(const uint8_t *plaintext,
                 uint64_t plaintext_len,
                 const uint8_t *key,
                 const uint8_t *iv,
                 uint8_t *ciphertext,
                 uint64_t * ciphertext_len);


#ifdef __cplusplus
}

#endif


#endif