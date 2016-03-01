#include "ofApp.h"

// global qml signal to slot object instance
QMLCallback qmlCallback;

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::white);

    // qml
    QQmlComponent component(&qmlEngine,
          QUrl(QStringLiteral("qrc:/main.qml")) );

    qmlWindow = component.create();
    qmlButton = qmlWindow->findChild<QObject*>("changeColorButton");
    qmlSlider = qmlWindow->findChild<QObject*>("changePositionSlider");

    // connect qml signals and slots
    qmlCallback.ofAppInstance = this;

    QObject::connect(qmlButton, SIGNAL( clicked() ),
                     &qmlCallback, SLOT( buttonSlot() ));
    QObject::connect(qmlSlider, SIGNAL( sliderSignal(QVariant) ),
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
void ofApp::qmlButtonPressed(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a video file");

    if(openFileResult.bSuccess){
        video.load(openFileResult.getPath());

        cout << "Video Res: " << video.getWidth() << "x" << video.getHeight() << endl;
        cout << "Nr of frames: " << video.getTotalNumFrames() << endl;

        video.play();
    }

}

//--------------------------------------------------------------
void ofApp::qmlSliderChanged(float msg){
    video.setVolume(msg);
}
