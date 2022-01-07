#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>

#include "general.h"

void handleErrors(void);

int __encrypt_aes( uint8_t *plaintext,
                uint64_t plaintext_len,
                uint8_t *key,
                uint8_t *iv,
                uint8_t *ciphertext,
                uint64_t * ciphertext_len);
#endif