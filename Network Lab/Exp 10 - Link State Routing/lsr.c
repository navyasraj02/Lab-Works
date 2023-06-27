#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
        int src,v,w,min,count,i,j,k,costmatrix[20][20],dist[20],flag[20],last[20];
        printf("Nodes :");
        scanf("%d",&count);
        min=11000;
         printf("Cost matrix :");
        for(i=0;i<count;i++){
                for(j=0;j<count;j++){
                        scanf("%d",&costmatrix[i][j]);
                        if(costmatrix[i][j]<0) costmatrix[i][j]=min;
                }
        }
        printf("Enter source :");
        scanf("%d",&src);
        for(v=0;v<count;v++){
                flag[v]=0;
                dist[v]= costmatrix[src][v];
                last[v]=src;
        }

        flag[src]=1;
        for(i=0;i<count;i++){
                min=1000;
                for(w=0;w<count;w++){
                        if(!flag[w]){
                                if(dist[w]<min){
                                        min=dist[w];
                                        v=w;
                                }
                        }
                }
        }

        flag[v]=1;
        for(w=0;w<count;w++){
                if(!flag[w]){
                        if(dist[w]>min+costmatrix[v][w]){
                                dist[w]=min+costmatrix[v][w];
                                last[w]=v;
                        }
                }
        }
        for(i=0;i<count;i++){
                printf("\n %d===>%d :Path taken : %d",src,i,i);
                w=i;
                while(w!=src){
                        printf("<-- %d",last[w]);
                        w=last[w];
                }
                printf("Shortest path cost :%d\n",dist[i]);
        }
        return 0;
}
