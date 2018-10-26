#include "CombinedCamera.hpp"
#include "perception/vision/NaoCamera.hpp"
#include "perception/vision/Vision.hpp"

Camera *CombinedCamera::top_camera_ = NULL;
Camera *CombinedCamera::bot_camera_ = NULL;

CombinedCamera::CombinedCamera(
    bool dumpframes,
    int dumprate,
    string dumpfile
){
    if (dumpframes) {
        // Setting recording on either camera starts it for both
        top_camera_->startRecording(dumpfile.c_str(), dumprate);
    }
}

Camera* CombinedCamera::getCamera() {
    return top_camera_;
}

CombinedCamera::~CombinedCamera(){
    // Stopping recording on either camera starts it for both
    top_camera_->stopRecording();
}

const uint8_t* CombinedCamera::getFrameTop() {
    return top_camera_->get();
}

const uint8_t* CombinedCamera::getFrameBottom() {
    return bot_camera_->get();
}

Camera* CombinedCamera::getCameraTop() {
    return top_camera_;
}
Camera* CombinedCamera::getCameraBot() {
    return bot_camera_;
}
void CombinedCamera::setCameraTop(Camera* camera) {
    top_camera_ = camera;
    Vision::top_camera = top_camera_;
}
void CombinedCamera::setCameraBot(Camera* camera) {
    bot_camera_ = camera;
    Vision::bot_camera = bot_camera_;
    Vision::camera = Vision::bot_camera;
}
