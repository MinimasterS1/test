﻿#include "gInputMg.h"
#include "Editor/gEditor.h"
#include "Core/gCommon.h"


Input::Input(Camera& cam) : camera(cam), FirstMouse(true) 

{
    // Инициализируйте массив previousKeyState
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        previousKeyState[i] = GLFW_RELEASE;
    }
}

Input::~Input() {}

void Input::startUp() {

  //  LOG.Log(Logger::LogLevel::INFO, "InputManager Start", NULL);
    
   

}

void Input::shutDown() {

  //  LOG.Log(Logger::LogLevel::INFO, "InputManager ShutDown", NULL);
}

void Input::update(GLFWwindow* window, float deltaTime) {

    ProcessInput(window, deltaTime);
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)

{

    if (FirstMouse) {
        Last_X = xpos;
        Last_Y = ypos;
        FirstMouse = false;
    }


    if (!EditorMode)
    {

        float xoffset = xpos - Last_X;
        float yoffset = Last_Y - ypos;

        Last_X = xpos;
        Last_Y = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);

    }

    else {

        float xoffset = xpos - Last_X;
        float yoffset = Last_Y - ypos;

        Last_X = xpos;
        Last_Y = ypos;

        // camera.ProcessMouseMovement(xoffset, yoffset);


        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        int x_offset = EditorAPI::getXoffset();
        int y_offset = EditorAPI::getYOffset();
        int  framebuffer_width = EditorAPI::getWidth();
        int  framebuffer_height = EditorAPI::getHeight();
       bool isInsideFramebuffer = (mouseX >= x_offset && mouseX <= x_offset + framebuffer_width) &&
            (mouseY >= y_offset && mouseY <= y_offset + framebuffer_height);

        if (isInsideFramebuffer) {


            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
            {
                camera.ProcessMouseMovement(xoffset, yoffset);
            }

        }
    }

}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) 
{

   
}

void Input::ProcessSingleKeyPress(GLFWwindow* window, int key, int action) {
    if (key == GLFW_KEY_1) {
        if (action == GLFW_PRESS && !keyQPressed) {
            // Первое нажатие
            GameConsole = false;
            keyQPressed = true;
        }
        else if (action == GLFW_PRESS && keyQPressed) {
            // Второе нажатие
            GameConsole = true;
            keyQPressed = false;
        }
    }
    previousKeyState[key] = action;
}

void Input::ProcessInput(GLFWwindow* window, float deltaTime) 
{

    if (EditorMode)
        {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        }

    else {


        float startValue = -5.0f;
        float endValue = 5.0f;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

 
}

