#include <stdio.h>
#include <inttypes.h>
#include <scrypt-kdf.h>
#include <assert.h>
#include "createkeys.h"

/* scrypt_kdf(passwd, passwdlen, salt, saltlen, N, r, p, buf, buflen):
 * Compute scrypt(passwd[0 .. passwdlen - 1], salt[0 .. saltlen - 1], N, r,
 * p, buflen) and write the result into buf.  The parameters r, p, and buflen
 * must satisfy r * p < 2^30 and buflen <= (2^32 - 1) * 32.  The parameter N
 * must be a power of 2 greater than 1.
 *
 * Return 0 on success; or -1 on error.
 */
/*int crypto_scrypt(const uint8_t *, size_t, const uint8_t *, size_t, uint64_t,
    uint32_t, uint32_t, uint8_t *, size_t);*/

int createAesKey   (uint8_t * buf32,
                    int buflen,
                    const uint8_t * originalKi1,
                    int originalKi1Len,
                    const uint8_t * originalKi2,
                    int originalKi2Len,
                    int parallelism)
{
    int rs;
    if (buf32
        && buflen == KEY_LENGTH
        && originalKi1
        && originalKi2
        && originalKi1Len >= MIN_ORIGKI_LENGTH
        && originalKi2Len >= MIN_ORIGKI_LENGTH
        && parallelism > 0) {


          rs = crypto_scrypt(originalKi1,
                             originalKi1Len,
                             originalKi2,
                             originalKi2Len,
                             NUMBER_OF_ITERATIONS_AES,
                             SCRYPT_BLOCK_SIZE,
                             parallelism,
                             buf32,
                             buflen);
        return rs;

    } else {
        return -1;
    }



}

/*FIX IT: SWAP args! */
int createIV (uint8_t * buf16,
                    int buflen,
                    const uint8_t * key,
                    int keyLen,
                    int parallelism)
{
    int rs = -1;
    const uint8_t * halfKeyPtr;
    if (buf16
        && buflen == IV_LENGTH
        && key
        && keyLen == KEY_LENGTH
        && parallelism > 0){
        halfKeyPtr = key + IV_LENGTH;
        rs = crypto_scrypt(  key,
                            KEY_LENGTH / 2,
                            halfKeyPtr,
                            KEY_LENGTH / 2,
                            NUMBER_OF_ITERATIONS_IV,
                            SCRYPT_BLOCK_SIZE, 
                            parallelism,
                            buf16,buflen);}
    return rs;
}
