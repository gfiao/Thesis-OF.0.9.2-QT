using namespace std;

#include <utility>
#include <iostream>

static const int LEFT = 0;
static const int RIGHT = 1;
static const int UNDEFINED = -1;

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

    //left - 0
    //right - 1
    //undifined - (-1)
    int movement;

public:

    ClipWithScore(pair<int, int> timestamps, double numberOfEmotions, float audioValues, int mov = -1);

    pair<int, int> getTimestamps();
    void setTimestamps(int start, int end);

    double getFinalScore();
    void calcFinalScore(double emotionWeight, double audioWeight);
    void setFinalScore(double score);

    float getAudioValues();
    void setAudioValues(float audioValues);

    int getNrOfEmotions();

    int setMovement(int mov);
    int getMovement();
};
