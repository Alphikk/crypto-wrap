cmake_minimum_required(VERSION 3.16)

#set(${OPENSSL_ROOT_DIR} "/usr/lib/x86_64-linux-gnu/")

#find_package(OpenSSL REQUIRED)

project (cryptoQR)

#find_package(PkgConfig REQUIRED)

find_package(OpenCV REQUIRED)
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

add_executable(test src/test.cpp)
target_include_directories(test PUBLIC ${INCLUDE_DIR})
target_link_libraries(test createkeys encrypt decrypt -lqrencode)

# for camera capture with gstreamer
#pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.8)

add_executable(capture_webcam src/capture_webcam.cpp)
target_include_directories(capture_webcam PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(capture_webcam ${OpenCV_LIBS})


