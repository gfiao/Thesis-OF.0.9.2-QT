#include "ofMain.h"
#include "ofApp.h"
#include <QApplication>

//========================================================================
int main( int argc, char *argv[]  ){
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    ofSetWindowTitle("oF Window");

    QApplication app(argc, argv);

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
