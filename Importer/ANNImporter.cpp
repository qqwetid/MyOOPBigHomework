//----------------------------------------------------------------------------------------------------------
//ANNImporter.cpp
//功能模块：ANNImporter类的成员函数；目的：定义ANNImporter类的成员函数
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <sstream>

#include "../Network/Network.hpp"
#include "Importer.hpp"
#include "ANNImporter.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：ImportFile
//函数功能：读取
//参数：
/*
    *   const char* FileNamePath                    输入参数，传入文件的名称（带路径）
    *   std::vector<NeuroContainer> MyNeuroVector   输出参数，传出神经元的信息
    *   std::set<SynapseContainer>  MySynapseSet    输出参数，传出树突的信息
    *   std::vector<LayerContainer> MyLayerVector   输出参数，传出层的信息
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/24
//更改记录
//----------------------------------------------------------------------------------------------------------

void ANNImporter::ImportFile(const char* FileNamePath, 
                std::vector<NeuroContainer> MyNeuroVector,
                std::set<SynapseContainer>  MySynapseSet,
                std::vector<LayerContainer> MyLayerVector,
                char* NetworkName) {
    std::ifstream InFile(FileNamePath, std::ios::in);   //根据输入的路径，打开一个文件
    if (!InFile.is_open()) {                            //如果文件没打开，throw错误信息
        std::ostringstream Stream;
        Stream << "Error: Failed to open a file from \"" << FileNamePath << "\".";
        throw std::invalid_argument(Stream.str());
    }
    MyNeuroVector.clear();                              //先清除容器内之前的内容
    MySynapseSet.clear();
    MyLayerVector.clear();
    while (!InFile.eof()) {                             //只要文件还没有结束，就继续循环
        char RowType;
        InFile >> RowType;                              //获取这一行的第一个字符，判断这一行的行为
        std::string ThisRow;
        switch (RowType) {
            case '#' :                                  //如果是注释行，则跳过
                std::getline(InFile, ThisRow);
                break;
            case 'N' :                                  //如果是神经元的信息，则输入到神经元的容器中
                //待编写
        }
    }
    //关闭文件
    //将向量缩到合适的大小
}