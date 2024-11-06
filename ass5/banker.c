	#include <stdio.h>

int issafe(int allot[][10], int max[][10], int need[][10], int n, int m, int avail[]) {
    int finish[10] = {0};
    int work[10];
    int safeseq[10];

    // Initialize work array with available resources
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        printf("count %d",count);
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int j;
                // Check if need of process p is less than or equal to work
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                // If all resources can be allocated to this process
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allot[p][k];
                    }
                    safeseq[count++] = p;
                    finish[p] = 1;
                    found = 1;

                    // Print current state
                    printf("Process P%d has finished; Work resources now: ", p);
                    for (int k = 0; k < m; k++) {
                        printf("%d ", work[k]);
                    }
                    printf("\n");
                }
            }
        }

        if (found == 0) {
            printf("System is not in a safe state\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeseq[i]);
    }
    printf("\n");
    return 1;
}

void requestResource(int allot[][10], int max[][10], int need[][10], int n, int m, int avail[]){
	int req[m];
	int process;
	printf("Enter the process no between 0 to %d :\n",n-1);
	scanf("%d",&process);
	printf("Enter the requested resource for process %d",process);
	for(int i=0;i<m;i++){
		scanf("%d",&req[i]);
	}
	
	for(int i=0;i<m;i++){
		if(req[i]>need[process][i]){
			printf("process exceeeded its maximum claim");
			return ;
		}
	}
	for(int i=0;i<m;i++){
		if(req[i]>avail[i]){
			printf("process exceeeded its maximum claim");
			return ;
		}
	}
	for(int i=0;i<m;i++){
		avail[i]+=req[i];
		allot[process][i]-=req[i];
		need[process][i]+=req[i];
	}
	if(issafe(allot, max, need, n, m, avail)){
		printf("\nResources allocated successfully.\n");
	}
	else{
		 printf("\nSystem is unsafe after allocation. Rolling back request.\n");
        for (int i = 0; i < m; i++) {
            avail[i] += req[i];
            allot[process][i] -= req[i];
            need[process][i] += req[i];
        }
        }
       }
       
	

	
			


int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int allot[n][10];
    int max[n][10];
    int need[n][10];
    int avail[10];

    printf("Enter the available resources (one for each type): ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    printf("\nEnter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    printf("\nEnter the maximum resources needed by each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Call issafe function
    issafe(allot, max, need, n, m, avail);
    requestResource(allot, max, need, n, m, avail);

    return 0;
}

