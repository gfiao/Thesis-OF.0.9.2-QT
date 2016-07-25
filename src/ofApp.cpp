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
    videoPath = "C:\\openFrameworks-master\\apps\\myApps\\thesis\\bin\\data\\WeFeel_1.mp4";
    cout << checkShotTypeClip(50, 75) << endl;*/

    /*video.load("WeFeel_1.mp4");
    video.play();
    video.setPaused(true);

    ofxXmlSettings xml;
    bool loadedFile = xml.loadFile("colorData.xml");
    xml.save("colorData.xml");

    xml.addTag("colorData");
    xml.pushTag("colorData");

    for(int i = 0; i < video.getTotalNumFrames(); i++){
        ofImage img;
        img.setFromPixels(video.getPixels());

        float pctInPeak = getPctInPeak(img, 9, 6);

        xml.addTag("data");
        xml.pushTag("data", i);

        xml.addValue("frame", i);
        xml.addValue("value", pctInPeak);

        xml.popTag();
        video.nextFrame();

        xml.saveFile();
    }*/




    /* ofDirectory dir("data");
    dir.allowExt("jpg");
    dir.listDir();
    ofImage img;
    float totalPeakPixels, pOfPeakPixels;
    for(int i = 0; i < dir.size(); i++){

        totalPeakPixels = 0, pOfPeakPixels = 0;

        img.load(dir.getPath(i));
        cout << dir.getPath(i) << endl;
        vector<ofImage> subImages = divideImage(img, 9);

        for(int i = 3; i < subImages.size(); i++){

            float totalSum = 0, maxValue = 0;
            int maxValueIndex = 0;
            vector<float> hist = getHistogram(img, totalSum, maxValue, maxValueIndex);

            int hMin = 0, hMax = 0;
            getMinMaxOfPeak(hist, hMin, hMax, maxValueIndex, maxValue);

            float peakPixels = 0;
            for(int j = hMin; j < hMax; j++){
                peakPixels += hist[j];
            }
            pOfPeakPixels = peakPixels / totalSum;
            totalPeakPixels += pOfPeakPixels;

        }

        totalPeakPixels = totalPeakPixels / 6;

        cout << totalPeakPixels << endl;

    }*/

    //TODO: isto aqui
    //    auto time = ofGetElapsedTimeMillis();
    //    longShotThreshold = detectShotThreshold();
    //    outOfFieldThreshold = 1 - longShotThreshold;
    //    cout << "Time to train: " << ofGetElapsedTimeMillis() - time << endl;
    //    cout << "Long-shot threshold: " << longShotThreshold << endl;
    //    cout << "Out-of-field threshold: " << outOfFieldThreshold << endl;

    cout << "OpenCV version: " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;

    emotionData = nullptr;
    audio = nullptr;

    ofBackground(ofColor::white);

    qmlSetup();
    loadDefaultCutFile();

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

    chartInterval = qmlWindow->findChild<QObject*>("chartInterval");

    // connect qml signals and slots
    qmlCallback.ofAppInstance = this;

    QObject::connect(qmlLoadDataFile, SIGNAL( clicked() ),
                     &qmlCallback, SLOT( dataFileSlot() ));
    QObject::connect(qmlLoadDataParameters, SIGNAL( clicked() ),
                     &qmlCallback, SLOT( dataParametersSlot() ));

    QObject::connect(qmlLoadVideo, SIGNAL( clicked() ),
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

    QObject::connect(chartInterval, SIGNAL( chartSignal(QVariant) ),
                     &qmlCallback, SLOT( chartIntervalSlot(QVariant) ));
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

float ofApp::detectShotThreshold(){

    ofDirectory dir(TRAIN_ASSETS);
    dir.listDir();
    ofImage img;

    int subImagesToProcess = 6;
    int nOfsubImages = 9;

    float threshold = 0;
    float totalPeakPixels, pOfPeakPixels;

    for(int i = 0; i < dir.size(); i++){
        //get image and the respective histogram
        img.load(dir.getPath(i));

        totalPeakPixels = 0, pOfPeakPixels = 0;

        //cout << dir.getName(i) << endl;

        vector<ofImage> subImages = divideImage(img, nOfsubImages);

        for(int i = (nOfsubImages - subImagesToProcess); i < subImages.size(); i++){

            float totalSum = 0, maxValue = 0;
            int maxValueIndex = 0;
            vector<float> hist = getHistogram(subImages[i], totalSum, maxValue, maxValueIndex);

            //cout << maxValue << " " << maxValueIndex << endl;

            //now we need to know the percentage of green pixels in the image
            int hMin = 0, hMax = 0;
            getMinMaxOfPeak(hist, hMin, hMax, maxValueIndex, maxValue);

            float peakPixels = 0;
            for(int j = hMin; j < hMax; j++){
                peakPixels += hist[j];
            }
            pOfPeakPixels = peakPixels / totalSum;
            totalPeakPixels += pOfPeakPixels;

            //cout << pOfGreenPixels << endl;
        }
        //percentage of green pixels in the image
        totalPeakPixels = totalPeakPixels / subImagesToProcess;
        //cout << totalPeakPixels << endl;

        threshold += totalPeakPixels;
    }

    threshold = threshold / dir.size();

    //cout << "Long-shot threshold: " << threshold << endl;

    return threshold;

}

//finds and return the min and max index of a peak
void ofApp::getMinMaxOfPeak(vector<float> hist, int& hMin, int& hMax, int maxValueIndex, float maxValue){

    for(int j = maxValueIndex; j < hist.size(); j++){
        //cout << sums[j] << endl;
        if(hist[j] < 0.2 * maxValue){
            hMax = j;
            break;
        }
    }
    // cout << endl;
    for(int j = maxValueIndex; j > 0; j--){
        // cout << sums[j] << endl;
        if(hist[j] < 0.2 * maxValue){
            hMin = j;
            break;
        }
    }
    //cout << hMin << " - " << maxValueIndex << " - " << hMax << endl;

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

    default:
        subImages.push_back(img);
        break;
    }

    return subImages;
}

