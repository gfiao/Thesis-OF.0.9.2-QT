using namespace std;

#include "ClipWithScore.h"


ClipWithScore::ClipWithScore(pair<int, int> timestamps, float audioValues){
    this->timestamps = timestamps;
    this->audioValues = audioValues;
    finalScore = 0;
}

double ClipWithScore::getFinalScore(){
    return finalScore;
}

//TODO: fazer a conta para calcular a score, utilizar pesos aqui
void ClipWithScore::calcFinalScore(double emotionWeight, double audioWeight){

}

float ClipWithScore::getAudioValues(){
    return audioValues;
}

void ClipWithScore::setAudioValues(float audioValues){
    this->audioValues = audioValues;
}
