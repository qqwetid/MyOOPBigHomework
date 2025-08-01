//----------------------------------------------------------------------------------------------------------
//Denderite.cpp
//功能模块与目的：在Synapse类的基础上，定义Denderite类中的函数
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： 2025/7/19 将树突的私有成员中的轴突改成了神经元，并将Getter的返回值从Neuro& 改成了 Neuro*
//----------------------------------------------------------------------------------------------------------

#include "ActivationFunction.hpp"
#include "Soma.hpp"
#include "Synapse.hpp"
#include "Axon.hpp"
#include "Dendrite.hpp"
#include "Neuro.hpp"
#include <iostream>
#include <string>
#include <sstream>

//----------------------------------------------------------------------------------------------------------
//函数名称：Dendrite（构造函数）
//函数功能：构造Dendrite类
//参数：double Weight_set = 1, const Neuro* pConnetNeuro_set = nullptr,均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/18
//更改记录: 2025/7/19 将输入参数的类型从 Axon* 改成了 Neuro*
//----------------------------------------------------------------------------------------------------------

Dendrite::Dendrite(double Weight_set, Neuro* pConnetNeuro_set) : Synapse(Weight_set) {
    m_pConnectNeuro = pConnetNeuro_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (重载赋值运算符)
//函数功能：重载赋值运算符，对Dendrite类赋值
//参数：const Dendrite& Source,输入参数
//返回值：Dendrite&
//开发者：Jason Cheng   日期：2025/7/18
//更改记录: 将赋值过程的m_pConnectAxon改成了GetNeuro()成员函数
//----------------------------------------------------------------------------------------------------------

Dendrite& Dendrite::operator=(const Dendrite& Source) {
    Synapse::SetWeight(Source.GetWeight());     //将Source中m_dWeight的权重赋给本对象
    m_pConnectNeuro = Source.GetNeuro();
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Dendrite（拷贝构造函数）
//函数功能：拷贝构造Dendrite类
//参数：const Dendrite& Source, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： 为了适应对私有成员的修改，Axon改成了Neuro
//----------------------------------------------------------------------------------------------------------

Dendrite::Dendrite(const Dendrite& Source) : Synapse(Source.GetWeight()) {
    m_pConnectNeuro = Source.GetNeuro();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~Dendrite
//函数功能：析构函数
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/18
//更改记录
//----------------------------------------------------------------------------------------------------------

Dendrite::~Dendrite() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetAxon()
//函数功能：获得连接的轴突
//参数：无
//返回值：Neuro*
//开发者：Jason Cheng   日期：2025/7/18
//更改记录: 2025/7/19 GetAxon改成了GetNeuro
//         2025/7/19 返回值改成了Neuro*
//----------------------------------------------------------------------------------------------------------

Neuro* Dendrite::GetNeuro() const {
    return m_pConnectNeuro;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetNeuro(Neuro& pConnection_set)
//函数功能：为这个树突连接一个轴突
//参数：Neuro& pConnection_set, 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： Axon& 改成了 Neuro& 
//----------------------------------------------------------------------------------------------------------

void Dendrite::SetNeuro(Neuro& pConnection_set) {
    m_pConnectNeuro = &pConnection_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString()
//函数功能：将树突的信息整合成一个字符串，带回车
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： 把里面的 Axon 都改成了 Neuro
//----------------------------------------------------------------------------------------------------------

std::string Dendrite::ToString() const {
    std::ostringstream Stream;
    Stream << "**Dendrite**" << std::endl;
    Stream << "Weight:\t" << Synapse::GetWeight() << std::endl;
    Stream << "Address of the connected Neuro:\t" << m_pConnectNeuro << std::endl;
    return Stream.str();
}