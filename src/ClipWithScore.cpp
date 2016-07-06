using namespace std;

#include "ClipWithScore.h"


ClipWithScore::ClipWithScore(pair<int, int> timestamps, double numberOfEmotions, float audioValues,
                             int mov, int shotType){
    this->timestamps = timestamps;
    this->nrOfEmotions = numberOfEmotions;
    this->audioValues = audioValues;
    finalScore = 0;
    movement = mov;
    this->shotType = shotType;
}

pair<int, int> ClipWithScore::getTimestamps(){
    return timestamps;
}

void ClipWithScore::setTimestamps(int start, int end){
    timestamps = pair<int, int>(start, end);;
}

double ClipWithScore::getFinalScore(){
    return finalScore;
}

//TODO: fazer a conta para calcular a score, utilizar pesos aqui
void ClipWithScore::calcFinalScore(double emotionWeight, double audioWeight){

    finalScore = nrOfEmotions * emotionWeight + audioValues * audioWeight;
    //cout << finalScore << " = " << nrOfEmotions << " * " << emotionWeight << " + "
      //   << audioValues << " * " << audioWeight << endl;


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

void ClipWithScore::setMovement(int mov){
    movement = mov;
}

int ClipWithScore::getMovement(){
    return movement;
}

void ClipWithScore::setShotType(int type){
    shotType = type;
}

int ClipWithScore::getShotType(){
    return shotType;
}
