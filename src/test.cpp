#include <stdlib.h>
#include <string.h>

#include "keysWrapper.hpp"
#include "encrypt.h"
#include "decrypt.h"

#define KEY_SIZE 256
/* Количество проходов scrypt для AES - влияет на размер оперативной памяти*/
#define SCRYPT_NUMBER_OF_ITERATIONS 524288
/* Размер блока для scrypt */
#define SCRYPT_BLOCK_SIZE 8 
/* Степень (математическая?) параллельности scrypt - влияет на время выполнения */
#define SCRYPT_DEGREE_OF_PARALLELISM 1 


int main( int argc, char *argv[])
{
    const size_t kS = KEY_SIZE;
    const uint64_t num = SCRYPT_NUMBER_OF_ITERATIONS;
    const uint32_t b = SCRYPT_BLOCK_SIZE;
    const uint32_t p = SCRYPT_DEGREE_OF_PARALLELISM;

    keywrapper::Key key(kS, num, b, p );
    /* create keys */
    key.create("12345678901234567890123456789013", "98765432109876543210987654321098");
    std::string teststring = "vasyavasyavasya";
    /* end create keys */

    /* crypt and decrypt */

    uint64_t pt_len = teststring.length();
    std::vector<uint8_t> encryptBuf;
    encryptBuf.resize(1000); // 1000 for test
    uint64_t ciphertextLen = 0;

    std::vector<uint8_t> decryptBuf;
    decryptBuf.resize(1000); // 1000 for test
    uint64_t plaintextLen = 0;
    
    int rs;
    key.createIv();
    keywrapper::IvResult iv = key.getAndClearIv();
    if (iv.ready) {
    rs = encrypt_aes_(reinterpret_cast<const uint8_t*>(teststring.data()),
                      teststring.length(),
                      key.getKey().result.data(),
                      iv.iv.data(),
                      encryptBuf.data(),
                      &ciphertextLen);
    }

    if (!rs) {
        rs = decrypt_aes_ (   encryptBuf.data(),
                              ciphertextLen,
                              key.getKey().result.data(),
                              iv.iv.data(),
                              decryptBuf.data(),
                              &plaintextLen );
    }

    if (!rs) {

        for (size_t i = 0; i < plaintextLen; ++i) {

            std::cout << decryptBuf[i];
        }
        std::cout << std::endl;
    }

    return 0;
}