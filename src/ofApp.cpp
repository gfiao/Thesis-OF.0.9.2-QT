#include "ofApp.h"

// global qml signal to slot object instance
QMLCallback qmlCallback;

void histTest(vector<ofImage> images){

    for(int i = 0; i < images.size(); i++){
        ofImage image = images[i];

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

        ofstream outFile;
        outFile.open(to_string(i) + ".txt");
        for (int h = 0; h < hbins; h++) {
            float sum = 0;
            for (int s = 0; s < sbins; s++)
            {
                //cout << hist.at<float>(i) << endl;
                sum += hist.at<float>(h, s);
            }

            string sSum = AuxFunc::split(to_string(sum), '.')[0];
            outFile << sSum + "\n";


        }
        outFile.close();



        ifstream f1, f2, f3, f4, f5, f6, f7, f8, f9;
        string line1, line2, line3, line4, line5, line6, line7, line8, line9;
        if(images.size() == 2){
            f1.open("0.txt"), f2.open("1.txt");

            ofstream finalFile;
            finalFile.open(to_string(images.size()) + ".csv");

            while(f1){
                getline(f1, line1, '\n'); getline(f2, line2, '\n');
                finalFile << line1 << ";;;;;;;;;;" << line2 << "\n";
            }

        }
        else if(images.size() == 4){
            f1.open("0.txt"), f2.open("1.txt"), f3.open("2.txt"), f4.open("3.txt");

            ofstream finalFile;
            finalFile.open(to_string(images.size()) + ".csv");

            while(f1){
                getline(f1, line1, '\n'); getline(f2, line2, '\n');
                getline(f3, line3, '\n'); getline(f4, line4, '\n');
                finalFile << line1 << ";;;;;;;;;;" << line2 << ";;;;;;;;;;" << line3 << ";;;;;;;;;;"
                          << line4 << "\n";
            }

        }
        if(images.size() == 6){
            f1.open("0.txt"), f2.open("1.txt"), f3.open("2.txt"),
                    f4.open("3.txt"), f5.open("4.txt"), f6.open("5.txt");

            ofstream finalFile;
            finalFile.open(to_string(images.size()) + ".csv");

            while(f1){
                getline(f1, line1, '\n'); getline(f2, line2, '\n');
                getline(f3, line3, '\n'); getline(f4, line4, '\n');
                getline(f5, line5, '\n'); getline(f6, line6, '\n');
                finalFile << line1 << ";;;;;;;;;;" << line2 << ";;;;;;;;;;" << line3 << ";;;;;;;;;;"
                          << line4 << ";;;;;;;;;;" << line5 << ";;;;;;;;;;" << line6 << "\n";
            }

        }
        else if(images.size() == 9){
            f1.open("0.txt");
            f2.open("1.txt");
            f3.open("2.txt");
            f4.open("3.txt");
            f5.open("4.txt");
            f6.open("5.txt");
            f7.open("6.txt");
            f8.open("7.txt");
            f9.open("8.txt");

            ofstream finalFile;
            finalFile.open(to_string(images.size()) + ".csv");

            while(f1){
                getline(f1, line1, '\n'); getline(f2, line2, '\n');
                getline(f3, line3, '\n'); getline(f4, line4, '\n');
                getline(f5, line5, '\n'); getline(f6, line6, '\n');
                getline(f7, line7, '\n'); getline(f8, line8, '\n');
                getline(f9, line9, '\n');
                finalFile << line1 << ";;;;;;;;;;" << line2 << ";;;;;;;;;;" << line3 << ";;;;;;;;;;"
                          << line4 << ";;;;;;;;;;" << line5 << ";;;;;;;;;;" << line6 << ";;;;;;;;;;"
                          << line7 << ";;;;;;;;;;" << line8 << ";;;;;;;;;;" << line9 << "\n";
            }

        }


    }
}

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

    /*ofImage img;
    img.load("verde2.jpg");
    histTest(divideImage(img, 9));*/
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
    qmlVideoSeekbar = qmlWindow->findChild<QObject*>("videoSeekbar");

    qmlNewCutButton = qmlWindow->findChild<QObject*>("newCutButton");
    qmlExistingCutButton = qmlWindow->findChild<QObject*>("existingCutButton");

    qmlCurrentRow = qmlWindow->findChild<QObject*>("cutsList");

    qmlRunAlgorithm = qmlWindow->findChild<QObject*>("runAlgorithm");

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
    QObject::connect(qmlVideoSeekbar, SIGNAL( videoSeekSignal(QVariant) ),
                     &qmlCallback, SLOT( videoSeekbarSlot(QVariant) ));

    QObject::connect(qmlNewCutButton, SIGNAL( clicked() ),
                     &qmlCallback, SLOT(newCutButtonSlot()));
    QObject::connect(qmlExistingCutButton, SIGNAL( clicked() ),
                     &qmlCallback, SLOT(existingCutButtonSlot()));

    QObject::connect(qmlCurrentRow, SIGNAL( currentRow(QVariant) ),
                     &qmlCallback, SLOT(currentRowSlot(QVariant)));

    QObject::connect(qmlRunAlgorithm, SIGNAL( clicked() ),
                     &qmlCallback, SLOT(runAlgorithmSlot()));
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

    if(emotionDataPath.size() == 0)
        qmlLoadDataParameters->setProperty("enabled", false);
    else
        qmlLoadDataParameters->setProperty("enabled", true);

    QObject* videoPosLabel = qmlWindow->findChild<QObject*>("videoPosition");
    string updLabel = AuxFunc::formatSeconds(video.getPosition() * video.getDuration())
            + " / " + AuxFunc::formatSeconds(video.getDuration());
    videoPosLabel->setProperty("text", QVariant(updLabel.c_str()));

    if(video.isLoaded() && emotionDataPath.size() != 0){
        QObject* tabView = qmlWindow->findChild<QObject*>("tabView");
        tabView->setProperty("enabled", true);

        qmlRunAlgorithm->setProperty("enabled", true);
    }

    /* if(video.isLoaded())
        if(video.getCurrentFrame() % 5000)
            qmlVideoSeekbar->setProperty("value", QVariant(video.getPosition()));*/

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
    /*  QVariant returnedValue;
    QVariant msg = "Hello from C++";
    QMetaObject::invokeMethod(qmlWindow, "myQmlFunction",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, msg));

    QString returnedValueString = returnedValue.toString();
    cout << "QML function returned: " << returnedValueString.toStdString() << endl;*/
}

