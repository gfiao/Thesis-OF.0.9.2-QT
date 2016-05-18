using namespace std;

#include <utility>
#include <iostream>

class ClipWithScore{

private:

    //start and end timestamp of the clip
    pair<int, int> timestamps;

    //score associated with this clip
    double finalScore;

    //number of emotions shared during the clip
    int nrOfEmotions;

    //audio values associated with this clip
    float audioValues;

public:

    ClipWithScore(pair<int, int> timestamps, int numberOfEmotions, float audioValues);

    pair<int, int> getTimestamps();
    void setTimestamps(int start, int end);

    double getFinalScore();
    void calcFinalScore(double emotionWeight, double audioWeight);
    void setFinalScore(double score);

    float getAudioValues();
    void setAudioValues(float audioValues);

    int getNrOfEmotions();
};
