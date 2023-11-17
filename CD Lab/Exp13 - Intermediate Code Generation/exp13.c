#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct exp{
 char op;
 int  pos;
 } k[20];
int i,j=0,tmpch=90,no=0;
char str[100],left[10],right[10],assign;
void fleft(int);
void fright(int);
void findopr();
void explore();
void find();

void main()
{
printf("Enter the expression:");
scanf("%s",str);
assign=str[0];
printf("Intermediate code for corresponding expression is :\n");
find();
explore();
}

void find()
{
for(i=0;str[i]!='\0';i++)
{
	if(str[i]==':'){
		k[j].pos=i;
		k[j++].op=':';
	}
}

//find position of  the operator /
for(i=0;str[i]!='\0';i++){
	if(str[i]=='/' || str[i] == '*'){
		k[j].pos=i;
    		if(str[i]=='/')
			k[j++].op='/';
     		else
      			k[j++].op='*';
	}
}

for(i=0;str[i]!='\0';i++){
	if(str[i]=='+' || str[i] == '-'){
		k[j].pos=i;
    		if(str[i]=='+') 
     			k[j++].op='+';
     		else
      			k[j++].op='-';
	}
}
}


//the function to explore the expression and break it down to 3 address format
void explore()
{
i=1;
while(k[i].op!='\0'){
 fleft(k[i].pos);
 fright(k[i].pos);
 str[k[i].pos]=tmpch--;
 printf("\t%c := %s%c%s\t",str[k[i].pos],left,k[i].op,right);
 printf("\n");
 i++;
}
fright(-1);
if(no==0){
  fleft(strlen(str));
  printf("\t%c :=%s\n",assign,left);
}
}

void fleft(int x){
int w=0,flag=0;
x--;
while(x!=-1 &&str[x]!='*' && str[x]!='+' && str[x]!='-' && str[x]!='/' && str[x]!=':'){
  if(str[x]!='#' && flag==0) {
  left[w++]=str[x];
  left[w]='\0';
  str[x]='#';
  flag=1;
  }
  x--;
}
}


void fright(int x){
int w=0,flag=0;
x++;
while(x!=-1 &&str[x]!='*' && str[x]!='+' && str[x]!='-' && str[x]!='/' && str[x]!=':'){
    if(str[x]!='#' && flag==0){
	right[w++]=str[x];
 	right[w]='\0';
  	str[x]='#';
   	flag=1;
    }
    x++;
}
}
