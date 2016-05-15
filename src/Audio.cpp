#include "Audio.h"

/*
code based on http://ofdsp.blogspot.pt/2011/07/loading-wav-file-with-sndfilehandle.html and
 https://github.com/erikd/libsndfile/blob/master/examples/sndfile-to-text.c
 */
Audio::Audio(const char* fileName) {
    maxValue, minValue = 0;

    //Bit rate = (bit depth) x (sampling rate) x (number of channels)
    SF_INFO sfinfo;
    SNDFILE *infile = sf_open(fileName, SFM_READ, &sfinfo);

    printf("Opened file '%s'\n", fileName);
    printf("    Sample rate : %d\n", sfinfo.samplerate);
    printf("    Channels    : %d\n", sfinfo.channels);
    printf("    Frames     : %d\n", int(sfinfo.frames));

    //read all of the frames to a array of floats
    float* frames = new float[sfinfo.channels * sfinfo.frames];
    sf_readf_float(infile, frames, sfinfo.channels * sfinfo.frames);

    for (int i = 0; i < sfinfo.frames; i += sfinfo.samplerate) {
        float sum = 0;
        for (int j = i; j < i + sfinfo.samplerate; j++) {
            sum += frames[j];
        }
        //multiply by 1000 so we can have readable values
        float normalizedValue = float(sum / sfinfo.samplerate) * 1000;
        if(normalizedValue < 0) normalizedValue -= (normalizedValue*2);
        samples.push_back(normalizedValue);

        if (normalizedValue > maxValue)
            maxValue = normalizedValue;
        if (normalizedValue < minValue)
            minValue = normalizedValue;
    }

    //cout << "MaxValue:  " << maxValue << endl;
    //cout << "MinValue:  " << minValue << endl;

    cout << "  Samples Size:   " << samples.size() << endl;

    /* for (int i = 0; i < samples.size(); i++)
        cout << samples[i] << endl;*/

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
