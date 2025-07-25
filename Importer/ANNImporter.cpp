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
#include <cstring>

#include "Importer.hpp"
#include "ANNImporter.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：ANNImporter（构造函数）
//函数功能：构造一个ANNImporter类对象
//参数：const char* SetFileName = 0 输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNImporter::ANNImporter(const char* SetFileName) : Importer(SetFileName)
{
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator=
//函数功能：实现赋值运算符的重载
//参数：const ANNImporter& Source  输入参数
//返回值：ANNImporter&
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNImporter& ANNImporter::operator=(const ANNImporter& Source) {
    strcpy_s(this->m_FileNamePath, 99, Source.m_FileNamePath);
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ANNImporter（构造函数）
//函数功能：构造一个ANNImporter类对象
//参数：const ANNImporter& Source  输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNImporter::ANNImporter(const ANNImporter& Source) : Importer(Source)
{
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~ANNImporter（析构函数）
//函数功能：析构一个ANNImporter类对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

ANNImporter::~ANNImporter() {
    //空函数体
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断文件是否合法
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

bool ANNImporter::IsValid() const {
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
    //如果没有问题，返回1并将神经元、层的个数输入到Importer中
    return true;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断文件是否合法，并查看路径中的.ANN文件中神经元、层的数量
//参数：
/*
    *   int& NumOfNeuros        输出参数，返回神经元的数量
    *   int& NumOfLayers        输出参数，返回层的数量
*/
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/25
//更改记录
//----------------------------------------------------------------------------------------------------------

bool ANNImporter::IsValid(int& NumOfNeuros, int& NumOfLayers) const {
    int MyNeuroNumber = 0;                              //定义临时变量存储神经元数量
    int MyLayerNumber = 0;                              //定义临时变量存储层的数量
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
            MyNeuroNumber++;
            double dBias;
            int iActvtnFnctn;
            InFile >> dBias >> iActvtnFnctn;
            std::getline(InFile, ThisRow);
            if (ThisRow != " ") {                        //如果这行不合法，throw错误信息
                throw std::invalid_argument("Error: There is an invalid neuron row.");
            }
            break;
        case 'L' :                                      //遇到L，层的数量+1
            MyLayerNumber++;
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
    //如果没有问题，返回1并将神经元、层的个数输入到Importer中
    NumOfNeuros = MyNeuroNumber;
    NumOfLayers = MyLayerNumber;
    return true;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ReadFile
//函数功能：读取文件内容
//参数：
/*
    *   std::vector<NeuroContainer>& MyNeuroVector   输出参数，传出神经元的信息
    *   std::set<SynapseContainer>&  MySynapseSet    输出参数，传出树突的信息
    *   std::vector<LayerContainer>& MyLayerVector   输出参数，传出层的信息
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/24
//更改记录
//----------------------------------------------------------------------------------------------------------

void ANNImporter::ReadFile(std::vector<NeuroContainer>& MyNeuroVector,
                std::set<SynapseContainer>&  MySynapseSet,
                std::vector<LayerContainer>& MyLayerVector,
                char* NetworkName) {
    std::ifstream InFile(m_FileNamePath, std::ios::in); //根据输入的路径，打开一个文件
    if (!InFile.is_open()) {                            //如果文件没打开，throw错误信息
        std::ostringstream Stream;
        Stream << "Error: Failed to open a file from \"" << m_FileNamePath << "\".";
        throw std::invalid_argument(Stream.str());
    }

    //先将Vector扩到合适的大小
    int NumOfNeuros;    //存储神经元的数量
    int NumOfLayers;    //存储层的数量
    IsValid(NumOfNeuros, NumOfLayers);                  //判断文件是否合法，并得到神经元、层的数量
    MyNeuroVector.clear();                              //清除容器内之前的内容
    MyNeuroVector.reserve(NumOfNeuros);                 //设置向量的大小为神经元的数量
    MySynapseSet.clear();
    MyLayerVector.clear();
    MyLayerVector.reserve(NumOfLayers);
    while (!InFile.eof()) {                             //只要文件还没有结束，就继续循环
        char RowType = '\0';
        InFile >> RowType;                              //获取这一行的第一个字符，判断这一行的行为
        std::string ThisRow;
        switch (RowType) {
            case '#' : {                                //如果是注释行，则跳过
                std::getline(InFile, ThisRow);
                break;
            }
            case 'N' : {                                //如果是神经元的信息，则输入到神经元的容器中
                NeuroContainer ThisNeuro;
                InFile >> ThisNeuro.Bias;               //获取偏置
                InFile >> ThisNeuro.NumOfActvtnFctn;    //获取激活函数
                MyNeuroVector.push_back(ThisNeuro);
                std::getline(InFile, ThisRow);          //将指针跳转到下一行开头
                break;
            }
            case 'L' : {
                LayerContainer ThisLayer;
                InFile >> ThisLayer.StartNeuro;         //获取起始神经元
                InFile >> ThisLayer.EndNeuro;           //获取结束神经元
                MyLayerVector.push_back(ThisLayer);
                std::getline(InFile, ThisRow);          //将指针跳转到下一行开头
                break;
            }
            case 'S' : {
                SynapseContainer ThisSynapse;
                InFile >> ThisSynapse.CnnctNeuro;       //获取前端的神经元
                InFile >> ThisSynapse.LyingNeuro;       //获取后端的神经元
                InFile >> ThisSynapse.Weight;           //获取权重
                auto result = MySynapseSet.insert(ThisSynapse); //将树突存到集合中
                if(!result.second) {                    //如果插入失败，进行提示
                    std::cerr << "Error: There is a same synapse in the set" << std::endl;
                }
                std::getline(InFile, ThisRow);
                break;
            }
            case 'G' : {
                std::getline(InFile, ThisRow);          //将文件名存到ThisRow中
                if (ThisRow.size() >= 40)               //如果文件名过长，返回警告信息，并裁掉多余部分
                {
                    std::cout << "Warning: Your Network name will be cut since it is to long." << std::endl;
                    ThisRow.erase(ThisRow.begin() + 39, ThisRow.end());
                }
                strcpy_s(NetworkName, 40, ThisRow.c_str());
                break;
            }

            default: {
                std::getline(InFile, ThisRow);
                break;
            }
        }
        RowType = '\0';                                 //重置RowType
    }
    //关闭文件
    InFile.close();
}


