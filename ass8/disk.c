#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sstf(int request[], int no_req, int head) {
    int sequence_index = 0;
    int completed[100] = {0}; // Initialize all to 0
    int current = head;
    int seek_sequence[100];
    int total_time = 0;

    seek_sequence[sequence_index++] = current;
    printf("Here is the SSTF Sequence:\n");
    printf("%d", current);

    for (int i = 0; i < no_req; i++) {
        int min_seek_time = 1e9;
        int min_index = -1;

        for (int j = 0; j < no_req; j++) {
            if (!completed[j]) {
                int seek_time = abs(request[j] - current);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    min_index = j;
                }
            }
        }

        if (min_index == -1) {
            break;
        }

        completed[min_index] = 1;
        current = request[min_index];
        seek_sequence[sequence_index++] = current;
        total_time += min_seek_time;

        printf(" %d", current);
    }
    
    printf("\nTotal Seek Time: %d\n", total_time);
}
void scan(int request[],int no_req,int head,int track){
    int i,total_time=0;
    int current=head;
    int index=0;
    for(int i=0;i<no_req;i++){
        if(head<request[i]){
            index=i;
            break;
        }
    }
    printf("\n Scan Sequence ");
    for(i=index;i<no_req;i++){
            printf("%d",request[i]);
            total_time+=abs(request[i]-current);
            current=request[i];
    }
    printf("%d",track-1);
    total_time+=abs(current-(track-1));
    current=track-1;
    for(int i=index-1;i>=0;i--){
        printf("%d",request[i]);
        total_time+=abs(current-request[i]);
        current=request[i];
    }
    printf("total seek time %d",total_time);

}

void clook(int request[],int no_req,int head,int track){
    int i,total_time=0;
    int current=head;
    int index=0;
    for(int i=0;i<no_req;i++){
        if(head<request[i]){
            index=i;
            break;
        }
    }
    printf("\n CLOOK Sequence ");
    for(i=index;i<no_req;i++){
            printf("%d",request[i]);
            total_time+=abs(request[i]-current);
            current=request[i];
    }
    if(index>0){
        total_time=abs(current-request[0]);
        current=request[0];
        for(int i=0;i<index;i++){
        printf("%d",request[i]);
        total_time+=abs(request[i]-current);
        current=request[i];
    }
    }
    
    printf("total seek time %d",total_time);

}
int main() {
    int track, no_req, head1, choice;
    
    printf("Enter total number of tracks: ");
    scanf("%d", &track);
    
    printf("Enter total number of disk requests: ");
    scanf("%d", &no_req);

    int diskRequired[no_req]; // Define after no_req is initialized

    printf("Enter disk requests:\n");
    for (int i = 0; i < no_req; i++) {
        scanf("%d", &diskRequired[i]);
    }

    qsort(diskRequired, no_req, sizeof(int), compare);

    printf("Enter current head position: ");
    scanf("%d", &head1);

    while (1) {
        printf("\nMenu:\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-LOOK\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(diskRequired, no_req, head1);
                printf("\n--------------------------------------------------------------------\n");
                break;
            // Uncomment and define cases 2 and 3 if needed
            case 2:
                scan(diskRequired, no_req, head1, track);
                printf("\n--------------------------------------------------------------------\n");
                break;
            case 3:
                clook(diskRequired, no_req, head1,track);
                printf("\n--------------------------------------------------------------------\n");
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Enter a valid choice.\n");
        }
    }
    return 0;
}