//code originally from http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=calcHist
vector<float> ofApp::getHistogram(ofImage image, float& totalSum, float& maxValue, int& maxValueIndex) {

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

    vector<float> sums;
    for (int h = 0; h < hbins; h++) {
        float sum = 0;
        for (int s = 0; s < sbins; s++) {
            sum += hist.at<float>(h, s);
            totalSum += hist.at<float>(h, s);
        }
        if(maxValue < sum){
            maxValue = sum;
            maxValueIndex = h;
        }

        sums.push_back(sum);
    }
    // cout << totalSum << " " << maxValue << " " << maxValueIndex << endl;

    return sums;
}

int ofApp::checkShotType(ofImage frame) {

    QObject* model = qmlWindow->findChild<QObject*>("subimmageCB");
    string processSpeed = model->property("currentText").toString().toStdString();
    int nOfSubImages;

    if(processSpeed == "1 (Fast)")
        nOfSubImages = 1;
    else if(processSpeed == "2")
        nOfSubImages = 2;
    else if(processSpeed == "3")
        nOfSubImages = 4;
    else if(processSpeed == "4")
        nOfSubImages = 6;
    else if(processSpeed == "5 (Slow)")
        nOfSubImages = 9;
    else
        nOfSubImages = 1;

    int subImagesToProcess;
    if(nOfSubImages == 9)
        subImagesToProcess = 6;
    else
        subImagesToProcess = 1;

    float totalPeakPixels = 0, pOfPeakPixels = 0;

    vector<ofImage> subImages = divideImage(frame, nOfSubImages);
    for(int i = (nOfSubImages - subImagesToProcess); i < subImages.size(); i++){

        float totalSum = 0, maxValue = 0;
        int maxValueIndex = 0;
        vector<float> hist = getHistogram(subImages[i], totalSum, maxValue, maxValueIndex);

        //cout << maxValue << " " << maxValueIndex << endl;

        //now we need to know the percentage of green pixels in the image
        int hMin = 0, hMax = 0;
        getMinMaxOfPeak(hist, hMin, hMax, maxValueIndex, maxValue);

        float peakPixels = 0;
        for(int j = hMin; j < hMax; j++){
            peakPixels += hist[j];
        }
        pOfPeakPixels = peakPixels / totalSum;
        totalPeakPixels += pOfPeakPixels;

        //cout << pOfGreenPixels << endl;
    }
    //percentage of peak pixels in the image
    totalPeakPixels = totalPeakPixels / subImagesToProcess;
    //cout << totalPeakPixels << endl;

    if(totalPeakPixels >= longShotThreshold)
        return LONG_SHOT;
    else if(totalPeakPixels <= outOfFieldThreshold)
        return OUT_OF_FIELD;
    else
        return CLOSEUP_SHOT;

}

float ofApp::getPctInPeak(ofImage frame, int nOfSubImages, int subImagesToProcess){

    float totalPeakPixels = 0, pOfPeakPixels = 0;

    vector<ofImage> subImages = divideImage(frame, nOfSubImages);
    for(int i = (nOfSubImages - subImagesToProcess); i < subImages.size(); i++){

        float totalSum = 0, maxValue = 0;
        int maxValueIndex = 0;
        vector<float> hist = getHistogram(subImages[i], totalSum, maxValue, maxValueIndex);

        //cout << maxValue << " " << maxValueIndex << endl;

        //now we need to know the percentage of green pixels in the image
        int hMin = 0, hMax = 0;
        getMinMaxOfPeak(hist, hMin, hMax, maxValueIndex, maxValue);

        float peakPixels = 0;
        for(int j = hMin; j < hMax; j++){
            peakPixels += hist[j];
        }
        pOfPeakPixels = peakPixels / totalSum;
        totalPeakPixels += pOfPeakPixels;

        //cout << pOfGreenPixels << endl;
    }
    //percentage of peak pixels in the image
    totalPeakPixels = totalPeakPixels / subImagesToProcess;

    return totalPeakPixels;

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
    cv::KeyPointsFilter::retainBest(keypoints, 60);

    return keypoints;

}

int ofApp::calcMotionDirection(int startTimestamp, int endTimestamp) {

    //=======================
    //so we can extract the keypoints, we need to start the video first
    video.play();
    video.setPaused(true);
    //=======================

    //auto start = ofGetElapsedTimeMillis();

    //extract the start keypoints
    vector<cv::KeyPoint> startKeypoints = detectKeypoints(startTimestamp);
    //cout << "startKeypoints: " << startKeypoints.size() << endl;

    //extract the end keypoints
    vector<cv::KeyPoint> endKeypoints = detectKeypoints(endTimestamp);
    // cout << "endKeypoints: " << endKeypoints.size() << endl;

    //cout << "Time to extract keypoints: " << ofGetElapsedTimeMillis() - start << "ms" << endl;


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

    //cout << "leftCounter: " << leftCounter << " ===== " << "rightCounter: " << rightCounter << endl;

    if(leftCounter > rightCounter)
        return LEFT;
    else if(leftCounter < rightCounter)
        return RIGHT;
    return UNDEFINED;
}

