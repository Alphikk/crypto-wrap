#include <stdlib.h>
#include "createkeys.h"
#include "encrypt.h"
#include "decrypt.h"


uint8_t * teststring = "Задача организации, в особенности же курс на социально-ориентированный национальный проект"
 "способствует подготовке и реализации форм воздействия? Соображения высшего порядка, а также социально-экономическое развитие"
  "требует от нас системного анализа системы масштабного изменения ряда параметров? Разнообразный и богатый опыт начало"
   "повседневной работы по формированию позиции требует от нас системного анализа дальнейших направлений развития проекта.";


int main( int argc, char *argv[])
{
    uint64_t pt_len = strlen(teststring)+1;
    uint8_t * ciphertext_ptr = malloc(pt_len + 16);
    uint8_t * decrypt_plain_text_ptr = malloc(pt_len+16);
    uint64_t ciphertext_len = 0;
    int rs;
    rs = __encrypt_aes(  teststring,
                        pt_len,
                        "11111111111111111111111111111111",
                        "1111111111111111",
                        ciphertext_ptr,
                        &ciphertext_len);
    if (!rs) {
        rs = __decrypt_aes (   ciphertext_ptr,
                                ciphertext_len,
                                "11111111111111111111111111111111",
                                "1111111111111111",
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
        printf("\n%d\n",*decrypt_plain_text_ptr);
    }

    return 0;
}