#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>


void handleErrors(void);

int encryptAes( unsigned char *plaintext,
                int plaintext_len, unsigned char *key,
                unsigned char *iv,
                unsigned char *ciphertext);

int encryptCamellia(unsigned char *plaintext,
                    int plaintext_len,
                    unsigned char * key,
                    unsigned char * iv,
                    unsigned char * ciphertext);