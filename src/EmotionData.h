using namespace std;

#include <vector>
#include <string>
#include <sstream>
#include "AuxFunc.h"
#include "EmotionInterval.h"

class EmotionData {

private:

	//emotions shared during a certain interval
	vector<EmotionInterval> emotionIntervals;

	int interval;

	//highest number of emotions shared, used in the creation of the emotions chart
	int maxValue;

public:

	EmotionData(string filePath, int interval = 5, int minNumEmotion = 0);

	//returns vector with all the intervals
	vector<EmotionInterval> getEmotionIntervals();
	int getInterval();
	int getMaxValue();
};