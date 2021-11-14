#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>


int __decrypt_aes( uint8_t *ciphertext,
                uint64_t ciphertext_len,
                uint8_t *key,
                uint8_t *iv,
                uint8_t *plaintext,
                uint64_t * plaintext_len);
