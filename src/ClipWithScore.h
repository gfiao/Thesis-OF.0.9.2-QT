using namespace std;

#include <utility>
#include <iostream>

static const int UNDEFINED = 0;
static const int LEFT = 1;
static const int RIGHT = 2;

class ClipWithScore{

private:

    //start and end timestamp of the clip
    pair<int, int> timestamps;

    //score associated with this clip
    double finalScore;

    //number of emotions shared during the clip
    double nrOfEmotions;

    //audio values associated with this clip
    float audioValues;

    //undefined - 0
    //left - 1
    //right - 2
    int movement;

public:

    ClipWithScore(pair<int, int> timestamps, double numberOfEmotions, float audioValues, int mov = 0);

    pair<int, int> getTimestamps();
    void setTimestamps(int start, int end);

    double getFinalScore();
    void calcFinalScore(double emotionWeight, double audioWeight);
    void setFinalScore(double score);

    float getAudioValues();
    void setAudioValues(float audioValues);

    int getNrOfEmotions();

    void setMovement(int mov);
    int getMovement();
};
