#include<stdio.h>

int issafe(int max[][100], int allot[][100], int avail[], int need[][100], int num_resources, int num_processes) {
    int finish[10] = {0};
    int work[10];
    int safeseq[10];
    
    // Initialize work with available resources
    for(int i = 0; i < num_resources; i++) {
        work[i] = avail[i];
    }
    
    int count = 0;
    while(count < num_processes) {
        int found = 0;
        
        for(int p = 0; p < num_processes; p++) {
            if(finish[p] == 0) {  // Process is not yet finished
                int i;
                for(i = 0; i < num_resources; i++) {
                    if(need[p][i] > work[i]) {
                        break;
                    }
                }
                
                // If all resources of process p can be satisfied
                if(i == num_resources) {
                    for(int k = 0; k < num_resources; k++) {
                        work[k] += allot[p][k];
                    }
                    safeseq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        
        // If no process could be completed in this round, not safe
        if(found == 0) {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }
    
    // Safe sequence found
    printf("The system is in a safe state.\n");
    printf("Safe Sequence is [ ");
    for(int i = 0; i < num_processes; i++) {
        printf("P%d ", safeseq[i]);
    }
    printf("]\n");
    return 1;
}

void resource_request(int max[][100], int allot[][100], int avail[], int need[][100], int num_resources, int num_processes) {
        printf("enter the process between 0 to %d ",num_processes-1);
        int process;
        scanf("%d",&process);
        int req[num_resources];
        printf("Enter the requested resources for process %d:\n", process);
            for(int i = 0; i < num_resources; i++) {
            scanf("%d", &req[i]);
        }
        for(int i = 0; i < num_resources; i++) {
        if(req[i] > need[process][i]) {
            printf("Error: Process exceeded its maximum claim.\n");
            return;
        }
        for(int i = 0; i < num_resources; i++) {
        if(req[i] > avail[i]) {
            printf("Error: Requested resources not available.\n");
            return;
        }
        }
        for(int i = 0; i < num_resources; i++) {
            avail[i] -= req[i];
        allot[process][i] += req[i];
        need[process][i] -= req[i];
        }
         if(issafe(max, allot, avail, need,num_resources,num_processes)) {
        printf("\nResources allocated successfully.\n");
         } else {
        printf("\nSystem is unsafe after allocation. Rolling back request.\n");
        // Roll back the allocation
        for(int i = 0; i < num_resources; i++) {
            avail[i] += req[i];
            allot[process][i] -= req[i];
            need[process][i] += req[i];
        }
    }

    }

}

int main() {
    int num_resources, num_processes;
    
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    
    int allot[num_processes][100];
    int max[num_processes][100];
    int need[num_processes][100];
    int avail[100];
    
    printf("Enter the available resources:\n");
    for(int i = 0; i < num_resources; i++) {
        scanf("%d", &avail[i]);
    }
    
    printf("Enter the allocated resources for each process:\n");
    for(int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for(int j = 0; j < num_resources; j++) {
            scanf("%d", &allot[i][j]);
        }
    }
    
    printf("Enter the maximum resources for each process:\n");
    for(int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for(int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    // Calculate the need matrix
    for(int i = 0; i < num_processes; i++) {
        for(int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
    
    // Check if the system is in a safe state
    issafe(max, allot, avail, need, num_resources, num_processes);
    resource_request(max, allot, avail, need, num_resources, num_processes);

    return 0;
}
