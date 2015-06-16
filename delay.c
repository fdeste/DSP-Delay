#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "delay.h"

#define MAX_DELAY_LENGTH 44100

float buffer[MAX_DELAY_LENGTH*4];
int offsetIndex;
int currentIndex;
int bufferLength;
int delay_length;
double feedbackLevel;
double delayLevel;

void initDelay(){

	int i = 0;
	for ( i = 0 ; i < MAX_DELAY_LENGTH; i++) buffer[i] = 0;

	offsetIndex = 44100/2;
	currentIndex = 0;
	bufferLength = 44100;
	feedbackLevel = 0.7;
	delayLevel = 0.9;
	
	
}




void resetDelayCoutners()
{
	currentIndex = 0;
	offsetIndex = bufferLength/2;
}

int getDelayLength(){

	//return 2;
	return delay_length;
	
}

double getValue(){
	return 0.2;
}

double getFeedBackLevel(){

	double feed = 0.5;

	return feed;
	//return feedbackLevel;
}

void setFeedBackLevel(double new_feedback){
	feedbackLevel = new_feedback;
}

void setDelayParams(int new_length, int bpm){


	double ratio = 60 / (double) bpm *4 *44100;
    int beat_duration =   (int) ratio / 8;
	bufferLength = beat_duration / 16 * new_length * 2;
	
	// find clostest power of two
	unsigned int v; // compute the next highest power of 2 of 32-bit v
/*
	v = bufferLength;
	
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	*/
	
	//bufferLength = v;
	currentIndex = 0;
	offsetIndex = bufferLength;
	delay_length = new_length;
	
}

void delayProcess(const float *input, float *output, long sampleFrames) 

{ 
    long i; 

    assert(input != NULL); 
    assert(output != NULL);  
    assert(sampleFrames >= 0); 


	
    for(i = 0; i < sampleFrames; i++) 
    { 
        buffer[offsetIndex] *= feedbackLevel;
        buffer[offsetIndex] += input[i] * delayLevel; 

        output[i] += buffer[currentIndex]; 

		if (output[i] >= 1.0) output[i] = 0.99;
		if (output[i] <= -1.0) output[i] = -0.99;

        currentIndex = (currentIndex + 1) % bufferLength; 
        offsetIndex = (offsetIndex + 1) % bufferLength;        
    }    
} 