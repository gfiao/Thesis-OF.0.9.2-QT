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

    //emotions shared during a certain interval
    vector<EmotionInterval> emotionIntervals;

    vector<pair<int, vector<string>>> emotionsInSecond;
    vector<bool> eventInSecond;

    int interval;

    //highest number of emotions shared, used in the creation of the emotions chart
    int maxValue;


public:

    EmotionData(string filePath, int interval = 5);

    vector<pair<int, vector<string>>> getEmotionsInSecond();
    vector<bool> getEventInSecond();

    //returns vector with all the intervals
    vector<EmotionInterval> getEmotionIntervals();

    int getInterval();
    vector<int> setInterval(int interval);

    int getMaxValue();

};
