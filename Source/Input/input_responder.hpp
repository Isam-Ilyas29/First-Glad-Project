#pragma once

#include "Core/std_types.hpp"
#include "Input/input.hpp"
#include "Camera/camera.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


/*----------------------------------------------------------------------------------*/

enum class sceneStates;

void enableSceneState(sceneStates state);
void disableSceneState(sceneStates state);
bool isSceneState(sceneStates state);

/*----------------------------------------------------------------------------------*/

void keyboardResponder(Camera& camera);
void mouseResponder(Camera& camera);
void scrollResponder(Camera& camera);

void update(f32 delta_time, Camera& camera, bool should_isolate);

/*----------------------------------------------------------------------------------*/
