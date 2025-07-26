//----------------------------------------------------------------------------------------------------------
//NeuroContainer.cpp
//功能模块：NeuroContainer类的成员函数；目的：定义NeuroContainer类的成员函数
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include "NeuroContainer.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：NeuroContainer（构造函数）
//函数功能：构造一个NeuroContainer类对象
//参数：double SetBias = 0, int SetActvtnFnctn = 0, 均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

NeuroContainer::NeuroContainer(double SetBias, int SetActvtnFnctn) {
    m_rBias = SetBias;
    m_iNumOfActvtnFnctn = SetActvtnFnctn;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：NeuroContainer（拷贝构造函数）
//函数功能：拷贝构造一个NeuroContainer类对象
//参数：const NeuroContainer& Source 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

NeuroContainer::NeuroContainer(const NeuroContainer& Source) {
    m_rBias = Source.m_rBias;
    m_iNumOfActvtnFnctn = Source.m_iNumOfActvtnFnctn;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (赋值运算符重载)
//函数功能：实现NeuroContainer对象的复制
//参数：const NeuroContainer& Source 输入参数
//返回值：NeuroContainer&
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

NeuroContainer& NeuroContainer::operator=(const NeuroContainer& Source) {
    m_rBias = Source.m_rBias;
    m_iNumOfActvtnFnctn = Source.m_iNumOfActvtnFnctn;
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~NeuroContainer （析构函数）
//函数功能：析构NeuroContainer对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

NeuroContainer::~NeuroContainer() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetBias
//函数功能：设置偏置
//参数：double SetBias
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void NeuroContainer::SetBias(double SetBias) {
    m_rBias = SetBias;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetActvtnFnctn
//函数功能：设置激活函数
//参数：int SetActvtnFnctn = 0, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void NeuroContainer::SetActvtnFnctn(int SetActvtnFnctn) {
    m_iNumOfActvtnFnctn = SetActvtnFnctn;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：展示容器信息
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

std::string NeuroContainer::ToString() const {
    std::ostringstream Stream;
    Stream << "**NeuroContainer**" << std::endl;
    Stream << "Bias, Activition Function = (" << m_rBias << ", " << m_iNumOfActvtnFnctn << ")" << std::endl;
    return Stream.str();
}