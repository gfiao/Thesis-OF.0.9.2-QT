using namespace std;

#include <vector>
#include <set>
#include <string>
#include <sstream>
#include "AuxFunc.h"
#include "EmotionInterval.h"
#include "ofxXmlSettings.h"

class EmotionData {

private:

    vector<pair<int, vector<string>>> emotionsInSecond;
    vector<bool> eventInSecond;

    int interval;

    //highest number of emotions shared
    int maxValue;

    int maxValueInterval;


public:

    EmotionData(string filePath, int interval = 5);

    vector<pair<int, vector<string>>> getEmotionsInSecond();
    vector<bool> getEventInSecond();

    int getInterval();
    vector<EmotionInterval> setInterval(int interval);

    int getMaxValue();
    int getMaxValueInterval();

};
