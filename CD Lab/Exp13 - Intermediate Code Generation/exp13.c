#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct exp{
        int pos;
        char op;
}k[10];

void find();
void explore();
void fleft(int);
void fright(int);

int i=0,j=0,tmpch=90;
char str[100],left[25],right[25];
int main(){
        printf("Enter expression : ");
        scanf("%s",str);
        printf("Intermediate Code\tExpression\n");
        find();
        explore();
}

void find(){
        for(i=0;str[i]!='\0';i++){
                if(str[i]==':'){
                        k[j].pos=i;
                        k[j++].op=':';
                }
        }
        for(i=0;str[i]!='\0';i++){
                if(str[i]=='/' || str[i]=='*'){
                        k[j].pos=i;
                        if(str[i]=='/') k[j++].op='/';
                        else k[j++].op='*';
                }
        }
        for(i=0;str[i]!='\0';i++){
                if(str[i]=='+' || str[i]=='-'){
                        k[j].pos=i;
                        if(str[i]=='+') k[j++].op='+';
                        else k[j++].op='-';
                }
        }
}

void explore(){
        i=1;
        while(k[i].op!='\0'){
                fleft(k[i].pos);
                fright(k[i].pos);
                str[k[i].pos]=tmpch--;
                printf("%c := %s%c%s\t\t",str[k[i].pos],left,k[i].op,right);
                for(j=0;j<strlen(str);j++){
                        if(str[j]!='$') printf("%c",str[j]);
                }
                printf("\n");
                i++;
        }
        fright(-1);
        fleft(strlen(str));
        printf("\t%s := %s\n",right,left);
}

void fleft(int x){
        int w=0,flag=0;
        x--;
        while(x!=-1 && str[x]!='+' && str[x]!='-' && str[x]!='*' && str[x]!='/' && str[x]!=':' && str[x]!='\0' && str[x]!='='){
                if(str[x]!='$' && flag==0){
                        left[w++]=str[x];
                        left[w]='\0';
                        str[x]='$';
                        flag=1;
                }
                x--;
        }
}
void fright(int x){
        int w=0,flag=0;
        x++;
        while(x!=-1 && str[x]!='+' && str[x]!='-' && str[x]!='*' && str[x]!='/' && str[x]!=':' && str[x]!='\0' && str[x]!='='){
                if(str[x]!='$' && flag==0){
                        right[w++]=str[x];
                        right[w]='\0';
                        str[x]='$';
                        flag=1;
                }
                x++;
        }
}
