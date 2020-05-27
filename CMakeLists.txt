cmake_minimum_required(VERSION 3.15)
project(groupe7)

set(CMAKE_C_STANDARD 11 )

#add_executable(test Main.c kademiliaTest.c kademiliaTest.h utilitaires/utilitaire.c utilitaires/utilitaire.h)

#add_executable(test Test/testSQLite.c lib/sqlite3.c lib/sqlite3.h Test/testFile.c utilitaires/fileTabChar.h utilitaires/fileTabChar.c)
add_executable(test Test/testFile.c utilitaires/fileTabChar.c)

#add_executable(test Test/testUdp.c package/node.c package/node.h utilitaires/utilitaire.c utilitaires/utilitaire.h package/send_udp.c package/send_udp.h)

find_package(Threads REQUIRED)
target_link_libraries(test pthread Threads::Threads dl)

#target_link_libraries(test pthread )