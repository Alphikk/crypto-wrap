#include <stdio.h>
#include <string.h>
#include "encrypt.h"


#ifdef __cplusplus

extern "C" {

#endif



int
encrypt_aes_(EVP_CIPHER_CTX *ctx,
             const    uint8_t * plaintext,
             const    uint64_t plaintext_len,
             const    uint8_t  * key,
             const    uint8_t  * iv,
             uint8_t  * ciphertext,
             uint64_t * ciphertext_len)
{
    int len = 0;
    
    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    int rs = -1;
    rs = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    if( rs != OPENSSL_SUCCESS_) {

        ERR_print_errors_fp(stderr);
        return -1;
    }
    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    rs = EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    if( rs != OPENSSL_SUCCESS_) {

        ERR_print_errors_fp(stderr);
        return -1;
    }
        
    *ciphertext_len = len;
    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    rs = EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    if( rs != OPENSSL_SUCCESS_ ) {
        
        ERR_print_errors_fp(stderr);
        return -1;
    }
    *ciphertext_len += len;

    return 0;
}


#ifdef __cplusplus
}

#endif