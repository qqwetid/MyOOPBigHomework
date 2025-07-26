//----------------------------------------------------------------------------------------------------------
//LayerContainer.cpp
//功能模块：LayerContainer类的成员函数；目的：定义LayerContainer类的成员函数
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include "LayerContainer.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：LayerContainer（构造函数）
//函数功能：构造一个LayerContainer类对象
//参数：unsigned int SetStartNeuro = 0, unsigned int SetEndNeuro = 0, 均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

LayerContainer::LayerContainer(unsigned int SetStartNeuro, unsigned int SetEndNeuro) {
    m_uStartNeuro = SetStartNeuro;
    m_uEndNeuro = SetEndNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：LayerContainer（拷贝构造函数）
//函数功能：拷贝构造一个LayerContainer类对象
//参数：const LayerContainer& Source 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

LayerContainer::LayerContainer(const LayerContainer& Source) {
    m_uStartNeuro = Source.StartNeuro;
    m_uEndNeuro = Source.EndNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (赋值运算符重载)
//函数功能：实现LayerContainer对象的复制
//参数：const LayerContainer& Source 输入参数
//返回值：LayerContainer&
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

LayerContainer& LayerContainer::operator=(const LayerContainer& Source) {
    m_uStartNeuro = Source.StartNeuro;
    m_uEndNeuro = Source.EndNeuro;
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~LayerContainer （析构函数）
//函数功能：析构LayerContainer对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

LayerContainer::~LayerContainer() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetStartNeuro
//函数功能：设置起始神经元
//参数：unsigned int SetStartNeuro
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void LayerContainer::SetStartNeuro(unsigned int SetStartNeuro) {
    m_uStartNeuro = SetStartNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetEndNeuro
//函数功能：设置结尾神经元
//参数：unsigned int SetEndNeuro, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void LayerContainer::SetEndNeuro(unsigned int SetEndNeuro) {
    m_uEndNeuro = SetEndNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：展示容器信息
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

std::string LayerContainer::ToString() const {
    std::ostringstream Stream;
    Stream << "**LayerContainer**" << std::endl;
    Stream << "StartNeuro, EndNeuro = (" << m_uStartNeuro << ", " << m_uEndNeuro << ")" << std::endl;
    return Stream.str();
}