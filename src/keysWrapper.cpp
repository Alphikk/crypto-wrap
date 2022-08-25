#include "keysWrapper.hpp"




// keywrapper::IvResult::IvResult(IvResult && old)
// {
//     ;
// }


keywrapper::Key::Key(const size_t keySize_,
                     const uint64_t n_,
                     const uint32_t b_,
                     const uint32_t p_)

: keySize                   (keySize_),
  scrypt_NumberOfIterations (n_),
  scrypt_BlockSize          (b_),
  scrypt_DegreeOfParallelism(p_)
{
    keyBuf.resize(keySize);
    ivBuf.resize(ivLen);
}

int
keywrapper::Key::generateKey(const std::string & password,
                             const std::string & salt )
{

    if (password.empty()) {
        
        std::cerr << "password is empty\n" << std::endl;
        return -1;
    }

    if (password.length() < this->minimumPasswordLen) {

        std::cerr << "password.length() < min length\n" << std::endl;
        return -1;

    }
    if (salt.empty()) {
        
        std::cerr << "salt is empty\n" << std::endl;
        return -1;
    }
    if (salt.length() < this->minimumPasswordLen) {

        std::cerr << "salt.length() < min length\n" << std::endl;
        return -1;

    }


    int rs = -1;
    rs =  createKey_( this->keyBuf.data(),
                      keySize,
                      reinterpret_cast<const uint8_t *>(password.c_str()),
                      password.length(),
                      reinterpret_cast<const uint8_t *>(salt.c_str()),
                      salt.length(),
                      scrypt_NumberOfIterations,
                      scrypt_BlockSize,
                      scrypt_DegreeOfParallelism);
        
    if (rs == 0) {

        this->keyGenerated = true;
    }
    return rs;

}


int
keywrapper::Key::generateIv()
{

    uint8_t randomValue = 0;
    size_t size = sizeof(randomValue);
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);

    if (urandom) {

        for (size_t i = 0; i < this->ivLen; ++i) {

            urandom.read(reinterpret_cast<char*>(&randomValue), size);
            if(urandom) {

                this->ivBuf.emplace_back(randomValue);

            } else {

                std::cerr << "failed to read part iv from /dev/urandom" << std::endl;
                this->ivBuf.clear();
                urandom.close();
                return -1;
            }
        }
        urandom.close(); //close stream
        return 0;
    } else {
        std::cerr << "failed to read from /dev/urandom" << std::endl;
        return -1;
    }

}




int
keywrapper::Key::create(const std::string & password, 
                        const std::string & salt )
{
    /// \todo: make as async method

    /// \todo make return as exception (for pybind example)
    int rs = -1;
    rs = this->generateKey(password, salt);
    return rs;
}

int
keywrapper::Key::createIv()
{
    int rs = 0;
    if (!ready) {

        ivBuf.resize(ivLen);
        rs = this->generateIv();

        if (!rs) {

            ready = true;
            return rs;
        }
    }
    return rs;
}

keywrapper::IvResult
keywrapper::Key::getAndClearIv()
{
    return IvResult{std::move(this->ivBuf), std::move(this->ready)};
}


keywrapper::KeyResult
keywrapper::Key::getKey()
{
    const std::vector<uint8_t> & temp = keyBuf;
    keywrapper::KeyResult result(temp, this->keyGenerated);

    return result;
}