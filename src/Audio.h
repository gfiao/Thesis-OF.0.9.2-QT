#pragma once

using namespace std;

#include <vector>
#include <string>
#include "sndfile.h"
#include <iostream>

class Audio {

private:

	//each position in the vector is the second in the audio file
	//ex: samples[329] gives you the data for the second 329
	vector<float> samples;

	//used in the creation of the value plotter
	float maxValue, minValue;

public:
	Audio(const char* fileName);
	vector<float> getSamples();
	float getMaxValue();
	float getMinValue();

    vector<float> setInterval(int interval, int& maxValue);

};
