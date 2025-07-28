//----------------------------------------------------------------------------------------------------------
//Controler.cpp
//功能模块：Controler类的成员函数；目的：定义Controler类的成员函数
//开发者：Jason Cheng   日期：2025/7/28
//更改记录：
//----------------------------------------------------------------------------------------------------------

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
    //待编写
}