vector<ofImage> ofApp::divideImage(ofImage img, int nrOfImages){

    vector<ofImage> subImages;
    int w = img.getWidth();
    int h = img.getHeight();
    ofImage img1, img2, img3, img4, img5, img6, img7, img8, img9;

    switch (nrOfImages) {
    case 2:
        img1.cropFrom(img, 0, 0, w/2, h);
        img2.cropFrom(img, w/2, 0, w/2, h);

        subImages.push_back(img1);
        subImages.push_back(img2);

        break;

    case 4:
        img1.cropFrom(img, 0, 0, w/2, h/2);
        img2.cropFrom(img, w/2, 0, w/2, h/2);
        img3.cropFrom(img, 0, h/2, w/2, h/2);
        img4.cropFrom(img, w/2, h/2, w/2, h/2);

        subImages.push_back(img1);
        subImages.push_back(img2);
        subImages.push_back(img3);
        subImages.push_back(img4);

        break;

    case 6:
        img1.cropFrom(img, 0, 0, w/3, h/2);
        img2.cropFrom(img, w/3, 0, w/3, h/2);
        img3.cropFrom(img, (w/3)*2, 0, w/3, h/2);
        img4.cropFrom(img, 0, h/2, w/3, h/2);
        img5.cropFrom(img, w/3, h/2, w/3, h/2);
        img6.cropFrom(img, (w/3)*2, h/2, w/3, h/2);

        subImages.push_back(img1);
        subImages.push_back(img2);
        subImages.push_back(img3);
        subImages.push_back(img4);
        subImages.push_back(img5);
        subImages.push_back(img6);

        break;

    case 9:
        img1.cropFrom(img, 0, 0, w/3, h/3);
        img2.cropFrom(img, w/3, 0, w/3, h/3);
        img3.cropFrom(img, (w/3)*2, 0, w/3, h/3);
        img4.cropFrom(img, 0, h/3, w/3, h/3);
        img5.cropFrom(img, w/3, h/3, w/3, h/3);
        img6.cropFrom(img, (w/3)*2, h/3, w/3, h/3);
        img7.cropFrom(img, 0, (h/3)*2, w/3, h/3);
        img8.cropFrom(img, w/3, (h/3)*2, w/3, h/3);
        img9.cropFrom(img, (w/3)*2, (h/3)*2, w/3, h/3);

        subImages.push_back(img1);
        subImages.push_back(img2);
        subImages.push_back(img3);
        subImages.push_back(img4);
        subImages.push_back(img5);
        subImages.push_back(img6);
        subImages.push_back(img7);
        subImages.push_back(img8);
        subImages.push_back(img9);

        break;
    }

    return subImages;
}

