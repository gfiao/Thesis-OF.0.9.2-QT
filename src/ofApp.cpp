#include "ofApp.h"

// global qml signal to slot object instance
QMLCallback qmlCallback;

//--------------------------------------------------------------
void ofApp::setup(){

    emotionData = nullptr;
    audio = nullptr;

    ofBackground(ofColor::white);

    qmlSetup();

    //TODO: code to get the text from the checkboxes, use later
    /* QObjectList checkboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    for(QObject* obj : checkboxes)
        cout << obj->property("text").toString().toStdString() << endl;*/
}

void ofApp::qmlSetup(){

    QQmlComponent component(&qmlEngine,
                            QUrl(QStringLiteral("qrc:/main.qml")) );

    qmlWindow = component.create();

    qmlLoadVideo = qmlWindow->findChild<QObject*>("loadVideo");
    qmVideoVolSlider = qmlWindow->findChild<QObject*>("videoVolume");

    qmlLoadDataFile = qmlWindow->findChild<QObject*>("loadDataFile");
    qmlLoadDataParameters = qmlWindow->findChild<QObject*>("loadDataParameters");

    qmlClearSelection = qmlWindow->findChild<QObject*>("clearSelection");

    qmlPlayButton = qmlWindow->findChild<QObject*>("playMouseArea");
    qmlPauseButton = qmlWindow->findChild<QObject*>("pauseMouseArea");
    qmlStopButton = qmlWindow->findChild<QObject*>("stopMouseArea");

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

    QObject::connect(qmlPlayButton, SIGNAL(entered()),
                     &qmlCallback, SLOT(playButtonSlot()));
    QObject::connect(qmlPauseButton, SIGNAL(entered()),
                     &qmlCallback, SLOT(pauseButtonSlot()));
    QObject::connect(qmlStopButton, SIGNAL(entered()),
                     &qmlCallback, SLOT(stopButtonSlot()));

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

    if(emotionDataPath.size() == 0)
        qmlLoadDataParameters->setProperty("enabled", false);
    else
        qmlLoadDataParameters->setProperty("enabled", true);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);

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

    //=============================

    ofSetHexColor(0x000000);
    if (video.isLoaded()) {
        vector<string> videoPathSplit = AuxFunc::split(video.getMoviePath(), '\\');
        ofDrawBitmapString("Video file: " + videoPathSplit.back(),
                           VIDEO_OFFSET_WIDTH, VIDEO_OFFSET_HEIGHT + videoHeight + 25);
    }

    if (emotionData != nullptr) {
        vector<string> emotionDataPathSplit = AuxFunc::split(emotionDataPath, '\\');
        ofDrawBitmapString("Data file: " + emotionDataPathSplit.back(),
                           VIDEO_OFFSET_WIDTH, VIDEO_OFFSET_HEIGHT + videoHeight + 50);
    }

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

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a data file");

    if (openFileResult.bSuccess) {
        ofLogVerbose("User selected a file");
        emotionDataPath = openFileResult.getPath();

        ofSystemAlertDialog("Data file loaded!");
        cout << emotionDataPath << endl;
    }

    QObject* label = qmlWindow->findChild<QObject*>("loadFileLabel");
    string emotionDataFileName = AuxFunc::split(emotionDataPath, '\\').back();
    label->setProperty("visible", true);
    label->setProperty("text", QVariant(emotionDataFileName.c_str()));
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

        string videoName = AuxFunc::split(video.getMoviePath().c_str(), '\\').back();
        //audio files will use the .wav container
        if (!boost::filesystem::exists("data\\" + AuxFunc::split(videoName, '.')[0] + ".wav")) {
            //extract the audio from the video file
            string cmd = "ffmpeg -i " + video.getMoviePath() + " data\\" + AuxFunc::split(videoName, '.')[0] + ".wav";
            system(cmd.c_str());
        }

        string audioFile = "data\\" + AuxFunc::split(videoName, '.')[0] + ".wav";
        audio = nullptr;
        audio = new Audio(audioFile.c_str());

        video.setVolume(qmVideoVolSlider->property("value").toFloat());
        //video.play();
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

void ofApp::play(){
    video.play();
}

void ofApp::pause(){
    if(video.isPaused())
        play();
    else
        video.setPaused(true);
}

void ofApp::stop(){
    video.stop();
}
