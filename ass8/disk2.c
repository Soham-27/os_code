#include <stdio.h>
#include<math.h>
#include<stdlib.h>
void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void bubble_sort(int requests[], int no_req) {
    for (int i = 0; i < no_req - 1; i++) {
        for (int j = 0; j < no_req - 1 - i; j++) {
            if (requests[j] > requests[j + 1]) {
                swap(&requests[j], &requests[j + 1]);
            }
        }
    }
}

void sstf(int request[],int no_req,int head){
    int current=head;
    int sequence_index=0;
    int sequence[100];
    int total_seek_time=0;
    printf("Current is %d",current);
    sequence[sequence_index++]=current;
    int completed[100]={0};
    for(int i=0;i<no_req;i++){
        int min_seek_time=1e9;
        int min_index=-1;
        for(int j=0;j<no_req;j++){
            if(completed[j]==0){
            int seek=abs(request[j]-current);
            if(seek<min_seek_time){
                min_seek_time=seek;
                min_index=j;
            }
            }
        }
        if(min_index==-1){
            break;
        }
        completed[min_index]=1;
        current=request[min_index];
        total_seek_time+=min_seek_time;
        sequence[sequence_index++]=current;
        
    }
    printf("Total Seek time %d \n",total_seek_time);
}
void scan(int request[],int no_req,int head,int track){
    int i,total_time=0;
    track=track-1;
    int current=head;
    int index=0;
    for(int i=0;i<no_req;i++){
        if(request[i]>current){
            index=i;
            break;
        }
    }
    for(int j=index;j<no_req;j++){
        total_time+=abs(request[j]-current);
        current=request[j];
    }


    total_time+=abs(track-current);
    current=track;

    printf("%d",total_time);
    for(int i=index-1;i>=0;i--){
        total_time+=abs(request[i]-current);
        current=request[i];
    }
     printf("Total Seek time %d ",total_time);
}

void clook(int request[],int no_req,int head,int track){
    int current=head;
    int index=0;
    int total_time=0;
    for(int i=0;i<no_req;i++){
        if(request[i]>head){
            index=i;
            break;
        }
    }
    for(int j=index;j<no_req;j++){
        total_time+=abs(request[j]-current);
        current=request[j];
    }
    total_time+=abs(request[0]-current);
    current=request[0];
    for(int i=1;i<=index-1;i++){
        total_time+=abs(request[i]-current);
        current=request[i];
    }
    printf("Total CLOOK Seek time %d ",total_time);


}
int main() {
    int track, No_requests;
    int requests[100]; // Fixed-size array with a maximum limit of 100

    printf("Enter the track for this: ");
    scanf("%d", &track);
    
    printf("Enter the number of requests (max 100): ");
    scanf("%d", &No_requests);

    if (No_requests > 100) {
        printf("Number of requests exceeds the maximum limit of 100.\n");
        return 1;
    }

    printf("Enter the requests: ");
    for (int i = 0; i < No_requests; i++) {
        scanf("%d", &requests[i]);
    }

    bubble_sort(requests, No_requests);

    printf("Sorted requests are: ");
    for (int i = 0; i < No_requests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Enter the head: ");
    int head;
    scanf("%d",&head);
    sstf(requests,No_requests,head);
    scan(requests,No_requests,head,track);
    clook(requests,No_requests,head,track);
    return 0;
}
