#include"EVEN.h"
typedef struct sl
{
    int slot_no;
    char slot_id;
}SLOT;
void addstudents(LIST *event_list,LIST *students)
{
    int i=0;
    while(i<*(int *)students->top.data)
    {
        LIST * stud = (LIST *)calloc(1,sizeof(LIST));
        init(stud);
        addevent_student(event_list,stud);
        append(stud,students);
        i++;
    }
    students->rear.data=(int *)event_list->rear.data;
}

double calhappy(LIST *slot_list,LIST *stud_list)
{
    double hap=0;
    NODE *pLoc_1=slot_list->top.link,*pLoc_2=stud_list->top.link;
    int m=*(int *)stud_list->rear.data;
    int pr=*(int *)stud_list->top.data;
    int size=countslots(*slot_list);
    while(pLoc_2!=NULL)
    {
        NODE *pLoc_3=((LIST *)(pLoc_2->data))->top.link;
        int i=m;
        int *flag=(int *)calloc(size,sizeof(int));
        while(pLoc_3!=NULL)
        {
            pLoc_1=slot_list->top.link;
            char two=*(char *)(pLoc_3->data);
            while(pLoc_1!=NULL)
            {
                char one=((SLOT *)(pLoc_1->data))->slot_id;
                int d=((SLOT *)(pLoc_1->data))->slot_no;
                if(one==two&&flag[d-1]==0)
                {
                    flag[d-1]=1;
                    hap+=i*(100/(((m*(m+1))/2)*1.0));
                   // printf("\n%c %d %lf ",one,d,hap);
                    break;
                }
                pLoc_1=pLoc_1->link;
            }
            pLoc_3=pLoc_3->link;
            i--;
        }
        free(flag);
        pLoc_2=pLoc_2->link;
    }
    //printf("happi = %lf\n",hap);
	return hap/(pr*1.0);
}
void showstudents(LIST *students)
{
    NODE * pLoc=students->top.link;
    int i=1;
    while(pLoc!=NULL)
    {
        printf("\nStudent : %d :-> ",i++);
        showevent_student((LIST *)pLoc->data);
        pLoc=pLoc->link;
    }
}
void catching(LIST * edge,LIST * stud,char id)
{
    NODE *pLoc_1=edge->top.link,*pLoc_2=stud->top.link;
    char one,two;
    int *cnt = (int *)calloc(1,sizeof(int));
    edge->top.data=cnt;
    while(pLoc_2!=NULL)
    {
        one=*(char *)(pLoc_2->data);
        if(searchin(*edge,one)==0&&one!=id)
        {
            (*cnt)++;
            append((char *)(pLoc_2->data),edge);
        }
        pLoc_2=pLoc_2->link;
    }
}
void setedge(LIST * stud_list,LIST * event_list)
{
    NODE * pLoc_s = stud_list->top.link,*pLoc_e=event_list->top.link;
    LIST * tmp;
    char d;
    while(pLoc_e!=NULL)
    {
        d=((EVENT *)pLoc_e->data)->id;
        pLoc_s = stud_list->top.link;
        while(pLoc_s!=NULL)
        {
            tmp = (LIST *)pLoc_s->data;
            if(searchin(*tmp,d)==1)
            {
                catching((&((EVENT *)pLoc_e->data)->edge),tmp,d);
            }
            pLoc_s=pLoc_s->link;
        }
        pLoc_e=pLoc_e->link;
    }
}
void getedge(LIST * event_list)
{
    NODE *pLoc = event_list->top.link;
    while(pLoc!=NULL)
    {
        printf("\n%c : ",((EVENT *)(pLoc->data))->id);
        display(((EVENT *)(pLoc->data))->edge);
        pLoc=pLoc->link;
    }
}
LIST* getedge_id(LIST * event_list,char id)
{
    NODE *pLoc = event_list->top.link;
    while(pLoc!=NULL)
    {
        if(id==((EVENT *)(pLoc->data))->id)
        return &((EVENT *)(pLoc->data))->edge;
        pLoc=pLoc->link;
    }
    return NULL;
}
NODE* searchinslot(LIST *slot_list,char one)
{
    NODE * pLoc_2=slot_list->top.link;
    while(pLoc_2!=NULL)
    {
        if(((SLOT *)(pLoc_2->data))->slot_id==one)
        {
            break;
        }
        pLoc_2=pLoc_2->link;
    }
    return pLoc_2;
}
int countslots(LIST slot)
{
	NODE *pLoc=slot.top.link;
	int cnt=0,max;
	int n=0;
	while(pLoc!=NULL)
	{
		n++;
		pLoc=pLoc->link;
	}
	pLoc=slot.top.link;
	int *a=(int *)calloc(n,sizeof(int ));
	while(pLoc!=NULL)
	{
		max=((SLOT *)(pLoc->data))->slot_no;
		a[max-1]=1;
		pLoc=pLoc->link;
	}
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i])cnt++;
	}
	return cnt;
}
void allocate(LIST * event_list,LIST *slot)
{
    NODE *pLoc_1= event_list->top.link,*pLoc_2;
    int cnt=0,*n=(int *)calloc(1,sizeof(int )),*m=(int *)calloc(1,sizeof(int ));
    *m=*(int *)event_list->top.data;
    *n=0;
    while(pLoc_1!=NULL)
    {
        char one=((EVENT *)pLoc_1->data)->id;
        SLOT * pNew= (SLOT *)calloc(1,sizeof(SLOT));
        pNew->slot_id=one;
        pNew->slot_no=++cnt;        
		NODE* f=searchinslot(slot,one);
        if(slot->top.link==NULL)
        {
        	append(pNew,slot);
    	}	
        else if(f==NULL)
        {
            int itt=0;
            int flag=0;
            for(itt=1;itt<cnt;itt++)
            {
                flag=0;
                pLoc_2=slot->top.link;
                while(pLoc_2!=NULL)
                {
                    if(((SLOT *)(pLoc_2->data))->slot_no==itt)
                    {
                        if(searchin(*getedge_id(event_list,((SLOT *)(pLoc_2->data))->slot_id),one)==1)
                        {flag=1;break;}
                    }
                    pLoc_2=pLoc_2->link;
                }
                if(flag==0)
                {
                    pNew->slot_no=itt;
                    append(pNew,slot);
                    break;
                }
            }
            if(flag==1)
            {
                append(pNew,slot);
            }
        }
        pLoc_1=pLoc_1->link;
    }
    *n=cnt;
    *m=countslots(*slot);
    slot->top.data=n;
    slot->rear.data=m;
}
void display_slot(LIST t)
{
    NODE *pLoc=t.top.link;
    while(pLoc!=NULL)
    {
        printf("\n%d :-> %c ",((SLOT *)pLoc->data)->slot_no,((SLOT *)pLoc->data)->slot_id);
        pLoc=pLoc->link;
    }
}
void count_value(LIST *stud_list,LIST * event_list)
{
    NODE * pLoc_1= stud_list->top.link,*pLoc_2;
    while(pLoc_1!=NULL)
    {
        pLoc_2=((LIST *)(pLoc_1->data))->top.link;
        int val=*(int *)event_list->rear.data;
        while(pLoc_2!=NULL)
        {
            char one = *(char *)(pLoc_2->data);
            NODE *pLoc_3=event_list->top.link;
            while(pLoc_3!=NULL)
            {
                char two = ((EVENT *)(pLoc_3->data))->id;
                if(one==two)
                {
                    ((EVENT *)(pLoc_3->data))->val+=val;
                }
                pLoc_3=pLoc_3->link;
            }
            pLoc_2=pLoc_2->link;
            val--;
        }
        pLoc_1=pLoc_1->link;
    }
}
int getval(LIST event_list,char s)
{
    NODE *pLoc=event_list.top.link;
    while(pLoc!=NULL)
    {
        if(s==(((EVENT *)(pLoc->data))->id))
            return (((EVENT *)(pLoc->data))->val);
        pLoc=pLoc->link;
    }
    return 0;
}
void show_val(LIST *event_list)
{
    NODE * pLoc=event_list->top.link;
    while(pLoc!=NULL)
    {
        printf(" %c  : %d\n",((EVENT *)(pLoc->data))->id,((EVENT *)(pLoc->data))->val);
        pLoc=pLoc->link;
    }
}
int isinslot(LIST slot,int i)
{
	NODE *pLoc=slot.top.link;
	while(pLoc!=NULL)
	{
		if(((SLOT *)(pLoc->data))->slot_no==i)
			return 1;
		pLoc=pLoc->link;
	}
	return 0;
}
void show_slot_vise(LIST slot_list)
{
    int i,n=*(int *)slot_list.top.data;
    printf("\n\tNo. Of Slots...:%4d\t\n",countslots(slot_list)); 
    int j=1;
	puts("\t+----------+-----------------+"); 
	puts("\t| Slot No. |    Event_Id     |");
	puts("\t+----------+-----------------+");
  	for(i=1;i<=n;i++)
    {
    	if(isinslot(slot_list,i)==1)
    	{
	        NODE *pLoc=slot_list.top.link;
	        printf("\t|    %2d    |",j++);
	        int space=0;
	        while(pLoc!=NULL)
	        {
	            if(((SLOT *)(pLoc->data))->slot_no==i)
	                space+=printf(" %2c ",((SLOT *)(pLoc->data))->slot_id);
	            pLoc=pLoc->link;
	        }
	        if(space==0)
	        {
	        	space+=printf("       -");
			}
	        while(space++<17)
	        printf(" ");
	        printf("|\n");
		}
    }
    puts("\t+----------+-----------------+\n\n"); 
}
int notin(char *arr,char sv,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(arr[i]==sv)
            return 1;
    }
    return 0;
}
NODE * isparallel(LIST *slot,char id)
{
    NODE *pLoc=slot->top.link,*pSea=searchinslot(slot,id);
    int no=((SLOT *)(pSea->data))->slot_no;
    while(pLoc!=NULL)
    {
        int one = ((SLOT *)(pLoc->data))->slot_no;
        char two= ((SLOT *)(pLoc->data))->slot_id;
        if(one==no&&two!=id)
        {
            break;
        }
        pLoc=pLoc->link;
    }
    return pLoc;
}
void createdupli(LIST *slot ,LIST *des,int *n)
{
    init(des);
    NODE *pLoc=slot->top.link;
    while(pLoc!=NULL)
    {
        SLOT *pNew=(SLOT *)malloc(sizeof(SLOT));
        *pNew=*(SLOT*)(pLoc->data);
        append(pNew,des);
        pLoc=pLoc->link;
        if(*n<(pNew->slot_no))
            *n=pNew->slot_no;
    }
}
void store_slot(LIST *slot,LIST *store_slot,LIST *stud_list)
{
    LIST *pNew=(LIST *)malloc(sizeof(LIST));
    NODE *pPre;
    init(pNew);
    int *n=(int *)calloc(1,sizeof(int));

    createdupli(slot,pNew,n);
    pNew->top.data=n;
    double *happ=(double *)malloc(sizeof(double));
    *happ=calhappy(slot,stud_list);
    pPre=(NODE *)malloc(sizeof(NODE));
    pPre->data=happ;
    pPre->link=NULL;
    (pNew->rear).link=pPre;
    //printf("%.2f\n",*(double *)(((slot->rear).link)->data));
    append(pNew,store_slot);
}
void show_store_slots(LIST *store_slots)
{
    NODE  *pLoc=store_slots->top.link;
    while(pLoc!=NULL)
    {
        LIST *tmp=((LIST *)(pLoc->data));
        double  val =*((double*)(tmp->rear.link)->data);
        //printf("\n No of slots : %d  %.2f \n",*(int *)((LIST *)(pLoc->data))->top.data,val);
        printf("\nHappiness : %.2lf\n",val);
    
		show_slot_vise(*((LIST *)(pLoc->data)));
        pLoc=pLoc->link;
    }
}

