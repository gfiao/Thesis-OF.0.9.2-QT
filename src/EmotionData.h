using namespace std;

#include <vector>
#include <set>
#include <string>
#include <sstream>
#include "AuxFunc.h"
#include "EmotionInterval.h"

class EmotionData {

private:

    //emotions shared during a certain interval
    vector<EmotionInterval> emotionIntervals;

    /*ofxJSONElement jsonFile;
    vector<pair<int, vector<string>>> emotionsInSecond;
    vector<bool> eventInSecond;*/

    int interval;

    //highest number of emotions shared, used in the creation of the emotions chart
    int maxValue;

    int minValue;

    //the emotions present in the data, used to create a combobox in the UI
    set<string> distinctEmotions;

public:

    EmotionData(string filePath, int interval = 5, int minNumEmotion = 0);

    //returns vector with all the intervals
    vector<EmotionInterval> getEmotionIntervals();
    int getInterval();
    int getMaxValue();

    set<string> getDistinctEmotions();
};
