//
// Created by vincent on 12/06/2020.
//

#include "bdd.h"


int createDatabase (Node * from) {
    char * loc = getPipeFromId(from->id);
    char * path = concat(loc,"/data.db");

    char *err_msg = 0;
    sqlite3 * db;
    //ouverture base de donnée
    int rc = sqlite3_open(path, &from->db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);

        return 1;
    } else {
        fprintf(stdout, "database opened successfully\n");
    }

    //creation table
    char *sql = "CREATE TABLE IF NOT EXISTS node(id1 BLOB, id2 BLOB, id3 BLOB, id4 BLOB, id5 BLOB,ip INT, port INT, bucket_id INT, PRIMARY KEY (id1, id2,id3,id4,id5));"
                "CREATE TABLE IF NOT EXISTS fichier_local(nom TEXT, chemin_fichier TEXT);"
                "CREATE TABLE IF NOT EXISTS fichier("
                "idnode1 BLOB, idnode2 BLOB, idnode3 BLOB, idnode4 BLOB, idnode5 BLOB, "
                "hashword1 BLOB, hashword2 BLOB, hashword3 BLOB, hashword4 BLOB, hashword5 BLOB, "
                "hashfile1 BLOB, hashfile2 BLOB, hashfile3 BLOB, hashfile4 BLOB, hashfile5 BLOB, nom TEXT , taille INT,"
                "PRIMARY KEY (hashword1, hashword2, hashword3, hashword4, hashword5),"
                "FOREIGN KEY(idnode1, idnode2, idnode3, idnode4, idnode5) REFERENCES node(id1, id2,id3,id4,id5));";


    sqlite3_exec(from->db, sql, 0,0 ,&err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(from->db);

        return 1;
    } else {

        fprintf(stdout, "Tables created successfully\n");
    }

    //sqlite3_close(from->db);

    return 0;
}

void getNode(Node * from,uint32_t id[5], Node *node) {

    fprintf(stderr, "fonction getNode\n");

    char *err_msg = 0;



    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "SELECT ip, port, bucket_id FROM node WHERE id1 = ? AND id2 =? AND id3 = ? AND id4 = ? AND id5 = ?",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);
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
    node->addr_ip.sin_family    = AF_INET; // IPv4

    sqlite3_finalize(stmt);

   // sqlite3_close(db);
}

void setNode( Node * from,Node *node ) {

    fprintf(stderr, "fonction setNode\n");

    uint32_t id[5];

    id[0] = node->id[0];
    id[1] = node->id[1];
    id[2] = node->id[2];
    id[3] = node->id[3];
    id[4] = node->id[4];

    int ip = node->addr_ip.sin_addr.s_addr;
    int port = node->addr_ip.sin_port;



    char *err_msg = 0;

    //ouverture base de donnée


    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "INSERT INTO node (id1,id2,id3,id4,id5,ip,port) VALUES (?,?,?,?,?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);
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

    //sqlite3_close(from->db);

}

