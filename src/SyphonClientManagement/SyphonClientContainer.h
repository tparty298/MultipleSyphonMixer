#include "common.h"

class SyphonClientContainer {
    
    float opacity;
    bool attached = false;
    glm::vec2 window_size;
    
public:
    SyphonClientContainer();
    void update();
    void drawScene();

    void setOpacity(const float g_opacity);
    const float getOpacity() const;
    ofTexture& getTexture();
    const string getName();
    const glm::vec2 getResolution();
    ofxSyphonClient client;
    
    bool judgeRender();
    
    void setClient(const ofxSyphonServerDescription &description);
    
    
    void windowResized(glm::vec2 size);
};
