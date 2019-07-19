#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setSize(1080,1920);
    settings.setGLVersion(4,1);
    settings.setPosition(glm::vec2(-10,0));
    settings.multiMonitorFullScreen = true;
    ofCreateWindow(settings);
//    ofToggleFullscreen();

    ofRunApp(new ofApp());
}