void SetFile(Node * from, Fichier *fichier){

    fprintf(stderr, "fonction setFile\n");


    char *err_msg = 0;



    sqlite3_stmt *stmt;


    if (sqlite3_prepare_v2(from->db, "INSERT INTO fichier (idnode1 , idnode2, idnode3, idnode4, idnode5, "
                               "hashword1 , hashword2 , hashword3 , hashword4 , hashword5 , "
                               "hashfile1 , hashfile2 , hashfile3 , hashfile4 , hashfile5 , nom , taille ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(from->db));
    //    sqlite3_close(from->db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,fichier->idnode[0]);
    sqlite3_bind_int(stmt,2,fichier->idnode[1]);
    sqlite3_bind_int(stmt,3,fichier->idnode[2]);
    sqlite3_bind_int(stmt,4,fichier->idnode[3]);
    sqlite3_bind_int(stmt,5,fichier->idnode[4]);
    sqlite3_bind_int(stmt,6,fichier->hashnom[0]);
    sqlite3_bind_int(stmt,7,fichier->hashnom[1]);
    sqlite3_bind_int(stmt,8,fichier->hashnom[2]);
    sqlite3_bind_int(stmt,9,fichier->hashnom[3]);
    sqlite3_bind_int(stmt,10,fichier->hashnom[4]);
    sqlite3_bind_int(stmt,11,fichier->hashfichier[0]);
    sqlite3_bind_int(stmt,12,fichier->hashfichier[1]);
    sqlite3_bind_int(stmt,13,fichier->hashfichier[2]);
    sqlite3_bind_int(stmt,14,fichier->hashfichier[3]);
    sqlite3_bind_int(stmt,15,fichier->hashfichier[4]);
    sqlite3_bind_text(stmt,16,fichier->nom, strlen(fichier->nom), SQLITE_STATIC);
    sqlite3_bind_int(stmt,17,fichier->taille);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    //sqlite3_close(from->db);


}

void findNode(Node * from,uint32_t hash[5], Node *node){

    fprintf(stderr, "fonction findNode\n");


    char *err_msg = 0;

    //ouverture base de donnée


    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "SELECT idnode1, idnode2, idnode3 , idnode4 , idnode5  FROM fichier WHERE hashword1 = ? AND hashword2 = ? AND hashword3 = ? AND hashword4 = ? AND hashword5 =? ",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);
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

    idnode[0] = sqlite3_column_int(stmt, 0);
    idnode[1] = sqlite3_column_int(stmt, 1);
    idnode[2] = sqlite3_column_int(stmt, 2);
    idnode[3] = sqlite3_column_int(stmt, 3);
    idnode[4] = sqlite3_column_int(stmt, 4);


    getNode(from,idnode, node);

    sqlite3_finalize(stmt);

    //sqlite3_close(from->db);

}

void setlocalfile(Node * from,char nom[], char chemin[]){

    fprintf(stderr, "fonction setLocalfile\n");


    char *err_msg = 0;

    //ouverture base de donnée


    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "INSERT INTO fichier_local (nom,chemin_fichier) VALUES (?,?)",-1,&stmt,NULL)) {
        fprintf(stderr,"Error: cannot execute sql statement SET %s \n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_text(stmt,1,nom,sizeof(nom), SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,chemin,sizeof(chemin), SQLITE_STATIC);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    //sqlite3_close(from->db);

}

char* getfilepath(Node * from,char nom[]){

    fprintf(stderr, "fonction getfilepath\n");


    char *err_msg = 0;

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "SELECT chemin_fichier FROM fichier_local WHERE nom LIKE ?",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(from->db));
        sqlite3_close(from->db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_text(stmt,1,nom, sizeof(nom), SQLITE_STATIC);

    sqlite3_step(stmt);

    char * cheminbuffer;
    // utilisation d'un buffer car le pointeur disparait après sqlite3_finalize(stmt)
    cheminbuffer = sqlite3_column_text(stmt, 0);

    char *chemin = malloc(sizeof(cheminbuffer));
    strcpy(chemin,cheminbuffer);

    sqlite3_finalize(stmt);

    //sqlite3_close(from->db);


    return chemin;

}

void getfichier(Node * from,uint32_t hashnom[5], Fichier *fichier, Node *node){

    fprintf(stderr, "fonction get fichier\n");


    char *err_msg = 0;

    //ouverture base de donnée


    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(from->db, "SELECT idnode1 , idnode2 , idnode3 , idnode4 , idnode5 ,"
                               " hashfile1 , hashfile2 , hashfile3 , hashfile4 , hashfile5 ,"
                               " nom  , taille"
                               " FROM fichier WHERE hashword1 = ? AND hashword2 = ? AND hashword3 = ? AND hashword4 = ? AND hashword5 =? ",-1,&stmt,NULL)!= SQLITE_OK) {
        fprintf(stderr,"Error: cannot execute sql statement GET %s \n", sqlite3_errmsg(from->db));
      //  sqlite3_close(from->db);
        exit(1);
    }

    //https://www.sqlite.org/c3ref/bind_blob.html
    sqlite3_bind_int(stmt,1,hashnom[0]);
    sqlite3_bind_int(stmt,2,hashnom[1]);
    sqlite3_bind_int(stmt,3,hashnom[2]);
    sqlite3_bind_int(stmt,4,hashnom[3]);
    sqlite3_bind_int(stmt,5,hashnom[4]);


    sqlite3_step(stmt);


    uint32_t idnode[5];

    idnode[0] = sqlite3_column_int(stmt, 0);
    idnode[1] = sqlite3_column_int(stmt, 1);
    idnode[2] = sqlite3_column_int(stmt, 2);
    idnode[3] = sqlite3_column_int(stmt, 3);
    idnode[4] = sqlite3_column_int(stmt, 4);


    getNode(from,idnode, node);

    for(int i=0; i<5; i++){
        fichier->idnode[i] = idnode[i];
    }
    for(int i=5; i<10; i++){
        fichier->hashfichier[i-5] = sqlite3_column_int(stmt, i);
    }
    char * nom = sqlite3_column_text(stmt, 10);
    for(int i=0; i<5; i++){
        fichier->nom[i] = nom[i];
    }
    fichier->taille = sqlite3_column_int(stmt,11);
    for(int i=0; i<5; i++){
        fichier->hashnom[i] = hashnom[i];
    }

    sqlite3_finalize(stmt);

   // sqlite3_close(from->db);

}