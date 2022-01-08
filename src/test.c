#include <stdlib.h>
#include <string.h>

#include "createkeys.h"
#include "encrypt.h"
#include "decrypt.h"


uint8_t * teststring = "ВасяВасяВасяВасяВасяВасяВасяВасяВасяВася";


int main( int argc, char *argv[])
{


    /* create keys */
    uint8_t key_buf[32];
    uint8_t IV_buf[16];
    char * source_text1 = "12345678901234567890123456789012";
    char * source_text2 = "98765432109876543210987654321098";

    createAesKey(key_buf,
                 32,
                 source_text1,
                 strlen(source_text1),
                 source_text2,
                 strlen(source_text2),
                 2);

    createIV(IV_buf,16,key_buf,32,2);

    /* end create keys */

    /* crypt and decrypt */
    uint64_t pt_len = strlen(teststring)+1;
    uint8_t * ciphertext_ptr = malloc(pt_len + 16);
    uint8_t * decrypt_plain_text_ptr = malloc(pt_len+16);
    uint64_t ciphertext_len = 0;
    /*end crypt and decrypt */

    int rs;
    rs = __encrypt_aes(  teststring,
                        pt_len,
                        key_buf,
                        IV_buf,
                        ciphertext_ptr,
                        &ciphertext_len);
                        
    for (int i = 0; i < ciphertext_len; i++) {

        printf("%c",ciphertext_ptr[i]);

    }
    printf("\n");
    
    if (!rs) {
        rs = __decrypt_aes (   ciphertext_ptr,
                                ciphertext_len,
                                key_buf,
                                IV_buf,
                                decrypt_plain_text_ptr,
                                &pt_len);
    }

/*
int __decrypt_aes( uint8_t *ciphertext,
                uint64_t ciphertext_len,
                uint8_t *key,
                uint8_t *iv,
                uint8_t *plaintext,
                uint64_t * plaintext_len)
 */
    if (!rs) {
        printf("%s\n",decrypt_plain_text_ptr);
    }

    return 0;
}