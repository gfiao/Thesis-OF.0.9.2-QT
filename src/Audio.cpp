using namespace std;

#include "Audio.h"
#include <iostream>

//code based on http://ofdsp.blogspot.pt/2011/07/loading-wav-file-with-sndfilehandle.html
Audio::Audio(const char* fileName) {
	maxValue, minValue = 0;

	//Bit rate = (bit depth) x (sampling rate) x (number of channels)
	SndfileHandle myf = SndfileHandle(fileName);

	printf("Opened file '%s'\n", fileName);
	printf("    Sample rate : %d\n", myf.samplerate());
	printf("    Channels    : %d\n", myf.channels());
	printf("    Error       : %s\n", myf.strError());
	printf("    Frames     : %d\n", int(myf.frames()));

	//read all of the frames to a array of floats
	float* frames = new float[myf.channels() * myf.frames()];
	myf.readf(frames, myf.frames());

	for (int i = 0; i < myf.frames(); i += myf.samplerate()) {
		float sum = 0;
		for (int j = i; j < i + myf.samplerate(); j++) {
			sum += frames[j];
		}
		//multiply by 1000 so we can have readable values
		float normalizedValue = float(sum / myf.samplerate()) * 1000;
		samples.push_back(normalizedValue);

		if (normalizedValue > maxValue)
			maxValue = normalizedValue;
		if (normalizedValue < minValue)
			minValue = normalizedValue;
	}

	//cout << "MaxValue:  " << maxValue << endl;
	//cout << "MinValue:  " << minValue << endl;

	cout << "  Samples Size:   " << samples.size() << endl;

	//for (int i = 0; i < samples.size(); i++)
		//cout << samples[i] << "  ===========  " << convertToDb(samples[i]) << endl;
	//cout << samples[i] << endl;

	cout << "Audio Loaded\n" << endl;

}

vector<float> Audio::getSamples() {
	return samples;
}

float Audio::getMaxValue() {
	return maxValue;
}

float Audio::getMinValue() {
	return minValue;
}

float Audio::convertToDb(float sample) {
	return 20 * log10f(abs(sample));
}