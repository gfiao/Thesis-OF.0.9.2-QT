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
#include <QtCharts>

using namespace QtCharts;

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
    string videoPath;
    ofVideoPlayer video;
    EmotionData *emotionData;
    Audio *audio;
    vector<string> cuts;

    //thresholds
    float longShotThreshold;
    float outOfFieldThreshold;

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

    //charts
    QObject *chartInterval;

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
    float detectShotThreshold();
    void getMinMaxOfPeak(vector<float> hist, int& hMin, int& hMax, int maxValueIndex, float maxValue);

    //color
    vector<ofImage> divideImage(ofImage img, int nrOfImages);
    vector<float> getHistogram(ofImage fileName, float& totalSum, float& maxValue, int& maxValueIndex);
    int checkShotType(ofImage frame);
    float getPctInPeak(ofImage img, int nOfSubImages, int subImagesToProcess);

    //movement
    vector<cv::KeyPoint> detectKeypoints(int timestamp);
    int calcMotionDirection(int startTimestamp, int endTimestamp);

    //cut detetion
    void loadDefaultCutFile();
    void detectCuts();
    void processCutsFile();
    vector<pair<int, int>> detectCutsIn(int start, int end);
    void motionHelper(int start, int end, ClipWithScore& newClip);

    void cutVideo(vector<ClipWithScore> clips);

    //algorithm
    int checkShotTypeClip(int startTimestamp, int endTimestamp);
    void useOnlyMov(bool useAudio, bool useCuts, bool useColor, vector<ClipWithScore>& clips);
    void algorithm(); //main function

    // qml
    void qmlSetup();
    void loadVideoFile();
    void loadDataFile();
    void loadFiles();
    void volSliderChanged(float msg);
    void clearSelection();
    void play();
    void pause();
    void stop();
    void videoSeekbarChanged(float pos);

    void populateChart();
    void changeChartInterval(int interval);

    void selectRow(int row);
    void selectClipMov(QObjectList firstHalfCheckboxes, int& totalDuration, vector<ClipWithScore>& clips,
                       vector<ClipWithScore>& clipsInSummary, int& index, bool useColor, bool longShot,
                       bool closeup, bool offField);
    void selectClipColor(vector<ClipWithScore>& clips, vector<ClipWithScore>& clipsInSummary,
                         bool longShot, bool closeup, bool offField, int& totalDuration, int& index);
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
        ofAppInstance->loadFiles();
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

    void chartIntervalSlot(QVariant msg){
        ofAppInstance->changeChartInterval(msg.toInt());
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
