#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QObject>

static const int VIDEO_OFFSET_WIDTH = 0;
static const int VIDEO_OFFSET_HEIGHT = 0;
static const int DEFAULT_INTERVAL_VAL = 5;

static const int LONG_SHOT = 0;
static const int CLOSEUP_SHOT = 1;
static const int OUT_OF_FIELD = 2;

static const string NOT_NUMBER = "Not a number!";
static const string WRONG_NUMBER = "The value must be between 0 and 1!";


class ofApp : public ofBaseApp {
private:
    //oF
    ofVideoPlayer video;

    //qml
    QQmlApplicationEngine qmlEngine;
    QObject *qmlWindow;
    QObject *qmlButton;
    QObject *qmlSlider;

public:
    // oF
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    // qml
    void qmlButtonPressed();
    void qmlSliderChanged(float msg);
};

// qml signal to slot object
class QMLCallback : public QObject {
    Q_OBJECT
public:
    ofApp *ofAppInstance;

public slots:
    void buttonSlot() {
        ofAppInstance->qmlButtonPressed();
    }
    void sliderSlot(QVariant msg) {
        ofAppInstance->qmlSliderChanged(msg.toFloat());
    }
};
