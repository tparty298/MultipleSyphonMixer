#include "common.h"
#include "SyphonClientContainer.h"
#include <istream>


#define MAX_SCENES 3

class SyphonClientManager {
    ofxSyphonServerDirectory directory;
    vector<string> server_labels;
    unordered_map<string,ofxSyphonServerDescription*> server_statuses;// name:status(-1:disconnect, 0~: index of syphon description list)
    
    // 実際に動かしてる部分
    array<SyphonClientContainer*, MAX_SCENES> client_container;
    
    bool addServers(vector<ofxSyphonServerDescription> servers);
    void initOsc();
    
public:
    SyphonClientManager();
    ~SyphonClientManager();
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    void update();
    void drawScene();
    void drawFbo();
    void attachUniforms(ofShader& shader);
    
    const int getSyphonIndexFromName(const string name);
    void setScene(size_t container_i, const string name);
//    BaseScene * getSceneByName(const string name);
    
    void windowResized(glm::vec2 size);
    
    const string createRegisterName(const ofxSyphonServerDescription s) {
        return s.serverName + "|" + s.appName;
    }
    
    const ofxSyphonServerDescription createDescription(const string s) {
        stringstream ss{s + "|"};
        string server_name, app_name;
        
        std::getline(ss, server_name, '|');
        std::getline(ss, app_name, '|');
        return ofxSyphonServerDescription(server_name, app_name);
    }
};
