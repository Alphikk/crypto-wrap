#include <stdlib.h>
#include <string.h>

#include "keysWrapper.hpp"
#include "cryptoWrapper.hpp"
#include "encrypt.h"
#include "decrypt.h"

#define KEY_SIZE 256
/* Количество проходов scrypt для AES - влияет на размер оперативной памяти*/
#define SCRYPT_NUMBER_OF_ITERATIONS 524288
/* Размер блока для scrypt */
#define SCRYPT_BLOCK_SIZE 8 
/* Степень (математическая?) параллельности scrypt - влияет на время выполнения */
#define SCRYPT_DEGREE_OF_PARALLELISM 1 

#define BLOCK_PADDING (16 - 1)

#define TEST_CRYPTO_BUF_SIZE 1000

int main( int argc, char *argv[])
{
    const size_t kS = KEY_SIZE;
    const uint64_t num = SCRYPT_NUMBER_OF_ITERATIONS;
    const uint32_t b = SCRYPT_BLOCK_SIZE;
    const uint32_t p = SCRYPT_DEGREE_OF_PARALLELISM;

    keywrapper::Key key(kS, num, b, p );
    /* create keys */
    key.create("12345678901234567890123456789013", "98765432109876543210987654321098");
    const std::string teststring = "vasyavasyavasya";
    /* end create keys */

    /* crypt and decrypt */

    cryptowrapper::CryptoBuf encryptBuf;
    // encryptBuf.buf.resize(teststring.length() + BLOCK_PADDING);
    encryptBuf.buf.resize(TEST_CRYPTO_BUF_SIZE);
    encryptBuf.cryptoSize = 0;

    cryptowrapper::CryptoBuf decryptBuf;
    // decryptBuf.buf.resize(teststring.length());
    decryptBuf.buf.resize(TEST_CRYPTO_BUF_SIZE);
    decryptBuf.cryptoSize = 0;

    int rs = key.createIv();
    if (rs) {
        return -1;
    }
    keywrapper::IvResult iv = key.getAndClearIv();

    cryptowrapper::Encrypt encrypt;
    rs = encrypt.init();
    cryptowrapper::Decrypt decrypt;
    decrypt.init();

    std::vector<char> plainData(teststring.begin(), teststring.end());


    if (iv.ready && key.getKey().keyGenerated ) {

        rs = encrypt.run(teststring,
                         key.getKey(),
                         iv.iv,
                         encryptBuf);
        if (rs != 0) {

            std::cout << "not encrypt, error "  << std::endl;
            return -1;
        }
        rs = decrypt.run(encryptBuf,key.getKey(), iv.iv , decryptBuf);

        if (rs != 0) {

            std::cout << "not decrypt, error "  << std::endl;
            return -1;
        }
        for (size_t i = 0; i < decryptBuf.cryptoSize; ++i) {

            std::cout << decryptBuf.buf[i] << std::endl;

        }
    }
    return 0;
}