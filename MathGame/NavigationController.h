#pragma once
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ArithmeticOperation.h"
#include "Configuration.h"

class NavigationController {
public:
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GL_RETURN) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
    void escController(GLFWwindow* window, ScreenNum& screen, int& menu_b, int& score) {
        if (screen == MAIN_SCREEN) {
            glfwSetWindowShouldClose(window, true);
        }
        else if (screen == OPTION_SCREEN) {
            screen = MAIN_SCREEN;
        }
        else {
            score = 0;
            menu_b = 0;
            screen = OPTION_SCREEN;
        }
    }
    void enterController(ScreenNum& screen, ModelSel& model, int& op1, int& op2, std::map<int, int>& choices, Digit& digit) {
        switch (screen)
        {
        case MAIN_SCREEN:
            screen = OPTION_SCREEN;
            break;
        case 2:
            ArithmeticOpertaion aop;
            aop.equationMaker(op1, op2, model, choices, digit);
            screen = (ScreenNum)model;
            break;
        default:
            break;
        }
    }
    void KeyUController(ModelSel& model) {
        if (model == MODEL_SEL_MAX)
        {
            model = MODEL_SEL_1;
        }
        else {
            model = ModelSel(model + 1);
        }
    }
    void KeyDController(ModelSel& model) {
        if (model == MODEL_SEL_1)
        {
            model = MODEL_SEL_MAX;
        }
        else {
            model = ModelSel(model - 1);
        }
    }
};