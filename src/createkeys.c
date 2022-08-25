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
#ifdef __cplusplus

extern "C" {

#endif
int
createKey_  (uint8_t *          buf,
             int                buflen,
             const uint8_t *    password,
             size_t             passwordLen,
             const uint8_t *    salt,
             size_t             saltLen,
             uint64_t           numberOfIterations,
             uint32_t           blockSize,
             uint32_t           parallelizm)
{
    int rs;
    if (buf && 
        buflen >= KEY_LENGTH &&
        password &&
        salt &&
        passwordLen >= SCRYPT_MIN_SOURCE_LENGTH &&
        saltLen >= SCRYPT_MIN_SOURCE_LENGTH ) {


          rs = crypto_scrypt(password,
                             passwordLen,
                             salt,
                             saltLen,
                             numberOfIterations,
                             blockSize,
                             parallelizm,
                             buf,
                             buflen);
        return rs;

    } else {
        return -1;
    }

}

// /*FIX IT: SWAP args! */
// int createIV (uint8_t * buf16,
//                     int buflen,
//                     const uint8_t * key,
//                     int keyLen)
// {
//     int rs = -1;
//     const uint8_t * halfKeyPtr;

//     if (buf16
//         && buflen == IV_LENGTH
//         && key
//         && keyLen == KEY_LENGTH) {


//         halfKeyPtr = key + IV_LENGTH;
//         rs = crypto_scrypt(  key,
//                             KEY_LENGTH / 2,
//                             halfKeyPtr,
//                             KEY_LENGTH / 2,
//                             SCRYPT_IV_NUMBER_OF_ITERATIONS,
//                             SCRYPT_BLOCK_SIZE, 
//                             SCRYPT_DEGREE_OF_PARALLELISM,
//                             buf16,
//                             buflen);}
//     return rs;
// }
#ifdef __cplusplus
}

#endif