void ofApp::loadDefaultCutFile(){

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

}

//detects sudden cuts between two timestamps
vector<pair<int, int>> ofApp::detectCutsIn(int start, int end){
    vector<pair<int, int>> ret;
    vector<int> cutsIn;

    for(string cut : cuts)
        if(ofToInt(cut) > start && ofToInt(cut) < end)
            cutsIn.push_back(ofToInt(cut));


    for(int i = 0; i < cutsIn.size(); i++){
        if(cutsIn[i] > start && cutsIn[i] < end){
            pair<int, int> ts(start, cutsIn[i]);
            ret.push_back(ts);
            start = cutsIn[i];
        }
    }
    pair<int, int> ts(start, end);
    ret.push_back(ts);

    return ret;
}

void ofApp::motionHelper(int start, int end, ClipWithScore& newClip){
    int motion = 0;
    vector<pair<int, int>> ts = detectCutsIn(start, end);
    //cout << "detectCutsIn size: " << ts.size() << endl;
    if(!ts.empty()){
        vector<int> movRes = {0, 0, 0};
        for(int i = 0; i < ts.size(); i++){
            movRes[calcMotionDirection(ts[i].first, ts[i].second)]++;
        }
        motion = AuxFunc::getMax(movRes);
    }
    else{
        //cout << "ktime: " << start << "-" << end << endl;
        motion = calcMotionDirection(start, end);
    }
    newClip.setMovement(motion);
    //cout << newClip.getMovement() << endl;
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

    //Load the emotions data
    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a data file");

    if (openFileResult.bSuccess) {
        if(ofFile(openFileResult.getPath()).getExtension() != "xml"){
            ofSystemAlertDialog("That's not a XML file!");
            return;
        }
        emotionDataPath = openFileResult.getPath();

        cout << emotionDataPath << endl;
    }

    QObject* emotionsLabel = qmlWindow->findChild<QObject*>("loadFileLabel");
    string emotionDataFileName = AuxFunc::split(emotionDataPath, '\\').back();
    emotionsLabel->setProperty("visible", true);
    emotionsLabel->setProperty("text", QVariant(emotionDataFileName.c_str()));
}

void ofApp::loadVideoFile(){

    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a video file");
    if(openFileResult.bSuccess){
        string extension = ofFile(openFileResult.getPath()).getExtension();
        if(extension != "mp4" && extension != "mpeg"){
            ofSystemAlertDialog("That's not a video file!");
            return;
        }
        videoPath = openFileResult.getPath();

        cout << videoPath << endl;
    }

    QObject* videoLabel = qmlWindow->findChild<QObject*>("loadVideoLabel");
    string videoName = AuxFunc::split(videoPath.c_str(), '\\').back();
    videoLabel->setProperty("visible", true);
    videoLabel->setProperty("text", QVariant(videoName.c_str()));

}

void ofApp::loadFiles(){

    QObject *interval_textfield = qmlWindow->findChild<QObject*>("interval_textfield");
    QString intervalValue = interval_textfield->property("text").toString();
    cout << intervalValue.toStdString() << endl;

    //QObject *dynInter_textfield = qmlWindow->findChild<QObject*>("dynInter_textfield");
    //QString dynIntValue = dynInter_textfield->property("text").toString();

    cout << intervalValue.size() << endl;

    if (intervalValue.size() > 0 /*&& dynIntValue.size() == 0*/){
        emotionData = new EmotionData(emotionDataPath, ofToInt(intervalValue.toStdString()));
    }
    /* else if (intervalValue.size() > 0 && dynIntValue.size() > 0){
        emotionData = new EmotionData(emotionDataPath, ofToInt(intervalValue.toStdString()),
                                      ofToInt(dynIntValue.toStdString()));
    }
    else if (dynIntValue.size() > 0){
        emotionData = new EmotionData(emotionDataPath, 5, ofToInt(dynIntValue.toStdString()));
    }*/
    else{
        emotionData = new EmotionData(emotionDataPath); //5 second intervals
    }

    cout << "Emotions Data Loaded!" << endl;

    //====================================================

    video.load(videoPath);

    cout << "Video duration: " << video.getDuration() << endl;
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

    cout << "Video file loaded!" << endl;

    populateChart();

    ofSystemAlertDialog("Files loaded successfully!");

    qmlWindow->findChild<QObject*>("loadDataWindow")->setProperty("visible", false);

}