//code originally from http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=calcHist
cv::MatND ofApp::getHistogram(ofImage image) {

    cv::Mat cvImg = ofxCv::toCv(image);
    cv::Mat hsvImage;

    cvtColor(cvImg, hsvImage, CV_RGB2HSV);

    // Quantize the hue to 180 levels
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

    // ofxCv::toOf(histImg, image);
    // image.update(); //update changes done by openCV

    return hist;
}

int ofApp::checkShotType(vector<ofImage> images) {

    int hbins = 180, sbins = 32;
    vector<int> types = {0, 0, 0};

    for(int i = 0; i < images.size(); i++){
        vector<float> sums; //sum of all the pixels of given color
        cv::MatND hist = getHistogram(images.at(i));
        float totalSum = 0;

        for (int h = 0; h < hbins; h++) {
            float sum = 0;
            for (int s = 0; s < sbins; s++) {
                sum += hist.at<float>(h, s);
                totalSum += hist.at<float>(h, s);
            }
            sums.push_back(sum);
        }

        int validInterval = 0;
        for(int i = 0; i < sums.size() - 10; i += 10){
            float sumInInterval;
            for(int j = i; j < j + 10; j++){
                sumInInterval += sums[j];
            }
            if(sumInInterval / totalSum >= 0.5)
                validInterval++;
        }

        if (validInterval == 1)
            types.at(LONG_SHOT)++;
        else if (validInterval == 2 || validInterval == 3)
            types.at(CLOSEUP_SHOT)++;
        else
            types.at(OUT_OF_FIELD)++;

    }

    int returnValue = types[0];
    for(int type : types)
        if(type > returnValue)
            returnValue = type;

    return returnValue;
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

//uses ffprobe to detect cuts in the video
void ofApp::detectCuts() {

    if(!video.isLoaded()){
        ofSystemAlertDialog("Load a video first!");
        return;
    }

    string threshold = qmlWindow->findChild<QObject*>("cutThreshold")->property("text").toString().toStdString();
    cout << threshold << endl;

    string videoPath = video.getMoviePath();
    /*
    we need to remove the c: portion of the path and replace all of the \ with /,
    or else ffprobe can't parse the path
    */
    vector<string> splitVideoPath = AuxFunc::split(videoPath, ':');
    replace(splitVideoPath[1].begin(), splitVideoPath[1].end(), '\\', '/');
    //filename: threshold-videoName.txt
    string fileName = "data\\" + threshold + "-" + AuxFunc::split(AuxFunc::split(video.getMoviePath(), '\\').back(), '.')[0] + "_cuts.txt";

    //this command will detect cuts in the video
    //the output is then written to a text file that will be parsed
    string cmd = "ffprobe -show_frames -of compact=p=0 -f lavfi \"movie="
            + splitVideoPath[1] + ", select=gt(scene\\," + threshold + ")\" > " + fileName;

    cout << cmd << endl;
    if (boost::filesystem::exists(fileName)) {
        ofSystemAlertDialog("File already exists!");
    }
    //cut detection was already done with a different threshold
    else if (AuxFunc::split(fileName, '-')[0].compare(threshold) != 0) {
        bool result = ofSystemYesNoDialoge("File already exists.", "A file with a different threshold already exists, do you wish to create a new one?");
        if (result) {
            system(cmd.c_str());
            ofSystemAlertDialog("Cuts detected!");
        }
    }
    else { //file doesn't exist
        system(cmd.c_str());
        ofSystemAlertDialog("Cuts detected!");
    }


    //now we need to parse the data given by ffprobe
    //the only information we are looking for is the timestamps of the cuts
    //  vector<string> cuts;
    cuts.clear();
    ifstream file(fileName);
    string line;
    vector<string> splitLine;
    while (file) {
        getline(file, line, '\n');
        //cout << line << endl;
        splitLine = AuxFunc::split(line, '|');
        if (splitLine.size() != 0) // last line is empty
            cuts.push_back(splitLine[4]);
    }

    QVariantList timestamps;
    for(string cut : cuts){
        cut = AuxFunc::formatSeconds(ofToInt(AuxFunc::split(cut, '=')[1]));
        timestamps.append(QVariant(cut.c_str()));
    }
    qmlWindow->findChild<QObject*>("cutsList")->setProperty("model", timestamps);
    qmlWindow->findChild<QObject*>("cutsList")->setProperty("visible", true);

    qmlWindow->findChild<QObject*>("loadedCutFile")->setProperty("text", fileName.c_str());

}

void ofApp::processCutsFile(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a file");
    string filePath;
    if (openFileResult.bSuccess) {

        filePath = openFileResult.getPath();
        cout << filePath << endl;
    }

    //now we need to parse the data given by ffprobe
    //the only information we are looking for is the timestamps of the cuts
    cuts.clear();
    ifstream file(filePath);
    string line;
    vector<string> splitLine;
    while (file) {
        getline(file, line, '\n');
        //cout << line << endl;
        splitLine = AuxFunc::split(line, '|');
        if (splitLine.size() != 0) // last line is empty
            cuts.push_back(splitLine[4]);
    }

    QVariantList timestamps;
    for(string cut : cuts){
        cut = AuxFunc::formatSeconds(ofToInt(AuxFunc::split(cut, '=')[1]));
        timestamps.append(QVariant(cut.c_str()));
    }
    qmlWindow->findChild<QObject*>("cutsList")->setProperty("model", timestamps);
    qmlWindow->findChild<QObject*>("cutsList")->setProperty("visible", true);

    string fileName = AuxFunc::split(filePath.c_str(), '\\').back();
    qmlWindow->findChild<QObject*>("loadedCutFile")->setProperty("text", fileName.c_str());

}

void ofApp::selectRow(int row){
    if(video.isLoaded()){
        video.setPosition(ofToFloat(AuxFunc::split(cuts[row], '=')[1]) / video.getDuration());
        qmlVideoSeekbar->setProperty("value", QVariant(video.getPosition()));
    }
}


//--------------------------------------------------------------
void ofApp::loadDataFile(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a data file");

    if (openFileResult.bSuccess) {
        ofLogVerbose("User selected a file");
        emotionDataPath = openFileResult.getPath();

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

        ofSystemAlertDialog("Video Loaded!");


        //calcMotionDirection(0, 0);
    }

}

void ofApp::clearSelection(){
    video.close();
    emotionData = nullptr;
    emotionDataPath = "";
}

//--------------------------------------------------------------
void ofApp::volSliderChanged(float msg){
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

void ofApp::videoSeekbarChanged(float pos){
    // cout << pos << endl;
    video.setPosition(pos);
}

void ofApp::cutVideo(vector<pair<int, int>> timestamps) {

    //create a folder for each run of the algorithm
    //code originally from http://en.cppreference.com/w/cpp/chrono/c/time and http://stackoverflow.com/a/997531
    time_t folderName = time(nullptr);
    string newFolder = "data\\" + to_string(folderName);
    boost::filesystem::create_directory(newFolder);
    string tempFolder = "data\\" + to_string(folderName) + "\\temp";
    boost::filesystem::create_directory(tempFolder);

    //the created clips will have the same extension as the input
    ofFile file;
    file.open(video.getMoviePath());
    string extension = file.getExtension();

    ofVideoPlayer clip;
    //extract each clip and apply the fade in/out effect
    for (int i = 0; i < timestamps.size(); i++) {
        pair<int, int> timestamp = timestamps.at(i);

        //create the ffmpeg command to extract the clip
        string command = "ffmpeg -i " + video.getMoviePath() + " -ss ";
        command += AuxFunc::formatSeconds(timestamp.first) + " -to " + AuxFunc::formatSeconds(timestamp.second);
        command += " -y " + tempFolder + "\\clip" + to_string(i) + "." + extension;
        //command += " -c:v ffv1 data\\" + to_string(folderName) + "\\temp\\clip" + to_string(i) + "." + extension;
        cout << command << endl;

        //system("ffmpeg -i data\\WeFeel.m4v -ss 00:01:00 -to 00:02:00 -c copy data\\cut.m4v"); //example
        std::system(command.c_str());

        //create the command to apply the fade in/out effects
        string fadeCommand = "ffmpeg -i " + tempFolder + "\\clip" + to_string(i) + "." + extension;

        clip.loadMovie(tempFolder + "\\clip" + to_string(i) + "." + extension);

        //fade in is not to be added to the first clip
        if (i == 0) {
            fadeCommand += " -vf \"fade=type=out:start_frame=" + to_string(clip.getTotalNumFrames() - 12) + ":d=0.5\"";
        }
        else {
            fadeCommand += " -vf \"fade=type=in:start_frame=0:d=0.5, fade=type=out:start_frame="
                    + to_string(clip.getTotalNumFrames() - 12) + ":d=0.5\"";
        }

        fadeCommand += " -y " + newFolder + "\\clipFade" + to_string(i) + "." + extension;
        cout << fadeCommand << endl;
        std::system(fadeCommand.c_str());


        //add each clip filename to a txt file that will then be used by ffmpeg to concatenate the clips
        if (i == 0) {
            //first clip to be extracted, so the txt file also has to be created
            string newClip = "echo file '" + newFolder + "\\clipFade" + to_string(i) +
                    "." + extension + "' > " + newFolder + "\\concat.txt";
            std::system(newClip.c_str());
        }
        else {
            string newClip = "echo file '" + newFolder + "\\clipFade" + to_string(i) +
                    "." + extension + "' >> " + newFolder + "\\concat.txt";
            std::system(newClip.c_str());
        }
    }

    //concatenate the clips
    string concatCmd = "ffmpeg -f concat -i " + newFolder + "\\concat.txt -r 25 " + newFolder + "\\output." + extension;
    std::system(concatCmd.c_str());

    //this command is faster, but loses frames after the second clip
    /*string concatCmd = "ffmpeg -f concat -i data\\" + to_string(folderName) + "\\concat.txt -codec copy -r 25 data\\" +
    to_string(folderName) + "\\output.m4v";
    system(concatCmd.c_str());
    system("ffmpeg -f concat -i concat.txt -codec copy data\\output.m4v");*/

}

void ofApp::algorithm() {

    int minNumberOfEmotions = qmlWindow->findChild<QObject*>("minNumberOfEmotions")->property("text").toInt();

    if(minNumberOfEmotions == 0){
        ofSystemAlertDialog("Please choose a minimum number of emotions!");
        return;
    }

    //min number of emotions a clip must have to be included in the summary
    cout << "minNumberOfEmotions: " << minNumberOfEmotions << endl;

    int numberOfEmotions;

    int endTimestamp;

    //timestamps of the clips to be included in the final video
    vector<pair<int, int>> timestamps;

    //in case the user wants to use the cuts data, load the default cuts file
    if(qmlWindow->findChild<QObject*>("useCuts")->property("checked") == true){
        cuts.clear();
        ifstream file(DEAFULT_CUTS_FILE); //the default file has a 0.4 threshold
        string line;
        vector<string> splitLine;
        while (file) {
            getline(file, line, '\n');
            //cout << line << endl;
            splitLine = AuxFunc::split(line, '|');
            if (splitLine.size() != 0) // last line is empty
                cuts.push_back(splitLine[4]);
        }
    }

    vector<EmotionInterval> emotions = emotionData->getEmotionIntervals();
    int startTimestamp = emotions.at(0).getTimestamp();
    for (int i = 1; i < emotions.size() - 1; i++) {
        numberOfEmotions = emotions.at(i).getNumberOfEmotions();
        int valueBefore = emotions.at(i - 1).getNumberOfEmotions();
        int valueAfter = emotions.at(i + 1).getNumberOfEmotions();

        //found a peak
        if (numberOfEmotions > valueBefore && numberOfEmotions >= valueAfter
                && numberOfEmotions >= minNumberOfEmotions) {

            //TODO: for test purposes
            int clipDuration = qmlWindow->findChild<QObject*>("clipDuration")->property("text").toInt();
            if(clipDuration == 0) clipDuration = 15;
            // two thirds of the duration before the peak, the rest after the peak
            startTimestamp = emotions.at(i).getTimestamp() - (clipDuration * 2/3);
            endTimestamp = emotions.at(i).getTimestamp() + (clipDuration / 3);

            if(qmlWindow->findChild<QObject*>("useCuts")->property("checked") == true){
                //check for a cut 5 seconds before the start timestamp
                for(string cutTimestamp : cuts)
                    if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5)
                        startTimestamp = ofToInt(cutTimestamp);

            }

            cout << startTimestamp << " - " << endTimestamp << endl;


            pair<int, int> ts(startTimestamp, endTimestamp);
            timestamps.push_back(ts);
        }
    }

    cutVideo(timestamps);

}
