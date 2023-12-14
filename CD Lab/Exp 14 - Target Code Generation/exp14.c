#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
        int i,n,op;
        char opr[4],icode[10][30];
        printf("Enter #lines of ICode : ");
        scanf("%d",&n);
        printf("Enter intermediate code (op,op1,op2,res) :\n");
        for(i=0;i<n;i++){
                printf("For ICode %d --> ",i+1);
                scanf("%s",icode[i]);
        }
        printf("Target Code\n");
        for(i=0;i<n;i++){
                op=icode[i][3];
                if(op=='+') strcpy(opr,"ADD");
                else if(op=='-') strcpy(opr,"SUB");
                else if(op=='*') strcpy(opr,"MUL");
                else if(op=='/') strcpy(opr,"DIV");
                else break;

                printf("MOV R%d,%c\n",i,icode[i][2]);
                printf("%s R%d,%c\n",opr,i,icode[i][4]);
                printf("MOV %c,R%d\n\n",icode[i][0],i);
        }
}
