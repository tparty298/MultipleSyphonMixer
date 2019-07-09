#include "SyphonClientManager.h"

SyphonClientManager::SyphonClientManager() {
    directory.setup();
    
    // init container[3]
    for (size_t i = 0; i < MAX_SCENES; ++i) {
        client_container[i] = new SyphonClientContainer();
    }
    
    this->addServers(directory.getServerList());
    
    ofAddListener(directory.events.serverAnnounced, this, &SyphonClientManager::serverAnnounced);
    ofAddListener(directory.events.serverRetired, this, &SyphonClientManager::serverRetired);
    
    this->initOsc();
}

SyphonClientManager::~SyphonClientManager() {
    
}

void SyphonClientManager::initOsc() {
    // set container scene
    ofxSubscribeOsc(OF_PORT, "/manager/set_scene", [=](const unsigned int container_i, const string name) {
        this->setScene(container_i, name);
    });
    
    // set container opacity
    ofxSubscribeOsc(OF_PORT, "/manager/set_opacity", [=](const unsigned int i, const float opacity) {
        client_container[i]->setOpacity(opacity);
    });
    
    ofxSubscribeOsc(OF_PORT, "/manager/get_syphon_list", [&]() {
        ofxSendOsc(MAX_HOST, MAX_PORT, "/syphon_list", server_labels);
    });
}

void SyphonClientManager::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg) {
    if (!this->addServers(arg.servers))
        ofLogError() << "server add failed";
}

bool SyphonClientManager::addServers(vector<ofxSyphonServerDescription> servers) {
    for (auto s : servers) {
        const string label = createRegisterName(s);
        
        if (server_statuses.count(label) == 0) {
            server_labels.push_back(label);
        }
        server_statuses[label] = &s;
        ofLogNotice() << "Announced: " << label;
    }
    
    // update max serverlist
    ofxSendOsc(MAX_HOST, MAX_PORT, "/syphon_list", server_labels);
    
    return true;
}

void SyphonClientManager::serverRetired(ofxSyphonServerDirectoryEventArgs &arg) {
    ofLogNotice() << "------------------------";
    
    for (auto s : arg.servers) {
        ofLogNotice() << "Retireed: " << s.serverName + "-" + s.appName;
        const string label = createRegisterName(s);
        
        server_statuses[label] = nullptr;
    }
}

void SyphonClientManager::update() {
    for (auto container : client_container) {
        container->update();
    }
}

void SyphonClientManager::drawScene() {
    for (auto container : client_container) {
        container->drawScene();
    }
    
//    client_container[0]->client.draw(0,0,ofGetWidth(), ofGetHeight());
}

void SyphonClientManager::attachUniforms(ofShader& shader) {
    for (int i = 0; i < MAX_SCENES; ++i) {
        if (client_container[i]->judgeRender()) {
            shader.setUniformTexture("s_texture" + to_string(i), client_container[i]->getTexture(), i);
            shader.setUniform1f("s_opacity" + to_string(i), client_container[i]->getOpacity());
            shader.setUniform2f("s_resolution" + to_string(i), client_container[i]->getResolution());
        }
    }
}

const int SyphonClientManager::getSyphonIndexFromName(const string name) {
    int i = 0;
    for (auto s : directory.getServerList()) {
        if (createRegisterName(s) == name) return i;
        i++;
    }
    
    return -1;
}

void SyphonClientManager::setScene(size_t container_i, const string name) {
    if (container_i < MAX_SCENES) {
//        const int syphon_i = getSyphonIndexFromName(name);
        ofLogNotice() << name;
        if (server_statuses.count(name) == 0) {
            ofLogError() << name << " is not found";
            return;
        } else if (server_statuses[name] == nullptr) {
            ofLogError() << name << " is disconnecting";
            return;
        }
        
        client_container[container_i]->setClient(this->createDescription(name));
        ofLogNotice() << client_container[container_i]->getName() << " is attatched to container " << container_i << ".";
    } else {
        cout << "SceneContainer index is out of range";
    }
}

void SyphonClientManager::windowResized(glm::vec2 size) {
    for (auto container : client_container) {
        container->windowResized(size);
    }
}
