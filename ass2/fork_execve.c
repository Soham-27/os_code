#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void bubble_sort(int numbers[],int number){
	for(int i=0;i<number;i++){
		for(int j=0;j<number-i-1;j++){
			if(numbers[j]>numbers[j+1]){
				int temp=numbers[j+1];
				numbers[j+1]=numbers[j];
				numbers[j]=temp;
			}
		}
	}
}

int main(){
	int n;
	int numbers[100];
	printf("enter the no of numbers : \n");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&numbers[i]);
	}
	
	pid_t pid=fork();
	if(pid<0){
		printf("Error in creating fork");
	}
	if(pid==0){
		char  arr_str[n][100];
		char* args[n+2];
		
		args[0]="./process";
		for(int i=0;i<n;i++){
			sprintf(arr_str[i],"%d",numbers[i]);
			args[i+1]=arr_str[i];
		}
		args[n+1]=NULL;
		
		execve(args[0],args,NULL);
		perror("execve");
		exit(1);
	}
	else{
		bubble_sort(numbers,n);
		wait(NULL);
		printf("Parent process ID : %d",getpid());
	}
}

		
