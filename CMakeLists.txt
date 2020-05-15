cmake_minimum_required(VERSION 3.15)
project(groupe7)

set(CMAKE_C_STANDARD 11 )

add_executable(test Main.c kademiliaTest.c kademiliaTest.h utilitaire.c utilitaire.h )
#add_executable(test Test/testSSL.c)
#include_directories(openssl/include/openssl/)
#link_libraries(openssl)
#link_libraries(crypto)

target_link_libraries(test pthread)