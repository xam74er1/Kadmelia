//
// Created by root on 5/20/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"
#include <inttypes.h>


int callback(void *, int, char **, char **);
int createDatabase();
int setNode(uint32_t, long, int);

int main(int argc, char* argv[]){


    createDatabase();



    uint32_t id= 32;
    long ip = 454545;
    int port = 8000;

    setNode(id,ip,port);


    //getNode(id);


    return 0;
}


//affichage de toutes les lignes des queries
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

int createDatabase () {

    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test2.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    //creation table
    char *sql = "CREATE TABLE IF NOT EXISTS users(id BLOB,ip INT, port INT);"
                "CREATE TABLE IF NOT EXISTS titre(hash TEXT,string TEXT);"
                "CREATE TABLE IF NOT EXISTS fichier(hash TEXT, chemin_fichier TEXT);";


    sqlite3_exec(db, sql, 0,0 ,&err_msg);

    printf("%s \n",err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    } else {

        fprintf(stdout, "Tables created successfully\n");
    }

    sqlite3_close(db);

    return 0;
}


int setNode(uint32_t id, long ip, int port ) {

    fprintf(stderr, "fonction setNode\n");


    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test2.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "INSERT INTO users(id,ip,port) VALUES (?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement\n");
       // sqlite3_close(db);
        // return 1;
    }
    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,id);
    sqlite3_bind_int(stmt,2,ip);
    sqlite3_bind_int(stmt,3,port);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;

}

