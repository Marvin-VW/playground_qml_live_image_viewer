// Copyright (C) 2024 Daniel-VW, Marvin-VW, twyleg
#ifndef WINDOW_H
#define WINDOW_H

#include <opencv2/opencv.hpp>



enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Window {
public:

    void createCameraSettingsWindow();
    
    void createCubeSettingsWindow();

    void handleMovement(int key);

    void updateCameraVectors();

    void moveCamera(Direction direction, int speed);

    void mouseMoveCamera();
    void moveCameraWithMouse(int deltaX, int deltaY);

public:

    int32_t cameraSystemTranslationX;
    int32_t cameraSystemTranslationY;
    int32_t cameraSystemTranslationZ;
    int32_t cameraSystemRotationRoll;
    int32_t cameraSystemRotationPitch;
    int32_t cameraSystemRotationYaw;

    int32_t cubeSystemTranslationX;
    int32_t cubeSystemTranslationY;
    int32_t cubeSystemTranslationZ;
    int32_t cubeSystemRotationRoll;
    int32_t cubeSystemRotationPitch;
    int32_t cubeSystemRotationYaw;
    int32_t cubeSystemScale;

    int32_t cubeSystemNormals;
    int32_t cubeSystemPoints;
    int32_t cubeSystemFaces;

private:
    
    double forwardX = 0;
    double forwardY = 0;
    double forwardZ = 0;

    double rightX = 0;
    double rightY = 0;

    int speed = 100;
    

};

#endif