#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 60
/* define structures */
typedef struct LAPTOP{
        char *name;
        char *seria;
        int RAM;
        int nucleus;
        float rate;
        float weight;
        float par[3];
}laptops;
typedef struct LNode {
    int   id;
    laptops *comp;  /* data area */
    struct LNode  *next; /* link to next node */
}Node;

typedef struct LHead {
    int cnt;
    struct LNode *first;
    struct LNode *last;
}Head; /* datatype for pointer to node */
// -----------Functions to work with data structure-----------
/* function to clear array of string */
void ClearStringArray(char **str, int n);

/* function to clear a structure */
void ClearStructure(laptops *str0);

/* function to split string to array by separator */
char **simple_split(char *str, int length, char sep);

/* function to create structure by array of strings*/
laptops *struct_fill(char **str);

void print_header();

void struct_out(laptops *str);
// ----------------------------------------------------------
// -------------Functions to work with the list--------------
Head *MakeHead();
Node *CreateNode(FILE *df);
void AddFirst(Head *MyHead, Node *NewNode);
void AddLast(Head *MyHead, Node *NewNode, Node *PrevNode);
void InsertAfter(Head *MyHead, Node *NewNode, Node *CurrentNode);
Node *SelectById(Head *MyHead, int num);
void deleteSelected(Head *MyHead, Node *CurrentNode);
#endif // LIST_H_INCLUDED
