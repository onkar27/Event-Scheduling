#include"LIST.h"
#include<conio.h>
#include<string.h>
/*
Event Scheduling:
Given a set of N events, e.g., events in college festival, each student is asked to
choose M events of his/her choice, in order of decreasing reference. If
there are K slots available to schedule the events out of which
at most P slots can be held in parallel, output a schedule that maximizes the happiness of most students. You are free to choose the definition of “happiness” as long as the definition is reasonable. The algorithm should work for any given N, M, K, P and the preference list of any number of students.
*/
int genid='A';
typedef struct e
{
    char id;
    char name[20];
    int fees;
    char des[100];
    int val;
    LIST edge;
}EVENT;
void update(int i,EVENT *t)
{
    system("cls");
    printf("\n\t\t#\tEvent No .....: %d\n",i+1);
    printf("\n\t\t#\tEnter the Event Id : %c\n",'A'+i);
    printf("\n\t\t#\tEnter the event name : ");
    scanf(" %[^\n]s",t->name);
    printf("\n\t\t#\tEnter the event fees : ");
    scanf("%d",&t->fees);
    printf("\n\t\t#\tEnter the description : ");
    scanf(" %[^\n]s",t->des);
    t->id=genid++;
    init(&(t->edge));
    t->val=0;
}
void show(EVENT t)
{
	printf("\n\n\n\n\t\t#\tEvent No..........: %5d",t.id-'A'+1);
    printf("\n\n\t\t#\tEvent Name........: %-10s",t.name);
    printf("\n\n\t\t#\tEvent Id..........: %5c",t.id);
    printf("\n\n\t\t#\tEvent Description.: %-10s",t.des);
    printf("\n\n\t\t#\tEvent fees........: %5d",t.fees);
}
void addevent_Admin(LIST *event_list)
{
    int i=0;
    while(i<(*(int*)event_list->top.data))
    {
        EVENT *New=(EVENT *)calloc(1,sizeof(EVENT));
        update(i,New);
        append(New,event_list);
        i++;
    }
}
void showevent_admin(LIST *event_list)
{
    NODE *pLoc=event_list->top.link;
    while(pLoc!=NULL)
    {
        show(*(EVENT *)pLoc->data);
        pLoc=pLoc->link;
    }
}
void ssearch(LIST *event_list)
{
    char sea[100],c=0;
    int i=0;
    NODE *pLoc=event_list->top.link;
    while(1)
    {
    	int j=1; 
    	printf("\n\t\tEnter Here...:");
		c=getch();
    	system("cls");
        if(c==13||(c>='1'&&c<='9'))break;
        if(c=='0')
        {
        	sea[--i]=0;
		}
		else
		{
			sea[i++]=c;
        	sea[i]=0;
		}
        printf("\n\t\t%s : \n",sea);
        pLoc=event_list->top.link;
        while(pLoc!=NULL)
        {
        	if(strstr(((EVENT *)(pLoc->data))->name,sea)!=NULL)
        		printf("\n\t\t%2d\t%-15s\t\tFrom Event id...:%2c",j++,((EVENT *)(pLoc->data))->name,((EVENT *)(pLoc->data))->id);
            char *de=((EVENT *)(pLoc->data))->des;
            if(strstr(de,sea)!=NULL)
			    printf("\n\t\t%2d\t%-15s\t\tFrom Event id...:%2c",j++,de,((EVENT *)(pLoc->data))->id);
            pLoc=pLoc->link;
        }
    }
}
void addevent_student(LIST *source,LIST *stud)
{
    char c;
    while(1)
    {
        system("cls");
        printf("\n\n\tEnter the Students Preferences :");
        printf("\n\tDo you want to search (Y/N) :");
        c=getch();
        if(c=='y'||c=='Y')
        {
            system("cls");
            ssearch(source);
        }
        else if(c=='n'||c=='N')
        {
            showevent_admin(source);
            printf("\n\n");
            stud->top.data=(int *)source->rear.data;
            char *datain;
            int i=0;
            while(i<(*(int *)source->rear.data))
            {
                datain=(char *)calloc(1,sizeof(char));
                printf("\n\tEnter the preference %d : ",i+1);
                scanf(" %c",datain);
                if(searchin(*source,(*datain))==false)
                {
                    printf("\n\tSorry Invalid input !!!");
                    free(datain);
                    continue;
                }
                NODE *pLoc=stud->top.link;
                int f=0;
                while(pLoc!=NULL)
                {
                	char one = *(char *)pLoc->data;
					if(one == *datain)
					{
						printf("\n\tSorry Duplication in input !!!");
                     	f=1;
                     	break;
                	}
                	pLoc=pLoc->link;
				}
				if(f==1)
					continue;
                
                append(datain,stud);
                i++;
            }
            break;
        }
        else continue;
    }
}
void showevent_student(LIST *event_list)
{
    NODE *pLoc=event_list->top.link;
    while(pLoc!=NULL)
    {
        printf(" %c ",*(char*)pLoc->data);
        pLoc=pLoc->link;
    }
}
