#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"

//this function get in an array of decibel values and find out
//the number of peaks in this array
int findPeaks(int d[]){
	int i, c=0;
	for(i=1;i<80;i++){
		if(d[i]>=75 && d[i-1]<75)  c++;
	}
	if(d[0]>=75)  c++;
	return c;
}

void showID(char*idname, char *id){
	int i;
	printf("%s : ",idname);
	for(i=0;i<4;i++){
		printf("%c",id[i]);
		puts("");
	}
}

//this function gets one second of samples (16000), and calculats
//80 pieces pof decibel values, we know we need to calculate one decibel value 
//from 200 sample, decibel value is calculated by RMS formula
void displayWAVDATA(short s[]){
	double rms[80];
	int db[80];//forh decibal values
	short *ptr = s;//we use a pointer, pointing to the beginning of array
	int i,j; // for the nested loop counters, outer loop repeats 80 times
		//inner loop repeats 200 times

	for(i=0;i<80;i++){
		double sum = 0;//accumulate sum of square
		for(j=0;j<200;j++){
			sum += (*ptr) * (*ptr);
			ptr++; //poiting to the next sample
		}
		rms[i] = sqrt(sum/200);
		db[i]=20*log10(rms[i]);
#ifdef DEBUG
		printf("rms[%d] = %f\n",i,rms[i]);
#endif
	}
#ifndef DEBUG
	barChart(db);
	int peaks = findPeaks(db);//get the numbers of peaks and set the colors
	setColors(WHITE,bg(BLACK));
	printf("\033[1;41H");//go to the row 1 and column 1
	printf("Peaks: %d        \n",peaks);
#endif
}

void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("ID",h.ChunkID);
	printf("Chunk size: %d\n",h.ChunkSize);
	showID("Format",h.Format);
	showID("Subchunk1ID",h.Subchunk1ID);
	printf("Subchunk1 size: %d\n",h.Subchunk1Size);
	printf("Audio format: %d\n",h.Format);
	printf("Num. of channels: %d\n",h.NumChannels);
	printf("Sample Rate: %d\n",h.SampleRate);
	printf("Byte Rate: %d\n",h.ByteRate);
	printf("Block align: %d\n",h.BlockAlign);
	printf("Bits per sample: %d\n",h.BitsPerSample);
	showID("Subchunk2ID ",h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);
#else 
	setColors(RED, bg(BLUE));
	printf("\033[1;1H");
	printf("test.wav                    \n");
	setColors(YELLOW,bg(GREEN));
	printf("\033[1;21H");
	printf("Sample rate= %d               \n",h.SampleRate);
	setColors(WHITE, bg(CYAN));
	printf("\033[1;61H"); 
	printf("Duration=%.2f                    \n",(float)h.Subchunk2Size/h.ByteRate);
#endif
}

void fillID(char *dst,const char*m){
	for(int i=0;i<4;i++)
		*dst++=*m++;
}

void testTone(int chan, int fre, float d){
	if(fre<30 || fre>16000){
		printf("frequency is out of range.\n");
		return;
	}
	if(chan<1 || chan>2){
		printf("Number of channels is not okay.\n");
		return;
	}
	if(d<1 || d>10){
		printf("Duration is not okay.\n");
		return;
	}
	struct WAVHDR h;
	int samples = d*44100;
	fillID(h.ChunkID,"RIFF");
	fillID(h.Format,"WAVE");
	fillID(h.Subchunk1ID,"fmt ");
	fillID(h.Subchunk2ID,"data");
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = chan;
	h.SampleRate = 44100;
	h.BitsPerSample = 16;
	h.ByteRate = h.SampleRate * chan * h.BitsPerSample/8;
	h.BlockAlign = chan * h.BitsPerSample/8;
	h.Subchunk2Size = d * h.SampleRate * h.BlockAlign;
	h.ChunkSize = h.Subchunk2Size + 36;
	//PREPARE SOUND DATA	
	FILE *fp = fopen("testTone.wav","w");
	if(fp == NULL){
		printf("we cannot open the file \n");
		return;
	}
	fwrite(&h,sizeof(h),1,fp);//write the header
	for (int i=0;i<d*h.SampleRate;i++){
		short data =32767.0*sin(2*PI*i*fre/44100);
		fwrite(&data,sizeof(short), 1,fp);
		if(chan==2){
			short dR = 32767.0*sin(2*PI*i*fre/2/44100);
			fwrite(&dR,sizeof(short),1,fp);
		} 
	}
	fclose(fp);
	printf("Test tone is generated!\n");
}

