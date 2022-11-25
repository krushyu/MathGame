#pragma execution_character_set("utf-8")
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <map>
//Classes
#include "Shader.h"
#include "TextRender.h"
#include "NavigationController.h"
#include "ArithmeticOperation.h"
#include "Configuration.h"

std::map<int, int> choices;
const unsigned int SCREEN_WIDTH = 1280; 
const unsigned int SCREEN_HEIGHT = 720;
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);

NavigationController nvt;
ArithmeticOpertaion aop;
ScreenNum screen = MAIN_SCREEN;
ModelSel model = MODEL_SEL_1;

int op1 = 0;
int op2 = 0;
int ans = 0;
Digit digit = SINGLE_DIGIT;
int score = 0;
std::string a;
std::string b;
std::string c;
std::string d;
int menu_b = 0;

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "计算能手", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallBack);
    //glfwSetCursorPosCallback(window, cursorPositionCallback);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        printf("Error\n");

    // When user resizes the screen
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TextRender txt(SCREEN_WIDTH, SCREEN_HEIGHT, "Fonts/B022-BanMaTuBiPinYinTi.ttf");
    TextRender txtNum(SCREEN_WIDTH, SCREEN_HEIGHT, "Fonts/msyh.ttc");

    srand((unsigned int)time(0));

    // While window is open
    while (!glfwWindowShouldClose(window))
    {
        // input
        nvt.processInput(window);

        glClearColor(0.79f, 0.92f, 0.85f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        switch (screen)
        {
        case MAIN_SCREEN:
            
            txt.RenderText("计算能手闯关比赛", 440.0f, 520.0f, 1.0f, glm::vec3(RedTomato));
            txt.RenderText("按ENTER键进入题型选择", 415.0f, 300, 0.8f, glm::vec3(RedCoral));
            txt.RenderText("版本1.0", 1100.0f, 25.0f, 0.6f, glm::vec3(BlueGreen));
            break;
        case OPTION_SCREEN:
            menu_b = 0;
            txt.RenderText("按上下键选择题型，按ENTER键确认", 260.0f, 440.0f, 1.0f, glm::vec3(Yellow));
            switch (model)
            {
            case MODEL_SEL_1:
                txt.RenderText("模式 1: 加法", 455.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_2:
                txt.RenderText("模式 2: 减法", 455.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_3:
                txt.RenderText("模式 3: 乘法", 455.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_4:
                txt.RenderText("模式 4: 除法", 455.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_5:
                txt.RenderText("模式 5: 混合运算加减法", 380.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_6:
                txt.RenderText("模式 6: 混合运算乘除法", 380.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            case MODEL_SEL_7:
                txt.RenderText("模式 7: 混合运算加减乘除", 370.0f, 320.0f, 0.9f, glm::vec3(BlueGreen));
                break;
            default:
                break;
            }
            break;
        case MODEL_SCREEN_1:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 加法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                txtNum.RenderText("题目:  " + op1_s + " + " + op2_s + "= __ " + " ，请选择：", 400.0f, 540.0f, 0.8f, glm::vec3(RedTomato));
                a = "A. " + to_string(choices[0]);
                b = "B. " + to_string(choices[1]);
                c = "C. " + to_string(choices[2]);
                d = "D. " + to_string(choices[3]);
                txtNum.RenderText(a, 420.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(b, 420.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(c, 650.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(d, 650.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
            }
            else
            {
                string s_score = "你的得分是: "+to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }
            
        }
            break;
        case MODEL_SCREEN_2:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 减法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                txtNum.RenderText("题目:  " + op1_s + " - " + op2_s + "= __ " + " ，请选择：", 400.0f, 540.0f, 0.8f, glm::vec3(RedTomato));
                a = "A. " + to_string(choices[0]);
                b = "B. " + to_string(choices[1]);
                c = "C. " + to_string(choices[2]);
                d = "D. " + to_string(choices[3]);
                txtNum.RenderText(a, 420.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(b, 420.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(c, 650.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(d, 650.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
        break;
        case MODEL_SCREEN_3:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 乘法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                txtNum.RenderText("题目:  " + op1_s + " x " + op2_s + "= __ " + " ，请选择：", 400.0f, 540.0f, 0.8f, glm::vec3(RedTomato));
                a = "A. " + to_string(choices[0]);
                b = "B. " + to_string(choices[1]);
                c = "C. " + to_string(choices[2]);
                d = "D. " + to_string(choices[3]);
                txtNum.RenderText(a, 420.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(b, 420.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(c, 650.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(d, 650.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
        break;
        case MODEL_SCREEN_4:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 除法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                txtNum.RenderText("题目:  " + op1_s + " ÷ " + op2_s + "= __ " + " ，请选择：", 400.0f, 540.0f, 0.8f, glm::vec3(RedTomato));
                a = "A. " + to_string(choices[0]);
                b = "B. " + to_string(choices[1]);
                c = "C. " + to_string(choices[2]);
                d = "D. " + to_string(choices[3]);
                txtNum.RenderText(a, 420.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(b, 420.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(c, 650.0f, 380.0f, 0.8f, glm::vec3(RedCoral));
                txtNum.RenderText(d, 650.0f, 300.0f, 0.8f, glm::vec3(RedCoral));
            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
        break;
        case MODEL_SCREEN_5:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 混合运算加减法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                //

            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
            break;
        case MODEL_SCREEN_6:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 混合运算乘除法", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                //

            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
        break;

        case MODEL_SCREEN_7:
        {
            if (menu_b == 0)
            {
                string op1_s = to_string(op1);
                string op2_s = to_string(op2);
                txt.RenderText("当前模式: 混合运算加减乘除", 80.0f, 650.0f, 0.7f, glm::vec3(YellowLight));
                //

            }
            else
            {
                string s_score = "你的得分是: " + to_string(score);
                txt.RenderText("游戏结束! 按ESC按键结束", 150.0f, 450.0f, 1.0f, glm::vec3(BlueGreen));
                txt.RenderText(s_score, 150.0f, 350.0f, 1.0f, glm::vec3(BlueGreen));
            }

        }
        break;
            break;
        default:
            break;
        }

        //Render the window

        // Swap the front and back buffers - we draw into the back, thus we swap.
        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ENTER:
            nvt.enterController(screen, model, op1, op2, choices, digit);
            std::cout << screen << std::endl;
            break;
        case GLFW_KEY_DOWN:
            nvt.KeyDController(model);
            break;
        case GLFW_KEY_UP:
            nvt.KeyUController(model);
            break;
        case GLFW_KEY_ESCAPE:
            nvt.escController(window, screen, menu_b, score);
            break;
        default:
            std::cout << key << std::endl;
            aop.equationChecker(op1, op2, model, key, menu_b, choices, score, digit);
            break;
        }
    }
};

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    std::cout << xPos << ":" << yPos << std::endl;
}
