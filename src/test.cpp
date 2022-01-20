#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

#include "createkeys.h"
#include "encrypt.h"
#include "decrypt.h"


int main( int argc, char *argv[])
{
    
    QRinput * qrInput = QRinput_new(); // need call QRinput_free(qrInput);


    /* create keys */
    uint8_t key_buf[32];
    uint8_t IV_buf[16];
    char * source_text1 = "12345678901234567890123456789012";
    char * source_text2 = "98765432109876543210987654321098";

    char teststring[] = "ВасяВасяВасяВася";

    createAesKey(key_buf,
                 32,
                 (const uint8_t *) source_text1,
                 strlen(source_text1),
                 (const uint8_t *) source_text2,
                 strlen(source_text2),
                 2);

    createIV(IV_buf,16,key_buf,32,2); // TODO: pull from /dev/null
    /* end create keys */

    /* make QR code */
    QRinput_append(qrInput,
                   QR_MODE_STRUCTURE,
                   16,
                   IV_buf); // add data to QR code;

    uint64_t textLen = strlen(teststring)+1;
    QRinput_append(qrInput,
                   QR_MODE_STRUCTURE,
                   textLen,
                   (const unsigned char *)teststring);

    QRcode* qrCode =  QRcode_encodeInput(qrInput);
    /* end make QR code */

    /* crypt and decrypt */
    uint64_t pt_len = strlen(teststring)+1;
    uint8_t * ciphertext_ptr = (uint8_t *) malloc(pt_len + 16);
    uint8_t * decrypt_plain_text_ptr = (uint8_t *) malloc(pt_len+16);
    uint64_t ciphertext_len = 0;
    /*end crypt and decrypt */

    int rs;
    rs = __encrypt_aes((uint8_t *)teststring,
                        pt_len,
                        key_buf,
                        IV_buf,
                        ciphertext_ptr,
                        &ciphertext_len);
    
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

    free(ciphertext_ptr);
    free(decrypt_plain_text_ptr);

    return 0;
}