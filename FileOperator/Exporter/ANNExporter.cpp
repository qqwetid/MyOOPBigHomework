//----------------------------------------------------------------------------------------------------------
//ANNExporter.cpp
//功能模块：ANNExporter类的成员函数；目的：定义ANNExporter类的成员函数
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstring>

#include "../Container/NeuroContainer.hpp"
#include "../Container/LayerContainer.hpp"
#include "../Container/SynapseContainer.hpp"
#include "Exporter.hpp"
#include "ANNExporter.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：ANNExporter（构造函数）
//函数功能：构造一个ANNExporter类对象
//参数：const char* SetFileName = 0 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNExporter::ANNExporter(const char* SetFileName) : Exporter(SetFileName)
{
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator=
//函数功能：实现赋值运算符的重载
//参数：const ANNExporter& Source  输入参数
//返回值：ANNExporter&
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNExporter& ANNExporter::operator=(const ANNExporter& Source) {
    strcpy_s(this->m_FileNamePath, 99, Source.m_FileNamePath);
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ANNExporter（构造函数）
//函数功能：构造一个ANNExporter类对象
//参数：const ANNExporter& Source  输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNExporter::ANNExporter(const ANNExporter& Source) : Exporter(Source)
{
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~ANNExporter（析构函数）
//函数功能：析构一个ANNExporter类对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNExporter::~ANNExporter() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsANNFile
//函数功能：判断存储的是不是.ANN文件
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

bool ANNExporter::IsANNFile() const {
    int PathLength = strlen(m_FileNamePath);
    const char* pCheckANN = m_FileNamePath + (PathLength - 1);
    while (pCheckANN != m_FileNamePath) {
        if (*pCheckANN != ' ') {            //排除空格后结尾是不是.ANN
            if (*pCheckANN == 'N' 
                && *(pCheckANN - 1) == 'N'
                && *(pCheckANN - 2) == 'A'
                && *(pCheckANN - 3) == '.') //如果文件是.ANN，返回true
            {
                return true;
            }
            throw std::invalid_argument("Error: Your File is not a .ANN file.");    //如果不是，跳出循环throw错误信息
            break;
        }
        pCheckANN--;
        if (pCheckANN == m_FileNamePath)    //如果循环结束，throw错误信息
        {
            throw std::invalid_argument("Error: There is nothing in your file.");
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断文件是否合法
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------

bool ANNExporter::IsValid() const {
    std::ifstream InFile(m_FileNamePath, std::ios::in); //根据文件的路径打开文件
    if (!InFile.is_open()) {                            //如果文件没打开，throw错误信息
        std::ostringstream Stream;
        Stream << "Error: Failed to open a file from \"" << m_FileNamePath << "\".";
        throw std::invalid_argument(Stream.str());
    }
    while (!InFile.eof()) {                             //只要文件没有结束，就继续
        char RowType;                                   //识别行的类型
        InFile >> RowType;
        std::string ThisRow;
        switch (RowType)
        {
        case 'N' :                                      //遇到N，神经元数量+1
            double dBias;
            int iActvtnFnctn;
            InFile >> dBias >> iActvtnFnctn;
            std::getline(InFile, ThisRow);
            if (ThisRow != " ") {                        //如果这行不合法，throw错误信息
                throw std::invalid_argument("Error: There is an invalid neuron row.");
            }
            break;
        case 'L' :                                      //遇到L，层的数量+1
            int iFirstNum;
            int iSecondNum;                             //定义两个整数存储信息
            InFile >> iFirstNum >> iSecondNum;
            std::getline(InFile, ThisRow);
            if (ThisRow != " ") {                        //如果这行不合法，throw错误信息
                throw std::invalid_argument("Error: There is an invalid Layer row.");
            }
            break;
        case 'S' :
            int iFirstNeuro;
            int iSecondNeuro;
            double rWeight;
            InFile >> iFirstNeuro >> iSecondNeuro >> rWeight;
            std::getline(InFile, ThisRow);
            if (ThisRow != " ") {                       //如果这行不合法，throw错误信息
                throw std::invalid_argument("Error: There is an invalid Synapse row.");
            }
            break;
        case 'G'  :                                     //注释行、网络名称行和空格行跳过
        case '#'  :
        case ' '  :
        case '\0' :
            std::getline(InFile, ThisRow);
            break;

        default:                                        //如果还有其他行，输出不合法信息
            throw std::invalid_argument("Error: Your .ANN file has an invalid row!");
            break;
        }
        //重置RowType
        RowType = '\0';
    }
    //如果没有问题，返回1并将神经元、层的个数输入到Exporter中
    return true;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：OutputFile
//函数功能：将神经网络的信息输出到文件
//参数：
/*
    *   const std::vector<NeuroContainer>& MyNeuroVector,   输入参数
    *   const std::set<SynapseContainer>&  MySynapseSet,    输入参数
    *   const std::vector<LayerContainer>& MyLayerVector,   输入参数
    *   const char* NetworkName                             输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/26
//更改记录
//----------------------------------------------------------------------------------------------------------
void ANNExporter::OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
                             const std::set<SynapseContainer>&  MySynapseSet,
                             const std::vector<LayerContainer>& MyLayerVector,
                             const char* NetworkName)
{
    IsANNFile();                                                //先判断路径中是否有.ANN文件，如果是，则继续
    //检查NetworkName中是否有空格，如果有空格，throw错误信息
    for (const char* pCheckSpace = NetworkName; *pCheckSpace != '\0'; pCheckSpace++) {
        if (*pCheckSpace == ' ') {
            throw std::invalid_argument("Error: There is a blank space in your NetworkName.");
        }
    }
    std::ofstream OutFile(m_FileNamePath, std::ios::out);
    if (!OutFile.is_open()) {                                   //如果文件没打开，throw错误信息
        std::ostringstream Stream;
        Stream << "Error: Failed to open a file from \"" << m_FileNamePath << "\".";
        throw std::invalid_argument(Stream.str());
        exit(1);
    }
    //# 文件名
    OutFile << "# " << m_FileNamePath << std::endl;

    //G NetworkName
    OutFile << "G " << NetworkName << std::endl;

    //神经元
    OutFile << "# " << MyNeuroVector.size() << " Neurons" << std::endl;
    std::vector<NeuroContainer>::const_iterator const_iter_Neuros = MyNeuroVector.begin();
    while (const_iter_Neuros != MyNeuroVector.end()) {          //对神经元循环，输出到文件中
        OutFile << "N " << const_iter_Neuros->Bias << " " << const_iter_Neuros->NumOfActvtnFnctn << " " << std::endl;
        const_iter_Neuros++;
    }

    //层
    std::vector<LayerContainer>::const_iterator const_iter_Layers = MyLayerVector.begin();
    while (const_iter_Layers != MyLayerVector.end()) {          //对层循环，输出到文件中
        OutFile << "# Layer " << (const_iter_Layers - MyLayerVector.begin()) 
                << ": Neuron " << const_iter_Layers->StartNeuro << " to " << const_iter_Layers->EndNeuro
                << std::endl;                                   //注释行
        OutFile << "L " << const_iter_Layers->StartNeuro << " " 
                << const_iter_Layers->EndNeuro << " " 
                << std::endl;                                   //L start end
        const_iter_Layers++;
    }

    //突触
    std::set<SynapseContainer>::const_iterator const_iter_Synapse = MySynapseSet.begin();
    //先连第一层
    OutFile << "# Neuron " << MyLayerVector.begin()->StartNeuro << " to " << MyLayerVector.begin()->EndNeuro
            << ": has one Dendrite" << std::endl;
    while (const_iter_Synapse != MySynapseSet.end()) {          //对突触循环，将第一层的树突输出到文件
        if (const_iter_Synapse->CnnctNeuro == -1) {
            OutFile << "S -1 " << const_iter_Synapse->LyingNeuro << " " << const_iter_Synapse->Weight << " " << std::endl;
        }
        const_iter_Synapse++;
    }
    //再连最后一层
    OutFile << "# Neuron" << (MyLayerVector.end() - 1)->StartNeuro << " to " << (MyLayerVector.end() - 1)->EndNeuro
            <<": has one Axon" << std::endl;
    const_iter_Synapse = MySynapseSet.begin();                  //重置树突指针
    while (const_iter_Synapse != MySynapseSet.end()) {          //对突触循环，将最后一层的轴突输出到文件
        if (const_iter_Synapse->LyingNeuro == -1) {
            OutFile << "S " << const_iter_Synapse->CnnctNeuro << " -1 " << const_iter_Synapse->Weight << " " << std::endl;
        }
        const_iter_Synapse++;
    }
    //再连其它层
    const_iter_Synapse = MySynapseSet.begin();                  //重置树突指针
    int NeuronNow = -1;                                         //存储器，存储当前神经元，方便写注释
    while (const_iter_Synapse != MySynapseSet.end()) {          //对突出循环，将其它层的树突输出到文件
        if (const_iter_Synapse->LyingNeuro != -1 && const_iter_Synapse->CnnctNeuro != -1) {
            if (NeuronNow != const_iter_Synapse->CnnctNeuro) {  //如果第一个神经元发生了变化，就该写注释了
                NeuronNow = const_iter_Synapse->CnnctNeuro;     //将存储器同步
                OutFile << "# Dendrites from Neuron " << NeuronNow << std::endl;
            }
            OutFile << "S " << const_iter_Synapse->CnnctNeuro << " "
                    << const_iter_Synapse->LyingNeuro << " "
                    << const_iter_Synapse->Weight << " " << std::endl;
        }
        const_iter_Synapse++;
    }
    OutFile.close();                                            //结束后关闭文件
}