void ofApp::clearSelection(){
    video.close();
    emotionData = nullptr;
    delete emotionData;
    audio = nullptr;
    delete audio;
    emotionDataPath = "";
    QObject* emotionLabel = qmlWindow->findChild<QObject*>("loadFileLabel");
    emotionLabel->setProperty("visible", false);
    QObject* videoLabel = qmlWindow->findChild<QObject*>("loadVideoLabel");
    videoLabel->setProperty("visible", false);

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

void ofApp::populateChart(){

    int interval = 30;

    //check what emotions are to be used in the algorithm
    //    vector<string> emotionCheckboxesStd;
    //    QObjectList emotionCheckboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    //    for(int i = 0; i < emotionCheckboxes.size()-1; i++){
    //        if(emotionCheckboxes[i]->property("checked").toBool())
    //            emotionCheckboxesStd.push_back(emotionCheckboxes[i]->property("text").toString().toStdString());
    //    }

    vector<EmotionInterval> emotions;
    if(emotionData != nullptr)
        emotions = emotionData->setInterval(interval);
    else{
        cout << "No data loaded!" << endl;
        return;
    }

    int maxX = emotions.back().getTimestamp();
    int maxY = emotionData->getMaxValueInterval();

    QObject* chart = qmlWindow->findChild<QObject*>("chartWindow");
    QVariant returnedValue;

    for(int i = 0; i < emotions.size(); i++){

        QVariant x = emotions[i].getTimestamp();
        QVariant y = emotions[i].getNumberOfEmotions();
        QMetaObject::invokeMethod(chart, "populateChart", Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, x), Q_ARG(QVariant, y),
                                  Q_ARG(QVariant, maxX), Q_ARG(QVariant, maxY));

    }

    int maxValue = 0;
    vector<float> audioValues = audio->setInterval(interval, maxValue);
    for(int i = 0; i < audioValues.size(); i++){

        QVariant x = interval * i;
        QVariant y = audioValues[i];
        QMetaObject::invokeMethod(chart, "populateAudio", Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, x), Q_ARG(QVariant, y), Q_ARG(QVariant, maxValue));

    }


}

void ofApp::changeChartInterval(int interval){

    //check what emotions are to be used in the algorithm
    //    vector<string> emotionCheckboxesStd;
    //    QObjectList emotionCheckboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    //    for(int i = 0; i < emotionCheckboxes.size()-1; i++){
    //        if(emotionCheckboxes[i]->property("checked").toBool())
    //            emotionCheckboxesStd.push_back(emotionCheckboxes[i]->property("text").toString().toStdString());
    //    }

    vector<EmotionInterval> emotions;
    if(emotionData != nullptr)
        emotions = emotionData->setInterval(interval);
    else{
        cout << "No data loaded!" << endl;
        return;
    }

    QObject* intervalLabel = qmlWindow->findChild<QObject*>("intervalValue");
    intervalLabel->setProperty("text", interval);

    int maxX = emotions.back().getTimestamp();
    int maxY = emotionData->getMaxValueInterval();

    QObject* chart = qmlWindow->findChild<QObject*>("chartWindow");
    QVariant returnedValue;

    //clear charts
    QMetaObject::invokeMethod(chart, "clearSeries", Q_RETURN_ARG(QVariant, returnedValue));

    for(int i = 0; i < emotions.size(); i++){

        QVariant x = emotions[i].getTimestamp();
        QVariant y = emotions[i].getNumberOfEmotions();
        QMetaObject::invokeMethod(chart, "populateChart", Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, x), Q_ARG(QVariant, y),
                                  Q_ARG(QVariant, maxX), Q_ARG(QVariant, maxY));

    }

    int maxValue = 0;
    vector<float> audioValues = audio->setInterval(interval, maxValue);
    for(int i = 0; i < audioValues.size(); i++){

        QVariant x = interval * i;
        QVariant y = audioValues[i];
        QMetaObject::invokeMethod(chart, "populateAudio", Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, x), Q_ARG(QVariant, y), Q_ARG(QVariant, maxValue));

    }

}

