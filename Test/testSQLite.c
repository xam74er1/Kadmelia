//
// Created by root on 5/20/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"

int callback(void *, int, char **, char **);

int main(int argc, char* argv[]){
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
    char *sql = "DROP TABLE IF EXISTS users;"
                "DROP TABLE IF EXISTS titre;"
                "DROP TABLE IF EXISTS fichier;"
                "CREATE TABLE users(id INT,ip TEXT, port INT);"
                "CREATE TABLE titre(hash TEXT,string TEXT);"
                "CREATE TABLE fichier(hash TEXT, chemin_fichier TEXT);";


    sqlite3_exec(db, sql, 0,0 ,&err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    } else {

        fprintf(stdout, "Tables created successfully\n");
    }

    //insertion dans table
    sql = "INSERT INTO users(id,ip,port) VALUES (1,'122.252.185.91',8000);";

    sqlite3_exec(db, sql, 0,0 ,&err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to insert in user table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    } else {

        fprintf(stdout, "Table user populated succefuly\n");
    }

    //Recuperation données
    sql = "SELECT * FROM users";

    sqlite3_exec(db, sql, callback, 0,&err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to iget user data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }


    sqlite3_close(db);

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

