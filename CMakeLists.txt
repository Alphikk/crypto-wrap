cmake_minimum_required(VERSION 3.16)

set(${OPENSSL_ROOT_DIR} "/usr/lib/x86_64-linux-gnu/")

#find_package(OpenSSL REQUIRED)

project (cryptoQR)

set (${INCLUDE_DIR} "./include")



add_library(createkeys STATIC src/createkeys.c)
add_library(encrypt STATIC src/encrypt.c)
add_library(decrypt STATIC src/decrypt.c)

add_executable(main src/main.c)


target_link_libraries(createkeys -lscrypt-kdf)
target_link_libraries(encrypt -lssl -lcrypto)
target_link_libraries(decrypt -lssl -lcrypto)


target_include_directories(main PUBLIC ${INCLUDE_DIR})
target_link_libraries(main createkeys encrypt decrypt)

