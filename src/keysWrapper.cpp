#include "keysWrapper.hpp"



keywrapper::Key::Key(size_t bufSize)
: keyBuf(bufSize)
{

}

int
keywrapper::Key::createKey( keywrapper::Mode mode,
                            const std::string & password, 
                            const std::string & salt )
{
    /// \todo: make as async method


    /// \todo make return as exception (for pybind example)
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

    if (!keyBuf.empty() && keyBuf.size() > keySize) {


        int rs = 0;
        rs =  createKey_( this->keyBuf.data(),
                          keySize,
                          reinterpret_cast<const uint8_t *>(password.c_str()),
                          password.length(),
                          reinterpret_cast<const uint8_t *>(salt.c_str()),
                          salt.length() );
        
        if (rs == 0) {
            this->keyGenerated = true;
        }
        return rs;

    }
    return -1;
}

keywrapper::KeyResult
keywrapper::Key::getKey()
{
    const std::vector<uint8_t> & temp = keyBuf;
    keywrapper::KeyResult result(temp, this->keyGenerated);

    return result;
}