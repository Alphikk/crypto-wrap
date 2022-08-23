#include "createkeys.h"
#include <memory>
#include <vector>
#include <iostream>
namespace keywrapper
{



struct KeyResult
{
    KeyResult(const std::vector<uint8_t> & result_, bool keyGenerated_)
    : result(result_), keyGenerated(keyGenerated_) {}
    const std::vector<uint8_t> & result;
    bool keyGenerated;
};



enum Mode
{
    KeyMode,
    IvMode
};


class Key
{


private:

const size_t minimumPasswordLen = MIN_ORIGKI_LENGTH;
const size_t keySize = KEY_LENGTH;

std::vector<uint8_t> keyBuf;

bool keyGenerated = false;

public:

explicit
Key(size_t bufSize);

int
createKey(  keywrapper::Mode mode,
            const std::string & password, 
            const std::string & salt );

KeyResult
getKey();



};

}