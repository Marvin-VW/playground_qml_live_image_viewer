// Copyright (C) 2024 Marvin-VW
#include "Engine.h"
#include <cmath>
#include <iostream>

#define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

float Engine::is_triangle_facing_camera(triangle& tri, cv::Vec3f cam) {

    float dot_product =    tri.normal.at<double>(0) * (tri.centroid.at<double>(0) - cam[0]) +
                           tri.normal.at<double>(1) * (tri.centroid.at<double>(1) - cam[1]) +
                           tri.normal.at<double>(2) * (tri.centroid.at<double>(2) - cam[2]);

    return dot_product;
};


Engine::Engine(int frame_width, int frame_height, playground_qml_live_image_viewer::ui::ParameterModel& parameterModel)
{
    this->parameterModel = parameterModel;

    // Initialize the graphics renderer
    renderer = new RenderSystem(parameterModel);

    //instances of shape, camera and matrix
    shape = renderer->createCube();
    camera = renderer->createCamera(0.00452, 0.00339, 0.004, frame_width, frame_height, frame_width / 2, frame_height / 2);
    matrix = renderer->init_matrices();
    clipping = renderer->init_clipping();
    vec = renderer->init_vector();
    color = renderer->init_color();

    //generate cube mesh
    mesh = shape->generate_mesh(0.035, 0.035, 0.035);

}


cv::Mat Engine::run(cv::Mat frame)
{

    int red = mParameterModel.getCameraSystemTranslationX();

    cv::Vec3f camera_vector_world = camera->getCameraVector(camera->V_T_C);

    camera->resetCameraImage(frame);

    renderer->create_matrices();

    std::vector<triangle> visiable_mesh;

    for (auto& tri : mesh) {

        camera->world_transform(&camera->V_T_Cube, &tri);
        camera->camera_transform(&camera->C_T_V, &tri);

        std::tuple<cv::Mat, cv::Mat> result = vec->normal(tri, 0.5f);

        cv::Mat normal_start = std::get<0>(result);
        cv::Mat normal_end = std::get<1>(result);
        cv::Mat normal_start_camera = camera->C_T_V * normal_start;
        cv::Mat normal_end_camera = camera->C_T_V * normal_end;

        //backface culling
        if (is_triangle_facing_camera(tri, camera_vector_world) < 0.0f) {


            if (mParameterModel.getCubeSystemNormals() == 1)
                camera->drawCameraImageArrow(normal_start_camera, normal_end_camera);

            cv::Vec3f light_direction(1.0f, -0.5f, -0.8f);
            cv::Scalar base_color(255, 248, 240);

            tri.ilm = color->intensity(light_direction, tri.normal);
            tri.color = color->adjust_bgr_intensity(base_color, tri.ilm);

            visiable_mesh.push_back(tri);

        }
        
    }

    //clipping
    std::vector<triangle> clipped_mesh;
    clipped_mesh = clipping->cubeInSpace(&visiable_mesh);

    
    if (mParameterModel.getCubeSystemPoints() == 1)
    {
        camera->drawAllPoints(&clipped_mesh);
    }

    if (mParameterModel.getCubeSystemFaces() == 1)
    {
            camera->fillCubeFaces(&clipped_mesh);
    }
    camera->drawAllLines(&clipped_mesh);
    
    
    renderer->update_fps();
    engine_frame = renderer->renderFrame();

    return engine_frame;

}

Engine::~Engine()
{
    delete renderer;
    delete shape;
    delete camera;
    delete matrix;
    delete clipping;
    delete vec;
    delete color;
    renderer->shutdown();
}
