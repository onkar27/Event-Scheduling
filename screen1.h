#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define Mx 165
#define My 38
#include "stud.h"
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
char assi[10];
char eventnm[10];
void page1()
{
    strcpy(assi,"JARVIS");
	char a[100]=">>> Hey,I am JARVIS , Your Software Assistant !!!";
	int i,j;
	gotoxy(30,10);
	for(i=0;a[i]!='\0';i++)
	{
		printf("%c",a[i]);
		if(i>2)
		delay(50);
	}
	getchar();
	gotoxy(30,11);
	int d=printf(">>> Do you want to rename your ASSISTANT ?? (y/n): ");
	char c,name[20];
	do
	{
	    gotoxy(30+d,11);
		c=getchar();
		if(c==13)gotoxy(30+d,11);
		if(c=='y'||c=='Y'||c=='n'||c=='N')break;
	}while(1);
	if(c=='y'||c=='Y')
	{
		gotoxy(13,15);
		printf(">>> JARVIS wants his New Name : ");
		scanf(" %[^\n]s",name);
		gotoxy(13,13);
		strcpy(assi,name);
		system("cls");
		printf(">>> %s is happy with his new name !!\n\n\n",name);

	}
	system("cls");
    gotoxy(10,10);
    printf("%s wants Main Event-Name : ",assi);
    scanf(" %s",eventnm);
}
void page2(LIST *event_list,LIST *stud_list)
{
    system("cls");
    printf("\n\n\n\n\t\t##################################%s###################################\n",eventnm);
    addevent_Admin(event_list);
    addstudents(event_list,stud_list);
}
void page3(LIST *event_list)
{
	system("cls");
    printf("\n\n\n\n\t\t##################################%s###################################\n",eventnm);
   	showevent_admin(event_list);
}
void printhappiness()
{
	printf("Do you want to know about ...\n\t\tHow %s Sets Happiness ? (y/n) :",assi);
	char c='n';
	c=getch();
	if(c=='y'||c=='Y')
	{	
		printf("\n\t\tHappiness : \n\n\t\tSuppose their are \'M\' preferences to fill then %s assigned the \'Weight\' to each preference then...\n\t\t1st preference get \'Weight \'     : M \n\t\t2nd will get                     : M-1 \n\t\t3rd will get                     : M-2\n\t\t.\n\t\t.\n\t\t.\n\t\tMth preference will get Weight   : 1\n\n\n\t\ti.e.They get Weight in decresing order \n\t\tThen %s Calculate Happiness by adding \n\n\n\t\tFor happines of n'th stud........: Weight(n'th) * 200\n\t\t                                    ------------\n\t\t                                     M*(M+1)",assi,assi);
		getch();
	}
}
