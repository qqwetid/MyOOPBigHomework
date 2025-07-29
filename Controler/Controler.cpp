//----------------------------------------------------------------------------------------------------------
//Controler.cpp
//功能模块：Controler类的成员函数；目的：定义Controler类的成员函数
//开发者：Jason Cheng   日期：2025/7/28
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>

#include "../Network/ActivationFunction.hpp"                //导入激活函数类
#include "../Network/Soma.hpp"                              //导入细胞体Soma类
#include "../Network/Synapse.hpp"                           //导入突触类
#include "../Network/Axon.hpp"                              //导入轴突类
#include "../Network/Dendrite.hpp"                          //导入树突类
#include "../Network/Neuro.hpp"                             //导入Neuro类的声明
#include "../Network/Layer.hpp"                             //导入Layer类的声明
#include "../Network/Network.hpp"                           //导入Network类的声明
#include "../FileOperator/Container/NeuroContainer.hpp"     //导入神经元的容器
#include "../FileOperator/Container/LayerContainer.hpp"     //导入层的容器
#include "../FileOperator/Container/SynapseContainer.hpp"   //导入突触的容器
#include "../FileOperator/Importer/Importer.hpp"            //导入Importer类的声明
#include "../FileOperator/Importer/ANNImporter.hpp"         //导入ANNImporter类的声明
#include "../FileOperator/Exporter/Exporter.hpp"            //导入Exporter类的声明
#include "../FileOperator/Exporter/ANNExporter.hpp"         //导入ANNExporter类的声明
#include "Controler.hpp"                                    //导入控制器

//----------------------------------------------------------------------------------------------------------
//函数名称：Controler（构造函数）
//函数功能：构造一个Controler类对象
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/28
//更改记录
//----------------------------------------------------------------------------------------------------------

Controler::Controler() {
    //空函数体
}

//初始化静态私有成员指针
Controler* Controler::m_pInstance_ = nullptr;

//----------------------------------------------------------------------------------------------------------
//函数名称：GetInstance
//函数功能：如果Controler类没有实例化，获取一个GetInstance实例
//参数：无
//返回值：Controler*
//开发者：Jason Cheng   日期：2025/7/28
//更改记录
//----------------------------------------------------------------------------------------------------------

Controler* Controler::GetInstance() {
    if (!m_pInstance_) {                //如果还没有实例，则创建一个实例
        m_pInstance_ = new Controler;
    }
    return m_pInstance_;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InputFilePath
//函数功能：输入文件的路径，并判断是否合法
//参数：
/*
    *   char* FilePath              输出参数
    *   unsigned int PathLength     输入参数，表示字符串的最大长度
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/28
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InputFilePath(char* FilePath, unsigned int PathLength) const {
    std::cout << "请输入文件路径：" << std::endl;
    std::string MyString;
    std::getline(std::cin, MyString);
    if (MyString.size() > PathLength) {                 //如果文件路径过长，throw错误信息
        std::ostringstream Stream;
        Stream << "Error: Your Path is too long!" << std::endl;
        Stream << "\tLength of your path should not longer than " << PathLength << " characters.";
        throw std::invalid_argument(Stream.str());
        exit(1);
    }
    strcpy_s(FilePath, PathLength + 1, MyString.c_str());   //如果没有问题，将路径复制给FilePath
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ImportNetwork
//函数功能：根据容器导入神经网络
//参数：
/*
    *   const std::vector<NeuroContainer>& MyNeuroVector    输入参数
    *   const std::set<SynapseContainer>&  MySynapseSet     输入参数
    *   const std::vector<LayerContainer>& MyLayerVector    输入参数
    *   const char* NetworkName                             输入参数
*/
//返回值：Network*
//开发者：Jason Cheng   日期：2025/7/29
//更改记录
//----------------------------------------------------------------------------------------------------------

Network* Controler::ImportNetwork(const std::vector<NeuroContainer>& MyNeuroVector,
                                  const std::set<SynapseContainer>&  MySynapseSet,
                                  const std::vector<LayerContainer>& MyLayerVector,
                                  const char* NetworkName) const 
{
    std::cout << "Importing Network..." << std::endl;
    Network* pMyNetwork = new Network(NetworkName, 1, MyLayerVector.size());
    //删除构造函数带来的第一层
    pMyNetwork->DeleteLayer(0);
    //创建神经元
    std::vector<Neuro> MyNeuros(MyNeuroVector.size());
    std::vector<NeuroContainer>::const_iterator const_iter_NrVctr = MyNeuroVector.begin();
    while (const_iter_NrVctr != MyNeuroVector.end()) {          //将神经元构造出来
        Neuro ThisNeuro(const_iter_NrVctr->Bias, const_iter_NrVctr->NumOfActvtnFnctn, 100, (const_iter_NrVctr - MyNeuroVector.begin()));
        MyNeuros.push_back(ThisNeuro);
        const_iter_NrVctr++;
    }
    //将层插入神经网络
    std::vector<LayerContainer>::const_iterator const_iter_LyrVctr = MyLayerVector.begin();
    while (const_iter_LyrVctr != MyLayerVector.end()) {         //对层的容器循环，将层插入到神经网络
        Layer ThisLayer;
        for (int i = const_iter_LyrVctr->StartNeuro; i <= const_iter_LyrVctr->EndNeuro; i++) {
            ThisLayer.InsertNeuro(*(MyNeuros.begin() + i));     //将神经元插入到层中
        }
        pMyNetwork->InsertLayer(ThisLayer);
        const_iter_LyrVctr++;
    }
    //将树突插入神经网络
    std::set<SynapseContainer>::const_iterator const_iter_SynpsSet = MySynapseSet.begin();
    while (const_iter_SynpsSet != MySynapseSet.end()) {         //对突触的容器循环，将突触插入到神经网络
        pMyNetwork->CnnctNursByDndrt(const_iter_SynpsSet->CnnctNeuro, const_iter_SynpsSet->LyingNeuro, const_iter_SynpsSet->Weight);
        const_iter_SynpsSet++;
    }
    std::cout << "Your Network " << NetworkName << " has been imported successfully!" << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ImportNetwork
//函数功能：根据输入的文件路径导入神经网络
//参数：
/*
    *   const char* FilePath    输入参数，传入文件路径
*/
//返回值：Network*
//开发者：Jason Cheng   日期：2025/7/29
//更改记录
//----------------------------------------------------------------------------------------------------------

Network* Controler::ImportNetwork(const char* FilePath) const {
    
}