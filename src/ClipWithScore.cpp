using namespace std;

#include "ClipWithScore.h"


ClipWithScore::ClipWithScore(pair<int, int> timestamps, int numberOfEmotions, float audioValues){
    this->timestamps = timestamps;
    this->nrOfEmotions = numberOfEmotions;
    this->audioValues = audioValues;
    finalScore = 0;
}

pair<int, int> ClipWithScore::getTimestamps(){
    return timestamps;
}

void ClipWithScore::setTimestamps(int start, int end){
    pair<int, int> ts(start, end);
    timestamps = ts;
}

double ClipWithScore::getFinalScore(){
    return finalScore;
}

//TODO: fazer a conta para calcular a score, utilizar pesos aqui
void ClipWithScore::calcFinalScore(double emotionWeight, double audioWeight){

    //cout << nrOfEmotions << " * " << emotionWeight << " + " << audioValues << " * " << audioWeight << endl;

    finalScore = nrOfEmotions * emotionWeight + audioValues * audioWeight;

}

void ClipWithScore::setFinalScore(double score){
    finalScore = score;
}

float ClipWithScore::getAudioValues(){
    return audioValues;
}

void ClipWithScore::setAudioValues(float audioValues){
    this->audioValues = audioValues;
}

int ClipWithScore::getNrOfEmotions(){
    return nrOfEmotions;
}
