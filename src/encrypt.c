#include <stdio.h>
#include <string.h>
#include "encrypt.h"

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int __encrypt_aes(IN   uint8_t *plaintext,
                  IN   uint64_t plaintext_len,
                  IN   uint8_t *key,
                  IN   uint8_t *iv,
                  OUT  uint8_t *ciphertext,
                  OUT  uint64_t * ciphertext_len)
{
    EVP_CIPHER_CTX *ctx;
    int len = 0;
    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();
    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx,
                               EVP_aes_256_cbc(),
                               NULL,
                               key,
                               iv)) {
        handleErrors();
    }
    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx,
                              ciphertext,
                              &len,
                              plaintext,
                              plaintext_len)) {
        handleErrors();
    }
        
    *ciphertext_len = len;
    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        handleErrors();
    }
    *ciphertext_len += len;
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return 0;
}


