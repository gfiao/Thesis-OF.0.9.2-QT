#include "ofApp.h"
#include "math.h"

// global qml signal to slot object instance
QMLCallback qmlCallback;

bool sortClips(ClipWithScore clip1, ClipWithScore clip2){
    return (clip1.getTimestamps().first < clip2.getTimestamps().first);
}
bool sortByScore(ClipWithScore clip1, ClipWithScore clip2){
    return (clip1.getFinalScore() > clip2.getFinalScore());
}

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
    /*video.load("WeFeel_1.mp4");
    //=======================
    video.play();
    video.setPaused(true);
    //=======================
    int start = 30, end = 60;
    video.setPosition(start / video.getDuration());//30 seconds into the video
    ofSleepMillis(100);
    //video.update();
    ofImage img1;
    img1.setFromPixels(video.getPixels());
    img1.save("img1.jpg");

    video.setPosition(end /video.getDuration());//60 seconds into the video
    ofSleepMillis(100);
    // video.update();
    ofImage img2(video.getPixels());
    img2.save("img2.jpg");*/





    /*string filePath = "EmotionsOverTime.json";
    ifstream file(filePath); //read JSON file
    std::string content( (std::istreambuf_iterator<char>(file) ),
                         (std::istreambuf_iterator<char>()    ) );


    ofxJSONElement jsonFile;
    bool parsingSuccessful = jsonFile.open(filePath);
    cout << jsonFile.size() << endl;

    file.close();

    vector<int> nrEmotionsInSecond;
    vector<vector<string>> emotionsInSecond;
    vector<bool> eventInSecond;

    nrEmotionsInSecond.resize(jsonFile[jsonFile.size()-1]["timestamp"].asInt());
    emotionsInSecond.resize(jsonFile[jsonFile.size()-1]["timestamp"].asInt());
    eventInSecond.resize(jsonFile[jsonFile.size()-1]["timestamp"].asInt());

    for (Json::ArrayIndex i = 0; i < jsonFile.size(); i++){
        //cout << jsonFile[i]["timestamp"].asInt() << "=====" << jsonFile[i]["event"].asBool() << endl;
        int timestamp = jsonFile[i]["timestamp"].asInt();
        cout << timestamp << endl;

        if(!jsonFile[i]["emotion"].isNull()){
            nrEmotionsInSecond[timestamp] +=  1;
            //   emotionsInSecond[timestamp].second.push_back(jsonFile[i]["emotion"].asString());
        }

        if(!jsonFile[i]["event"].isNull())
            eventInSecond[timestamp] = true;
    }


    for(int i = 1; i < nrEmotionsInSecond.size(); i++){

        cout << "Timestamp: " << i << "  NrEmotions: " << emotionsInSecond[i].size() << endl;

    }*/






    cout << "OpenCV version: " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;

    emotionData = nullptr;
    audio = nullptr;

    ofBackground(ofColor::white);

    qmlSetup();

    //load the default cuts file
    cuts.clear();
    ifstream file(DEAFULT_CUTS_FILE); //the default file has a 0.4 threshold
    string line;
    vector<string> splitLine;
    while (file) {
        getline(file, line, '\n');
        //cout << line << endl;
        splitLine = AuxFunc::split(line, '|');
        if (splitLine.size() != 0) // last line is empty
            cuts.push_back(AuxFunc::split(splitLine[4], '=')[1]);
    }


    /*QObjectList checkboxes = qmlWindow->findChild<QObject*>("firstDirectionRow")->children();
    for(int i = 0; i < checkboxes.size()-1; i++)
        cout << checkboxes[i]->property("checked").toBool() << endl;*/

    /*QObjectList checkboxes1 = qmlWindow->findChild<QObject*>("secondDirectionRow")->children();
    for(QObject* obj : checkboxes1)
        cout << obj->property("checked").toBool() << endl;*/




    //TODO: code to get the text from the checkboxes, use later
    /* QObjectList checkboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    for(QObject* obj : checkboxes)
        cout << obj->property("text").toString().toStdString() << endl;*/

    // int time = ofGetElapsedTimeMillis();

    /* ofImage img;
    img.load("verde2.jpg");
    vector<ofImage> images = divideImage(img, 9);
    int res1 = checkShotType(images);
    cout << "verde2:  " << res1 << endl;

    ofImage img2;
    img2.load("ibra.jpg");
    vector<ofImage> images2 = divideImage(img2, 9);
    int res2 = checkShotType(images2);
    cout << "ibra:  " << res2 << endl;

    ofImage img3;
    img3.load("ronaldo.jpg");
    vector<ofImage> images3 = divideImage(img3, 9);
    int res3 = checkShotType(images3);
    cout << "ronaldo:  " << res3 << endl;*/

    //cout << time - ofGetElapsedTimef() << endl;
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

    /*string formatedNumber = to_string(video.getPosition()).substr(0, 5);
    //cout << ofToFloat(formatedNumber) << endl;
    // double videoPos = (double)video.getPosition();
    if(video.isLoaded())
       // if(video.getCurrentFrame() % 100 == 0)
            qmlVideoSeekbar->setProperty("value", QVariant(ofToFloat(formatedNumber)));*/


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

