


//this is main.c
#include <stdio.h>
#include "screen.h" //for user-defined header, use double quotes
#include <time.h>
#include <stdlib.h>

int main(){
	int arr[80]; //just for making a bar chart
	srand(time(NULL));
	for(int i=0;i<80;i++)
		 arr[i]=rand()%70+30;//the result is from 30 to 99
	clearScreen();
	setColors(MAGENTA,bg(CYAN));//(fore,back)
	//printf("printed from main.\n");
	barChart(arr);
	resetColors();
	printf("Another message");
	getchar();
}
