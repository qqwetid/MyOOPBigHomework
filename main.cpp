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
    Controler* pMyControler = Controler::GetInstance();
    pMyControler->start();
    /*
    View::Main();
    View::Branch3();
    View::Branch5();
    try
    {
        Controler* pMyControler = Controler::GetInstance();
        Network* pMyNetwork = pMyControler->ImportNetwork("../../Code/CPP/MyOOPBigHomework/ANNFiles/simple.ANN");
        if (pMyNetwork != nullptr)
        {
            pMyControler->ShowNetwork(*pMyNetwork);
            for (int i = 0; i < 6; i++) {
                pMyControler->ShowNeuro(*pMyNetwork, i);
            }
            pMyControler->ShowElementNumbers(*pMyNetwork);
            double MyInput[3] = {1, 1, 1};
            double MyOutput[3];
            pMyControler->Inference(*pMyNetwork, MyInput, 3, MyOutput, 3);
            std::cout << MyOutput[0] << ",," << MyOutput[1] << ",," << MyOutput[2] << std::endl;
        }
        delete pMyControler;
        delete pMyNetwork;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    */
    
    /*
    std::cout << "Hello World" << std::endl;
    ANNImporter MyFileImporter("../../Code/CPP/MyOOPBigHomework/ANNFiles/simple.ANN");
    std::vector<NeuroContainer> MyNeuroVector;
    std::vector<LayerContainer> MyLayerVector;
    std::set<SynapseContainer> MySynapseSet;
    char MyNetworkName[40];
    try
    {
        MyFileImporter.ReadFile(MyNeuroVector, MySynapseSet, MyLayerVector, MyNetworkName);
        
        std::vector<NeuroContainer>::iterator iter_Neuro = MyNeuroVector.begin();
        std::vector<LayerContainer>::iterator iter_Layer = MyLayerVector.begin();
        std::set<SynapseContainer>::iterator iter_Synapse = MySynapseSet.begin();
        std::cout << "Neuros:" << std::endl;
        while (iter_Neuro != MyNeuroVector.end()) {
            std::cout << iter_Neuro->ToString() << std::endl;
            iter_Neuro++;
        }
        std::cout << "Layers:" << std::endl;
        while (iter_Layer != MyLayerVector.end()) {
            std::cout << iter_Layer->ToString() << std::endl;
            iter_Layer++;
        }
        std::cout << "Synapses:" << std::endl;
        while (iter_Synapse != MySynapseSet.end()) {
            std::cout << iter_Synapse->ToString() << std::endl;
            iter_Synapse++;
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    ANNExporter MyFileExporter("../../Code/CPP/MyOOPBigHomework/ANNFiles/testANNExporter.ANN");
    MyFileExporter.OutputFile(MyNeuroVector, MySynapseSet, MyLayerVector, "MyFirstNetwork");
    
    std::cout << "====================================================================" << std::endl;
    Controler* MyControler = Controler::GetInstance();
    try
    {
        Network* MyNetwork = MyControler->ImportNetwork(MyNeuroVector, MySynapseSet, MyLayerVector, MyNetworkName);
        std::cout << MyNetwork->ToString_brief() << std::endl;
        delete MyControler;
        delete MyNetwork;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete MyControler;
    }
    */
    return 0;
}
