#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>

void swap_process(int array[][3], int row1, int row2, int n) {
	int temp;
	for (int i = 0; i < n; i++) {
		temp = array[row1][i];
		array[row1][i] = array[row2][i];
		array[row2][i] = temp;
	}
}

void sort(int array[][3], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (array[j][1] > array[j + 1][1]) {
				swap_process(array, j, j + 1, 3);
			}
		}
	}
}

void round_robin(int arr[][3], int n, int quantum) {
    // Sort processes by arrival time
    sort(arr, n);

    int completionTime[n], turnaroundTime[n], waitingTime[n];
    int remainingTime[n];
    int currentTime = 0, completed = 0, ganttIndex = 0;
    int ganttProcess[100], ganttTime[100];

    for (int i = 0; i < n; i++) {
        remainingTime[i] = arr[i][2];
    }

    int i = 0;
    while (completed != n) {
        if (remainingTime[i] > 0 && arr[i][1] <= currentTime) {
            ganttProcess[ganttIndex] = arr[i][0];
            ganttTime[ganttIndex] = currentTime;
            ganttIndex++;

            if (remainingTime[i] > quantum) {
                remainingTime[i] -= quantum;
                currentTime += quantum;
            } else {
                currentTime += remainingTime[i];
                remainingTime[i] = 0;
                completed++;
                completionTime[i] = currentTime;
                turnaroundTime[i] = completionTime[i] - arr[i][1];
                waitingTime[i] = turnaroundTime[i] - arr[i][2];
            }
        } else if (arr[i][1] > currentTime) {
            ganttTime[ganttIndex] = currentTime;
            ganttProcess[ganttIndex] = -1; // Idle process
            ganttIndex++;
            currentTime++;
        }
        i = (i + 1) % n;
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i][0], arr[i][1], arr[i][2], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    float sumWT = 0;
    for (i = 0; i < n; i++) {
        sumWT += waitingTime[i];
    }
    float avgWT = sumWT / n;
    printf("Average Waiting Time: %.2f\n", avgWT);

    printf("\nGantt Chart\n");
    for (i = 0; i < ganttIndex; i++) {
        if (i == 0 || ganttProcess[i] != ganttProcess[i - 1]) {
            if (ganttProcess[i] == -1) {
                printf("| Idle ");
            } else {
                printf("| P%d ", ganttProcess[i]);
            }
        }
    }
    printf("|\n");
    for (i = 0; i < ganttIndex; i++) {
        if (i == 0 || ganttProcess[i] != ganttProcess[i - 1]) {
            printf("%d ", ganttTime[i]);
        }
    }
    printf("%d\n", currentTime);
}

int main() {
    int process;
    printf("Enter the number of processes:\n");
    scanf("%d", &process);

    int quantum;
    printf("Enter the time quantum:\n");
    scanf("%d", &quantum);

    int array[process][3];
    for (int i = 0; i < process; i++) {
        array[i][0] = i + 1;  // Process ID
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d", &array[i][1], &array[i][2]);
    }

    printf("ProcessNo\tArrivalTime\tBurstTime\n");
    for (int i = 0; i < process; i++) {
        printf("%d\t\t%d\t\t%d\n", array[i][0], array[i][1], array[i][2]);
    }

    // Call round robin function
    round_robin(array, process, quantum);

    return 0;
}
