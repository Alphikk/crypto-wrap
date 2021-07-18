#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>


int decryptAes( unsigned char *ciphertext,
                int ciphertext_len,
                unsigned char *key,
                unsigned char *iv,
                unsigned char *plaintext);

int decryptCamellia(unsigned char *ciphertext,
                    int ciphertext_len,
                    unsigned char *key,
                    unsigned char *iv,
                    unsigned char *plaintext);