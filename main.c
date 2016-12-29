#include"screen1.h"

int main()
{
	
	system("COLOR F0");													// To set Bk color
	
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    page1();															//To display Startup
    
    LIST event_list;													//To Store event list for further use
    
	init(&event_list);													//To set NULL to list
    
	int *n,*m;
    n=(int*)malloc(sizeof(int));
    m=(int*)malloc(sizeof(int));
    
	do{
	printf("\n\t\tWhere , \n\t\t      N stands for No. of Events....\n\t\t      M stands for No. of preferences i/p by students !!!");
	
	printf("\n\n\t#\tEnter the Value of N and M: ");
    
	scanf("%d %d",n,m);													//To set precision and constraints
	if(*n>0&&*m>0)break;
	
	}while(1);															//N is for Number of total events                          stored at top of event_list
	event_list.top.data=n;												// M is for no. of preferences inputed by students		   stored at rear of event_list	
	event_list.rear.data=m;

	LIST stud_list;														//To Store all students data

    init(&stud_list);

    int *no;
    no=(int *)malloc(sizeof(int));						
	printf("\n\n\t#\tEnter The Students Count : ");						//This is no. of students that are inputed preferences
    scanf("%d",no);
	stud_list.top.data=no;

    page2(&event_list,&stud_list);										//Admin sets all events 

    page3(&event_list);

	showstudents(&stud_list);											//Shows all students preferences
    
	setedge(&stud_list,&event_list);
    getedge(&event_list);												//To display all edges of list
    
	LIST slot;															//To show slot lists
    
	init(&slot);
    
	allocate(&event_list,&slot);										//100 % solution 
    LIST store_slots;													//Store of slot list
    
	init(&store_slots);
	printf("\n\t\tThis is 100 Solution :");
	printf("\n\t\tHappiness : 100\n");
	show_slot_vise(slot);												//Function to store slots  
  	store_slot(&slot,&store_slots,&stud_list);
					
	printhappiness();													//Defination of Happiness 
	
	LIST count_val;														//To count all weighted of events
    init(&count_val);
    
	count_value(&stud_list,&event_list);
    
	
    printf("Value of Each event : \n");
    show_val(&event_list);
	
	    int *p,*k;
	    p=(int*)malloc(sizeof(int));
	    k=(int*)malloc(sizeof(int));									// p is for No. of parallel slots that can be run
																		// K is for No. of available slots for event
	
	printf("\n\n\t\t%s wants to know how Many Slots Are their ????",assi);
	printf("\n\n\t\tEnter the value of k and p : ");
	
	do{
	printf("\n\t\tWhere , \n\t\t      K stands for No. of Slots....\n\t\t      P stands for No. of slots can be held in parallel!!!");
	
	printf("\n\n\t#\tEnter the Value of K and P : ");
    
	scanf("%d %d",&(*k),&(*p));
	
	if(*p>0&&*k>0)break;
	}while(1);															//N is for Number of total events                          stored at top of event_list
	
	modify(&slot,event_list,*p,*k,&stud_list,&store_slots);				// This is function can modify our 100 % solution 
	
	printf("\n\n\t\tThis are suggested Slots for you :\n\n");
	
	show_store_slots(&store_slots);										//This are possible solution of slots 
	getch();
	return 0;
}
