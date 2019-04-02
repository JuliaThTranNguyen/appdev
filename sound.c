#include <stdio.h>
#include "sound.h"

void showID(char*idname, char *id){
	int i;
	printf("%s: ",idname);
	for(i=0;i<4;i++){
		printf("%c",id[i]);
		puts("");
	}
}
void displayWAVHDR(struct WAVHDR h){
	showID("ChunkID",h.ChunkID);
	printf("Chunk size: %d\n",h.ChunkSize);
	showID("Format",h.Format);
	showID("Subchunk1ID: %d\n",h.Subchunk1ID);
	printf("Subchunk1 size: %d\n",h.Subchunk1Size);
	printf("Audio format: %d\n",h.Format);
	printf("Num. of channels: %d\n",h.NumChannels);
	printf("Sample Rate: %d\n",h.SampleRate);
	printf("Byte Rate: %d\n",h.ByteRate);
	printf("Block align: %d\n",h.BlockAlign);
	printf("Bits per sample: %d\n",h.BitsPerSample);
	showID("Subchunk2ID",h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);

}
