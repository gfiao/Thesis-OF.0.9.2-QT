#pragma once

using namespace std;

#include <vector>
#include <string>
#include <sstream>
#include "AuxFunc.h"

//Class used to represent the emotions present in a X seconds interval (5 is the default value)
class EmotionInterval {
private:

	int timestamp;
	string dominantEmotion;
	vector<string> emotions;
    float audioValues;

public:

    EmotionInterval(int timestamp, vector<string> emotions);

	int getTimestamp();

	string getDominantEmotion();

	int getNumberOfEmotions();

	vector<string> getEmotions();
    void setEmotions(vector<string> newEmotions);

    void setAudioValues(float newValue);
    float getAudioValues();

};
