cmake_minimum_required(VERSION 3.16)

#set(${OPENSSL_ROOT_DIR} "/usr/lib/x86_64-linux-gnu/")

#find_package(OpenSSL REQUIRED)

project (cryptoQR)

#find_package(PkgConfig REQUIRED)

set (INCLUDE_DIR "./include")



add_library(createkeys STATIC src/createkeys.c)
target_include_directories(createkeys PUBLIC ${INCLUDE_DIR})
target_link_libraries(createkeys -lscrypt-kdf)


add_library(encrypt STATIC src/encrypt.c)
target_include_directories(encrypt PUBLIC ${INCLUDE_DIR})
target_link_libraries(encrypt -lssl -lcrypto)

add_library(decrypt STATIC src/decrypt.c)
target_include_directories(decrypt PUBLIC ${INCLUDE_DIR})
target_link_libraries(decrypt -lssl -lcrypto)


add_library(key_wrapper SHARED src/keysWrapper.cpp)
target_include_directories(key_wrapper PUBLIC ${INCLUDE_DIR})
target_link_libraries(createkeys)

add_library(crypto_wrapper SHARED src/cryptoWrapper.cpp)
target_include_directories(crypto_wrapper PUBLIC ${INCLUDE_DIR})
target_link_libraries(encrypt decrypt)


add_executable(test src/test.cpp)
target_include_directories(test PUBLIC ${INCLUDE_DIR})
target_link_libraries(test key_wrapper crypto_wrapper createkeys encrypt decrypt)


