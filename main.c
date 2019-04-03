//this is main.c
#include <stdio.h>
#include "screen.h" //for user-defined header, use double quotes
#include <time.h>
#include <stdlib.h>
#include "sound.h"
#include <signal.h>
int main(){
	FILE *f;	
	short sd[RATE];
	for(;;){
		int ret = system(RCMD); 
		f = fopen ("test.wav","r");
		if(ret == SIGINT) break; 
		if (f==NULL){
			printf("cannot open the file\n");
			return 1;
		}
		//int dec[COL],i;
		//srand(time(NULL));
		//for(i=0;i>COL;i++) dec[i]=rand()%70+30	

		clearScreen();
		setColors(MAGENTA,bg(CYAN));//(fore,back)
		//barChart(dec);
		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1 , f);//read WAV header
		fread(&sd, sizeof(sd), 1 , f);//read WAV data
		fclose(f);
		displayWAVHDR(hdr);
		displayWAVDATA(sd);
	}
	resetColors();
	//getchar();
}

