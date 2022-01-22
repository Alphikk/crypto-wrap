#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

#include <opencv2/opencv.hpp>

#include "createkeys.h"
#include "encrypt.h"
#include "decrypt.h"





cv::Mat drawQRcode (QRcode* code, int imgSize, cv::Scalar fColor)
{
    int sqareSize = imgSize / code->width;
    sqareSize = (sqareSize == 0)  ? 1 : sqareSize;
    // cv::Mat img = cv::Mat::zeros(imgSize,imgSize,CV_8UC3);
    cv::Mat img (imgSize,imgSize,CV_8UC3,fColor);

    u_char *p = code->data;

    int x; 
    int y;
    int posX = 0;
    int posY = 0;

    for (y = 0 ; y < code->width ; y++)
    {
        for (x = 0 ; x < code->width ; x++)
        {
            if (*p & 1)
            {
                posX = x * sqareSize;
                posY = y * sqareSize;

                cv::Rect rect(posX,posY,sqareSize,sqareSize); // x,y,w,h

                cv::rectangle(img, rect, {0,0,0}, -1, 8);

            } else {

            }
            p++;
        }
    }
    return img;
}



int main( int argc, char *argv[])
{
    cv::Mat qrImg;

    /* create keys */
    uint8_t key_buf[32];
    uint8_t IV_buf[16];
    char * source_text1 = "12345678901234567890123456789013";
    char * source_text2 = "98765432109876543210987654321098";

     const char * teststring = "MTExMTExMTExMTExMTExMdCf0YDQuNCy0LXRgiDQutCw0Log0LTQtdC70LA/";

    createAesKey(key_buf,
                 32,
                 (const uint8_t *) source_text1,
                 strlen(source_text1),
                 (const uint8_t *) source_text2,
                 strlen(source_text2),
                 2);

    createIV(IV_buf,16,key_buf,32,2); // TODO: pull from /dev/null
    /* end create keys */

    // QRinput_append(qrInput,
    //                QR_MODE_8, // QR_MODE_8
    //                16,
    //                IV_buf); // add data to QR code;



    /* crypt and decrypt */
    uint64_t pt_len = strlen((const char *)teststring)+1;
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

    // QRinput_append(qrInput,
    //                QR_MODE_8,
    //                ciphertext_len,
    //                ciphertext_ptr);


    QRcode * code = QRcode_encodeString (teststring,0,QR_ECLEVEL_L,QR_MODE_8,1);

    qrImg = drawQRcode(code,400,{255,255,255});
    printf("code width =  %d\n",code->width);
    printf("code version =  %d\n",code->version);
    cv::imshow("image",qrImg);
    cv::waitKey(0);

    
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