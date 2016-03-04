#include "ofApp.h"

// global qml signal to slot object instance
QMLCallback qmlCallback;

//--------------------------------------------------------------
void ofApp::setup(){

    emotionData = nullptr;
    audio = nullptr;

    ofBackground(ofColor::white);

    qmlSetup();
}

void ofApp::qmlSetup(){

    // qml
    QQmlComponent component(&qmlEngine,
                            QUrl(QStringLiteral("qrc:/main.qml")) );

    qmlWindow = component.create();
    qmlLoadData = qmlWindow->findChild<QObject*>("loadData");
    qmlLoadVideo = qmlWindow->findChild<QObject*>("loadVideo");
    qmVideoVolSlider = qmlWindow->findChild<QObject*>("videoVolume");

    // connect qml signals and slots
    qmlCallback.ofAppInstance = this;

    QObject::connect(qmlLoadData, SIGNAL( triggered() ),
                     &qmlCallback, SLOT( buttonSlot() ));
    QObject::connect(qmlLoadVideo, SIGNAL( triggered() ),
                     &qmlCallback, SLOT( menuSlot() ));
    QObject::connect(qmVideoVolSlider, SIGNAL( sliderSignal(QVariant) ),
                     &qmlCallback, SLOT( sliderSlot(QVariant) ));

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

    /* if(video.isLoaded())
        qmlButton->setProperty("enabled", false);*/

}

//--------------------------------------------------------------
void ofApp::draw(){

    //========================
    double videoWidth = video.getWidth();
    double videoHeight = video.getHeight();
    double newWidth = ofGetWidth() - (VIDEO_OFFSET_WIDTH + 10);
    //no space to draw the video
    if (static_cast<float>(newWidth) < video.getWidth()) {
        double ratio = newWidth / video.getWidth();
        videoWidth = videoWidth * ratio;
        videoHeight = videoHeight * ratio;
    }
    video.draw(VIDEO_OFFSET_WIDTH, VIDEO_OFFSET_HEIGHT, videoWidth, videoHeight);
    //
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // call a qml function
    QVariant returnedValue;
    QVariant msg = "Hello from C++";
    QMetaObject::invokeMethod(qmlWindow, "myQmlFunction",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, msg));

    QString returnedValueString = returnedValue.toString();
    cout << "QML function returned: " << returnedValueString.toStdString() << endl;
}

//--------------------------------------------------------------
void ofApp::qmlLDButtonPressed(){
    cout << "KEKEKEKEKEKEKEK" << endl;
    /* ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a data file");

    if (openFileResult.bSuccess) {
        ofLogVerbose("User selected a file");
        emotionDataPath = openFileResult.getPath();

        if (intervalValue.size() > 0)
            emotionData = new EmotionData(emotionDataPath, atoi(intervalInput->getText().c_str()));
        else if (intervalValue.size() > 0 && dynIntValue.size() > 0)
            emotionData = new EmotionData(emotionDataPath, atoi(intervalInput->getText().c_str()),
                                          atoi(dynIntValue.c_str()));
        else if (dynIntValue.size() > 0)
            emotionData = new EmotionData(emotionDataPath, 5, atoi(dynIntValue.c_str()));
        else
            emotionData = new EmotionData(emotionDataPath); //5 second intervals

        ofSystemAlertDialog("Data loaded successfully!");

    }
    else
        ofLogVerbose("User hit cancel");*/

}

void ofApp::qmlLVButtonPressed(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a video file");

    if(openFileResult.bSuccess){
        video.load(openFileResult.getPath());

        cout << "Video Res: " << video.getWidth() << "x" << video.getHeight() << endl;
        cout << "Nr of frames: " << video.getTotalNumFrames() << endl;

        video.setVolume(qmVideoVolSlider->property("value").toFloat());
        video.play();
    }

}

//--------------------------------------------------------------
void ofApp::qmlVolSliderChanged(float msg){
    video.setVolume(msg);
}
