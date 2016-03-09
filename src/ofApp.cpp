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

    qmlLoadVideo = qmlWindow->findChild<QObject*>("loadVideo");
    qmVideoVolSlider = qmlWindow->findChild<QObject*>("videoVolume");

    qmlLoadDataFile = qmlWindow->findChild<QObject*>("loadDataFile");
    qmlLoadDataParameters = qmlWindow->findChild<QObject*>("loadDataParameters");

    qmlClearSelection = qmlWindow->findChild<QObject*>("clearSelection");

    // connect qml signals and slots
    qmlCallback.ofAppInstance = this;

    QObject::connect(qmlLoadDataFile, SIGNAL( clicked() ),
                     &qmlCallback, SLOT( dataFileSlot() ));
    QObject::connect(qmlLoadDataParameters, SIGNAL( clicked() ),
                     &qmlCallback, SLOT( dataParametersSlot() ));

    QObject::connect(qmlLoadVideo, SIGNAL( triggered() ),
                     &qmlCallback, SLOT( loadVideoSlot() ));
    QObject::connect(qmVideoVolSlider, SIGNAL( sliderSignal(QVariant) ),
                     &qmlCallback, SLOT( sliderSlot(QVariant) ));

    QObject::connect(qmlClearSelection, SIGNAL(triggered()),
                     &qmlCallback, SLOT(clearSelectionSlot()));

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

    /* if(video.isLoaded())
        qmlButton->setProperty("enabled", false);*/

    if(emotionDataPath.size() == 0)
        qmlLoadDataParameters->setProperty("enabled", false);
    else
        qmlLoadDataParameters->setProperty("enabled", true);

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
void ofApp::loadDataFile(){
    cout << "kwkwkwkwkwkw" << endl;

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a data file");

    if (openFileResult.bSuccess) {
        ofLogVerbose("User selected a file");
        emotionDataPath = openFileResult.getPath();

        ofSystemAlertDialog("Data file loaded!");
        cout << emotionDataPath << endl;
    }
}

void ofApp::loadDataParameters(){

    QObject *interval_textfield = qmlWindow->findChild<QObject*>("interval_textfield");
    QString intervalValue = interval_textfield->property("text").toString();
    cout << intervalValue.toStdString() << endl;

    QObject *dynInter_textfield = qmlWindow->findChild<QObject*>("dynInter_textfield");
    QString dynIntValue = dynInter_textfield->property("text").toString();
    cout << dynIntValue.toStdString() << endl;

    cout << intervalValue.size() << endl;
    cout << dynIntValue.size() << endl;

    if (intervalValue.size() > 0 && dynIntValue.size() == 0){
        emotionData = new EmotionData(emotionDataPath, ofToInt(intervalValue.toStdString()));
    }
    else if (intervalValue.size() > 0 && dynIntValue.size() > 0){
        emotionData = new EmotionData(emotionDataPath, ofToInt(intervalValue.toStdString()),
                                      ofToInt(dynIntValue.toStdString()));
    }
    else if (dynIntValue.size() > 0){
        emotionData = new EmotionData(emotionDataPath, 5, ofToInt(dynIntValue.toStdString()));
    }
    else{
        emotionData = new EmotionData(emotionDataPath); //5 second intervals
    }

    ofSystemAlertDialog("Data loaded successfully!");

    qmlWindow->findChild<QObject*>("loadDataWindow")->setProperty("visible", false);

}

void ofApp::loadVideoFile(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a video file");

    if(openFileResult.bSuccess){
        video.load(openFileResult.getPath());

        cout << "Video Res: " << video.getWidth() << "x" << video.getHeight() << endl;
        cout << "Nr of frames: " << video.getTotalNumFrames() << endl;

        video.setVolume(qmVideoVolSlider->property("value").toFloat());
        video.play();
    }

}

void ofApp::clearSelection(){
    video.close();
    emotionData = nullptr;
    emotionDataPath = "";
}

//--------------------------------------------------------------
void ofApp::qmlVolSliderChanged(float msg){
    video.setVolume(msg);
}
