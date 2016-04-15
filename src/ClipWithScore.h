using namespace std;

#include <utility>
#include <iostream>

class ClipWithScore{

private:

    //start and end timestamp of the clip
    pair<int, int> timestamps;

    //score associated with this clip
    double finalScore;

    //audio values associated with this clip
    float audioValues;

public:

    ClipWithScore(pair<int, int> timestamps, float audioValues);

    double getFinalScore();
    void calcFinalScore(double emotionWeight, double audioWeight);

    float getAudioValues();
    void setAudioValues(float audioValues);
};
