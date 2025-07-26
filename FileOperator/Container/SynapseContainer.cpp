//----------------------------------------------------------------------------------------------------------
//SynapseContainer.cpp
//功能模块：SynapseContainer类的成员函数；目的：定义SynapseContainer类的成员函数
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include "SynapseContainer.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：SynapseContainer（构造函数）
//函数功能：构造一个SynapseContainer类对象
//参数：int SetCnnctNeuro = -1, int SetLyingNeuro = -1, double SetWeight = 1, 均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

SynapseContainer::SynapseContainer(int SetCnnctNeuro, int SetLyingNeuro, double SetWeight) {
    m_iCnnctNeuro = SetCnnctNeuro;
    m_iLyingNeuro = SetLyingNeuro;
    m_rWeight = SetWeight;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SynapseContainer（拷贝构造函数）
//函数功能：拷贝构造一个SynapseContainer类对象
//参数：const SynapseContainer& Source 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

SynapseContainer::SynapseContainer(const SynapseContainer& Source) {
    m_iCnnctNeuro = Source.CnnctNeuro;
    m_iLyingNeuro = Source.LyingNeuro;
    m_rWeight     = Source.Weight;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (赋值运算符重载)
//函数功能：实现SynapseContainer对象的复制
//参数：const SynapseContainer& Source 输入参数
//返回值：SynapseContainer&
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

SynapseContainer& SynapseContainer::operator=(const SynapseContainer& Source) {
    m_iCnnctNeuro = Source.CnnctNeuro;
    m_iLyingNeuro = Source.LyingNeuro;
    m_rWeight     = Source.Weight;
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~SynapseContainer （析构函数）
//函数功能：析构SynapseContainer对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

SynapseContainer::~SynapseContainer() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator< (比较运算符重载)
//函数功能：使得SynapseContainer的对象可以比较大小，便于放入Set集合
//参数：const SynapseContainer& Source
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

bool SynapseContainer::operator<(const SynapseContainer& Source) const {    //为了放在set中，需要定义比较大小的函数
    if (CnnctNeuro != Source.CnnctNeuro) {
        return (CnnctNeuro< Source.CnnctNeuro);                             //优先比较所在神经元的序号大小
    }
    else if (LyingNeuro != Source.LyingNeuro) {
        return (LyingNeuro < Source.LyingNeuro);                            //再比较连接的神经元的序号大小
    }
    else {
        return false;                                                       //如果两个神经元都相同，就认为两个树突一样，不允许同时出现
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetCnnctNeuro
//函数功能：设置连接的神经元
//参数：int SetCnnctNeuro
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void SynapseContainer::SetCnnctNeuro(int SetCnnctNeuro) {
    m_iCnnctNeuro = SetCnnctNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetLyingNeuro
//函数功能：设置所在的神经元
//参数：int SetLyingNeuro, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void SynapseContainer::SetLyingNeuro(int SetLyingNeuro) {
    m_iLyingNeuro = SetLyingNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetWeight
//函数功能：设置权重
//参数：double SetWeight, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

void SynapseContainer::SetWeight(double SetWeight) {
    m_rWeight = SetWeight;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：展示容器信息
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

std::string SynapseContainer::ToString() const {
    std::ostringstream Stream;
    Stream << "**SynapseContainer**" << std::endl;
    Stream << "First, Second, Weight: (" << this->CnnctNeuro << ", " << this->LyingNeuro << ", " << this->Weight << ")" << std::endl;
    return Stream.str();
}