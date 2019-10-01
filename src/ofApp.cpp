#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
//    ofSetVerticalSync(false);
//    ofDisableArbTex();
    
//    ofEnableAlphaBlending();
    ofHideCursor();
    
    // post_processingのソース変更
    post_processing.load("InitShader/default.vert", "InitShader/default_pfs.frag");
    pvs_text = post_processing.getShaderSource(GL_VERTEX_SHADER);
    pfs_text = post_processing.getShaderSource(GL_FRAGMENT_SHADER);
    
    initOsc();
    
    manager = new SyphonClientManager();
    
    screen_size = glm::vec2(ofGetWidth(), ofGetHeight());
    
    screen_plane.set(screen_size.x*2., screen_size.y*2.);
    screen_plane.setPosition(0, 0, 0);
    
    windowResized(ofGetWidth(), ofGetHeight());
}

void ofApp::initOsc() {
    ofxPublishOsc(MAX_HOST, MAX_PORT, "/fps", &ofGetFrameRate);
    ofxPublishOsc(MAX_HOST, MAX_PORT, "/time", &ofGetElapsedTimef);
    
    ofxSubscribeOsc(OF_PORT, "/post_processing/fragment", [=](const string &str) {
        const string before = post_processing.getShaderSource(GL_FRAGMENT_SHADER);
        post_processing.setupShaderFromSource(GL_VERTEX_SHADER, pvs_text);
        const bool result = post_processing.setupShaderFromSource(GL_FRAGMENT_SHADER, str);
        
        if (!result) {
            post_processing.setupShaderFromSource(GL_FRAGMENT_SHADER, before);
            ofLogNotice() << "pfs failed";
        } else {
            ofLogNotice() << "pfs changed";
        }
        
        post_processing.bindDefaults();
        post_processing.linkProgram();
    });
    
    ofxSubscribeOsc(OF_PORT, "/post_processing/seeds", seeds);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    manager->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    manager->drawScene();
    
    pingPong[0].begin();
    ofClear(0);
    
    post_processing.begin();
    
    ofSetColor(255);
    ofDisableArbTex();
    manager->attachUniforms(post_processing);
    
    post_processing.setUniform4f("seeds", seeds);
    post_processing.setUniform1f("time", ofGetElapsedTimef());
    post_processing.setUniformTexture("before_texture", pingPong[1], 3);
    
    post_processing.setUniform2f("resolution", screen_size);
    
    ofSetColor(255,255,255,255);
    screen_plane.draw();
    post_processing.end();
    pingPong[0].end();
    
    ofSetColor(255);
    
    pingPong[1].draw(0,0,screen_size.x, screen_size.y);
    
    swap(pingPong[0], pingPong[1]);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

void ofApp::windowResized(int x, int y) {
    screen_size = glm::vec2(ofGetWidth(), ofGetHeight());
    screen_plane.set(screen_size.x*2., screen_size.y*2.);
    manager->windowResized(screen_size);
    
//    ofEnableArbTex();
    pingPong[0].allocate(ofGetWidth(), ofGetHeight());
    pingPong[1].allocate(ofGetWidth(), ofGetHeight());
    
    pingPong[0].getTexture().getTextureData().bFlipTexture = true;
    pingPong[1].getTexture().getTextureData().bFlipTexture = true;
};
