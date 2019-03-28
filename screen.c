//we need a set of functions in here
#include <stdio.h>
#include "screen.h"

void barChart(int a[])
{
	int i,j;    //counter for your nested loop
	for(i=0;i<80;i++){
		for(j=0;j<a[i]/3;j++){//every rows is 3 db
			//printf("\033[%d;%dH",j+1,i+1);//j:rows,i:cols,up to down
			printf("\033[%d;%dH",35-j,i+1);//underneath to top
#ifdef UNICODE
			printf("%s","\u2590");//draw a bar chart by 
				              //using unicode table
#else
			printf("%c",' ');//for the terminal doesnt support UNICODE
#endif
		}
	}
}

void clearScreen(void)
{
	printf("\033[2J");//clear the whole screen
	fflush(stdout);   //output the escape sequence immediately
}

void setColors(short fg, short bg)//for foreground and back ground
{
	printf("\033[%d;%d;2m",fg,bg);
	fflush(stdout);
}

void resetColors(void)
{
	//black background and white foreground
	printf("\033[0m");//reset all of the attitudes
	fflush(stdout);
}
