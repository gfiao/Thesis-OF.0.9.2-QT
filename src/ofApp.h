#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "EmotionData.h"
#include "AuxFunc.h"
#include "Audio.h"
#include <vector>

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QObject>

static const int VIDEO_OFFSET_WIDTH = 10;
static const int VIDEO_OFFSET_HEIGHT = 10;
static const int DEFAULT_INTERVAL_VAL = 5;

static const int LONG_SHOT = 0;
static const int CLOSEUP_SHOT = 1;
static const int OUT_OF_FIELD = 2;

static const string NOT_NUMBER = "Not a number!";
static const string WRONG_NUMBER = "The value must be between 0 and 1!";


class ofApp : public ofBaseApp {
private:
    //oF
    string emotionDataPath;
    ofVideoPlayer video;
    EmotionData *emotionData;
    Audio *audio;

    //qml
    QQmlApplicationEngine qmlEngine;
    QObject *qmlWindow;

    //video
    QObject *qmlLoadVideo;
    QObject *qmVideoVolSlider;

    //emotion data
    QObject *qmlLoadDataFile;
    QObject *qmlLoadDataParameters;

    QObject *qmlClearSelection;

    //cut detection buttons
    QObject *qmlNewCutButton;
    QObject *qmlExistingCutButton;

    //video controls
    QObject *qmlPlayButton;
    QObject *qmlPauseButton;
    QObject *qmlStopButton;


public:
    // oF
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    //color
    pair<ofImage, cv::MatND> calcDominantColor(ofImage fileName);
    int checkShotType(cv::MatND hist);

    //movement
    vector<cv::KeyPoint> extractKeypoints(int timestamp);
    pair<int, int> calcMotionDirection(int startTimestamp, int endTimestamp);

    //cut detetion
    void detectCuts();
    void processCutsFile();

    // qml
    void qmlSetup();
    void loadVideoFile();
    void loadDataFile();
    void loadDataParameters();
    void qmlVolSliderChanged(float msg);
    void clearSelection();
    void play();
    void pause();
    void stop();

};

// qml signal to slot object
class QMLCallback : public QObject {
    Q_OBJECT
public:
    ofApp *ofAppInstance;

public slots:
    void loadVideoSlot(){
        ofAppInstance->loadVideoFile();
    }

    void dataFileSlot() {
        ofAppInstance->loadDataFile();
    }
    void dataParametersSlot(){
        ofAppInstance->loadDataParameters();
    }

    void clearSelectionSlot(){
        ofAppInstance->clearSelection();
    }

    void playButtonSlot(){
        ofAppInstance->play();
    }
    void pauseButtonSlot(){
        ofAppInstance->pause();
    }
    void stopButtonSlot(){
        ofAppInstance->stop();
    }

    void sliderSlot(QVariant msg) {
        ofAppInstance->qmlVolSliderChanged(msg.toFloat());
    }

    void newCutButtonSlot(){
        ofAppInstance->detectCuts();
    }
    void existingCutButtonSlot(){
        ofAppInstance->processCutsFile();
    }
};
