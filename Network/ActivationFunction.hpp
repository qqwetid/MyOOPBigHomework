//----------------------------------------------------------------------------------------------------------
//ActivationFunction.hpp
//定义激活函数
//开发者：Jason Cheng   日期：2025/7/15
//更改记录
//----------------------------------------------------------------------------------------------------------

#ifndef ACTIVATION_FUNCTION_HPP
#define ACTIVATION_FUNCTION_HPP

//----------------------------------------------------------------------------------------------------------
//类名：ActivationFunction
//功能：定义激活函数
//接口：Sigmoid(double Signal), Tanh(double Signal), ReLU(double Signal)
//开发者：Jason Cheng   日期：2025/7/15
//更改记录
//----------------------------------------------------------------------------------------------------------

class ActivationFunction
{
    public:
        static double Sigmoid(const double& Signal);    //Sigmoid函数
        static double Tanh(const double& Signal);       //Tanh函数
        static double ReLU(const double& Signal);       //ReLU函数
};

#endif /*ACTIVATION_FUNCTION_HPP*/