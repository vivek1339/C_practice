#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>
void remap(int);
int get_key(char*);
void increse_size();
void insert(char*,int);
typedef struct Entry{
	int full;
	char st[100];
}entry;
entry* table;
int size=0,capacity=10;
int link[10]={-1};
int get_key(char* st)
{
	int i=0,sum=0;
	int p=1;
	//printf("%d\t",strlen(st));
	for(i=0;i<strlen(st);i++){
		sum+=(int)st[i]*p ;
		p*=2;
	//printf("%d\n",sum);
	
	}
	return sum%capacity;
}
void increse_size()
{
	int i=0;
	table=realloc(table,2*capacity);
	for(i=capacity;i<2*capacity;i++){
		(table+i)->full=0;
		//printf("%d made 0\n",i);
	}
	capacity*=2;
	//for(i=0;i<capacity;i++)
	//		printf("%d\n",(table+i)->full);
	//printf("%d\n",capacity);
	
	remap(capacity/2);
	
}
void insert(char* st,int key)
{	
	//printf("%d\n",key);
	if(size<capacity && (table+key)->full==0){
		strcpy((table+key)->st,st);
		(table+key)->full=1;
		//printf("%d made 1\n",key);
		size++;
		//printf("Inserted  %s at %d with full as %d\n",st,key,(table+key)->full);
	}
	else if((table+key)->full!=0 && strcmp(st,(table+key)->st)==0){
		printf("Duplicate string: %s\n",st);
	}
	else{
		////printf("%s insert %d\n",st,key);

		//printf("  %s %d\n",(table+key)->st,get_key((table+key)->st));
		increse_size();
		insert(st,get_key(st));
	}

}
void remap(int cap)
{
	//printf("here\n");
	int i=0;
	char str[100];
	//printf("%d",(table+i)->full);
	//printf("cap  %d\n",cap);
	for(i=0;i<cap;i++){
		//printf("iii %d\n",i);
		if((table+i)->full!=0){
			(table+i)->full=0;
			strcpy(str,(table+i)->st);
			strcpy((table+i)->st,"\0");
			insert(str,get_key(str));

		}
	}
	
	//printf("Remap done\n");   
}
int main(void)
{
	FILE* fp; 
	int i=0;
	table=malloc(10*sizeof(entry));
	fp=fopen("strings.txt","r");
	char st[100];
	while(fscanf(fp,"%s",st)!=EOF){
		//printf("%s ^^^^%d\n",st,get_key(st));
		insert(st,get_key(st));
		//printf("done insert on %s\n",st);
	}
	for(i=0;i<capacity;i++){
		if((table+i)->full==1)
			printf("%d %s\n",i,(table+i)->st);
	}
	//printf("%d\n",get_key("afuicgpsdvascvg\n"));
}
