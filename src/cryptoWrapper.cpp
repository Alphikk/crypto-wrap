#include "cryptoWrapper.hpp"


/// @brief  Encrypt
cryptowrapper::Encrypt::Encrypt()
{
    

}


cryptowrapper::Encrypt::~Encrypt()
{
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }


}


int
cryptowrapper::Encrypt::init()
{
    /* Create and initialise the context */
    this->ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {

        return -1;
    }
    return 0;
}

int
cryptowrapper::Encrypt::run(const std::vector<uint8_t> & plainText,
                            keywrapper::KeyResult key,
                            std::vector<uint8_t> iv,
                            CryptoBuf & cipherText)
{
    int rs = 0;
    if (!this->ctx) {
        return -1;
    }

    if ( !key.keyGenerated ) {

        return -1;
    } 
    uint64_t cipherTextSize = 0;
    rs = encrypt_aes_(this->ctx,
                 plainText.data(),
                 plainText.size(),
                 key.result.data(),
                 iv.data(),
                 cipherText.buf.data(),
                 &cipherText.cryptoSize);
    return rs;

}


int
cryptowrapper::Encrypt::run(const std::string & plainText,
                            keywrapper::KeyResult key,
                            std::vector<uint8_t> iv,
                            CryptoBuf & cipherText)
{
    int rs = 0;
    if (!this->ctx) {
        return -1;
    }

    if ( !key.keyGenerated ) {

        return -1;
    } 
    uint64_t cipherTextSize = 0;
    rs = encrypt_aes_(this->ctx,
                      reinterpret_cast<const uint8_t* >(plainText.data()),
                      plainText.size(),
                      key.result.data(),
                      iv.data(),
                      cipherText.buf.data(),
                      &cipherText.cryptoSize);
    return rs;

}


/// @brief  Decrypt
cryptowrapper::Decrypt::Decrypt()
{
    

}


cryptowrapper::Decrypt::~Decrypt()
{
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }


}


int
cryptowrapper::Decrypt::init()
{
    /* Create and initialise the context */
    this->ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {

        return -1;
    }
    return 0;
}

int
cryptowrapper::Decrypt::run(const CryptoBuf & cipherText,
                            keywrapper::KeyResult key,
                            std::vector<uint8_t> iv,
                            CryptoBuf & plainData)
{
    int rs = 0;
    if (!this->ctx) {
        std::cout << "here 1 "  << std::endl;
        return -1;
    }

    if ( !key.keyGenerated ) {
        std::cout << "here 2 "  << std::endl;
        return -1;
    }

    // if ( plainData.size() < cipherData.size() ) {

    //     return -1;
    // }

    rs = decrypt_aes_(this->ctx,
                      cipherText.buf.data(),
                      cipherText.cryptoSize,
                      key.result.data(),
                      iv.data(),
                      plainData.buf.data(),
                      &plainData.cryptoSize);
    
    return rs;

}