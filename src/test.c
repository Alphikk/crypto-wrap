#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <scrypt-kdf.h>
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include "createkeys.h"

/* тестовый стенд */
uint8_t * ki1 = "01234567890123456789012345678912"; // 32 +1 
uint8_t * ki2 = "98765432109876543210987654321098"; // 32 +1
typedef struct st_test {
    int name;
    char cchhaarr;
} sttest;

int main (void)
{
    EVP_CIPHER_CTX ctx;
    sttest vasya;
    return 0;
}


int testCreateKeys (void)
{
    uint8_t aesKeyBuf[KEY_LENGTH] = {0};
    uint8_t camelliaKeyBuf[KEY_LENGTH] = {0};
    uint8_t aesIVBuf[IV_LENGTH] = {0};
    uint8_t camelliaIVBuf[IV_LENGTH] = {0};
    int aesKeyStatus = createAesKey (aesKeyBuf,
                                        KEY_LENGTH,
                                        ki1,
                                        KEY_LENGTH,
                                        ki2,
                                        KEY_LENGTH,
                                        1);

    printf("aesKeyStatus = %d, ",aesKeyStatus);
    for (int i = 0;i < KEY_LENGTH;i++)
    {
        printf("%02x", aesKeyBuf[i] & 0xff);
    }
    printf("\n");
    int camelliaKeyStatus = createCamelliaKey ( camelliaKeyBuf,
                                                KEY_LENGTH,
                                                ki1,
                                                KEY_LENGTH,
                                                ki2,
                                                KEY_LENGTH,
                                                1);
    printf("camelliaKeyStatus = %d, ",camelliaKeyStatus);
    for (int i = 0;i < KEY_LENGTH;i++)
    {
        printf("%02x", camelliaKeyBuf[i] & 0xff);
    }
    printf("\n");
    if (0 == aesKeyStatus)
        { int aesIVStatus = createIV (  aesIVBuf,
                                        IV_LENGTH,
                                        aesKeyBuf,
                                        KEY_LENGTH,
                                        1);
        printf("aesIVStatus = %d, ",camelliaKeyStatus);
        for (int i = 0;i < IV_LENGTH;i++)
            {
            printf("%02x", aesIVBuf[i] & 0xff);
            }
        }
    printf("\n");
    if ( 0 == camelliaKeyStatus )
        { int camelliaIVStatus = createIV ( camelliaIVBuf,
                                            IV_LENGTH,
                                            camelliaKeyBuf,
                                            KEY_LENGTH,
                                        1);
        printf("camelliaIVStatus = %d, ",camelliaIVStatus);
        for (int i = 0;i < IV_LENGTH;i++)
            {
            printf("%02x", camelliaIVBuf[i] & 0xff);
            }
        }
    printf("\n");
    return 0; // не отражает правильности выполнения


}