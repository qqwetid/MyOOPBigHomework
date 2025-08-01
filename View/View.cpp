//----------------------------------------------------------------------------------------------------------
//View.cpp
//功能模块：View类的成员函数；目的：定义View类的成员函数
//开发者：Jason Cheng   日期：2025/8/1
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>

#include "View.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：StartView
//函数功能：程序开始的界面
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void View::StartView() {
    std::cout << "Hello! Let's start!" << std::endl;
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Main
//函数功能：程序主界面
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void View::Main() {
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Main" << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Press   `1'   to import another network." << std::endl;
    std::cout << "Press   `2'   to export your current network." << std::endl;
    std::cout << "Press   `3'   to modify your network." << std::endl;
    std::cout << "Press   `4'   to show the number of layers, neurons and synapses in your network." << std::endl;
    std::cout << "Press   `5'   to check the validity and do inference." << std::endl;
    std::cout << "Press   `0'   to exit the programme." << std::endl;
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Branch3
//函数功能：程序修改神经网络的界面
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void View::Branch3() {
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Branch3: Modify your Network" << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Press   `1'   to show all layers." << std::endl;
    std::cout << "Press   `2'   to delete a layer." << std::endl;
    std::cout << "Press   `3'   to insert a layer with no neuron." << std::endl;
    std::cout << "Press   `4'   to insert a neuron into a layer." << std::endl;
    std::cout << "Press   `5'   to show neurons in a layer." << std::endl;
    std::cout << "Press   `6'   to reset the bias of a neuron." << std::endl;
    std::cout << "Press   `7'   to show synapses connecting with the neuron." << std::endl;
    std::cout << "Press   `8'   to delete a neuron." << std::endl;
    std::cout << "Press   `9'   to connect two neurons" << std::endl;
    std::cout << "Press   `0'   to go back to main interface." << std::endl;
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Branch5
//函数功能：程序验证人工神经网络和推理的界面
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void View::Branch5() {
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Branch5: check your network and do inference." << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Press   `1'   to check the validity of your Network." << std::endl;
    std::cout << "Press   `2'   to do inference." << std::endl;
    std::cout << "Press   `0'   to go back to main interface." << std::endl;
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << std::endl;
}