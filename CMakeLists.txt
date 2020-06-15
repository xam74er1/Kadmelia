cmake_minimum_required(VERSION 3.15)
project(groupe7)

set(CMAKE_C_STANDARD 11 )

SET(PROGAMENAME serveur)
SET(SendName send)

FILE(GLOB UtilitaireC utilitaires/*.c)
FILE(GLOB UtilitaireH utilitaires/*.h)

FILE(GLOB PackageC package/*.c)
FILE(GLOB PackageH package/*.h)

add_executable(${PROGAMENAME} Test/testTCPNode.c event/lisent.c event/lisent.h ${PackageC}  ${UtilitaireC} ${PackageH} ${UtilitaireH} package/bdd.c lib/sqlite3.c lib/sqlite3.h)


find_package(Threads REQUIRED)
target_link_libraries(${PROGAMENAME}  pthread Threads::Threads dl)
target_link_libraries(${PROGAMENAME} crypto)


