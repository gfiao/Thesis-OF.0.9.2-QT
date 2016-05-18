#include "EmotionData.h"
#include <fstream>
#include <iostream>
#include <algorithm>

EmotionData::EmotionData(string filePath, int interval, int minNumEmotions) {

    /* ifstream file(filePath); //read JSON file
    std::string content( (std::istreambuf_iterator<char>(file) ),
                         (std::istreambuf_iterator<char>()    ) );


    bool parsingSuccessful = jsonFile.open(filePath);
    cout << jsonFile.size() << endl;

    file.close();

    emotionsInSecond.resize(jsonFile[jsonFile.size()+1]["timestamp"].asInt());
    eventInSecond.resize(jsonFile[jsonFile.size()+1]["timestamp"].asInt());

    for (Json::ArrayIndex i = 0; i < jsonFile.size(); i++){
        //cout << jsonFile[i]["timestamp"].asInt() << "=====" << jsonFile[i]["event"].asBool() << endl;
        int timestamp = jsonFile[i]["timestamp"].asInt();

        if(!jsonFile[i]["emotion"].isNull()){
            emotionsInSecond[timestamp].first++;
            emotionsInSecond[timestamp].second.push_back(jsonFile[i]["emotion"].asString());
        }

        if(!jsonFile[i]["event"].isNull())
            eventInSecond[timestamp] = true;
    }


    for(int i = 0; i < emotionsInSecond.size(); i++){

        cout << "Timestamp: " << i << "  NrEmotions: " << emotionsInSecond[i].second.size() << endl;

    }*/


    /*int c = 0;
    for(int i : eventInSecond)
        if(i != 0) c++;
    cout << c << endl;*/





    //count the number of lines in the file to allocate in the vectors
    /* ifstream file(filePath);
    string line;
    getline(file, line, '\n'); //skip first line
    int maxTimestamp = 0;
    while(file){

        if(AuxFunc::split(line, ':').size() == 2){
            if(maxTimestamp < atoi(AuxFunc::split(line, ':').at(0).c_str()))
                maxTimestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
        }

        else if(maxTimestamp < atoi(AuxFunc::split(line, ';').at(0).c_str())){
            maxTimestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
        }

        getline(file, line, '\n');
    }
    cout << maxTimestamp << endl;
    emotionsInSecond.resize(maxTimestamp);
    eventInSecond.resize(maxTimestamp);

    file.close();

    //===========================================

    file.open(filePath);
    getline(file, line, '\n'); //skip first line

    getline(file, line, '\n'); //get first line
    int timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
    while(file){
        //cout << line << endl;
        if(AuxFunc::split(line, ':').size() == 2){
            eventInSecond[timestamp] = 1;
            getline(file, line, '\n');
            timestamp = atoi(AuxFunc::split(line, ':').at(0).c_str());
            continue;
        }

        string emotion = AuxFunc::split(line, ';')[1];
        emotionsInSecond[timestamp].first++;
        emotionsInSecond[timestamp].second.push_back(emotion);

        getline(file, line, '\n');
        timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
    }

    file.close();

    for(int i = 0; i < emotionsInSecond.size(); i++){

        cout << "Timestamp: " << i << "  NrEmotions: " << emotionsInSecond[i].second.size() << endl;

    }

    int c = 0;
    for(int i : eventInSecond)
        if(i != 0) c++;
    cout << c << endl;
*/

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
    bool event;
    while (file) {
        event = false;
        while (timestamp < interval && file/*wtf*/) {

            if(AuxFunc::split(line, ':').size() == 2){
                //cout << "aqui" << endl;
                event = true;
            }

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

            EmotionInterval ei(interval, emotions, event);
            // cout << ei.getTimestamp() << "--" << ei.getEvent() << endl;
            emotionIntervals.push_back(ei);

            if (emotions.size() > maxValue)
                maxValue = emotions.size();

            emotions.clear();
        }
        interval += i;
    }

    cout << "MaxValue: " << maxValue << endl;
    //cout << emotionIntervals.size() << endl;
   // for (EmotionInterval e : emotionIntervals)
     //   cout << "Timestamp: " << e.getTimestamp() << "  NrEmocoes: " << e.getNumberOfEmotions()
       //      << "   Event: " << e.getEvent() << endl;

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
