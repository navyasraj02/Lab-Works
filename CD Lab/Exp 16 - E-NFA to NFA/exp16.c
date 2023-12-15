//-----------------CODE NOT WORKING---------------------

#include<stdio.h>
#include<stdlib.h>

struct node{
        int st;
        struct node *link;
};

void find_closure(int,int);
void insert_transition(int,char,int);
int find_alpha(char);
void print_state(int);
void find_final_state(void);
void union_closure(int);

static int c,start,set[20],b,f,buffer[20],final[20],noalpha,nostates,notrans,nofinals;
char alpha[20];
static int e_closure[20][20]={0};
struct node *transitions[20][20]={NULL};

int main(){
        int i,j,k,m,n,t;
        struct node *temp;
        printf("Enter #alpha : ");
        scanf("%d",&noalpha);
        getchar();
        printf("Enter alphabets (e in last) : ");
        for(i=0;i<noalpha;i++){
                alpha[i]=getchar();
                getchar();
        }
        printf("Enter #states : ");
        scanf("%d",&nostates);
        printf("Enter start state : ");
        scanf("%d",&start);
         printf("Enter #final states : ");
        scanf("%d",&nofinals);
        printf("Enter final states :");
        for(i=0;i<nofinals;i++){
                scanf("%d",&final[i]);
        }
        printf("Enter #transitions : ");
        scanf("%d",&notrans);
        printf("Enter transitions (bs,alpha,es) :\n");
        for(i=0;i<notrans;i++){
                scanf("%d %c%d",&b,&c,&f);
                insert_transition(b,c,f);
        }
        for(i=1;i<=nostates;i++){
                c=0;
                for(j=0;j<20;j++){
                        buffer[j]=0;    //**
                        e_closure[i][j]=0;
                }
                find_closure(i,i);
        }
        printf("-----NFA without Epsilon transitions-----\n");

        //1. START STATE
        printf("Start state :");
        print_state(start);

        //2. ALPHABETS
        printf("\nAlphabets : ");
        for(i=0;i<noalpha;i++)
                printf("%c ",alpha[i]);

        //3. STATES
        printf("\nStates : ");
        for(i=1;i<=nostates;i++)
                print_state(i);

        //4. TRANSITIONS
        printf("\nTransitions :\n");
        for(i=1;i<=nostates;i++){
                for(j=0;j<noalpha-1;j++){
                        for(m=1;m<=nostates;m++)
                                set[m]=0;

                        for(k=0;e_closure[i][k]!=0;i++){    //INDICES**
                                t=e_closure[i][k];
                                temp=transitions[t][j];      //INDICES**
                                while(temp!=NULL){
                                        union_closure(temp->st);   //**
                                        temp=temp->link;
                                }
                        }
                        printf("\n");
                        print_state(i);                 printf(" %c\t",alpha[j]);       //**
                        printf("{ ");
                        for(n=1;n<=nostates;n++){
                                if(set[n]!=0)           //CONDITION**
                                        printf("q%d, ",n);
                        }
                        printf("}");
                }
        }

        //5. FINAL STATES
        printf("\nFinal states : ");
        find_final_state();
}

void find_closure(int x,int sta){
        struct node *temp;
        if(buffer[x])
                return;
        e_closure[sta][c++]=x;
        buffer[x]=1;

        if(alpha[noalpha-1]=='e' && transitions[x][noalpha-1]!=NULL){   //IF (not WHILE)**
                temp=transitions[x][noalpha-1];         //**

                while(temp!=NULL){
                        find_closure(temp->st,sta);     //**
                        temp=temp->link;
                }
        }
}

void insert_transition(int b,char c,int f){
        int j=find_alpha(c);
        struct node *temp;
        if(j==999){
                printf("Wrong char entered\n");
                exit(0);
        }

        temp=(struct node *)malloc(sizeof(struct node *));
        temp->st=f; //st corresponds to final state
        temp->link=transitions[b][j]; //link corresponds to transition[begin_state,alpha_index]
        transitions[b][j]=temp; //link  established !!
}


int find_alpha(char c){
        for(int i=0;i<noalpha;i++){
                if(alpha[i]==c) return i;
        }
        return 999;
}


void print_state(int i){
        int j=0;
        printf("{");
       if(e_closure[i][j]!=0)
                        printf("q%d,",e_closure[i][0]);
         printf("}\t");

}

void find_final_state(void){
        for(int i=0;i<nofinals;i++){
                for(int j=1;j<=nostates;j++){
                        for(int k=0;e_closure[j][k]!=0;k++){    //**
                                if(final[i]==e_closure[j][k])
                                        print_state(j);
                        }
                }
        }
}

void union_closure(int i){
        int j=0,k;
        while(e_closure[i][j]!=0){
                k=e_closure[i][j];
                set[k]=1;
                j++;
        }
}
