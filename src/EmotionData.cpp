#include "EmotionData.h"
#include <fstream>
#include <iostream>
#include <algorithm>

EmotionData::EmotionData(string filePath, int interval) {

    this->interval = interval; //default is 5

    ofxXmlSettings xmlFile;
    if( xmlFile.loadFile(filePath) ){
        cout << "xml file loaded" << endl;
    }else{
        cout << "xml error" << endl;
    }

    xmlFile.pushTag("emotionData", 0);
    int numOfData = xmlFile.getNumTags("data");
    xmlFile.pushTag("data", numOfData-1);
    int maxTimestamp = xmlFile.getValue("timestamp", 0);
    xmlFile.popTag();

    emotionsInSecond.resize(maxTimestamp+1);
    eventInSecond.resize(maxTimestamp+1);

    //cout << numOfData << endl;

    for(int i = 0; i < numOfData; i++){
        xmlFile.pushTag("data", i);
        int timestamp = xmlFile.getValue("timestamp", 0);

        if(xmlFile.tagExists("emotion")){
            emotionsInSecond[timestamp].first++;
            emotionsInSecond[timestamp].second.push_back(xmlFile.getValue("timestamp", ""));
        }

        if(xmlFile.tagExists("event"))
            eventInSecond[timestamp] = true;

        xmlFile.popTag();
    }

    maxValue = 0;
    for(int i = 0; i < emotionsInSecond.size(); i++){
        if(emotionsInSecond[i].first > maxValue)
            maxValue = emotionsInSecond[i].first;
    }

    /* vector<int> inter = setInterval(5);
    for(int i = 0; i < inter.size(); i++){
        cout << "Timestamp: " << i << " Emotions: " << inter[i] << endl;
    }*/

    /*for(int i = 0; i < eventInSecond.size(); i++){
        if(eventInSecond[i])
            cout << "Timestamp: " << i << endl;
    }

    for(int i = 0; i < emotionsInSecond.size(); i++){
        cout << "Timestamp: " << i << " Emotions: " << emotionsInSecond[i].first << endl;
    }*/




    //    this->interval = interval;
    //    maxValue = 0;
    //    int i = interval;

    //    cout << "Interval: " << interval << endl;

    //    ifstream file(filePath);
    //    string line;
    //    getline(file, line, '\n'); //skip first line
    //    vector<string> emotions;

    //    getline(file, line, '\n'); // read a string until next newline
    //    int timestamp;
    //    timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());
    //    bool event;
    //    while (file) {
    //        event = false;
    //        while (timestamp < interval && file/*wtf*/) {

    //            if(AuxFunc::split(line, ':').size() == 2){
    //                //cout << "aqui" << endl;
    //                event = true;
    //            }

    //            if(AuxFunc::split(line, ':').size() == 1){
    //                timestamp = atoi(AuxFunc::split(line, ';').at(0).c_str());

    //                if (timestamp >= interval)
    //                    continue;

    //                emotions.push_back(AuxFunc::split(line, ';').at(1));

    //                distinctEmotions.insert(AuxFunc::split(line, ';').at(1));
    //            }
    //            getline(file, line, '\n');

    //        }
    //        if (emotions.size() >= minNumEmotions) {//dynamic interval

    //            EmotionInterval ei(interval, emotions, event);
    //            // cout << ei.getTimestamp() << "--" << ei.getEvent() << endl;
    //            emotionIntervals.push_back(ei);

    //            if (emotions.size() > maxValue)
    //                maxValue = emotions.size();

    //            emotions.clear();
    //        }
    //        interval += i;
    //    }

    //    cout << "MaxValue: " << maxValue << endl;
    //    //cout << emotionIntervals.size() << endl;
    //    // for (EmotionInterval e : emotionIntervals)
    //    //   cout << "Timestamp: " << e.getTimestamp() << "  NrEmocoes: " << e.getNumberOfEmotions()
    //    //      << "   Event: " << e.getEvent() << endl;

    //    //for(string s: distinctEmotions)
    //    //cout << s << endl;
    //    file.close();
}

vector<pair<int, vector<string> > > EmotionData::getEmotionsInSecond(){
    return emotionsInSecond;
}

vector<bool> EmotionData::getEventInSecond(){
    return eventInSecond;
}

vector<EmotionInterval> EmotionData::getEmotionIntervals() {
    return emotionIntervals;
}

int EmotionData::getInterval() {
    return interval;
}

vector<pair<int, vector<string>>> EmotionData::setInterval(int interval){
    this->interval = interval;

    vector<pair<int, vector<string>>> ret;
    for(int i = 0; i < emotionsInSecond.size(); i+=interval){

        int countEmotions = 0;
        vector<string> emotions;
        for(int j = i; j < i+interval && j < emotionsInSecond.size(); j++){
            countEmotions += emotionsInSecond[j].first;
            for(string e : emotionsInSecond[j].second)
                emotions.push_back(e);
        }
        pair<int, vector<string>> retEle(countEmotions, emotions);
        ret.push_back(retEle);
    }
    return ret;
}

int EmotionData::getMaxValue() {
    return maxValue;
}