void ofApp::cutVideo(vector<ClipWithScore> clips) {

    //create a folder for each run of the algorithm
    /*string newFolder = "data\\" + ofGetTimestampString();
    boost::filesystem::create_directory(newFolder);
    string tempFolder = "data\\" + ofGetTimestampString() + "\\temp";
    boost::filesystem::create_directory(tempFolder);*/
    time_t folderName = time(nullptr);
    string newFolder = "data\\" + to_string(folderName);
    boost::filesystem::create_directory(newFolder);
    string tempFolder = "data\\" + to_string(folderName) + "\\temp";
    boost::filesystem::create_directory(tempFolder);

    //the created clips will have the same extension as the input
    ofFile file;
    file.open(video.getMoviePath());
    string extension = file.getExtension();
    vector<string> clipNames;
    //ofVideoPlayer clip;

    string extractCmd = "ffmpeg -i " + video.getMoviePath();
    //extract each clip and apply the fade in/out effect
    for (int i = 0; i < clips.size(); i++) {
        pair<int, int> timestamp = clips[i].getTimestamps();

        //create the ffmpeg command to extract the clip
        extractCmd += " -ss " + AuxFunc::formatSeconds(timestamp.first) + " -to " + AuxFunc::formatSeconds(timestamp.second);
        extractCmd += " -qscale 6 -c copy " + tempFolder + "\\clip" + to_string(i) + "." + extension;
        //command += " -c:v ffv1 data\\" + to_string(folderName) + "\\temp\\clip" + to_string(i) + "." + extension;


        //system("ffmpeg -i data\\WeFeel.m4v -ss 00:01:00 -to 00:02:00 -c copy data\\cut.m4v"); //example
        //std::system(command.c_str());

        /*
        //add fade in/out effect
        if(qmlWindow->findChild<QObject*>("fadeInOut")->property("checked") == true){

            //create the command to apply the fade in/out effects
            string fadeCommand = "ffmpeg -i " + tempFolder + "\\clip" + to_string(i) + "." + extension;

            clip.load(tempFolder + "\\clip" + to_string(i) + "." + extension);

            //fadein is not to be added to the first clip
            if (i == 0) {
                fadeCommand += " -vf \"fade=type=out:start_frame=" + to_string(clip.getTotalNumFrames() - 12) + ":d=0.5\"";
            }
            else {
                fadeCommand += " -vf \"fade=type=in:start_frame=0:d=0.5, fade=type=out:start_frame="
                        + to_string(clip.getTotalNumFrames() - 12) + ":d=0.5\"";
            }

            fadeCommand += " -qscale 6 " + newFolder + "\\clipFade" + to_string(i) + "." + extension;
            cout << fadeCommand << endl;
            std::system(fadeCommand.c_str());


            //add each clip filename to a txt file that will then be used by ffmpeg to concatenate the clips
            string clipPath;
            if (i == 0) {
                //first clip to be extracted, so the txt file also has to be created
                string newClip = "echo file '" + newFolder + "\\clipFade" + to_string(i) +
                        "." + extension + "' > " + newFolder + "\\concat.txt";
                std::system(newClip.c_str());
                clipPath = newFolder + "\\clipFade" + to_string(i) + "." + extension;
            }
            else {
                string newClip = "echo file '" + newFolder + "\\clipFade" + to_string(i) +
                        "." + extension + "' >> " + newFolder + "\\concat.txt";
                std::system(newClip.c_str());
                clipPath = newFolder + "\\clipFade" + to_string(i) + "." + extension;
            }
            clipNames.push_back(clipPath);
        }*/

        // else{//dont add fade in/out effect
        //add each clip filename to a txt file that will then be used by ffmpeg to concatenate the clips
        string clipPath;
        if (i == 0) {
            //first clip to be extracted, so the txt file also has to be created
            string newClip = "echo file '" + newFolder + "\\temp\\clip" + to_string(i) +
                    "." + extension + "' > " + newFolder + "\\concat.txt";
            std::system(newClip.c_str());
            clipPath = newFolder + "\\temp\\clip" + to_string(i) + "." + extension;
        }
        else {
            string newClip = "echo file '" + newFolder + "\\temp\\clip" + to_string(i) +
                    "." + extension + "' >> " + newFolder + "\\concat.txt";
            std::system(newClip.c_str());
            clipPath = newFolder + "\\temp\\clip" + to_string(i) + "." + extension;
        }
        clipNames.push_back(clipPath);
        //}
    }
    cout << extractCmd << endl;
    system(extractCmd.c_str());

    //concatenate the clips
    string concatCmd = "";
    if(extension == "mpeg"){
        string files;
        for(string s : clipNames){
            files += s + "|";
        }
        files.pop_back();
        concatCmd = "ffmpeg -i \"concat:" + files + "\" -c copy " + newFolder + "\\output." + extension;
    }
    else
        concatCmd = "ffmpeg -safe 0 -f concat -i " + newFolder + "\\concat.txt -qscale 6 -c copy " + newFolder + "\\output." + extension;
    cout << concatCmd << endl;
    system(concatCmd.c_str());

    ofSystemAlertDialog("The videos has been created!");

    //this command is faster, but loses frames after the second clip
    /*string concatCmd = "ffmpeg -f concat -i data\\" + to_string(folderName) + "\\concat.txt -codec copy -r 25 data\\" +
                        to_string(folderName) + "\\output.m4v";
                        system(concatCmd.c_str());
                        system("ffmpeg -f concat -i concat.txt -codec copy data\\output.m4v");*/

}

bool ofApp::useAllEmotions(){

    bool res = true;
    QObjectList emotionCheckboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    for(int i = 0; i < emotionCheckboxes.size()-1; i++){
        if(!emotionCheckboxes[i]->property("checked").toBool())
            res = false;
    }

    return res;
}

void ofApp::setEmotionsToUse(EmotionInterval &ei){

    vector<string> emotions;
    QObjectList emotionCheckboxes = qmlWindow->findChild<QObject*>("checkboxRow")->children();
    for(string s : ei.getEmotions()){
        for(int i = 0; i < emotionCheckboxes.size()-1; i++){
            string emotion = emotionCheckboxes[i]->property("text").toString().toStdString();
            bool compare = boost::iequals(s, emotion);
            if(compare && emotionCheckboxes[i]->property("checked").toBool())
                emotions.push_back(s);
        }
    }
    ei.setEmotions(emotions);

}

int ofApp::checkShotTypeClip(int startTimestamp, int endTimestamp){

    //TODO: resultados mais interessantes
    longShotThreshold = 0.6;
    outOfFieldThreshold = 0.15;

    ofxXmlSettings xml;
    string fileName = AuxFunc::split( ofFile(videoPath).getFileName(), '.')[0];
    // cout << fileName << endl;
    if(!xml.load("color\\" + fileName + ".xml")){
        //criar ficheiro mais tarde
        cout << "criar ficheiro" << endl;
        return -1;
    }
    else{
        //cout << "acessing xml" << endl;
    }

    vector<float> types = {0.0, 0.0, 0.0};
    video.setPosition(startTimestamp / video.getDuration());
    int startFrame = video.getCurrentFrame();
    video.setPosition(endTimestamp / video.getDuration());
    int endFrame = video.getCurrentFrame();

    xml.pushTag("colorData");

    for(int i = startFrame; i < endFrame; i++){

        xml.pushTag("data", i);
        //cout << xml.getValue("value", 0.0) << endl;
        if(xml.getValue("value", 0.0) >= longShotThreshold)
            types[LONG_SHOT]++;
        else if(xml.getValue("value", 0.0) <= outOfFieldThreshold)
            types[OUT_OF_FIELD]++;
        else types[CLOSEUP_SHOT]++;

        //cout << xml.getValue("value", 0.0) << endl;

        xml.popTag();

    }

    float nOfFrames = endFrame - startFrame;
    /* cout << types[LONG_SHOT] <<"/"<< nOfFrames << "=" << types[LONG_SHOT] / nOfFrames << endl;
    cout << types[CLOSEUP_SHOT] <<"/"<< nOfFrames << "=" << types[CLOSEUP_SHOT] / nOfFrames << endl;
    cout << types[OUT_OF_FIELD] <<"/"<< nOfFrames << "=" << (types[OUT_OF_FIELD] / nOfFrames) << endl;

    cout << endl;*/
    if(types[OUT_OF_FIELD] / nOfFrames >= 0.2){
        // cout << "set as OUT_OF_FIELD" << endl;
        return OUT_OF_FIELD;
    }
    else if(types[LONG_SHOT] / nOfFrames >= 0.55){
        //cout << "set as LONG_SHOT" << endl;
        return LONG_SHOT;
    }
    else{
        //cout << "set as CLOSEUP_SHOT" << endl;
        return CLOSEUP_SHOT;
    }


}

