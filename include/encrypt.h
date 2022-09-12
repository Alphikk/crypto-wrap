#ifndef ENCRYPT_H
#define ENCRYPT_H



#ifdef __cplusplus

extern "C" {

#endif


#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>

#include "general.h"

#define OPENSSL_SUCCESS_ 1

int
encrypt_aes_(EVP_CIPHER_CTX *ctx,
             const    uint8_t * plaintext,
             const    uint64_t plaintext_len,
             const    uint8_t  * key,
             const    uint8_t  * iv,
             uint8_t  * ciphertext,
             uint64_t * ciphertext_len);


#ifdef __cplusplus
}

#endif


#endif