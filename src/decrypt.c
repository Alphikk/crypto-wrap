#include <stdio.h>
#include <string.h>
#include "decrypt.h"

int decrypt_aes_( EVP_CIPHER_CTX * ctx,
                  const uint8_t * ciphertext,
                  uint64_t ciphertext_len,
                  const uint8_t * key,
                  const uint8_t * iv,
                  uint8_t * plaintext,
                  uint64_t * plaintext_len )
{

    int len = 0;
    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    int rs = 0;
    rs = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    if( rs != OPENSSL_SUCCESS_ ) {

        ERR_print_errors_fp(stderr);
        return -1;
    } 

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    rs = EVP_DecryptUpdate(ctx, 
                           plaintext,
                           &len,
                           ciphertext,
                           ciphertext_len);
    if ( rs != OPENSSL_SUCCESS_ ) {

        ERR_print_errors_fp(stderr);
        return -1;

    }
    *plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    rs = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    if( rs != OPENSSL_SUCCESS_ ) {

        ERR_print_errors_fp(stderr);
        return -1;
    }

    *plaintext_len += len;

    return 0;
}