void ofApp::useOnlyMov(bool useAudio, bool useCuts, bool useColor, vector<ClipWithScore> &clips){

    int duration = video.getDuration();
    int clipDuration = qmlWindow->findChild<QObject*>("clipDuration")->property("text").toInt();
    if(clipDuration == 0) clipDuration = 20;

    for(int i = 1;i < duration; i += clipDuration){

        int startTimestamp = i;
        int endTimestamp = i + clipDuration;

        if(useCuts)//check for a cut 5 seconds before the start timestamp
            for(string cutTimestamp : cuts)
                if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5)
                    startTimestamp = ofToInt(cutTimestamp);


        //we need to get the audio values associated with the timestamps
        float audioValues = 0;
        if(useAudio){
            for(int i = startTimestamp; i < endTimestamp; i++){
                float normalizedAudio = audio->getSamples()[i] / audio->getMaxValue();
                audioValues += normalizedAudio;
            }
        }

        pair<int, int> ts(startTimestamp, endTimestamp);
        ClipWithScore newClip(ts, 0, audioValues);

        if(useColor){
            int shotType = checkShotTypeClip(startTimestamp, endTimestamp);
            newClip.setShotType(shotType);
        }

        if(useAudio)
            newClip.calcFinalScore(0, 1);
        else
            newClip.calcFinalScore(0, 0);

        motionHelper(startTimestamp, endTimestamp, newClip);

        clips.push_back(newClip);

    }

}

void ofApp::selectClipMov(int& totalDuration, vector<ClipWithScore>& clips,
                          vector<ClipWithScore>& clipsInSummary, int& index, bool useColor, bool longShot,
                          bool closeup, bool offField){

    if(useColor){
        int type = clips[index].getShotType();
        if(!longShot && type == LONG_SHOT){
            return;
        }
        else if(!closeup && type == CLOSEUP_SHOT){
            return;
        }
        else if(!offField && type == OUT_OF_FIELD){
            return;
        }
    }

    QObjectList firstHalfCheckboxes = qmlWindow->findChild<QObject*>("firstDirectionRow")->children();
    QObjectList secondHalfCheckboxes = qmlWindow->findChild<QObject*>("secondDirectionRow")->children();

    bool firstLeftCheckbox = firstHalfCheckboxes[0]->property("checked").toBool();
    bool firstRightCheckbox = firstHalfCheckboxes[1]->property("checked").toBool();

    bool secondLeftCheckbox = secondHalfCheckboxes[0]->property("checked").toBool();
    bool secondRightCheckbox = secondHalfCheckboxes[1]->property("checked").toBool();

    int halfTime = video.getDuration() / 2;
    pair<int, int> ts = clips[index].getTimestamps();

    if(ts.first < halfTime){

        if(firstLeftCheckbox && !firstRightCheckbox){
            if(clips[index].getMovement() == LEFT){
                clipsInSummary.push_back(clips[index]);
                totalDuration += (ts.second - ts.first);
            }
        }
        else if(firstRightCheckbox && !firstLeftCheckbox){
            if(clips[index].getMovement() == RIGHT){
                clipsInSummary.push_back(clips[index]);
                totalDuration += (ts.second - ts.first);
            }
        }
        else{//any direction
            clipsInSummary.push_back(clips[index]);
            totalDuration += (ts.second - ts.first);
        }
    }
    else{

        if(secondLeftCheckbox && !secondRightCheckbox){
            if(clips[index].getMovement() == LEFT){
                clipsInSummary.push_back(clips[index]);
                totalDuration += (ts.second - ts.first);
            }
        }
        else if(secondRightCheckbox && !secondLeftCheckbox){
            if(clips[index].getMovement() == RIGHT){
                clipsInSummary.push_back(clips[index]);
                totalDuration += (ts.second - ts.first);
            }
        }
        else{//any direction
            clipsInSummary.push_back(clips[index]);
            totalDuration += (ts.second - ts.first);
        }

    }
}

void ofApp::selectClipColor(vector<ClipWithScore> &clips, vector<ClipWithScore> &clipsInSummary,
                            bool longShot, bool closeup, bool offField, int& totalDuration, int& index){

    pair<int, int> ts = clips[index].getTimestamps();
    int type = clips[index].getShotType();
    if(longShot && type == LONG_SHOT){
        clipsInSummary.push_back(clips[index]);
        totalDuration += (ts.second - ts.first);
    }
    else if(closeup && type == CLOSEUP_SHOT){
        clipsInSummary.push_back(clips[index]);
        totalDuration += (ts.second - ts.first);
    }
    else if(offField && type == OUT_OF_FIELD){
        clipsInSummary.push_back(clips[index]);
        totalDuration += (ts.second - ts.first);
    }

}

