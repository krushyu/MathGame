#pragma once

// color parameters
#define RedTomato        1.0f, 0.39f, 0.29f
#define RedCoral         1.0f, 0.50f, 0.31f
#define BlueGreen        0.16, 0.67f, 0.53f
#define BlueGreenLight   0.25, 0.88f, 0.82f
#define Yellow           0.93f, 0.57f, 0.13f
#define YellowLight      1.0f, 0.63f, 0.48f

typedef enum SCREENNUMBER
{
    MAIN_SCREEN = 1,
    OPTION_SCREEN,
    MODEL_SCREEN_1,
    MODEL_SCREEN_2,
    MODEL_SCREEN_3,
    MODEL_SCREEN_4,
    MODEL_SCREEN_5,
    MODEL_SCREEN_6,
    MODEL_SCREEN_7,
    MODEL_SCREEN_MAX = MODEL_SCREEN_7
}ScreenNum;

typedef enum MODELSELECT
{
    MODEL_SEL_1 = 3,
    MODEL_SEL_2,
    MODEL_SEL_3,
    MODEL_SEL_4,
    MODEL_SEL_5,
    MODEL_SEL_6,
    MODEL_SEL_7,
    MODEL_SEL_MAX = MODEL_SEL_7
}ModelSel;

typedef enum DIGIT
{
    SINGLE_DIGIT,
    DOUBLE_DIGIT,
}Digit;


#define MAX_MULTIPLY_NUM    8