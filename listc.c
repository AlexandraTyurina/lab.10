#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 60
// -------------------------------------------------------
void ClearStringArray(char **str, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;

}
// -------------------------------------------------------
void ClearStructure(laptops *str0)
{
    str0->name=NULL;
    str0->seria=NULL;
    free(str0->name);
    free(str0->seria);
    free(str0);
    str0=NULL;
}
// -------------------------------------------------------
char **simple_split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++)
    {
        if(str[j]==sep) m++;
    }

    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if((str[j]!=sep)&&(str[j]!='\n'))
                {
                    str_array[m][k]=str[j];
                    k++;
                }
                else
                {
                    str_array[m][k]='\0';
                    k=0;
                    m++;
                }
            }
        }
        else
        {
            ClearStringArray(str_array,count);
        }
     }
     return str_array;
}
// -------------------------------------------------------
laptops *struct_fill(char **str)
{
    laptops *str0=NULL;

    str0=(laptops*)malloc(sizeof(laptops));
    if(str0!=NULL)
    {
        str0->name=str[0];
        str0->seria=str[1];
        str0->RAM=atoi(str[2]);
        str0->nucleus=atoi(str[3]);
        str0->rate=atof(str[4]);
        str0->weight=atof(str[5]);
        str0->par[0]=atof(str[6]);
        str0->par[1]=atof(str[7]);
        str0->par[2]=atof(str[8]);
    }
    return str0;
}
// -------------------------------------------------------
void print_header()
{
    printf("|%10s|%13s| %3s | %3s | %6s | %6s | %6s | %6s | %6s |\n","name","seria","RAM","nucleous","rate","weight","parameter[1]","parameter[2]","parameter[3]");
    printf("+----------+-------------+-----+----------+--------+--------+--------------+--------------+--------------+\n");

}

void struct_out(laptops *str)
{
    printf("|%10s|%13s| %3d | %8d | %6.3f | %6.3f | %12.3f | %12.3f | %12.3f |\n",
        str->name,str->seria,str->RAM,str->nucleus,str->rate,str->weight,str->par[0],str->par[1],str->par[2]);
}
/* --------Functions for linear single-linked list-------- */
// -------------------------------------------------------
Head *MakeHead()
{
 Head *ph=NULL;
 ph=(Head*)malloc(sizeof(Head));
 if(ph!=NULL)
 {
    ph->cnt=0;
    ph->first=NULL;
    ph->last=NULL;
 }
 return ph;
}
// -------------------------------------------------------
Node *CreateNode(FILE *df)
{
 Node *NewNode=NULL;
 int slen;
 char **s2=NULL;
 char *s1;
 char sep=';';
 NewNode = (Node*)malloc(sizeof(Node));
 s1 = (char*)malloc(MAXLEN*sizeof(char));
 if(NewNode&&s1)
 {
    NewNode->id = 1;
    fgets(s1,MAXLEN,df);
    slen=strlen(s1);
    s1[slen-1]='\0';
    slen=strlen(s1);
    s2=simple_split(s1,slen,sep);//память выделяется в функции
    if(s2!=NULL)
    {
        NewNode->comp=struct_fill(s2);
    }
    else puts("Error at data reading!");
    NewNode->comp=struct_fill(s2);
    NewNode->next = NULL;
 }
 free(s1);
 s1=NULL;
 return NewNode;
}
// -------------------------------------------------------
void AddFirst(Head *MyHead, Node *NewNode)
{
 if(MyHead&&NewNode)
 {
    MyHead->first = NewNode;
    MyHead->last = NewNode;
    MyHead->cnt++;
 }
}
// -------------------------------------------------------
void AddLast(Head *MyHead, Node *NewNode, Node *PrevNode)
{
    int n;

    if(MyHead&&NewNode&&PrevNode)
    {
        n=MyHead->cnt+1;
        PrevNode->next=NewNode;
        NewNode->id=n;
        MyHead->last=NewNode;
        MyHead->cnt=n;
    }
}
// -------------------------------------------------------
void InsertAfter(Head *MyHead, Node *NewNode, Node *CurrentNode)
{
    int n;
    if(MyHead&&NewNode&&CurrentNode)
    {
        n=MyHead->cnt+1;
        if(CurrentNode->next==NULL)
        {
            CurrentNode->next=NewNode;
            MyHead->last=NewNode;
        }
        else
        {
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
        }
        NewNode->id=n;
        MyHead->cnt=n;
    }
}
// -------------------------------------------------------
Node *SelectById(Head *MyHead, int num)
{
    Node *q;
    int k,n;
    n=num-1;
    q=MyHead->first;
    k=MyHead->cnt;
    if((n>=1)&&(n<=k))
    {
        while((q->id)!=n) q=q->next;
    }
    else q=NULL;
    return q;
}
// -------------------------------------------------------
void deleteSelected(Head *MyHead, Node *CurrentNode)
{
    Node *q, *q1;

    q=MyHead->first;
    q1=MyHead->last;
    if(CurrentNode==q)
    {
        MyHead->first=CurrentNode->next;
        CurrentNode->next=NULL;
        free(CurrentNode);
    }
    else
    {
        while(q!=NULL)
        {
            if(q->next==CurrentNode)
            {
                if(CurrentNode==q1) MyHead->last=q;
                q->next=CurrentNode->next;
                CurrentNode->next=NULL;
                free(CurrentNode);
            }
            else q=q->next;
        }
    }
}
/* ------------------The end of this part------------------ */
