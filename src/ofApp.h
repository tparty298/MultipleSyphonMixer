#pragma once

#include "common.h"

#include "SyphonClientManager.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void initOsc();

		void keyPressed(int key);
    void windowResized(int x, int y);
    
    private:

    ofEasyCam cam;
    
    // syphone management
    SyphonClientManager *manager;

    
    // post processing
    array<ofFbo, 2> pingPong;
    ofShader post_processing;
    string pvs_text;
    string pfs_text;
    
    glm::vec4 seeds;
    
    glm::vec2 screen_size;
    
    ofPlanePrimitive screen_plane;
    
    ofImage image;

};
