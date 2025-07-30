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
#include <vector>
#include <set>

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
    std::cout << std::endl;
    return pMyNetwork;
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
    ANNImporter ImportANNFile(FilePath);
    std::vector<NeuroContainer> MyNeuroVector;
    std::set<SynapseContainer>  MySynapseSet;
    std::vector<LayerContainer> MyLayerVector;
    char NetworkName[40];
    ImportANNFile.ReadFile(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
    Network* pMyNetwork = ImportNetwork(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
    return pMyNetwork;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ExportNetwork
//函数功能：根据网络导出存储网络的容器
//参数：
/*
    *   const Network& SourceNetwork                输入参数
    *   std::vector<NeuroContainer>& MyNeuroVector  输出参数
    *   std::set<SynapseContainer>&  MySynapseSet   输出参数
    *   std::vector<LayerContainer>& MyLayerVector  输出参数
    *   char* NetworkName                           输出参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/30
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ExportNetwork(const Network& SourceNetwork,
                              std::vector<NeuroContainer>& MyNeuroVector,
                              std::set<SynapseContainer>&  MySynapseSet,
                              std::vector<LayerContainer>& MyLayerVector,
                              char* NetworkName) const
{
    strcpy_s(NetworkName, 40, SourceNetwork.NetworkName);               //获取神经网络的名称
    MyNeuroVector.clear();
    MyNeuroVector.reserve(SourceNetwork.GetNumberOfNeuros());
    MySynapseSet.clear();
    MyLayerVector.clear();
    MyLayerVector.reserve(SourceNetwork.GetNumberOfLayers());

    /*填充容器*/
    MyLayersType::const_iterator const_iter_Layers = SourceNetwork.MyLayers.begin();
    while (const_iter_Layers != SourceNetwork.MyLayers.end()) {         //对层循环
        const Layer& ThisLayer = *const_iter_Layers;
        /*填充层的容器*/
        LayerContainer ThisLyrCntnr(const_iter_Layers->GetMyNeuros().begin()->first, const_iter_Layers->GetMyNeuros().rbegin()->first);
        MyLayerVector.push_back(ThisLyrCntnr);

        MyNeurosType::const_iterator const_iter_Neuros = ThisLayer.GetMyNeuros().begin();
        while (const_iter_Neuros != ThisLayer.GetMyNeuros().end()) {    //对神经元循环
            const Neuro& ThisNeuro = const_iter_Neuros->second;
            /*填充神经元的容器*/
            NeuroContainer ThisNrCntnr(ThisNeuro.MySoma.GetBias(), ThisNeuro.MySoma.GetActvtnFunc());
            MyNeuroVector.push_back(ThisNrCntnr);

            /*填充突触的容器（树突）*/
            MyDndrtType::const_iterator const_iter_Dndrts = ThisNeuro.MyDendrites.begin();
            while (const_iter_Dndrts != ThisNeuro.MyDendrites.end()) {
                const Dendrite& ThisDendrite = *const_iter_Dndrts;
                SynapseContainer ThisDndrtCntnr(-1, ThisNeuro.NeuroID, ThisDendrite.GetWeight());
                if (ThisDendrite.GetNeuro() != nullptr) {
                    ThisDndrtCntnr.SetCnnctNeuro(ThisDendrite.GetNeuro()->NeuroID);
                }
                MySynapseSet.insert(ThisDndrtCntnr);
                const_iter_Dndrts++;
            }
            /*填充突触的容器（轴突）*/
            if (const_iter_Layers == (SourceNetwork.MyLayers.end() - 1)) {  //如果在最后一行，就加入轴突
                SynapseContainer ThisAxonCntnr(ThisNeuro.NeuroID, -1, 1.0);
                MySynapseSet.insert(ThisAxonCntnr);
            }
            const_iter_Neuros++;
        }

        const_iter_Layers++;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ExportNetwork
//函数功能：根据网络导出.ANN文件
//参数：
/*
    *   const Network& SourceNetwork        输入参数
    *   const char* FilePath                输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/30
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ExportNetwork(const Network& SourceNetwork, const char* FilePath) const {
    std::vector<NeuroContainer> MyNeuroVector;
    std::set<SynapseContainer>  MySynapseSet;
    std::vector<LayerContainer> MyLayerVector;
    char NetworkName[40];
    //将网络导出到容器
    ExportNetwork(SourceNetwork, MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
    //将容器导出到文件
    ANNExporter OutFile(FilePath);
    OutFile.OutputFile(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ShowNetwork
//函数功能：列出所有Layer对象，显示其序号和内部神经元的数量、序号
//参数：
/*
    *   const Network& SourceNetwork        输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/30
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ShowNetwork(const Network& SourceNetwork) const {
    std::cout << std::endl;
    std::cout << SourceNetwork.ToString_brief() << std::endl;
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteLayer
//函数功能：删除指定Layer 对象，同时删除此Layer 内部神经元及其关联的层间突触连接
//参数：
/*
    *   Network& SourceNetwork        输入参数
    *   unsigned int LayerNumber            输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/30
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::DeleteLayer(Network& SourceNetwork, unsigned int LayerNumber) const {
    SourceNetwork.DeleteLayer(LayerNumber);
}

