using namespace std;

#include <utility>
#include <iostream>

class ClipWithScore{

private:

    //start and end timestamp of the clip
    pair<int, int> timestamps;

    //score associated with this clip
    int finalScore;

    //audio values associated with this clip
    float audioValues;

public:

    ClipWithScore(pair<int, int> timestamps, float audioValues);

    int getFinalScore();
    void setFinalScore(int finalScore);

    float getAudioValues();
    void setAudioValues(float audioValues);
};