void modify(LIST *slot,LIST event_list,int p,int k,LIST *stud_list,LIST *store_slots)
{
    NODE *pLoc=event_list.top.link,*pPre=NULL;
    int n=*(int *)(slot->top.data);
    int m=*(int *)(slot->rear.data);
	double *happ=(double *)malloc(sizeof(double));
    *happ=calhappy(slot,stud_list);
    //show_slot_vise(*slot);
	
	pPre=(NODE *)calloc(1,sizeof(NODE));
    pPre->data=happ;
    pPre->link=NULL;
    (slot->rear).link=pPre;
    
    // To store maximum happiness i.e.100%
    
    //int size=*(int *)event_list.top.data;
    //char *arr= (char *)calloc(size,sizeof(char));
    int val=0,i=1,j=0;
    while(k<countslots(*slot))
    {
    	
        int mini=1000000;
        pLoc=event_list.top.link;
        pPre=NULL;
        while(pLoc!=NULL)
        {
            if(isparallel(slot,((EVENT *)(pLoc->data))->id)==NULL&&mini>((EVENT *)(pLoc->data))->val)
            {
                mini=((EVENT *)(pLoc->data))->val;
                pPre=pLoc;
            }
            pLoc=pLoc->link;
        }
    	if(pPre==NULL)
    		return ;
        int j,l;
        double ma=0,tm;
        char one=((EVENT *)(pPre->data))->id;
	    pLoc=slot->top.link;
        NODE *b=searchinslot(slot,one);
        while(pLoc!=NULL)
        {
            char two=((SLOT *)(pLoc->data))->slot_id;
            if(one!=two)
            {
                int num=((SLOT*)(b->data))->slot_no;
                ((SLOT*)(b->data))->slot_no=((SLOT *)(pLoc->data))->slot_no;
                tm=calhappy(slot,stud_list);
                if(ma<tm)
                    ma=tm;
                ((SLOT*)(b->data))->slot_no=num;
            }
            pLoc=pLoc->link;
        }
        pLoc=slot->top.link;
        while(pLoc!=NULL)
        {
            char two=((SLOT *)(pLoc->data))->slot_id;
            if(one!=two)
            {
                int num=((SLOT*)(b->data))->slot_no;
                ((SLOT*)(b->data))->slot_no=((SLOT *)(pLoc->data))->slot_no;
                tm=calhappy(slot,stud_list);
                if(ma==tm)
                {
                    //printf("  Happiness : %.2lf with %d\n",calhappy(slot,stud_list),l);
                    store_slot(slot,store_slots,stud_list);
					//show_slot_vise(*slot);
                    break;
                }
                ((SLOT*)(b->data))->slot_no=num;
            }
            pLoc=pLoc->link;
        }
    }
}
