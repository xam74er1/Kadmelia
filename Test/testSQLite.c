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

void getNode(uint32_t id[5], Node *node);
void setNode(Node *node);

void SetFile(uint32_t idnode[5], uint32_t hashword[5], uint32_t hashfile[5],char nom[], int taille);
void findNode(uint32_t hash[5], Node * node);

int main(int argc, char* argv[]){

    createDatabase();

    uint32_t id[5] = { 4, 8 ,9 ,10, 110 };
    long ip = 454545;
    int port = 8000;
    int bucket_id = 1 ;

    Node node;
    ini(&node);

    node.id[0] = id[0];
    node.id[1] = id[1];
    node.id[2] = id[2];
    node.id[3] = id[3];
    node.id[4] = id[4];


    Node node2;
    ini(&node2);

    setNode(&node);

    fprintf(stdout,"id post set: %d \n", node.id[0]);

    getNode(id,&node2);

    fprintf(stdout,"id 2 post get: %d \n", node2.id[0]);

    Node node3;
    ini(&node3);

    uint32_t fichier[5] = { 1, 2 ,3 ,4, 5 };
    char nom[6] = { 'm', 'a', 't', 'r', 'i', 'x'};
    int taille = 12;

    SetFile(id, fichier, id, nom, taille);

    findNode(fichier, &node3);

    fprintf(stdout,"id 3 post get: %d \n", node3.id[1]);


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
                "CREATE TABLE IF NOT EXISTS fichier_local(nom TEXT, chemin_fichier TEXT);"
                "CREATE TABLE IF NOT EXISTS fichier("
                "idnode1 BLOB, idnode2 BLOB, idnode3 BLOB, idnode4 BLOB, idnode5 BLOB, "
                "hashword1 BLOB, hashword2 BLOB, hashword3 BLOB, hashword4 BLOB, hashword5 BLOB, "
                "hashfile1 BLOB, hashfile2 BLOB, hashfile3 BLOB, hashfile4 BLOB, hashfile5 BLOB, nom TEXT , taille INT);";


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

void getNode(uint32_t id[5], Node *node) {

    fprintf(stderr, "fonction getNode\n");

    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "SELECT ip, port, bucket_id FROM node WHERE id1 = ? AND id2 =? AND id3 = ? AND id4 = ? AND id5 = ?",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,id[0]);
    sqlite3_bind_int(stmt,2,id[1]);
    sqlite3_bind_int(stmt,3,id[2]);
    sqlite3_bind_int(stmt,4,id[3]);
    sqlite3_bind_int(stmt,5,id[4]);

    sqlite3_step(stmt);

    int ip = sqlite3_column_int(stmt, 0);
    int port = sqlite3_column_int(stmt, 1);


    node->id[0] = id[0];
    node->id[1] = id[1];
    node->id[2] = id[2];
    node->id[3] = id[3];
    node->id[4] = id[4];

    node->addr_ip.sin_addr.s_addr = ip;
    node->addr_ip.sin_port = port;

    sqlite3_finalize(stmt);

    sqlite3_close(db);
}

void setNode( Node *node ) {

    fprintf(stderr, "fonction setNode\n");

    uint32_t id[5];

    id[0] = node->id[0];
    id[1] = node->id[1];
    id[2] = node->id[2];
    id[3] = node->id[3];
    id[4] = node->id[4];

    int ip = node->addr_ip.sin_addr.s_addr;
    int port = node->addr_ip.sin_port;


    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "INSERT INTO node (id1,id2,id3,id4,id5,ip,port) VALUES (?,?,?,?,?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
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

}

void SetFile(uint32_t idnode[5], uint32_t hashword[5], uint32_t hashfile[5],char nom[], int taille){

    fprintf(stderr, "fonction setFile\n");

    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;


    if (sqlite3_prepare_v2(db, "INSERT INTO fichier (idnode1 , idnode2, idnode3, idnode4, idnode5, "
                               "hashword1 , hashword2 , hashword3 , hashword4 , hashword5 , "
                               "hashfile1 , hashfile2 , hashfile3 , hashfile4 , hashfile5 , nom , taille ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,idnode[0]);
    sqlite3_bind_int(stmt,2,idnode[1]);
    sqlite3_bind_int(stmt,3,idnode[2]);
    sqlite3_bind_int(stmt,4,idnode[3]);
    sqlite3_bind_int(stmt,5,idnode[4]);
    sqlite3_bind_int(stmt,6,hashword[0]);
    sqlite3_bind_int(stmt,7,hashword[1]);
    sqlite3_bind_int(stmt,8,hashword[2]);
    sqlite3_bind_int(stmt,9,hashword[3]);
    sqlite3_bind_int(stmt,10,hashword[4]);
    sqlite3_bind_int(stmt,11,hashfile[0]);
    sqlite3_bind_int(stmt,12,hashfile[1]);
    sqlite3_bind_int(stmt,13,hashfile[2]);
    sqlite3_bind_int(stmt,14,hashfile[3]);
    sqlite3_bind_int(stmt,15,hashfile[4]);
    sqlite3_bind_text(stmt,16,nom, sizeof(*nom), SQLITE_STATIC);
    sqlite3_bind_int(stmt,17,taille);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);


}

void findNode(uint32_t hash[5], Node *node){

    fprintf(stderr, "fonction findNode\n");

    sqlite3 *db;
    char *err_msg = 0;

    //ouverture base de donnée
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);

    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, "SELECT idnode1 BLOB, idnode2 BLOB, idnode3 BLOB, idnode4 BLOB, idnode5 BLOB FROM fichier WHERE hashword1 = ? AND hashword2 = ? AND hashword3 = ? AND hashword4 = ? AND hashword5 =? ",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,hash[0]);
    sqlite3_bind_int(stmt,2,hash[1]);
    sqlite3_bind_int(stmt,3,hash[2]);
    sqlite3_bind_int(stmt,4,hash[3]);
    sqlite3_bind_int(stmt,5,hash[4]);

    sqlite3_step(stmt);


    uint32_t idnode[5];

    idnode[0] = sqlite3_column_blob(stmt, 0);
    idnode[1] = sqlite3_column_blob(stmt, 1);
    idnode[2] = sqlite3_column_blob(stmt, 2);
    idnode[3] = sqlite3_column_blob(stmt, 3);
    idnode[4] = sqlite3_column_blob(stmt, 4);


    getNode(idnode, node);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

}