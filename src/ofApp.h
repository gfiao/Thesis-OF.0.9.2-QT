#pragma once
#include <string>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxXmlSettings.h"
#include <opencv2/opencv.hpp>
#include "ofxCv.h"
#include "EmotionData.h"
#include "EmotionInterval.h"
#include "AuxFunc.h"
#include "Audio.h"
#include <vector>
#include <fstream>
#include "ClipWithScore.h"

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QObject>

static const int VIDEO_OFFSET_WIDTH = 10;
static const int VIDEO_OFFSET_HEIGHT = 10;
static const int DEFAULT_INTERVAL_VAL = 5;

static const string DEAFULT_CUTS_FILE = "data\\0.30-WeFeel_1_cuts.txt";

static const int LONG_SHOT = 0;
static const int CLOSEUP_SHOT = 1;
static const int OUT_OF_FIELD = 2;

static const string NOT_NUMBER = "Not a number!";
static const string WRONG_NUMBER = "The value must be between 0 and 1!";

static const string TRAIN_ASSETS = "data\\training";

class ofApp : public ofBaseApp {
private:
    //oF
    string emotionDataPath;
    ofVideoPlayer video;
    EmotionData *emotionData;
    Audio *audio;
    vector<string> cuts;

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
    QObject *qmlVideoSeekbar;

    QObject* qmlCurrentRow;

    QObject* qmlRunAlgorithm;


public:
    // oF
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    //training for the shot detection
    void train();

    //color
    vector<ofImage> divideImage(ofImage img, int nrOfImages);
    cv::MatND getHistogram(ofImage fileName);
    int checkShotType(vector<ofImage> images);

    //movement
    vector<cv::KeyPoint> detectKeypoints(int timestamp);
    int calcMotionDirection(int startTimestamp, int endTimestamp);

    //cut detetion
    void detectCuts();
    void processCutsFile();
    vector<pair<int, int>> detectCutsIn(int start, int end);
    void motionHelper(int start, int end, ClipWithScore& newClip);

    void cutVideo(vector<ClipWithScore> clips);
    void algorithm();

    // qml
    void qmlSetup();
    void loadVideoFile();
    void loadDataFile();
    void loadDataParameters();
    void volSliderChanged(float msg);
    void clearSelection();
    void play();
    void pause();
    void stop();
    void videoSeekbarChanged(float pos);

    void selectRow(int row);
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
    void videoSeekbarSlot(QVariant pos){
        ofAppInstance->videoSeekbarChanged(pos.toFloat());
    }

    void sliderSlot(QVariant msg) {
        ofAppInstance->volSliderChanged(msg.toFloat());
    }

    void newCutButtonSlot(){
        ofAppInstance->detectCuts();
    }
    void existingCutButtonSlot(){
        ofAppInstance->processCutsFile();
    }

    void currentRowSlot(QVariant row){
        ofAppInstance->selectRow(row.toInt());
    }

    void runAlgorithmSlot(){
        ofAppInstance->algorithm();
    }
};
