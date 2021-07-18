#include <inttypes.h>
#define MIN_ORIGKI_LENGTH 32 // Минимальная длина строки для пароля и соли
#define IV_LENGTH 16 // Размер Вектора Инициализации (Подходит для обоих алгоритмов, равен размеру блока)
#define KEY_LENGTH 32 // Размер ключа для обоих алгоритмов 256 бит
#define NUMBER_OF_ITERATIONS_AES 524288 // Количество проходов scrypt для AES - влияет на размер оперативной памяти
#define NUMBER_OF_ITERATIONS_CAMELLIA 524288 // Количество проходов scrypt для camellia
#define NUMBER_OF_ITERATIONS_IV 131072 // Количество проходов scrypt для Вектора инициализации
#define SCRYPT_BLOCK_SIZE 8 // Размер блока для scrypt
#define DEGREE_OF_PARALLELISM 1 // Степень параллельности scrypt - влияет на время выполнения

int createAesKey (uint8_t * buf32,
                    int buflen,
                    const uint8_t * originalKi1,
                    int originalKi1Len,
                    const uint8_t * originalKi2,
                    int originalKi2Len,
                    int parallelism);

int createCamelliaKey (uint8_t * buf32,
                    int buflen,
                    const uint8_t * originalKi1,
                    int originalKi1Len,
                    const uint8_t * originalKi2,
                    int originalKi2Len,
                    int parallelism);

int createIV (uint8_t * buf16,
                    int buflen,
                    const uint8_t * key,
                    int keyLen,
                    int parallelism);