#pragma once
#include <iostream>
#include <map>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Configuration.h"

class ArithmeticOpertaion {
public:
    void equationMaker(int& op1, int& op2, ModelSel& model, std::map<int, int>& temp_map, Digit& digit) {
        temp_map.clear();

        int i, choice, ans, ans_fake;
        switch (model)
        {
        case MODEL_SEL_1:   //Addition
        {
            NumberGenerator(op1, op2, digit);
            ans = op1 + op2;
            while(ans >= 100 || op1*op2 == 0)
            {
                NumberGenerator(op1, op2, digit);
                ans = op1 + op2;
            }
            choice = rand() % 4;
            for ( i = 0; i < 4; i++)
            {
                if (i==choice)
                {
                    temp_map.emplace(i, ans);
                }
                else {
                    AnswerGenerator(ans, ans_fake, model, digit);
                    temp_map.emplace(i, ans_fake);
                }
            }
        }
            break;
        case MODEL_SEL_2:   //Subtraction
        {
            NumberGenerator(op1, op2, digit);
            ans = op1 - op2;
            while(ans <= 0)
            {
                NumberGenerator(op1, op2, digit);
                ans = op1 - op2;
            }
            choice = rand() % 4;
            for (i = 0; i < 4; i++)
            {
                if (i == choice)
                {
                    temp_map.emplace(i, ans);
                }
                else {
                    AnswerGenerator(ans, ans_fake, model, digit);
                    temp_map.emplace(i, ans_fake);
                }
            }
        }
            break;
        case MODEL_SEL_3:   //Multiplication
        {
            Digit sev = SINGLE_DIGIT;
            NumberGenerator(op1, op2, sev);

            while(op1 > MAX_MULTIPLY_NUM || op2 > MAX_MULTIPLY_NUM || op1 * op2 == 0)
            {
                NumberGenerator(op1, op2, digit);
            }
            ans = op1 * op2;
            choice = rand() % 4;
            for (i = 0; i < 4; i++)
            {
                if (i == choice)
                {
                    temp_map.emplace(i, ans);
                }
                else {
                    AnswerGenerator(ans, ans_fake, model, digit);
                    temp_map.emplace(i, ans_fake);
                }
            }
        }
            break;
        case MODEL_SEL_4:   //Division, reversion of Multiplication
        {
            Digit sev = SINGLE_DIGIT;
            NumberGenerator(op1, op2, sev);

            while(op1 > MAX_MULTIPLY_NUM || op2 > MAX_MULTIPLY_NUM || op1 * op2 == 0)
            {
                NumberGenerator(op1, op2, digit);
            }
            ans = op1 * op2;
            swap(ans, op1);
            choice = rand() % 4;
            for (i = 0; i < 4; i++)
            {
                if (i == choice)
                {
                    temp_map.emplace(i, ans);
                }
                else {
                    AnswerGenerator(ans, ans_fake, model, digit);
                    temp_map.emplace(i, ans_fake);
                }
            }
        }
            break;
        case MODEL_SEL_5: {

        }
            break;
        case MODEL_SEL_6: {

        }
            break;
        case MODEL_SEL_7: {

        }
            break;
        default:
            break;
        }
    }

    void equationChecker(int& op1, int& op2, ModelSel& model, int key,int& menu, std::map<int, int>& temp_map, int& score, Digit& digit) {
        int u_ans=0;
        switch (key)
        {
        case 65:
            u_ans = temp_map[0];
            break;
        case 66:
            u_ans = temp_map[1];
            break;
        case 67:
            u_ans = temp_map[2];
            break;
        case 68:
            u_ans = temp_map[3];
            break;
        default:
            break;
        }
        switch (model)
        {
        case MODEL_SEL_1: {
            int ans = op1 + op2;
            if (ans == u_ans)
            {
                score += 10;
                DynamicSeverity(score, digit);
            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_2: {
            int ans = op1 - op2;
            if (ans == u_ans)
            {
                score += 10;
                DynamicSeverity(score, digit);
            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_3: {
            int ans = op1 * op2;
            if (ans == u_ans)
            {
                score += 10;
                DynamicSeverity(score, digit);
            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_4: {
            int ans = op1 / op2;
            if (ans == u_ans)
            {
                score += 10;
                DynamicSeverity(score, digit);
            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_5: {

        }
            break;
        case MODEL_SEL_6: {

        }
            break;
        case MODEL_SEL_7: {

        }
            break;
        default:
            break;
        }
        equationMaker(op1, op2, model, temp_map, digit);
    }

    void NumberGenerator(int& num1, int& num2, Digit& digit) {
        if (digit == DOUBLE_DIGIT)
        {
            num1 = rand() % 100;
            num2 = rand() % 100;
        }
        else
        {
            num1 = rand() % 10;
            num2 = rand() % 10;
        }
    }

    void AnswerGenerator(int& ans, int& ans_fake, ModelSel& model, Digit& digit) {
        ans_fake = rand() % 100;
        switch (model)
        {
        case MODEL_SEL_1: {
            if (digit == SINGLE_DIGIT)
            {
                while (ans_fake > 19 || ans_fake == ans)
                {
                    ans_fake = rand() % 100;
                }
            }
            else
            {
                while (ans_fake < 20 || ans_fake == ans)
                {
                    ans_fake = rand() % 100;
                }
            }
        }
            break;
        case MODEL_SEL_2: {
            if (digit == SINGLE_DIGIT)
            {
                while (ans_fake > 9 || ans_fake == ans)
                {
                    ans_fake = rand() % 10;
                }
            }
        }
            break;
        default:
            break;
        }
    }

    void DynamicSeverity(int& score, Digit& digit) {
        if(score > 100)
        {
            digit = DOUBLE_DIGIT;
        }
    }

    void AnswerCheck(int& op1, int& op2, ModelSel& model, int key, int& menu) {
        switch (model)
        {
        case MODEL_SEL_1: {
            int ans = op1 + op2;
            if (ans == key)
            {

            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_2: {
            int ans = op1 - op2;
            if (ans == key)
            {

            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_3: {
            int ans = op1 * op2;
            if (ans == key)
            {

            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_4: {
            int ans = op1 / op2;
            if (ans == key)
            {

            }
            else {
                menu = 1;
            }
        }
            break;
        case MODEL_SEL_5: {

        }
            break;
        case MODEL_SEL_6: {

        }
            break;
        case MODEL_SEL_7: {

        }
            break;
        default:
            break;
        }
    }
};