//----------------------------------------------------------------------------------------------------------
//main.cpp
//目的：示范程序的使用方式
//开发者：Jason Cheng   日期：2025/8/1
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <set>
#include <vector>
#include <map>

#include "./Network/ActivationFunction.hpp"                 //导入激活函数类
#include "./Network/Soma.hpp"                               //导入细胞体Soma类
#include "./Network/Synapse.hpp"                            //导入突触类
#include "./Network/Axon.hpp"                               //导入轴突类
#include "./Network/Dendrite.hpp"                           //导入树突类
#include "./Network/Neuro.hpp"                              //导入Neuro类的声明
#include "./Network/Layer.hpp"                              //导入Layer类的声明
#include "./Network/Network.hpp"                            //导入Network类的声明
#include "./FileOperator/Container/NeuroContainer.hpp"      //导入NeuroContainer类的声明
#include "./FileOperator/Container/LayerContainer.hpp"      //导入LayerContainer类的声明
#include "./FileOperator/Container/SynapseContainer.hpp"    //导入SynapseContainer类的声明
#include "./FileOperator/Importer/Importer.hpp"             //导入Importer类的声明
#include "./FileOperator/Importer/ANNImporter.hpp"          //导入ANNImporter类的声明
#include "./FileOperator/Exporter/Exporter.hpp"             //导入Exporter类的声明
#include "./FileOperator/Exporter/ANNExporter.hpp"          //导入ANNExporter类的声明
#include "./View/View.hpp"                                  //导入用户界面
#include "./Controler/Controler.hpp"                        //导入Controler类的声明



int main() {
    Controler* pMyControler = Controler::GetInstance(); //初始化Controler类
    pMyControler->start();                              //调用Controler类的start函数即可使程序开始运行
    return 0;
}
