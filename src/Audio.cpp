#include "Audio.h"

/*
code based on http://ofdsp.blogspot.pt/2011/07/loading-wav-file-with-sndfilehandle.html and
 https://github.com/erikd/libsndfile/blob/master/examples/sndfile-to-text.c
 */
Audio::Audio(const char* fileName) {
    maxValue = 0, minValue = 0;

    //Bit rate = (bit depth) x (sampling rate) x (number of channels)
    SF_INFO sfinfo;
    SNDFILE *infile = sf_open(fileName, SFM_READ, &sfinfo);

    printf("Opened file '%s'\n", fileName);
    printf("    Sample rate : %d\n", sfinfo.samplerate);
    printf("    Channels    : %d\n", sfinfo.channels);
    printf("    Frames     : %d\n", int(sfinfo.frames));


    int BLOCK_SIZE = sfinfo.samplerate;
    float* buf = new float[BLOCK_SIZE * sfinfo.channels];
    int readcount = 0;

    while((readcount = sf_readf_float(infile, buf, BLOCK_SIZE)) > 0){
        //cout << readcount << endl;

        float sum = 0;
        for(int i = 0; i < BLOCK_SIZE; i++){
            sum += buf[i];
        }

        //multiply by 1000 so we can have readable values
        float readableValue = float(sum / sfinfo.samplerate) * 1000;
        if(readableValue < 0) readableValue -= (readableValue*2);
        samples.push_back(readableValue);

        if (readableValue > maxValue)
            maxValue = readableValue;
        if (readableValue < minValue)
            minValue = readableValue;

    }

    cout << "    MaxValue:  " << maxValue << endl;
    cout << "    MinValue:  " << minValue << endl;

    cout << "    Samples Size:   " << samples.size() << endl;

    //for (int i = 0; i < samples.size(); i++)
    // cout << samples[i] << endl;

    cout << "Audio Loaded\n" << endl;

}

vector<float> Audio::getSamples() {
    return samples;
}

float Audio::getMaxValue() {
    return maxValue;
}

float Audio::getMinValue() {
    return minValue;
}

vector<float> Audio::setInterval(int interval, int& maxValue){

    vector<float> ret;
    for(int i = 0; i < samples.size(); i+=interval){

        float audioValues = 0;
        for(int j = i; j < i+interval && j < samples.size(); j++){
            audioValues += samples[j];
        }

        if(maxValue < audioValues)
            maxValue = audioValues;

        ret.push_back(audioValues);
    }
    return ret;

}
