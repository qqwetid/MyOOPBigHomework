//----------------------------------------------------------------------------------------------------------
//Soma.cpp
//功能模块：对Soma类中函数进行定义；目的：定义细胞体类的函数
//开发者：Jason Cheng   日期：2025/7/16
//更改记录： 2025/7/18 更改了IsValid()函数，具体更改见该函数注释
//----------------------------------------------------------------------------------------------------------

#include "ActivationFunction.hpp"
#include "Soma.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

//----------------------------------------------------------------------------------------------------------
//函数名称：Soma（构造函数）
//函数功能：构造Soma类
//参数：const double Bias_set = 0, const int Num_set = 0，均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

Soma::Soma(const double Bias_set, const int Num_set) {
    try
    {
//        Soma::IsValid(Num_set);     //判断激活函数号码是否合法，若不合法会throw错误信息
        m_iNumOfActvtnFunc = Num_set;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "We set the activation function to be empty function(f(x) = x, NumOfActvtnFunc = 0)." << std::endl;
        m_iNumOfActvtnFunc = 0;     //将激活函数设置为空函数
    }
    m_rBias = Bias_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (赋值运算符)
//函数功能：为Soma类赋值
//参数：const Soma& Source，输入参数
//返回值：Soma&
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

Soma& Soma::operator=(const Soma& Source) {
    try
    {
        if (IsValid(Source) == 1);                  //判断Source是否合法，如果不合法，就不进行赋值(Bias, NumOfActvtnFunc都不会改变)
        {
            m_rBias = Source.GetBias();
            m_iNumOfActvtnFunc = Source.GetActvtnFunc();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "The origional Soma will not be valued by the source Soma." << std::endl;
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Soma（拷贝构造函数）
//函数功能：拷贝构造Soma类
//参数：const Soma& Source，输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

Soma::Soma(const Soma& Source) {
    try
    {
        if (IsValid(Source) == 1);                  //判断Source是否合法，如果不合法，就不进行赋值(Bias, NumOfActvtnFunc都不会改变)
        {
            m_rBias = Source.GetBias();
            m_iNumOfActvtnFunc = Source.GetActvtnFunc();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "This Soma will be created by Soma(0, 0)." << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~Soma（析构函数）
//函数功能：析构Soma类
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

Soma::~Soma() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断参数是否指出一个合理的激活函数
//参数：const double Bias, const int NumOfActvtnFunc，均为输入参数
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/17
//更改记录：2025/7/18 在throw的输出中加上了"Error: "
//----------------------------------------------------------------------------------------------------------

bool Soma::IsValid(const int NumOfActvtnFunc) {
    if (NumOfActvtnFunc > 3 || NumOfActvtnFunc < 0)      //判断构造函数是否存在
    {
        throw std::invalid_argument("Error: Cannot find such activatiton function!");
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断参数中的Soma类的激活函数是否合理
//参数：const Soma& Source，输入参数
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Soma::IsValid(const Soma& Source) {
    return Soma::IsValid(Source.GetActvtnFunc());
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断当前Soma类的激活函数是否合理
//参数：无参数
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Soma::IsValid() const {
    return Soma::IsValid(this->m_iNumOfActvtnFunc);
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Output
//函数功能：细胞体的输出，接收输入信号的求和，整合函数+激活函数
//参数：const double& SumOfSignals
//返回值：double
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

double Soma::Output(const double& SumOfSignals) const {
    double AfterSumFunc;    //存储加上偏置后的求和
    AfterSumFunc = SumOfSignals + m_rBias;
    try
    {
        IsValid();      //判断是否有明确的激活函数，若没有，则throw错误信息
        switch (m_iNumOfActvtnFunc)
        {
        case 0:
            return AfterSumFunc;
            break;
        case 1:
            return ActivationFunction::Sigmoid(AfterSumFunc);
            break;
        case 2:
            return ActivationFunction::Tanh(AfterSumFunc);
            break;
        case 3:
            return ActivationFunction::ReLU(AfterSumFunc);
            break;
        //已经列举了所有情况，不需要default
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "We will consider the activation function f(x) = x" << std::endl;
    }
    return AfterSumFunc;    //如果没有合法的激活函数，就认为是空激活函数
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetBias
//函数功能：细胞体偏置m_dBias的Getter
//参数：无
//返回值：double
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

double Soma::GetBias() const {
    return m_rBias;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetActivtnFunc
//函数功能：细胞体偏置m_iNumOfActvtnFunc的Getter
//参数：无
//返回值：int
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

int Soma::GetActvtnFunc() const {
    return m_iNumOfActvtnFunc;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetBias
//函数功能：细胞体偏置m_dBias的Setter
//参数：const double& Bias_set， 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

void Soma::SetBias(const double& Bias_set) {
    m_rBias = Bias_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetActvtnFunc
//函数功能：细胞体激活函数编号m_iNumOfActvtnFunc的Setter
//参数：const int& NumOfActvtnFunc_set， 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

void Soma::SetActvtnFunc(const int& NumOfActvtnFunc_set) {
    try
    {
        IsValid(NumOfActvtnFunc_set);   //判断设置的激活函数是否合规，若不合规，则throw错误信息
        m_iNumOfActvtnFunc = NumOfActvtnFunc_set;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "This activition function number will not be set." << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：将细胞体的信息整合为一个字符串
//参数：无
//返回值：string
//开发者：Jason Cheng   日期：2025/7/17
//更改记录      2025/7/24   增加default的部分
//----------------------------------------------------------------------------------------------------------

std::string Soma::ToString() const {
    std::ostringstream Stream;
    Stream << "**Soma**" << std::endl;
    Stream << "Bias: \t" << m_rBias << std::endl;
    try
    {
        IsValid();  //判断激活函数是否合理
        Stream << "Activition Function: \tNo." << m_iNumOfActvtnFunc << " \t";
        switch (m_iNumOfActvtnFunc)
        {
        case 0:
            Stream << "empty activation function";
            break;
        case 1:
            Stream << "Sigmoid Function";
            break;
        case 2:
            Stream << "Tanh Function";
            break;
        case 3:
            Stream << "ReLU Function";
            break;
        default:                    //事实上如果判断程序正确，错误的激活函数不会让程序出现在这里
            Stream << "Unknown Type";
            break;
    }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        Stream << "There is no legal activation function.";
    }
    Stream << std::endl;
    return Stream.str();
}
