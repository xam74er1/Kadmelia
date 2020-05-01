//
// Created by root on 5/1/20.
//


#ifndef GROUPE7_LISTCHAINE_H
#define GROUPE7_LISTCHAINE_H

typedef struct Ellements{
   Ellements * next;
   Node * value;
}Ellements;

typedef struct ListCaine{
    Ellements * first;
    Ellements * last;
    Node * value;
}ListCaine;
#endif //GROUPE7_LISTCHAINE_H
