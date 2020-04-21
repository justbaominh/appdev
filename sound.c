#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"

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
	
	for (int i = 0; i < 160; i++){
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;
		for (int j = 0; j<500; j++) {
			sum += samples[j]*samples[j];
		}
		double re = sqrt(sum/500);
		array[i] = 20*log10(re);
	}
	int count = 0;
	for (int i = 0; i < 160; i++) {
		if (array[i] > array[i-1] && array[i] < array[i+1]) count +=1;
}
	printf("Duration: %lf\n", (float)h.subchunk2Size/h.byteRate);
	printf("Number of peak: %d", count);
	for (int i = 0; i < 160; i++){
#ifdef SDEBUG
	printf("db[%d] = %lf\n",i+1, 20*log10(re));
#else
	// displaybar for re value
	if(array[i] > 70) {
		setfgcolor(RED);
		drawbar(i+1, (int)array[i]/3);
		resetcolor();
	}
	else drawbar(i+1, (int)array[i]/3);
#endif
	}
}
 // end of file 
