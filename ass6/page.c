#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>


bool ispresent(int frame[],int framesize,int n){
	for(int j=0;j<framesize;j++){
		if(frame[j]==n){
			return true;
		}
	}
	return false;
}
void fifo(int framesize,int seqlength,int sequence[]){
	int frame[framesize];
    	for (int i = 0; i < framesize; i++) {
        frame[i] = -1;  // Initialize all frame slots as empty
    	}
    	for (int i = 0; i < framesize; i++) {
        	printf("%d \n",frame[i]);  // Initialize all frame slots as empty
    	}
    	float hit=0;
    	int pagefault=0;
    	int startIndex=0;
    	float count=0;
    	for(int j=0;j<seqlength;j++){
    		if(!(ispresent(frame,framesize,sequence[j]))){
    			pagefault++;
    			frame[startIndex]=sequence[j];
    			startIndex=(startIndex+1)%framesize;
			count++;
		}
		else{
			hit++;
		}
		
		printf("fifo frame \n");
		for(int j=0;j<framesize;j++){
			printf("%d   		",frame[j]);
		}
		printf("\n");
	}
	printf("hits : %f \n",hit);
	printf("page Faults : %f \n",count);
	float h_ratio = hit/seqlength;
	float m_ratio = count/seqlength;

	printf("Hit Ratio : %f \n",h_ratio);
	printf("Miss Ratio : %f \n",m_ratio);
}	
		
void lru(int framesize,int seqlength,int sequence[]){
	int lastused[framesize]={};
	int frame[framesize]={};
	for(int i=0;i<framesize;i++){
		lastused[i]=-1;
	}
	for(int i=0;i<framesize;i++){
		frame[i]=-1;
	}
	float count=0;
	float hit=0;
	for(int j=0;j<seqlength;j++){
		int page=sequence[j];
		if(ispresent(frame,framesize,sequence[j])){
			hit++;
			for(int i=0;i<framesize;i++){
				if(frame[i]==page){
					lastused[i]=j;
				}
			}
		}
		else{
			int index;
			if(j>=framesize){
				int min=lastused[0];
				index=0;
				for(int k=1;k<framesize;k++){
					if(lastused[k]<min){	
						min=lastused[k];
						index=k;
					}
				}
			}
			else{
				index=j;
			}
			frame[index]=page;
			lastused[index]=j;
			count++;
		}
		printf("lru frame \n");
		for(int z=0;z<framesize;z++){
			printf("%d   		",frame[z]);
		}
		 printf("LastUsed : [");
            for(int k=0;k<framesize;k++){
            printf("%d ",lastused[k]);

            }
		printf("\n");
	}
	printf("hits : %f \n",hit);
	printf("page Faults : %f \n",count);
	float h_ratio = hit/seqlength;
	float m_ratio = count/seqlength;

	printf("Hit Ratio : %f \n",h_ratio);
	printf("Miss Ratio : %f \n",m_ratio);
	

}
    	

int optimal_page_replacement(int sequence[], int frame[], int frameSize, int seqlength, int starting) {
    int farthest = starting;
    int index = -1;
    
    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = farthest; j < seqlength; j++) {
            if (frame[i] == sequence[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        // If the page is not found in the sequence, return current index
        if (j == seqlength) {
            return i;
        }
    }
    return (index == -1) ? 0 : index; // Fallback in case no farthest index is found
}

void optimal_replacement(int framesize, int seqlength, int sequence[]) {
    int frame[framesize];
    float count = 0;
    float hit = 0;
    
    for (int i = 0; i < framesize; i++) {
        frame[i] = -1;
    }
    
    for (int j = 0; j < seqlength; j++) {
        int page = sequence[j];
        if (ispresent(frame, framesize, page)) {
            hit++;
            continue;
        } else {
            int index;
            if (j < framesize) {
                index = j;
            } else {
                index = optimal_page_replacement(sequence, frame, framesize, seqlength, j + 1);
            }
            frame[index] = page;
            count++;
        }
        
        printf("optimal frame \n");
        for (int z = 0; z < framesize; z++) {
            printf("%d    ", frame[z]);
        }
        printf("\n");
    }
    
    float h_ratio = hit / seqlength;
    float m_ratio = count / seqlength;

    printf("Hit Ratio : %f \n", h_ratio);
    printf("Miss Ratio : %f \n", m_ratio);
}

	
int main(){
	int frameSize;
	printf("\nEnter frame size (minimum 3): ");
    	scanf("%d", &frameSize);
    	if (frameSize < 3) {
        	printf("Frame size must be at least 3.\n");
    	}
    	printf("enter the sequence length\n");
    	int seqlength;
    	scanf("%d",&seqlength);
    	int sequence[seqlength]={};
    	printf("Enter the Sequence \n");
    	for(int i=0;i<seqlength;i++){
    		scanf("%d",&sequence[i]);
    	}
    	
    	int choice;
    	printf("\n Enter your choice \n");
    	scanf("%d",&choice);
    	switch(choice){
    		case 1:
    			fifo(frameSize,seqlength,sequence);
    			break;
    		case 2:
    			lru(frameSize,seqlength,sequence);
    			break;
    		case 3:
    			optimal_replacement(frameSize,seqlength,sequence);
    			break;
    	}	
    	return 0;
  
}
  
