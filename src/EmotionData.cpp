#include "EmotionData.h"
#include <fstream>
#include <iostream>
#include <algorithm>

EmotionData::EmotionData(string filePath, int interval) {

    this->interval = interval; //default is 5
    maxValueInterval = 0;

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
            //            emotionsInSecond[timestamp].first++;
            emotionsInSecond[timestamp].push_back(xmlFile.getValue("emotion", ""));
        }

        if(xmlFile.tagExists("event"))
            eventInSecond[timestamp] = true;

        xmlFile.popTag();
    }

    maxValue = 0;
    for(int i = 0; i < emotionsInSecond.size(); i++){
        if(emotionsInSecond[i].size() > maxValue)
            maxValue = emotionsInSecond[i].size();
    }

    /* vector<EmotionInterval> intEmo = setInterval(30);
    for(EmotionInterval e : intEmo){
        cout << e.getTimestamp() << endl;
    }
    cout << endl;
    for(EmotionInterval e : intEmo){
        cout << e.getNumberOfEmotions() << endl;
    }*/
}

vector<vector<string>> EmotionData::getEmotionsInSecond(){
    return emotionsInSecond;
}

vector<bool> EmotionData::getEventInSecond(){
    return eventInSecond;
}

int EmotionData::getInterval() {
    return interval;
}

vector<EmotionInterval> EmotionData::setInterval(int interval){
    this->interval = interval;

    vector<EmotionInterval> ret;
    for(int i = 0; i < emotionsInSecond.size(); i+=interval){

        vector<string> emotions;
        for(int j = i; j < i+interval && j < emotionsInSecond.size(); j++){
            for(string e : emotionsInSecond[j])
                emotions.push_back(e);
        }

        if(maxValueInterval < emotions.size())
            maxValueInterval = emotions.size();

        EmotionInterval retEle(i, emotions);
        ret.push_back(retEle);
    }
    return ret;
}

int EmotionData::getMaxValue() {
    return maxValue;
}

int EmotionData::getMaxValueInterval(){
    return maxValueInterval;
}
