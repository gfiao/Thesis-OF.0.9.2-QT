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

    //TODO: change later
    /* if(video.isLoaded() && emotionDataPath.size() != 0){
        QObject* tabView = qmlWindow->findChild<QObject*>("tabView");
        tabView->setProperty("enabled", true);
    }*/


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

//code originally from http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=calcHist
pair<ofImage, cv::MatND> ofApp::calcDominantColor(ofImage image) {

    cv::Mat cvImg = ofxCv::toCv(image);
    cv::Mat hsvImage;

    cvtColor(cvImg, hsvImage, CV_RGB2HSV);

    // Quantize the hue to 50 levels
    // and the saturation to 32 levels
    int hbins = 180, sbins = 32;
    int histSize[] = { hbins, sbins };
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    cv::MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = { 0, 1 };

    calcHist(&hsvImage, 1, channels, cv::Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false);
    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins * 10, CV_8UC3);

    /*for (int h = 0; h < hbins; h++)
        for (int s = 0; s < sbins; s++)
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            rectangle(histImg, cv::Point(h*scale, s*scale),
                cv::Point((h + 1)*scale - 1, (s + 1)*scale - 1),
                cv::Scalar::all(intensity),
                CV_FILLED);
        }*/

    /*for (int h = 0; h < hbins; h++) {
            float sum = 0;
            for (int s = 0; s < sbins; s++)
            {
                //cout << hist.at<float>(i) << endl;
                sum += hist.at<float>(h, s);
            }
            string cmd = "echo " + to_string(sum) + " >> teste.txt";
            system(cmd.c_str());
        }*/

    ofxCv::toOf(histImg, image);
    image.update(); //update changes done by openCV

    return pair<ofImage, cv::MatND>(image, hist);
}

//TODO: rever valores
int ofApp::checkShotType(cv::MatND hist) {

    int hbins = 180, sbins = 32;
    vector<float> sums; //sum of all the intesities of given color

    for (int h = 0; h < hbins; h++) {
        float sum = 0;
        for (int s = 0; s < sbins; s++) {
            sum += hist.at<float>(h, s);
        }
        sums.push_back(sum);
    }

    int validWindows = 0; //more than 1 validWindow means the shot is not a long shot
    for (int i = 0; i < sums.size() - 10; i++) {
        int count = 0;
        for (int j = 0; j < 10; j++) {
            if (sums[j] > 20000) count++;
        }
        if (count >= 5) validWindows++; //a color can be considered dominant
    }

    if (validWindows == 1)
        return LONG_SHOT;
    else if (validWindows == 2 || validWindows == 3)
        return CLOSEUP_SHOT;
    return OUT_OF_FIELD;

}


vector<cv::KeyPoint> ofApp::extractKeypoints(int timestamp) {

    //=======================
    //so we can extract the keypoints, we need to start the video first
    video.play();
    video.setPaused(true);
    //=======================

    cv::Mat grey;

    //extract the start keypoints
    vector<cv::KeyPoint> keypoints;
    video.setPosition(timestamp / video.getDuration());
    video.update();
    ofxCv::copyGray(video, grey);
    cv::FAST(grey, keypoints, 2);
    cv::KeyPointsFilter::retainBest(keypoints, 30);

    return keypoints;

}

//TODO: for now use only the first and last frame
pair<int, int> ofApp::calcMotionDirection(int startTimestamp, int endTimestamp) {

    startTimestamp = 200;
    endTimestamp = 220;

    auto start = ofGetElapsedTimeMillis();

    //extract the start keypoints
    vector<cv::KeyPoint> startKeypoints = extractKeypoints(startTimestamp);
    cout << "startKeypoints: " << startKeypoints.size() << endl;

    //extract the end keypoints
    vector<cv::KeyPoint> endKeypoints = extractKeypoints(endTimestamp);
    cout << "endKeypoints: " << endKeypoints.size() << endl;

    cout << "Time to extract keypoints: " << ofGetElapsedTimeMillis() - start << endl;

    //TODO: resolver o problema (se é que é um problema)
    if (startKeypoints.size() == 0 || endKeypoints.size() == 0) {
        ofSystemAlertDialog("extractKeypoints returns 0");
        return pair<int, int>(0, 0);
    }

    /* Compare each of the keypoints with it's counterpart (best approach?) */
    int rightCounter = 0, leftCounter = 0;
    if (startKeypoints.size() <= endKeypoints.size())
        for (int i = 0; i < startKeypoints.size(); i++) {
            //cout << startKeypoints[i].pt << " ======== " << endKeypoints[i].pt << endl;
            if (startKeypoints[i].pt.x < endKeypoints[i].pt.x)
                rightCounter++;
            else leftCounter++;
        }
    else
        for (int i = 0; i < endKeypoints.size(); i++) {
            //cout << startKeypoints[i].pt << " ======== " << endKeypoints[i].pt << endl;
            if (startKeypoints[i].pt.x < endKeypoints[i].pt.x)
                rightCounter++;
            else leftCounter++;
        }

    cout << "leftCounter: " << leftCounter << " ===== " << "rightCounter: " << rightCounter << endl;

    return pair<int, int>(leftCounter, rightCounter);
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



        calcMotionDirection(0, 0);
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
