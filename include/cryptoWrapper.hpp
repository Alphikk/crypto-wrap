#pragma once
#ifndef CRYPTO_WRAPPER_HPP
#define CRYPTO_WRAPPER_HPP

#include "decrypt.h"
#include "encrypt.h"
#include "keysWrapper.hpp"
#include <vector>


namespace cryptowrapper
{


struct CryptoBuf
{
    std::vector<uint8_t> buf;
    size_t cryptoSize;
};

class Encrypt
{


public:

Encrypt();
~Encrypt();

/* call init is required! */
int
init();

int
run(const std::vector<uint8_t> & plainData,
    keywrapper::KeyResult key,
    std::vector<uint8_t> iv,
    CryptoBuf & cipherText);

int
run(const std::string & plainText,
    keywrapper::KeyResult key,
    std::vector<uint8_t> iv,
    CryptoBuf & cipherText);

private:

EVP_CIPHER_CTX * ctx {nullptr};



};

class Decrypt
{


public:

Decrypt();
~Decrypt();

/* call init is required! */
int
init();

int
run(const CryptoBuf & cipherText,
    keywrapper::KeyResult key,
    std::vector<uint8_t> iv,
    CryptoBuf & plainData);


private:

EVP_CIPHER_CTX * ctx {nullptr};



};


}

#endif