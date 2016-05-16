#include "EmotionData.h"
#include <fstream>
#include <iostream>

EmotionData::EmotionData(string filePath, int interval, int minNumEmotions) {

    this->interval = interval;
    maxValue = 0;
    int i = interval;

    cout << "Interval: " << interval << endl;

    ifstream file(filePath);
    string line;
    getline(file, line, '\n'); //skip first line
    vector<string> emotions;

    getline(file, line, '\n'); // read a string until next newline
    int timestamp;
    timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
    bool event = false;
    while (file) {

        //cout <<line << "==============" << AuxFunc::split(line, ':').size() << endl;
        if(AuxFunc::split(line, ':').size() == 2){
            cout << "aqui" << endl;
            event = true;
        }

        while (timestamp < interval && file/*wtf*/) {
            if(AuxFunc::split(line, ':').size() == 1){
                timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());

                if (timestamp >= interval)
                    continue;

                emotions.push_back(AuxFunc::split(line, ';').at(1));

                distinctEmotions.insert(AuxFunc::split(line, ';').at(1));
            }
            getline(file, line, '\n');

        }
        if (emotions.size() >= minNumEmotions) {//dynamic interval
            emotionIntervals.push_back(EmotionInterval(interval, emotions, event));

            if (emotions.size() > maxValue)
                maxValue = emotions.size();

            emotions.clear();
        }
        interval += i;
    }

    //cout << "MaxValue: " << maxValue << endl;
    //cout << emotionIntervals.size() << endl;
    for (EmotionInterval e : emotionIntervals)
        cout << "Timestamp: " << e.getTimestamp() << "  NrEmocoes: " << e.getNumberOfEmotions()
            << "   Event: " << event << endl;

    //for(string s: distinctEmotions)
    //cout << s << endl;

    file.close();
}

vector<EmotionInterval> EmotionData::getEmotionIntervals() {
    return emotionIntervals;
}

int EmotionData::getInterval() {
    return interval;
}

int EmotionData::getMaxValue() {
    return maxValue;
}

set<string> EmotionData::getDistinctEmotions(){
    return distinctEmotions;
}
