//
// Created by root on 5/20/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"
#include <inttypes.h>
#include "../package/node.h"


int callback(void *, int, char **, char **);
int createDatabase();
int getNode(uint32_t,Node *);
int setNode(Node);
int main(int argc, char* argv[]){


    createDatabase();

    uint32_t id[5] = { 19, 10 ,8 ,23, 56 };
    long ip = 454545;
    int port = 8000;
    int bucket_id = 1 ;

    Node node1;

    ini(&node1);
    setNodeIdSimple(&node1,4);

    node1.id[0] = id[3];

    setNode(node1);



    getNode(19, &node1);

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
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    //creation table
    char *sql = "CREATE TABLE IF NOT EXISTS node(id1 BLOB, id2 BLOB, id3 BLOB, id4 BLOB, id5 BLOB,ip INT, port INT, bucket_id INT);"
                "CREATE TABLE IF NOT EXISTS bucket(id BLOB, nb_voisin INT);"
                "CREATE TABLE IF NOT EXISTS titre(hash TEXT,string TEXT);"
                "CREATE TABLE IF NOT EXISTS fichier(hash TEXT, chemin_fichier TEXT);";


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

    sqlite3_close(db);

    return 0;
}

int getNode(uint32_t id, Node *node) {

    fprintf(stderr, "fonction getNode\n");


    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "SELECT id1, id2, id3, id4, id5, ip, port FROM node WHERE id1 = ?",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,id);

    sqlite3_step(stmt);

    fprintf(stdout,"%d\n", sqlite3_column_blob(stmt, 0));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 1));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 2));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 3));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 4));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 5));
    fprintf(stdout,"%d\n", sqlite3_column_int(stmt, 6));

    uint32_t idarray[5];

    idarray[0] = sqlite3_column_blob(stmt, 0);
    idarray[1] = sqlite3_column_blob(stmt, 1);
    idarray[2] = sqlite3_column_blob(stmt, 2);
    idarray[3] = sqlite3_column_blob(stmt, 3);
    idarray[4] = sqlite3_column_blob(stmt, 4);


    *node->id = idarray;



    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;

}


int setNode( Node node ) {

    fprintf(stderr, "fonction setNode\n");

    uint32_t id[5];

    id[0] = node.id[0];
    id[1] = node.id[1];
    id[2] = node.id[2];
    id[3] = node.id[3];
    id[4] = node.id[4];

    int ip = node.addr_ip.sin_addr.s_addr;
    int port = node.addr_ip.sin_port;



    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "INSERT INTO node (id1,id2,id3,id4,id5,ip,port) VALUES (?,?,?,?,?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,id[0]);
    sqlite3_bind_int(stmt,2,id[1]);
    sqlite3_bind_int(stmt,3,id[2]);
    sqlite3_bind_int(stmt,4,id[3]);
    sqlite3_bind_int(stmt,5,id[4]);
    sqlite3_bind_int(stmt,6,ip);
    sqlite3_bind_int(stmt,7,port);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;

}

