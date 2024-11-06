#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(){
    int fd_read,fd_write;
    char *myfifo1="/tmp/myfifo1";
    char *myfifo2="/tmp/myfifo2";

    mkfifo(myfifo1,0666);
    mkfifo(myfifo2,0666);

    char str1[180],str2[180];
    FILE *file;
    while(1){
        fd_read=open(myfifo1,O_RDONLY);
        if(fd_read==-1){
            printf("Error in reading file");
        }
        read(fd_read,str1,sizeof(str1));
        printf("message from process 1 %s \n",str1);
        close(fd_read);

        int lines=0;
        int words=0;
        int charceters=0;
        int i=0;
        while(str1[i]!='\0'){
            charceters++;
            if(str1[i]==' ')words++;
            if(str1[i]=='.')lines++;
            i++;
        }
        words++;

        snprintf(str2,sizeof(str2),"words count : %d \n Lines Count : %d \n Charcters Count : %d",words,lines,charceters-1);

        file=fopen("results.txt","a");
        if(file==NULL){
        perror("Error opening file ");
        exit(1);
        }
        fprintf(file,"Message : %s \n%s\n\n",str1,str2);
        fclose(file);
        fd_write=open(myfifo2,O_WRONLY);
        if(fd_write==-1){
            printf("Error in opening file");
        }
        write(fd_write,str2,strlen(str1)+1);
        close(fd_write);



    }
}