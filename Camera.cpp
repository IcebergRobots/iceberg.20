#include "Camera.h"

Camera::Camera(){
    
}

void Camera::init(){
   if(isEnabled()){
       SPI.begin();
       Pixy::init();
   }
}

void Camera::update(){
    if(isEnabled()){
        blockCount = getBlocks();
        if (blockCount != 0){
            for(int i = 0; i < blockCount; i++){
                int signature = blocks[i].signature;
                int position = blocks[i].x;
                int height = blocks[i].height;
                int width = blocks[i].width;
                int area = height * width;
                switch(signature){
                case SIG_BALL :
                    if (area > ballArea){
                    ballArea = area;
                    ballPos = position;
                    ballCount++;
                    }
                case SIG_GOAL :
                    if (area > goalArea){
                    goalArea = area;
                    goalPos = position;
                    goalCount++;
                    }
                }
            }
        Serial.println("AREA:" + getBArea());
        Serial.println("POSITON:" + getBPos());
        }else{
            Serial.print("No blocks found.");
        }
    }
}

bool Camera::isEnabled(){
    return CAM_EN;
}

int Camera::getBArea(){
    return ballArea;
}

int Camera::getBPos(){
    return ballPos;
}