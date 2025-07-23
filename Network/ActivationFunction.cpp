//----------------------------------------------------------------------------------------------------------
//ActivationFunction.cpp
//激活函数声明
//开发者：Jason Cheng   日期：2025/7/15
//更改记录
//----------------------------------------------------------------------------------------------------------

#include "ActivationFunction.hpp"
#include <cmath>

//----------------------------------------------------------------------------------------------------------
//函数名称：Sigmoid
//函数功能：定义Sigmoid构造函数
//参数：const double& Signal，输入参数
//返回值：double类型，代表激活函数Sigmoid的运算结果
//开发者：Jason Cheng   日期：2025/7/16
//更改记录
//----------------------------------------------------------------------------------------------------------

double ActivationFunction::Sigmoid(const double& Signal) {
    return 1.0 / (1.0 + exp(-Signal));
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Tanh
//函数功能：定义Tanh激活函数
//参数：const double& Signal，输入参数
//返回值：double类型，代表激活函数Tanh的运算结果
//开发者：Jason Cheng   日期：2025/7/16
//更改记录
//----------------------------------------------------------------------------------------------------------

double ActivationFunction::Tanh(const double& Signal) {
    return (exp(Signal) - exp(-Signal)) / (exp(Signal) + exp(-Signal));
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ReLU
//函数功能：定义ReLU激活函数
//参数：const double& Signal，输入参数
//返回值：double类型，代表激活函数ReLU的运算结果
//开发者：Jason Cheng   日期：2025/7/16
//更改记录
//----------------------------------------------------------------------------------------------------------

double ActivationFunction::ReLU(const double& Signal) {
    return (Signal > 0) ? Signal : 0;   //ReLU(x) = max(x, 0)
}

/*
#include <iostream>
int main() {
    double d;
    std::cin >> d;
    std::cout << ActivationFunction::Sigmoid(d) << std::endl;
    std::cout << ActivationFunction::Tanh(d) << std::endl;
    std::cout << ActivationFunction::ReLU(d) << std::endl;
    return 0;
}
*/