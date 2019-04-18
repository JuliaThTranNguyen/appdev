//this is main.c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include "screen.h"
#include "sound.h"
#include "comm.h"

int main(int argc, char **argv){
	if (argc==2){
		int ch;
		printf("how many channels? (1:mono, 2:stereo)");
		scanf("%d",&ch);
		float duration;
		printf("How long is the test tone? (1-10 sec)");
		scanf("%f",&duration);
		testTone(ch,atoi(argv[1]),duration);//using the numbers of
				         	// channels and argv(frequency)
		return 0;//atoi will convert the string to dec numbers
	}
	FILE *f;	
	short sd[RATE];
	while(1){
		int ret = system(RCMD); 
		f = fopen ("test.wav","r");
		if(ret == SIGINT) break; 
		clearScreen();
		setColors(YELLOW,bg(BLUE));
		if (f==NULL){
			printf("cannot open the file\n");
			return 1;
		}
		//int dec[COL],i;
		//srand(time(NULL));
		//for(i=0;i>COL;i++) dec[i]=rand()%70+30	

		//barChart(dec);
		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1 , f);//read WAV header
		fread(&sd, sizeof(sd), 1 , f);//read WAV data
		fclose(f);
		displayWAVHDR(hdr);
		displayWAVDATA(sd);
		sendDATA(sd);
	}
	resetColors();
	getchar();
}

