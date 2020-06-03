cmake_minimum_required(VERSION 3.15)
project(groupe7)

set(CMAKE_C_STANDARD 11 )


#add_executable(test Test/testSQLite.c lib/sqlite3.c lib/sqlite3.h)
#add_executable(test Test/testSSL.c lib/openssl/sha.h)
#target_link_libraries(test PUBLIC crypto)
#Pour installez oppen ssl :
# 1- telecharge open ssl (vertion 1.1.1)
# 2- copie le dans le dossier lib
# 3- faite ./config
# 4- make
#set(OPENSSL_ROOT_DIR "lib/openssl")
#find_package(OpenSSL)
#set(OPENSSL_INCLUDE_DIR,"lib/openssl-1.1.1g/include")
#include_directories(${OPENSSL_INCLUDE_DIR})


FILE(GLOB UtilitaireC utilitaires/*.c)
FILE(GLOB UtilitaireH utilitaires/*.h)

FILE(GLOB PackageC package/*.c)
FILE(GLOB PackageH package/*.h)

#add_executable(test Test/testUdp.c package/node.c package/node.h utilitaires/utilitaire.c utilitaires/utilitaire.h package/send_udp.c package/send_udp.h)
#add_executable(test Test/testUdp.c ${PackageC} ${UtilitaireC} ${PackageH} ${UtilitaireH})

add_executable(test Test/testCreationArbre.c ${PackageC} ${UtilitaireC} ${PackageH} ${UtilitaireH} )
#add_executable(test Test/testSSL.c lib/openssl/sha.h)


find_package(Threads REQUIRED)
target_link_libraries(test pthread Threads::Threads dl)
target_link_libraries(test crypto)

#target_link_directories(test PRIVATE "lib/openssl")
#target_link_libraries(test crypto ssl)

#target_link_libraries(test pthread )