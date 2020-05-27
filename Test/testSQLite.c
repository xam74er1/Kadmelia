//
// Created by root on 5/20/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"

int main(int argc, char* argv[]){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test2.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);
}