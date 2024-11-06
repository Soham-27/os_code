#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<stdbool.h>

bool ispresent(int frame[],int framesize,int n){
	for(int j=0;j<framesize;j++){
		if(frame[j]==n){
			return true;
		}
	}
	return false;
}
void fcfs(int framesize,int seqlength,int sequence[]){
    int frame[framesize];
    for(int i=0;i<framesize;i++){
        frame[i]=-1;
    }
    int startIndex=0;
    float hit=0;
    float count=0;
    printf("FCFS Frame \n");
    for(int j=0;j<seqlength;j++){
        int page=sequence[j];
        if(!ispresent(frame,framesize,page)){
            frame[startIndex]=page;
            startIndex=(startIndex+1)%framesize;
            count++;
        }
        else{
            hit++;
        }
        
        printf("Frame : [");
        for(int k=0;k<framesize;k++){
            printf("%d ",frame[k]);

        }
        printf("]\n");
    }
    float h_ratio=hit/seqlength;
    float m_ratio=count/seqlength;
    printf("hit ratio : %f , miss ratio : %f \n",h_ratio,m_ratio);

}

void lru(int framesize,int seqlength,int sequence[]){
    int frame[framesize];
    for(int i=0;i<framesize;i++){
        frame[i]=-1;
    }
    int lastused[framesize];
    for(int i=0;i<framesize;i++){
        lastused[i]=-1;
    }
    int count=0;
    int hit=0;
    printf("LRU Frame \n");
    for(int j=0;j<seqlength;j++){
        int page=sequence[j];
        if(ispresent(frame,framesize,page)){
            hit++;
            for(int k=0;k<framesize;k++){
                if(frame[k]==page){
                    lastused[k]=j;
                    break;
                }
            }
        }
        else{
            int index=0;
            if(j>=framesize){
                int min=lastused[0];
                for(int k=1;k<framesize;k++){
                    if(lastused[k]<min){
                        min=lastused[k];
                        index=k;
                        printf("index %d",index);
                    }
                }
            }
            else{
                index=j;
            }
            frame[index]=page;
            lastused[index]=j;
            count++;
            printf("Frame : [");
            for(int k=0;k<framesize;k++){
            printf("%d ",frame[k]);

            }
            printf("]\n");
             printf("LastUsed : [");
            for(int k=0;k<framesize;k++){
            printf("%d ",lastused[k]);

            }
            printf("]\n");
        }

    }
}
int optimal_replacement_index(int framesize,int sequence[],int seqlength,int starting,int frame[]){
    int farthest=starting;
    int index=-1;
    for(int i=0;i<framesize;i++){
        int j;
        for( j=farthest;j<framesize;j++){
            if(frame[i]==sequence[j]){
                if(farthest<j){
                    farthest=j;
                    index=i;
                }
                break;
            }
        }
        if(j==seqlength){
            return i;
        }
        
    }
    return (index==-1)? 0:index;
}

void optimal_replacement(int framesize,int seqlength,int sequence[]){
    int frame[framesize];
    for(int i=0;i<framesize;i++){
        frame[i]=-1;
    }
    int hit=0;
    int count=0;
    for(int j=0;j<seqlength;j++){
        int page=sequence[j];
        if(ispresent(frame,framesize,page)){
            hit++;
            continue;
        }
        else{
            int index=0;
            if(j<framesize){
                index=j;
            }
            else{
                index=optimal_replacement_index(framesize,sequence,seqlength,j+1,frame);
            }
            frame[index]=page;
            count++;

        }
        printf("Frame : [");
        for(int k=0;k<framesize;k++){
            printf("%d ",frame[k]);

        }
        printf("]\n");


    }
}
int main(){
    int framesize;
    int seqlength;
    
    printf("Enter the framesize \n");
    scanf("%d",&framesize);
    printf("Enter the seqlength \n");
    scanf("%d",&seqlength);
    int sequence[seqlength]={};
    printf("Enter the Sequence \n");
    	for(int i=0;i<seqlength;i++){
    		scanf("%d",&sequence[i]);
	}
    int choice;
    printf("enter your choice : \n");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
        fcfs(framesize,seqlength,sequence);
        break;
        case 2:
        lru(framesize,seqlength,sequence);
        break;
    default:
        optimal_replacement(framesize,seqlength,sequence);
        break;
    }
    return 0;
}