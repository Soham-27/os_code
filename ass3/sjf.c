#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>
void swap_process(int array[][3],int row1,int row2,int n){
	int temp;
	for(int i=0;i<n;i++){
		temp=array[row1][i];
		array[row1][i]=array[row2][i];
		array[row2][i]=temp;
	}
}
void sort(int array[][3],int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1-i;j++){
			if(array[j][1]>array[j+1][1]){
				swap_process(array,j,j+1,3);
			}
		}
	}
}

void sjf_preemptive(int array[][3], int process) {
    int completed = 0;
    int completed_time[process];
    int turn_around_time[process];
    int remaining_time[process];
    int waiting_time[process];
    int current_time = 0;
    int last_process = -1;
    
    // Initialize remaining times
    for (int i = 0; i < process; i++) {
        remaining_time[i] = array[i][2];
    }

    // Track Gantt chart details
    int gantprocess[100];
    int ganttime[100];
    int gantindex = 0;

    while (completed != process) {
        int minindex = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with minimum remaining time that has arrived
        for (int i = 0; i < process; i++) {
            if (array[i][1] <= current_time && remaining_time[i] > 0 && remaining_time[i] < minRemainingTime) {
                minindex = i;
                minRemainingTime = remaining_time[i];
            }
        }

        // If no process is available, increment time and continue
        if (minindex == -1) {
            current_time++;
            continue;
        }

        // Update Gantt chart only when switching processes
        if (last_process != minindex) {
            gantprocess[gantindex] = array[minindex][0];
            ganttime[gantindex] = current_time;
            gantindex++;
            last_process = minindex;
        }

        // Execute process for one unit of time
        remaining_time[minindex]--;
        current_time++;

        // If process completes, update completion and waiting times
        if (remaining_time[minindex] == 0) {
            completed++;
            completed_time[minindex] = current_time;
            turn_around_time[minindex] = completed_time[minindex] - array[minindex][1];
            waiting_time[minindex] = turn_around_time[minindex] - array[minindex][2];
        }
    }

    // Print the results table
    printf("Process\tArrival time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < process; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", array[i][0], array[i][1], array[i][2], completed_time[i],
               turn_around_time[i], waiting_time[i]);
    }

    // Calculate and display average waiting time
    float sumWT = 0;
    for (int i = 0; i < process; i++) {
        sumWT += waiting_time[i];
    }
    float avgWT = sumWT / process;
    printf("Average Waiting Time: %.2f\n", avgWT);

    // Print the Gantt chart
    printf("\nGantt Chart\n");
    for (int i = 0; i < gantindex; i++) {
        if (i == 0 || gantprocess[i] != gantprocess[i - 1]) {
            printf("| P%d ", gantprocess[i]);
        }
    }
    printf("|\n");

    for (int i = 0; i < gantindex; i++) {
        if (i == 0 || gantprocess[i] != gantprocess[i - 1]) {
            printf("%d ", ganttime[i]);
        }
    }
    printf("%d\n", current_time);
}

int main(){
	int process;
	printf("enter the number of process :\n");
	scanf("%d",&process);
	int array[process][3];
	for(int i=0;i<process;i++){
		array[i][0]=i+1;
		printf("%d ",i+1);
		scanf("%d",&array[i][1]);
		scanf("%d",&array[i][2]);
		printf("\n");
	}
	printf("ProcessNo	ArriavalTime	BurstTime\n");
	sjf_preemptive(array,process);
	for(int i=0;i<process;i++){
		printf("%d",array[i][0]);
		printf(" %d",array[i][1]);
		printf(" %d",array[i][2]);
		printf("\n");
	}
	return 0;
}
