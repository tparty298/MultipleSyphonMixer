#include "SyphonClientContainer.h"

SyphonClientContainer::SyphonClientContainer() {
    attached = false;
    opacity = 0.;
    window_size = glm::vec2(ofGetWidth(), ofGetHeight());
    
    client.setup();
}

void SyphonClientContainer::setOpacity(const float g_opacity) {
    opacity = g_opacity;
};

const float SyphonClientContainer::getOpacity() const {
    return opacity;
};

ofTexture& SyphonClientContainer::getTexture() {
    return client.getTexture();
}

const glm::vec2 SyphonClientContainer::getResolution() {
    return glm::vec2(client.getWidth(), client.getHeight());
}

const string SyphonClientContainer::getName() {
    return client.getServerName() + ":" + client.getApplicationName();
}

void SyphonClientContainer::setClient(const ofxSyphonServerDescription &description) {
    ofLogNotice() << description.serverName;
    ofLogNotice() << description.appName;
    
    client.set(description);
    
    ofLogNotice() << client.getServerName();
    ofLogNotice() << client.getApplicationName();
    
    attached = true;
};

void SyphonClientContainer::update() {
    if (judgeRender()) {
        
    };
}

void SyphonClientContainer::drawScene() {
    if (judgeRender()) {
        ofPushMatrix();
        ofPushView();
        ofPushStyle();
        client.draw(0,0, window_size.x, window_size.y);
        ofPopStyle();
        ofPopView();
        ofPopMatrix();
    };
}

bool SyphonClientContainer::judgeRender() {
    return attached && opacity > 0.0;
};

void SyphonClientContainer::windowResized(glm::vec2 size) {
    window_size = size;
};