//TODO: MUDAR
int ofApp::checkShotType(vector<ofImage> images) {

    int hbins = 180, sbins = 32;
    vector<int> types = {0,0,0};

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
        int peaks = 0;
        int validInterval = 0;
        for(int i = 1; i < sums.size() - 1; i++){
            float valueBefore = sums[i-1];
            float valueAfter = sums[i+1];

            float sumInInterval = 0;

            if(valueBefore < sums[i] && valueAfter > sums[i] && sums[i] >= 1500){
                peaks++;
                for(int j = i - 2; j < i + 2; j++){
                    sumInInterval += sums[j];
                    // cout << j << endl;

                }
                if(sumInInterval / totalSum >= 0.3)
                    validInterval++;
            }
        }
        cout << peaks << endl;

        if (validInterval == 1)
            types[LONG_SHOT]++;
        else if (validInterval == 2 || validInterval == 3 || validInterval == 4)
            types[CLOSEUP_SHOT]++;
        else
            types[OUT_OF_FIELD]++;

    }

    int returnValue = 0;
    for(int i = 0; i < types.size(); i++){
        cout << i  << " : "<< types[i] << endl;
        if(types[i] > types[returnValue])
            returnValue = i;
    }

    return returnValue;
}


vector<cv::KeyPoint> ofApp::detectKeypoints(int timestamp) {

    cv::Mat grey;

    //extract the start keypoints
    vector<cv::KeyPoint> keypoints;
    video.setPosition(timestamp / video.getDuration());
    ofSleepMillis(150);

    ofxCv::copyGray(video, grey);

    //ofImage img(video.getPixels());
    //img.save(ofToString(timestamp) + ".jpg");

    //cv::Ptr<cv::BRISK> ptrBrisk = cv::BRISK::create();
    //ptrBrisk->detect(grey, keypoints);

    cv::FAST(grey, keypoints, 2);
    cv::KeyPointsFilter::retainBest(keypoints, 30);

    return keypoints;

}

//TODO: for now use only the first and last frame
int ofApp::calcMotionDirection(int startTimestamp, int endTimestamp) {

    //=======================
    //so we can extract the keypoints, we need to start the video first
    video.play();
    video.setPaused(true);
    //=======================

    auto start = ofGetElapsedTimeMillis();

    //extract the start keypoints
    vector<cv::KeyPoint> startKeypoints = detectKeypoints(startTimestamp);
    //cout << "startKeypoints: " << startKeypoints.size() << endl;

    //extract the end keypoints
    vector<cv::KeyPoint> endKeypoints = detectKeypoints(endTimestamp);
    // cout << "endKeypoints: " << endKeypoints.size() << endl;

    cout << "Time to extract keypoints: " << ofGetElapsedTimeMillis() - start << "ms" << endl;


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

    if(leftCounter > rightCounter)
        return LEFT;
    else if(leftCounter < rightCounter)
        return RIGHT;
    return UNDEFINED;
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
        delete audio;
        audio = new Audio(audioFile.c_str());

        video.setVolume(qmVideoVolSlider->property("value").toFloat());

        ofSystemAlertDialog("Video Loaded!");

        //calcMotionDirection(0, 0);
    }

}

