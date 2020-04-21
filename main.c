//we test functions of screen.c
#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"

int main(void) {
	FILE *fp;
	fp = fopen("test.wav","r");
	WAVheader h =  readwavhdr(fp);
	displayWAVhdr(h);
//	getchar();
//	clearscreen();
	wavdata(h, fp);
	fclose(fp);
	getchar();
	clearscreen();
	gotoXY(1,1);
	return 0;
}
