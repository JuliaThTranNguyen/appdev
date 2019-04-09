//const defidefinition
//#define DEBUG

#define RATE 16000	//samples per second
#define DUR 1
#define RCMD "arecord -r16000 -c1 -f S16_LE -d1 -q test.wav"
//data structures
struct WAVHDR{
	char ChunkID[4];//it has to be "RIFF"
	int ChunkSize;//4 bytes number
	char Format[4];//it has to be "WAVE"

	char Subchunk1ID[4];//"fmt"
	int Subchunk1Size; //PCM = 16
	short AudioFormat; //the size should be 1
	short NumChannels; //should be 1 for mono
	int SampleRate;//16000
	int ByteRate;//16000*NumChannels*BisperSample/8
	short BlockAlign;//NUmChannels*BitsperSample/8
	short BitsPerSample;//in our app, 16 (-f S16_LE)

	char Subchunk2ID[4];//"data"
	int Subchunk2Size;
};
//function declaration
void displayWAVHDR(struct WAVHDR);
void showID(char *,char *);
void displayWAVDATA(short []);