void ofApp::clearSelection(){
    video.close();
    emotionData = nullptr;
    delete emotionData;
    audio = nullptr;
    delete audio;
    emotionDataPath = "";
    QObject* label = qmlWindow->findChild<QObject*>("loadFileLabel");
    label->setProperty("visible", false);

    QObject* tabView = qmlWindow->findChild<QObject*>("tabView");
    tabView->setProperty("enabled", false);
    qmlRunAlgorithm->setProperty("enabled", false);

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

void ofApp::cutVideo(vector<ClipWithScore> clips) {

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
    for (int i = 0; i < clips.size(); i++) {
        pair<int, int> timestamp = clips[i].getTimestamps();

        //create the ffmpeg command to extract the clip
        string command = "ffmpeg -i " + video.getMoviePath() + " -ss ";
        command += AuxFunc::formatSeconds(timestamp.first) + " -to " + AuxFunc::formatSeconds(timestamp.second);
        command += " -y " + tempFolder + "\\clip" + to_string(i) + "." + extension;
        //command += " -c:v ffv1 data\\" + to_string(folderName) + "\\temp\\clip" + to_string(i) + "." + extension;
        cout << command << endl;

        //system("ffmpeg -i data\\WeFeel.m4v -ss 00:01:00 -to 00:02:00 -c copy data\\cut.m4v"); //example
        std::system(command.c_str());

        if(qmlWindow->findChild<QObject*>("fadeInOut")->property("checked") == true){

            //create the command to apply the fade in/out effects
            string fadeCommand = "ffmpeg -i " + tempFolder + "\\clip" + to_string(i) + "." + extension;

            clip.load(tempFolder + "\\clip" + to_string(i) + "." + extension);

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
        else{
            //add each clip filename to a txt file that will then be used by ffmpeg to concatenate the clips
            if (i == 0) {
                //first clip to be extracted, so the txt file also has to be created
                string newClip = "echo file '" + newFolder + "\\temp\\clip" + to_string(i) +
                        "." + extension + "' > " + newFolder + "\\concat.txt";
                std::system(newClip.c_str());
            }
            else {
                string newClip = "echo file '" + newFolder + "\\temp\\clip" + to_string(i) +
                        "." + extension + "' >> " + newFolder + "\\concat.txt";
                std::system(newClip.c_str());
            }
        }
    }

    //concatenate the clips
    string concatCmd = "ffmpeg -f concat -i " + newFolder + "\\concat.txt -r 25 " + newFolder + "\\output." + extension;
    std::system(concatCmd.c_str());

    ofSystemAlertDialog("The videos has been created!");

    //this command is faster, but loses frames after the second clip
    /*string concatCmd = "ffmpeg -f concat -i data\\" + to_string(folderName) + "\\concat.txt -codec copy -r 25 data\\" +
                        to_string(folderName) + "\\output.m4v";
                        system(concatCmd.c_str());
                        system("ffmpeg -f concat -i concat.txt -codec copy data\\output.m4v");*/

}

void ofApp::algorithm() {

    //TODO: stupid solution, change later
    ifstream file(emotionDataPath);
    string line;
    getline(file, line, '\n'); //skip first line
    vector<pair<double, bool>> emotionsSecond (841); //vec[i] has the number of emotions at second i
    getline(file, line, '\n');
    while(file){
        if(AuxFunc::split(line, ':').size() == 2){
            int timestamp = ofToInt(AuxFunc::split(line, ':')[0]);
            emotionsSecond[timestamp].second = true;
            getline(file, line, '\n');
        }else{
            int timestamp = ofToInt(AuxFunc::split(line, ';')[0]);
            emotionsSecond.at(timestamp).first++;
            getline(file, line, '\n');
        }
    }
    file.close();

    //for(int i = 0; i < emotionsSecond.size(); i++)
      //  cout << emotionsSecond[i].first << endl;

    double maxValue = 0;
    for(int i = 0; i < emotionsSecond.size(); i++)
        if(emotionsSecond[i].first > maxValue)
            maxValue = emotionsSecond[i].first;


    // for(int i = 0; i < emotionsSecond.size(); i++)
    //   cout << "Timestamp: " << i << " NR: " << emotionsSecond[i].first << " Event:  " << emotionsSecond[i].second << endl;


    //===================================================

    /*int minNumberOfEmotions = qmlWindow->findChild<QObject*>("minNumberOfEmotions")->property("text").toInt();
                    //min number of emotions a clip must have to be included in the summary
                    cout << "minNumberOfEmotions: " << minNumberOfEmotions << endl;*/

    int numberOfEmotions;

    //timestamps of the clips to be included in the final video
    vector<ClipWithScore> clipsInSummary;
    vector<ClipWithScore> clips;

    bool useEmotions = qmlWindow->findChild<QObject*>("useEmotions")->property("checked").toBool();
    bool useAudio = qmlWindow->findChild<QObject*>("soundCheckbox")->property("checked").toBool();

    if(!useEmotions && !useAudio){
        ofSystemAlertDialog("You need to use emotions data and/or audio data!");
        return;
    }

    vector<EmotionInterval> emotions = emotionData->getEmotionIntervals();
    vector<pair<int, int>> eventTimestamps;
    int startTimestamp = emotions.at(0).getTimestamp();
    int endTimestamp;
    int clipDuration = qmlWindow->findChild<QObject*>("clipDuration")->property("text").toInt();
    if(clipDuration == 0) clipDuration = 20;

    //weights
    double emotionWeight = qmlWindow->findChild<QObject*>("emotionSlider")->property("value").toDouble();
    double audioWeight = qmlWindow->findChild<QObject*>("audioSlider")->property("value").toDouble();

    //movement
    string halfTime = qmlWindow->findChild<QObject*>("halfTime")->property("text").toString().toStdString();
    QObjectList firstHalfCheckboxes = qmlWindow->findChild<QObject*>("firstDirectionRow")->children();
    QObjectList secondHalfCheckboxes = qmlWindow->findChild<QObject*>("secondDirectionRow")->children();
    // for(int i = 0; i < checkboxes.size()-1; i++)
    //   cout << checkboxes[i]->property("checked").toBool() << endl;

    if(useEmotions){

        //add the events first
        for(int i = 0; i < emotionsSecond.size(); i++){
            if(emotionsSecond[i].second){
                int start = i - (clipDuration / 2);
                int end = i + (clipDuration / 2);
                pair<int, int> ts(start, end);
                eventTimestamps.push_back(ts);
            }
        }

        for(pair<int, int> event : eventTimestamps){
            ClipWithScore newClip(event, 0, 0);
            clipsInSummary.push_back(newClip);
        }


        for (int i = 1; i < emotions.size() - 1; i++) {
            numberOfEmotions = emotions[i].getNumberOfEmotions();
            int valueBefore = emotions[i - 1].getNumberOfEmotions();
            int valueAfter = emotions[i + 1].getNumberOfEmotions();


            //found a peak
            if (numberOfEmotions > valueBefore && numberOfEmotions >= valueAfter
                    /*&& numberOfEmotions >= minNumberOfEmotions*/) {

                // two thirds of the duration before the peak, the rest after the peak
                startTimestamp = emotions.at(i).getTimestamp() - (clipDuration * 3/4);
                endTimestamp = emotions.at(i).getTimestamp() + (clipDuration / 4);

                if(qmlWindow->findChild<QObject*>("useCuts")->property("checked") == true){
                    //check for a cut 5 seconds before the start timestamp
                    for(string cutTimestamp : cuts)
                        if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5){
                            startTimestamp = ofToInt(cutTimestamp);
                            // cout << "Cut detected" << endl;
                        }
                }
                //cout << startTimestamp << " - " << endTimestamp << endl;

                //we need to get the number of emotions associated with the timestamps
                double emotionsInClip = 0;
                for(int i = startTimestamp; i < endTimestamp; i++){
                    double normalizedEmotions = emotionsSecond[i].first / maxValue;
                    //cout << emotionsSecond[i].first << "/" << maxValue << endl;
                    emotionsInClip += normalizedEmotions;
                }
                //cout << "MaxValue: " << maxValue << endl;
               // cout << emotionsInClip << endl;

                //we need to get the audio values associated with the timestamps
                float audioValues = 0;
                if(useAudio){
                    for(int i = startTimestamp; i < endTimestamp; i++){
                        float normalizedAudio = audio->getSamples()[i] / audio->getMaxValue();
                        audioValues += normalizedAudio;
                    }
                }

                pair<int, int> ts(startTimestamp, endTimestamp);
                ClipWithScore newClip(ts, emotionsInClip, audioValues);
                newClip.calcFinalScore(emotionWeight, audioWeight);
                clips.push_back(newClip);

                //cout << startTimestamp << " - " << endTimestamp << " == " << newClip.getFinalScore() << endl;

            }
        }

    }else{//use only audio
        vector<float> audioSamples = audio->getSamples();

        float audioThreshold = 0;
        for(float f : audioSamples)
            audioThreshold += f;
        audioThreshold = (audioThreshold / audioSamples.size())*2;
        cout << "AudioThreshold: " << audioThreshold << endl;

        for(int i = 1; audioSamples.size() - 1; i++){
            if(i == audioSamples.size()) break; //TODO: ????????

            float sample = audioSamples[i];
            int valueBefore = audioSamples[i - 1];
            int valueAfter = audioSamples[i + 1];

            //found a peak
            if (sample > valueBefore && sample >= valueAfter
                    && sample >= audioThreshold) {

                // two thirds of the duration before the peak, the rest after the peak
                startTimestamp = i - (clipDuration * 2/3);
                endTimestamp = i + (clipDuration / 3);

                if(qmlWindow->findChild<QObject*>("useCuts")->property("checked") == true){
                    //check for a cut 5 seconds before the start timestamp
                    for(string cutTimestamp : cuts)
                        if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5){
                            startTimestamp = ofToInt(cutTimestamp);
                            // cout << "Cut detected" << endl;
                        }
                }

                //we need to get the audio values associated with the timestamps
                float audioValues = 0;
                for(int i = startTimestamp; i < endTimestamp; i++)
                    audioValues += audio->getSamples()[i];

                pair<int, int> ts(startTimestamp, endTimestamp);
                ClipWithScore newClip(ts, 0, audioValues);
                double emotionWeight = qmlWindow->findChild<QObject*>("emotionSlider")->property("value").toDouble();
                double audioWeight = qmlWindow->findChild<QObject*>("audioSlider")->property("value").toDouble();
                newClip.calcFinalScore(emotionWeight, audioWeight);
                clips.push_back(newClip);

                cout << startTimestamp << " - " << endTimestamp << " == " << newClip.getFinalScore() << endl;

            }
        }

    }


    ofSort(clips, sortClips);
    for(int n = 0; n < 2; n++) //merge extracted clips
        for(int i = 0; i < clips.size() - 1; i++){
            pair<int, int> ts = clips[i].getTimestamps();
            if(clips[i].getTimestamps().second > clips[i+1].getTimestamps().first){
                //cout << "merge" << endl;
                clips.erase(clips.begin()+i);
                clips[i].setTimestamps(ts.first, ts.second + 5);
            }
        }

    //for(ClipWithScore c : clips)
    //  cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore() << endl;
    //cout << "===========================" <<endl;

    ofSort(clips, sortClips);
    for(int n = 0; n < 2; n++) //merge event clips with other clips
        for(int i = 0; i < eventTimestamps.size(); i++){
            int eventEnd = eventTimestamps[i].second;
            for(int j = 0; j < clips.size(); j++){
                if(eventEnd > clips[j].getTimestamps().first){
                    clips.erase(clips.begin()+j);
                    break;
                }

            }
        }

    for(ClipWithScore c : clips)
        cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore() << endl;

    int summaryDuration = qmlWindow->findChild<QObject*>("summaryDuration")->property("text").toInt();
    if(summaryDuration == 0) summaryDuration = 3;
    ofSort(clips, sortByScore);
    //  for(ClipWithScore c : clips)
    //    cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore() << endl;

    int totalDuration = clipsInSummary.size() * clipDuration;
    int i = 0;
    while(totalDuration < summaryDuration * 60 && i < clips.size()){
        clipsInSummary.push_back(clips[i]);
        pair<int, int> ts = clips[i].getTimestamps();
        totalDuration += (ts.second - ts.first);
        i++;
    }

    ofSort(clipsInSummary, sortClips);
    //merge clips in the final summary
    for(int i = 0; i < clipsInSummary.size()-1; i++){
        pair<int, int> ts = clipsInSummary[i].getTimestamps();
        pair<int, int> nextTs = clipsInSummary[i+1].getTimestamps();
        if(clipsInSummary[i].getTimestamps().second > nextTs.first){
            //cout << ts.first << " " << ts.second << endl;
            //cout << nextTs.first << " " << nextTs.second << endl << endl;
            clipsInSummary.erase(clipsInSummary.begin()+(i+1));
            clipsInSummary[i].setTimestamps(ts.first, ts.second + 3);
            //cout << "merge " << ts.first << " to " << nextTs.second << endl;
        }
    }

    totalDuration = clipsInSummary.size() * clipDuration;
    cout << "TotalDuration: " << totalDuration << " === " << "SummaryDur: " << summaryDuration * 60 << endl;
    cout << "Clips in summary: " << clipsInSummary.size() << endl;


    for(ClipWithScore c : clipsInSummary)
        cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore() << endl;

    //cutVideo(clipsInSummary);

}
