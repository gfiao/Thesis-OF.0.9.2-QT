using namespace std;

#include "ClipWithScore.h"


ClipWithScore::ClipWithScore(pair<int, int> timestamps, int numberOfEmotions, float audioValues){
    this->timestamps = timestamps;
    this->nrOfEmotions = numberOfEmotions;
    this->audioValues = audioValues;
    finalScore = 0;
}

double ClipWithScore::getFinalScore(){
    return finalScore;
}

//TODO: fazer a conta para calcular a score, utilizar pesos aqui
void ClipWithScore::calcFinalScore(double emotionWeight, double audioWeight){

    finalScore = nrOfEmotions * emotionWeight + audioValues * audioWeight;

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
