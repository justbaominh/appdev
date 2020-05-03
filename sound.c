#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"
#include "comm.h"
WAVheader readwavhdr(FILE *fp) {
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}
void displayWAVhdr(WAVheader h) {
	printf("Chunk ID: ");
	for (int i = 0; i < 4; i++) 
		printf("%c",h.chunkID[i]);
	printf("\nChunk size: %d\n", h.chunkSize);
	printf("Num of Channels: %d\n", h.numChannels);
	printf("Sample rate: %d\n", h.sampleRate);
	printf("Block align: %d\n", h. blockAlign);
	printf("Bits per sample: %d\n", h.bitsPerSample);
}
void wavdata(WAVheader h, FILE *fp) {
	// this function will read sound sample from the opened file
	// the samples are calculated in to decibel value using ROOT MEAN SQUARE
	// (RMS) formula. We will display a 5-sec recorded sound into bar chart
	// our sound file uses sample rate of 16000,for 5 seconds, there are
	// 5*16000 = 800000 samples, we want to display into 160 bars
	short samples[500];
	double array[160];
	double max = 0.0;
	int peaks = 0, flag = 0;
	for (int i = 0; i < 160; i++){
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;
		for (int j = 0; j<500; j++) {
			sum += samples[j]*samples[j];
		}
		double re = sqrt(sum/500);
		double result = 20*log10(re);

	if (result > max) max = result;

#ifdef SDEBUG
	printf("db[%d] = %lf\n",i+1, 20*log10(re));
#else
	// displaybar for re value
	if (result > max) max = result;
		if(result > 60){
		if(flag ==0){
			flag=1;
			peaks++;
		}
		setfgcolor(RED);
	}
	else{
		flag=0;
	}
	drawbar(i+1, (int)result/3);
	resetcolor();
#endif
	}
	char sound_data[200];	
	sprintf(sound_data, "peaks=%d&max=%f", peaks, max);
	senddata(sound_data, URL);
	gotoXY(1,1);
	printf("Sample Rate: %d\n", h.sampleRate);
	printf("Duration: %f s\n", (float)h.subchunk2Size/h.byteRate);
	printf("Peaks: %d\n", peaks);
	printf("Maximum decibel value: %lf decibels\n", max);
}
 // end of file 
