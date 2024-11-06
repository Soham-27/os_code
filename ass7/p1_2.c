#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    int fd_write,fd_read;
    char *myfifo1="/tmp/myfifo1";
    char *myfifo2="/tmp/myfifo2";
    if (mkfifo(myfifo1, 0666) == -1) {
    perror("mkfifo myfifo1");
}
if (mkfifo(myfifo2, 0666) == -1) {
    perror("mkfifo myfifo2");
}



    char str1[180],str2[180];

    while(1){
        printf("Enter message : \n");
        fgets(str1,180,stdin);

        fd_write=open(myfifo1,O_WRONLY);
        if(fd_write==-1){
            printf("Error in opening file");
        }
        write(fd_write,str1,strlen(str1)+1);
        close(fd_write);

        fd_read=open(myfifo2,O_RDONLY);
        if(fd_read==-1){
            printf("Error in reading file");
        }
        read(fd_read,str2,sizeof(str2));
        printf("the message from process 2 :%s\n",str2);
        close(fd_read);

        
    }

}