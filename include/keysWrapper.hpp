#include "createkeys.h"
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
namespace keywrapper
{

enum IvMode
{
    Urandom,
    UrandomWithScrypt
};

struct KeyResult
{
    KeyResult(const std::vector<uint8_t> & result_, bool keyGenerated_)
    : result(result_), keyGenerated(keyGenerated_) {}
    const std::vector<uint8_t> & result;
    bool keyGenerated;
};

struct IvResult
{
    std::vector<uint8_t> iv;
    bool ready;

    IvResult(IvResult && old);
    IvResult(std::vector<uint8_t> && iv_, bool && ready_ )
    {
        iv = iv_;
        ready = ready_;

        iv_.clear();
        ready_ = false;
    }
};


class Key
{


private:


const size_t minimumPasswordLen = SCRYPT_MIN_SOURCE_LENGTH;
const size_t keySize = KEY_LENGTH;
const size_t ivLen = IV_LENGTH;


/* SCRYPT INTERNAL PARAMS */
const uint64_t scrypt_NumberOfIterations;
const uint32_t scrypt_BlockSize;
const uint32_t scrypt_DegreeOfParallelism;

/* BUFFERS */
std::vector<uint8_t> keyBuf;
std::vector<uint8_t> ivBuf;

bool keyGenerated = false;
bool ready = false;

int
generateKey( const std::string & password, 
             const std::string & salt );


int
generateIv();

public:

Key(const size_t bufSize,
    const uint64_t scrypt_NumberOfIterations,
    const uint32_t scrypt_BlockSize,
    const uint32_t scrypt_DegreeOfParallelism);

int
create( const std::string & password, 
        const std::string & salt );

int
createIv();

/* getters  */

KeyResult
getKey();

keywrapper::IvResult
getAndClearIv();


};

}