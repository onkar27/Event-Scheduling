#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node
{
    void * data;
    struct node *link;
}NODE;
typedef struct list
{
    NODE  top;
    NODE  rear;
}LIST;
void init(LIST *t)
{
    t->rear.link=t->top.link=NULL;
}
NODE * setnew(void *datain)
{
    NODE *pNew=(NODE *)malloc(sizeof(NODE));
    pNew->data=datain;
    pNew->link=NULL;
    return pNew;
}
void append(void *datain,LIST * t)
{
    if(t->rear.link==NULL)
        t->top.link=t->rear.link=setnew(datain);
    else
    {
        (t->rear.link)->link=setnew(datain);
        t->rear.link=(t->rear.link)->link;
    }
}
void display(LIST t)
{
    NODE *pLoc=t.top.link;
    while(pLoc!=NULL)
    {
        printf("%c ",(*(char *)pLoc->data));
        pLoc=pLoc->link;
    }
}
int searchin(LIST t,char datain)
{
    NODE *pLoc=t.top.link;
    while(pLoc!=NULL)
    {
        if(*(char *)pLoc->data==datain)
            return 1;
        pLoc=pLoc->link;
    }
    return 0;
}
void createlist(LIST *a)
{
    int *data;
    while(1)
    {
        data=(int *)malloc(sizeof(int));
        printf("Enter data: ");
        scanf("%d",data);
        append(data,a);
        if(*data==0)
            break;
    }
}
/*int main()
{
    LIST a;
    init(&a);
    createlist(&a);
    display(a);
    printf("%d",search(a,3));
}
*/
