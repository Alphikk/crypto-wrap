#ifndef CREATE_KEYS_H
#define CREATE_KEYS_H

#ifdef __cplusplus

extern "C" {

#endif

#include <inttypes.h>
#include "general.h"

#define SCRYPT_MIN_SOURCE_LENGTH 32 // Минимальная длина строки для пароля и соли
#define IV_LENGTH 16 // Размер Вектора Инициализации (Подходит для обоих алгоритмов, равен размеру блока)
#define KEY_LENGTH 32 // Размер ключа для обоих алгоритмов 256 бит
// #define SCRYPT_NUMBER_OF_ITERATIONS 524288 // Количество проходов scrypt для AES - влияет на размер оперативной памяти
// #define SCRYPT_IV_NUMBER_OF_ITERATIONS 131072 // Количество проходов scrypt для Вектора инициализации
// #define SCRYPT_BLOCK_SIZE 8 // Размер блока для scrypt
// #define SCRYPT_DEGREE_OF_PARALLELISM 1 // Степень параллельности scrypt - влияет на время выполнения

int
createKey_  (uint8_t *          buf,
             int                buflen,
             const uint8_t *    password,
             size_t             passwordLen,
             const uint8_t *    salt,
             size_t             saltLen,
             uint64_t           numberOfIterations,
             uint32_t           blockSize,
             uint32_t           parallelizm);

// int createIV_ ( uint8_t * buf16,
//                 int buflen,
//                 const uint8_t * key,
//                 int keyLen );

/* ZMQ */
//void createkeys_init(void);
/*
enum createkeys_func {
    CREATE_AES_KEY,
    CREATE_CAMELLIA_KEY,
    CREATE_IV
}; */

#ifdef __cplusplus
}

#endif

#endif