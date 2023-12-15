#include<stdio.h>
#include<stdlib.h>

struct node{
        int st;
        struct node *link;
};

void find_closure(int,int);
void insert_transition(int,char,int);   //transtions form:b_state,alpha,e_state
int find_alpha(char);   //pass alpha and retun its index;
void print_e_closure(int); //pass state_no

static int b,c,f,noalpha,notrans,nostates,buffer[20];
char alphabet[20]; //to store alphabets
static int e_closure[20][20]={0}; //store e_closure as state_nos
struct node *transition[20][20]={NULL};

void main(){
        int i,j;
        printf("Enter #alphabets : ");
        scanf("%d",&noalpha);
        getchar();
        printf("Enter e for Epsilon and as the last alphabet,if present\n");
        printf("Enter alphabets :");
        for(i=0;i<noalpha;i++){
                alphabet[i]=getchar();
                getchar();  //for enter/space IMP****
        }
        printf("Enter #states : ");
        scanf("%d",&nostates);
        printf("Enter #transitions : ");
        scanf("%d",&notrans);
        printf("Keep State values > 0\n");
        printf("Enter transitions (b_state,alphabet,e_state) :\n");
        for(i=0;i<notrans;i++){
                printf("For trans %d -->",i+1);

                scanf("%d %c%d",&b,&c,&f);   //Space before %c IMP****
                insert_transition(b,c,f);
        }
        printf("e-closure\n");
        for(i=1;i<=nostates;i++){
                c=0;
                for(j=0;j<20;j++){
                        buffer[i]=0;
                        e_closure[i][j]=0;
                }
                find_closure(i,i);
                printf("e-closure (q%d) :",i);
                print_e_closure(i);
        }
}

void insert_transition(int b,char c,int f){
        int j=find_alpha(c);
        struct node *temp;

        //check if entered alphabet is correct
        if(j==999){
                printf("Wrong char entered\n");
                exit(0);
        }

        //initialize temp and assign values
        temp=(struct node *)malloc(sizeof(struct node *));
        temp->st=f; //st corresponds to final state
        temp->link=transition[b][j]; //link corresponds to transition[begin_state,alpha_index]
        transition[b][j]=temp; //link  established !!
}


int find_alpha(char c){
        for(int i=0;i<noalpha;i++){
                if(alphabet[i]==c) return i;
        }
        return 999;
}

void find_closure(int x,int sta){       //x:resulting state from e-trans, s:state under consideration
        struct node *temp;
        if(buffer[x]){
                return;
        }

        //1. Add current state
        //c: counter for #states

        e_closure[sta][c++]=x;       //MAIN STEP
        buffer[x]=1;

        //2. Add e-transtions
        if(alphabet[noalpha-1]=='e' && transition[x][noalpha-1]!=NULL){

                temp=transition[x][noalpha-1]; //set x to resulting state

                //until temp becomes final state(NULL), continue
                while(temp!=NULL){
                        find_closure(temp->st,sta);
                        temp=temp->link;
                }
        }
}

void print_e_closure(int stateno){
        printf("{ ");
        for(int j=0;e_closure[stateno][j]!=0;j++){
                printf("q%d, ",e_closure[stateno][j]);
        }
        printf("}\n");
}
