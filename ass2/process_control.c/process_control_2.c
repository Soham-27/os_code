#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void bubble_sort(int arr[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void printarr(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ,",arr[i]);
    }
}
int main(){
    int number;
    printf("Enter the number of element :\n");
    scanf("%d",&number);
    int numbers[100];
    printf("Enter the numbers :");
    for(int i=0;i<number;i++){
        scanf("%d",&numbers[i]);
    }
    pid_t pid=fork();

    if(pid>1){
        printf("Parent process sorting array \n");
        bubble_sort(numbers,number);
        printf("the printed array usin parent process is :\n");
        printarr(numbers,number);
        sleep(10);
        int status;
        wait(&status);
        
        printf("child process finished with process status : %d \n",WEXITSTATUS(status));
    }
    else{
        printf("child process sorting array \n");
        bubble_sort(numbers,number);
        printf("the printed array usin child process is \n");
        printarr(numbers,number);
        exit(0);
    }
}