void ofApp::algorithm() {

    //auto time = ofGetElapsedTimeMillis();


    vector<pair<int, vector<string>>> emotionsInSecond = emotionData->getEmotionsInSecond();
    vector<bool> eventInSecond = emotionData->getEventInSecond();

    vector<ClipWithScore> clips;
    vector<ClipWithScore> clipsInSummary;


    bool useEmotions = qmlWindow->findChild<QObject*>("useEmotions")->property("checked").toBool();
    bool useAudio = qmlWindow->findChild<QObject*>("soundCheckbox")->property("checked").toBool();
    bool useMov = qmlWindow->findChild<QObject*>("useMov")->property("checked").toBool();
    bool useColor = qmlWindow->findChild<QObject*>("useColor")->property("checked").toBool();
    bool useCuts = qmlWindow->findChild<QObject*>("useCuts")->property("checked").toBool();

    bool longShot = qmlWindow->findChild<QObject*>("LONG_SHOT")->property("checked").toBool();
    bool closeup = qmlWindow->findChild<QObject*>("CLOSEUP_SHOT")->property("checked").toBool();
    bool offField = qmlWindow->findChild<QObject*>("OUT_OF_FIELD")->property("checked").toBool();


    //=======================================================


    int clipDuration = qmlWindow->findChild<QObject*>("clipDuration")->property("text").toInt();
    if(clipDuration == 0) clipDuration = 20;

    if(!useEmotions && !useAudio && !useMov && !useColor){
        ofSystemAlertDialog("You need to use a data source!");
        return;
    }


    //add events to summary
    for(int i = 0; i < eventInSecond.size(); i++){
        if(eventInSecond[i]){
            int start = i - (clipDuration / 2);
            int end = i + (clipDuration / 2);
            pair<int, int> timestamps(start, end);

            ClipWithScore newClip(timestamps, 100, 100);

            if(useMov) motionHelper(start, end, newClip);

            newClip.calcFinalScore(0.9, 0.1);
            clips.push_back(newClip);
        }
    }


    int interval = qmlWindow->findChild<QObject*>("emotionInterval")->property("text").toInt();
    if(interval == 0) interval = 5;
    vector<EmotionInterval> emotionsInterval = emotionData->setInterval(interval);

    //weights
    double emotionWeight = qmlWindow->findChild<QObject*>("emotionSlider")->property("value").toDouble();
    double audioWeight = qmlWindow->findChild<QObject*>("audioSlider")->property("value").toDouble();

    if(useEmotions){

        for(int i = 1; i < emotionsInterval.size() - 1; i++){

            if(!useAllEmotions()){
                setEmotionsToUse(emotionsInterval[i]);
                setEmotionsToUse(emotionsInterval[i - 1]);
                setEmotionsToUse(emotionsInterval[i + 1]);
            }


            int numberOfEmotions = emotionsInterval[i].getNumberOfEmotions();
            int valueBefore = emotionsInterval[i - 1].getNumberOfEmotions();
            int valueAfter = emotionsInterval[i + 1].getNumberOfEmotions();

            //found a peak
            if (numberOfEmotions > valueBefore && numberOfEmotions >= valueAfter
                    /*&& numberOfEmotions >= minNumberOfEmotions*/) {

                //discard clips with a low number of emotions
                //if(numberOfEmotions <= emotionData->getMaxValueInterval() / 2)
                //  continue;

                // two thirds of the duration before the peak, the rest after the peak
                int startTimestamp = emotionsInterval[i].getTimestamp() - (clipDuration * 3/4);
                int endTimestamp = emotionsInterval[i].getTimestamp() + (clipDuration / 4);

                if(useCuts)//check for a cut 5 seconds before the start timestamp
                    for(string cutTimestamp : cuts)
                        if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5)
                            startTimestamp = ofToInt(cutTimestamp);

                //we need to get the number of emotions associated with the timestamps
                double emotionsInClip = 0;
                for(int i = startTimestamp; i < endTimestamp; i++){
                    double normalizedEmotions = emotionsInSecond[i].first / (float)emotionData->getMaxValue();
                    //cout << emotionsInSecond[i].first /(float) emotionData->getMaxValue() << endl;
                    emotionsInClip += normalizedEmotions;
                }
                //cout << "MaxValue: " << maxValue << endl;
                //cout << emotionsInClip << endl;

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

                if(useColor){
                    int shotType = checkShotTypeClip(startTimestamp, endTimestamp);
                    newClip.setShotType(shotType);
                }

                if(useAudio)
                    newClip.calcFinalScore(emotionWeight, audioWeight);
                else
                    newClip.calcFinalScore(1, 0);

                if(useMov) motionHelper(startTimestamp, endTimestamp, newClip);

                clips.push_back(newClip);

                //cout << startTimestamp << " - " << endTimestamp << " == " << newClip.getFinalScore() << endl;

            }

        }
    }
    else if(useAudio && !useEmotions){//use only audio
        cout << "Using only audio!" << endl;

        vector<EmotionInterval> audioInterval = emotionsInterval;
        float maxAudioValue;
        for(EmotionInterval &ei : audioInterval){
            int startTimestamp = ei.getTimestamp();
            int endTimestamp = ei.getTimestamp() + interval;
            float audioValues = 0;
            for(int i = startTimestamp; i < endTimestamp; i++){
                // cout << audioValues << endl;
                audioValues += audio->getSamples()[i];
            }
            if(audioValues > maxAudioValue)
                maxAudioValue = audioValues;
            //cout << audioValues << endl;
            ei.setAudioValues(audioValues);
            //cout << ei.getAudioValues() << endl;
            // cout << "timestamp: " << ei.getTimestamp() << " audio: " << ei.getAudioValues() << endl;
        }

        for(EmotionInterval e : audioInterval)
            cout << "timestamp: " << e.getTimestamp() << " audio: " << e.getAudioValues() << endl;


        float audioThreshold = maxAudioValue / 2;
        cout << "AudioThreshold: " << audioThreshold << endl;
        for(int i = 1; i < audioInterval.size(); i++){

            float currentValue = audioInterval[i].getAudioValues();
            float valueBefore = audioInterval[i - 1].getAudioValues();
            float valueAfter = audioInterval[i + 1].getAudioValues();

            if(currentValue < audioThreshold)
                continue;

            if(currentValue > valueBefore && currentValue >= valueAfter){
                cout << "audio peak" << endl;

                // two thirds of the duration before the peak, the rest after the peak
                int startTimestamp = audioInterval[i].getTimestamp() - (clipDuration * 3/4);
                int endTimestamp = audioInterval[i].getTimestamp() + (clipDuration / 4);

                if(useCuts)//check for a cut 5 seconds before the start timestamp
                    for(string cutTimestamp : cuts)
                        if(ofToInt(cutTimestamp) < startTimestamp && startTimestamp - ofToInt(cutTimestamp) <= 5)
                            startTimestamp = ofToInt(cutTimestamp);

                //we need to get the audio values associated with the timestamps
                float audioValues = 0;
                for(int i = startTimestamp; i < endTimestamp; i++){
                    float normalizedAudio = audio->getSamples()[i] / audio->getMaxValue();
                    audioValues += normalizedAudio;
                }

                pair<int, int> ts(startTimestamp, endTimestamp);
                ClipWithScore newClip(ts, 0, audioValues);

                if(useColor){
                    int shotType = checkShotTypeClip(startTimestamp, endTimestamp);
                    newClip.setShotType(shotType);
                }

                newClip.calcFinalScore(0, 1);

                if(useMov) motionHelper(startTimestamp, endTimestamp, newClip);

                clips.push_back(newClip);

                cout << startTimestamp << " - " << endTimestamp << " == score: " << newClip.getFinalScore()
                     << " audio: " << currentValue << endl;
            }

        }
    }
    else if(!useEmotions && useMov){//extract clips based only on movement

        useOnlyMov(useAudio, useCuts, useColor, clips);

    }

    else if(!useEmotions && useColor){
        //TODO: vale a pena? mesma maneira que mov?
    }



    //Choose what clips to be included in the final summary
    //merge the extracted clips
    ofSort(clips, sortClips);
    for(int n = 0; n < 2; n++){
        for(int i = 0; i < clips.size() - 1; i++){
            ClipWithScore currClip = clips[i];
            ClipWithScore nextClip = clips[i+1];

            if(currClip.getTimestamps().second > nextClip.getTimestamps().first){
                if(currClip.getFinalScore() > nextClip.getFinalScore()){
                    clips.erase(clips.begin()+(i+1));
                    clips[i].setTimestamps(currClip.getTimestamps().first, currClip.getTimestamps().second+3);
                }
                else{
                    clips.erase(clips.begin()+i);
                    clips[i+1].setTimestamps(nextClip.getTimestamps().first, nextClip.getTimestamps().second+3);
                }
            }
        }
    }

    cout << endl;
    for(ClipWithScore c : clips)
        cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore()
             << " - shot: " << c.getShotType() << endl;


    int summaryDuration = qmlWindow->findChild<QObject*>("summaryDuration")->property("text").toInt();
    if(summaryDuration == 0) summaryDuration = 3;

    ofSort(clips, sortByScore);
    int totalDuration = clipsInSummary.size() * clipDuration;
    int index = 0;
    while(totalDuration < summaryDuration * 60 && index < clips.size()){
        // cout << index << endl;
        //TODO: falta halfTime
        if(useMov){

            selectClipMov(totalDuration, clips, clipsInSummary, index,
                          useColor, longShot, closeup, offField);

        }
        else if(useColor){

            selectClipColor(clips, clipsInSummary, longShot, closeup, offField, totalDuration,
                            index);

        }
        else{
            clipsInSummary.push_back(clips[index]);
            pair<int, int> ts = clips[index].getTimestamps();
            totalDuration += (ts.second - ts.first);
        }

        index++;
    }
    ofSort(clipsInSummary, sortClips);

    cout << endl;
    cout << "TotalDuration: " << totalDuration << " === " << "SummaryDur: " << summaryDuration * 60 << endl;
    cout << "Clips in summary: " << clipsInSummary.size() << endl;

    for(ClipWithScore c : clipsInSummary)
        cout << c.getTimestamps().first << " - " << c.getTimestamps().second << " === " << c.getFinalScore()
             << "  -  shot: " << c.getShotType() << endl;

    //cutVideo(clipsInSummary);


    //cout << "Elapsed time: " << ofGetElapsedTimeMillis() - time << endl;

}
