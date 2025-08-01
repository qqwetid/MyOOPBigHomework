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
#include "../View/View.hpp"                                 //导入用户界面
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
//函数名称：start
//函数功能：开始程序
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::start() const{
    while (true) {
        try
        {
            View::StartView();
            char FilePath[100];
            InputFilePath(FilePath, 100);                       //导入文件
            Network* pMyNetwork = ImportNetwork(FilePath);      //导入神经网络
            MainInterface(pMyNetwork);                          //进入主界面
            break;
        }
        catch(int a)
        {
            if (a == -1) {
                std::cout << "Exit the programme" << std::endl;
            }
            break;
        }
        catch(double b)
        {
            std::cout << "Your Program has not started yet! Let's restart." << std::endl;
            continue;
        }
        
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
        catch(...)
        {
            std::cout << "Caught an unknown exception! " << std::endl;
            std::cout << "Your should restart." << std::endl;
            bool WhetherToContinue = IsToContinue();
            if (WhetherToContinue == true) {
                continue;                                    //返回初始界面
            }
            else {
                std::cout << "Exit the programme." << std::endl;
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：MainInterface
//函数功能：主界面
//参数：Network* pMyNetwork
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::MainInterface(Network* pMyNetwork) const {
    while (true)
    {
        try
        {
            View::Main();                                               //导入用户界面
            unsigned int choice;
            InputUint(choice);
            switch (choice) {
                case 1 : {
                    char FilePath[100];
                    InputFilePath(FilePath, 100);                       //导入文件
                    Network* pAnotherNetwork = ImportNetwork(FilePath);   //导入神经网络
                    delete pMyNetwork;
                    pMyNetwork = pAnotherNetwork;
                    //MainInterface(pMyNetwork);                        //进入主界面
                    break;
                }
                case 2 : {
                    char FilePath[100];
                    InputFilePath(FilePath, 100);                       //输入文件路径
                    if (pMyNetwork == nullptr) {                        //如果神经网络不见了
                        std::cout << "Error: Your network is missed!" << std::endl;
                        std::cout << "Your should restart." << std::endl;
                        bool WhetherToContinue = IsToContinue();
                        if (WhetherToContinue == true) {
                            throw std::invalid_argument("Error: You missed your network."); //返回初始界面
                        }
                        else {
                            throw int(-1);
                        }
                    }
                    else {                                              //如果神经网络还在
                        ExportNetwork(*pMyNetwork, FilePath);
                        //MainInterface(pMyNetwork);                      //返回主界面
                    }
                    break;
                }
                case 3 : {
                    Branch3Modify(pMyNetwork);
                    break;
                }
                case 4 : {
                    if (pMyNetwork == nullptr) {                        //如果神经网络不见了
                        std::cout << "Error: Your network is missed!" << std::endl;
                        std::cout << "Your should restart." << std::endl;
                        bool WhetherToContinue = IsToContinue();
                        if (WhetherToContinue == true) {
                            start();                                    //返回初始界面
                        }
                        else {
                            throw int(-1);
                        }
                    }
                    else {
                        ShowElementNumbers(*pMyNetwork);
                        //MainInterface(pMyNetwork);
                    }
                    break;
                }
                case 5 : {
                    Branch5Inference(pMyNetwork);
                    break;
                }
                case 0 : {
                    throw int(-1);
                    break;
                }
                default:
                    std::cout << "The number you've input is not 0~5." << std::endl;
                    std::cout << "You should try again." << std::endl;
                    bool WhetherToContinue = IsToContinue();
                    if (WhetherToContinue == true) {
                        MainInterface(pMyNetwork);
                    }
                    else {
                        throw int(-1);
                    }
                    break;
            }
        }
        catch(double b)
        {
            std::cout << "Back to main interface." << std::endl;
            continue;
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Branch3Modify
//函数功能：分支3的界面
//参数：Network* pMyNetwork
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::Branch3Modify(Network* pMyNetwork) const {
    while (true)
    {
        if (pMyNetwork == nullptr) {                        //如果神经网络不见了
            std::cout << "Error: Your network is missed!" << std::endl;
            std::cout << "Your should restart." << std::endl;
            bool WhetherToContinue = IsToContinue();
            if (WhetherToContinue == true) {
                start();                                    //返回初始界面
            }
            else {
                throw int(-1);
            }
        }
        try
        {
            View::Branch3();                                //导入用户界面
            unsigned int choice;
            InputUint(choice);
            switch (choice) {
                case 1 : {
                    ShowNetwork(*pMyNetwork);
                    break;
                }
                case 2 : {
                    std::cout << "Input ID of the layer which is to be deleted:" << std::endl;
                    unsigned int LayerID;
                    InputUint(LayerID);
                    DeleteLayer(*pMyNetwork, LayerID);
                    break;
                }
                case 3 : {
                    std::cout << "Input position of your layer which is to be inserted:" << std::endl;
                    unsigned int LayerID;
                    InputUint(LayerID);
                    InsertLayer(*pMyNetwork, LayerID);
                    break;
                }
                case 4 : {
                    std::cout << "Input The layerID where you want to insert your neuron:" << std::endl;
                    unsigned int LayerID;
                    InputUint(LayerID);
                    std::cout << "Input your Bias:" << std::endl;
                    double Bias;
                    InputDouble(Bias);
                    std::cout << "Input your Activation Function: " << std::endl;
                    unsigned int ActvtnFnctn;
                    InputUint(ActvtnFnctn);
                    std::cout << "Input ID of your neuron:" << std::endl;
                    unsigned int NeuroID;
                    InputUint(NeuroID);
                    InsertNeuro(*pMyNetwork, LayerID, Bias, ActvtnFnctn, NeuroID);
                    break;
                }
                case 5 : {
                    std::cout << "Input position of your layer which you want to show:" << std::endl;
                    unsigned int LayerID;
                    InputUint(LayerID);
                    ShowLayer(*pMyNetwork, LayerID);
                    break;
                }
                case 6 : {
                    std::cout << "Input ID of your neuron:" << std::endl;
                    unsigned int NeuroID;
                    InputUint(NeuroID);
                    std::cout << "Input bias you want to set:" << std::endl;
                    double Bias;
                    InputDouble(Bias);
                    SetBias(*pMyNetwork, NeuroID, Bias);
                    break;
                }
                case 7 : {
                    std::cout << "Input ID of your neuron:" << std::endl;
                    unsigned int NeuroID;
                    InputUint(NeuroID);
                    ShowNeuro(*pMyNetwork, NeuroID);
                    break;
                }
                case 8 : {
                    std::cout << "Input ID of the neuron to delete:" << std::endl;
                    unsigned int NeuroID;
                    InputUint(NeuroID);
                    DeleteNeuro(*pMyNetwork, NeuroID);
                    break;
                }
                case 9 : {
                    std::cout << "Input ID of your first neuro:" << std::endl;
                    unsigned int FirstNeuroID;
                    InputUint(FirstNeuroID);
                    std::cout << "Input ID of your second neuro:" << std::endl;
                    unsigned int SecondNeuroID;
                    InputUint(SecondNeuroID);
                    std::cout << "Input the weight of your dendrite:" << std::endl;
                    double Weight;
                    InputDouble(Weight);
                    CnnctNeuro(*pMyNetwork, FirstNeuroID, SecondNeuroID, Weight);
                    break;
                }
                case 0 : {
                    throw double(1.0);
                    break;
                }
                default : {
                    std::cout << "The number you've input is not 0~9." << std::endl;
                    std::cout << "You should try again." << std::endl;
                    bool WhetherToContinue = IsToContinue();
                    if (WhetherToContinue == true) {
                        throw char('3');
                    }
                    else {
                        throw double(1.0);
                    }
                    break;
                }
            }
        }
        catch(char c)
        {
            std::cout << std::endl;
            std::cout << "Branch 3" << std::endl;
            std::cout << std::endl;
            continue;
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Branch5Inference
//函数功能：分支5的界面
//参数：Network* pMyNetwork
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::Branch5Inference(Network* pMyNetwork) const {
    while (true) {
        if (pMyNetwork == nullptr) {                        //如果神经网络不见了
            std::cout << "Error: Your network is missed!" << std::endl;
            std::cout << "Your should restart." << std::endl;
            bool WhetherToContinue = IsToContinue();
            if (WhetherToContinue == true) {
                start();                                    //返回初始界面
            }
            else {
                throw int(-1);
            }
        }
        try
        {
            View::Branch5();                                //导入用户界面
            unsigned int choice;
            InputUint(choice);
            switch (choice) {
                case 1 : {
                    IsValid(*pMyNetwork);
                    std::cout << "Your network is valid!" << std::endl;
                    break;
                }
                case 2 : {
                    unsigned int NeuroNumInFstLyr  = pMyNetwork->GetNmbrOfNursInFstLyr();
                    unsigned int NeuroNumInLstLyr = pMyNetwork->MyLayers.back().GetNeuroNumber();
                    std::cout << "Please input " << NeuroNumInFstLyr << " double precision floating point numbers "
                              << "as your input into your network:" << std::endl;
                    double* Myinput = new double[NeuroNumInFstLyr];
                    for (int i = 0; i < NeuroNumInFstLyr; i++) {
                        if (i == 0) {
                            std::cout << ">>> The 1st number: ";
                        }
                        else if (i == 1) {
                            std::cout << ">>> The 2nd number: ";
                        }
                        else {
                            std::cout << ">>> The " << i+1 << "th number: ";
                        }
                        InputDouble(*(Myinput + i));
                    }
                    double* Myoutput = new double[NeuroNumInLstLyr];
                    std::cout << std::endl;
                    std::cout << "Doing inference..." << std::endl;
                    std::cout << std::endl;
                    Inference(*pMyNetwork, Myinput, NeuroNumInFstLyr, Myoutput, NeuroNumInLstLyr);
                    std::cout << "The result of inference:" << std::endl;
                    std::cout << "[";
                    for (int i = 0; i < NeuroNumInLstLyr; i++) {
                        if (i != 0 && i % 10 == 0) {                //从第二行开始，第一个元素前加一个空格（对齐）
                            std::cout << " " << std::endl;
                        }
                        std::cout << *(Myoutput + i);
                        if (i != NeuroNumInLstLyr - 1) {            //如果不是最后一个元素，则加上逗号
                            std::cout << ",\t";
                            if (i % 10 == 9) {
                                std::cout << std::endl;             //如果i mod 10 余 9，则换行（10个一换）
                            }
                        }
                    }
                    std::cout << "]" << std::endl;
                    delete[] Myinput;
                    delete[] Myoutput;
                    break;
                }
                case 0 : {
                    throw double(1.0);
                    break;
                }
                default: {
                    std::cout << "The number you've input is not 0~2." << std::endl;
                    std::cout << "You should try again." << std::endl;
                    bool WhetherToContinue = IsToContinue();
                    if (WhetherToContinue == true) {
                        throw char('5');
                    }
                    else {
                        throw double(1.0);
                    }
                    break;
                }
            }
        }
        catch(char c)
        {
            std::cout << std::endl;
            std::cout << "Branch 5" << std::endl;
            std::cout << std::endl;
            continue;
        }
        
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InputInt
//函数功能：输入整数
//参数：    int& Myint      输出参数
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InputInt(int& Myint) const {
    int intInput;
    while (true) {
        std::cout << ">>> Enter an integer: ";
        if (std::cin >> intInput) {
            break;  // 输入成功
        }
        std::cin.clear();  // 清除错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
        std::cout << "Invalid input! Try again.\n";
    }
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
    Myint = intInput;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InputUint
//函数功能：输入无符号整数
//参数：    unsigned int& Myint      输出参数
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InputUint(unsigned int& MyUint) const {
    unsigned int value;
    while (true) {
        std::cout << ">>> Enter an unsigned integer: ";
        if (std::cin >> value) {
            break;  // 输入成功
        }
        std::cin.clear();  // 清除错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
        std::cout << "Invalid input! Try again.\n";
    }
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
    MyUint = value;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Inputdouble
//函数功能：输入双精度浮点数
//参数：    double& Mydouble      输出参数
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InputDouble(double& Mydouble) const {
    double value;
    while (true) {
        std::cout << ">>> Enter a double precision floating point: ";
        if (std::cin >> value) {
            break;  // 输入成功
        }
        std::cin.clear();  // 清除错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
        std::cout << "Invalid input! Try again.\n";
    }
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
    Mydouble = value;
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
    while (true) {
        try
        {
            /*
            std::cin.clear();                                   // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
            */
            std::cout << ">>> Please input the path of your file (e.g. ./ANNFiles/simple.ANN):" << std::endl;
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
            break;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            bool WhetherContinue = IsToContinue();
            if (WhetherContinue == true) {
                continue;
            }
            else {
                std::cout << "We will be back to main interface. Press 'y' to continue, and press 'n' to exit the programme." << std::endl;
                bool WhetherNoExit = IsToContinue();
                if (WhetherNoExit == true) {
                    throw double(1.0);
                }
                else {
                    throw int(-1);              //如果不继续，则throw-1以退出程序
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsToContinue
//函数功能：判断是否继续
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Controler::IsToContinue() const {
    while (true) {
    std::cout << ">>> Whether to continue?[y/n]:";
    char YN;
    std::cin.get(YN);
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 丢弃无效输入
        switch (YN) {
            case 'Y' :              //Y和y则程序继续
            case 'y' :
                return true;
                break;
            case 'N' :
            case 'n' :
                return false;
                break;
            default :
                break;
        }
        std::cout << "Invalid input! Try again.\n";
    }
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
    //std::vector<Neuro> MyNeuros(MyNeuroVector.size());
    std::vector<Neuro> MyNeuros;
    MyNeuros.reserve(MyNeuroVector.size());
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
            ThisLayer.InsertNeuro(MyNeuros.at(i));     //将神经元插入到层中
        }
        pMyNetwork->InsertLayer(ThisLayer);
        const_iter_LyrVctr++;
    }
    /*test*/
    //unsigned int test = pMyNetwork->QueryNeuro(3)->MyDendrites.size();
    //将树突插入神经网络
    std::set<SynapseContainer>::const_iterator const_iter_SynpsSet = MySynapseSet.begin();
    while (const_iter_SynpsSet != MySynapseSet.end()) {         //对突触的容器循环，将突触插入到神经网络
        pMyNetwork->CnnctNursByDndrt(const_iter_SynpsSet->CnnctNeuro, const_iter_SynpsSet->LyingNeuro, const_iter_SynpsSet->Weight);
        const_iter_SynpsSet++;
    }
    //test = pMyNetwork->QueryNeuro(3)->MyDendrites.size();
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
    while (true) {
        try
        {
            ANNImporter ImportANNFile(FilePath);
            std::vector<NeuroContainer> MyNeuroVector;
            std::set<SynapseContainer>  MySynapseSet;
            std::vector<LayerContainer> MyLayerVector;
            char NetworkName[40];
            ImportANNFile.ReadFile(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
            Network* pMyNetwork = ImportNetwork(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
            return pMyNetwork;
            break;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            bool WhetherContinue = IsToContinue();
            if (WhetherContinue == true) {
                continue;
            }
            else {
                std::cout << "We will be back to main interface. Press 'y' to continue, and press 'n' to exit the programme." << std::endl;
                bool WhetherNoExit = IsToContinue();
                if (WhetherNoExit == true) {
                    throw double(1.0);
                }
                else {
                    throw int(-1);              //如果不继续，则throw-1以退出程序
                }
            }
        }
        
    }
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
    while (true) {
        try
        {
            std::vector<NeuroContainer> MyNeuroVector;
            std::set<SynapseContainer>  MySynapseSet;
            std::vector<LayerContainer> MyLayerVector;
            char NetworkName[40];
            //将网络导出到容器
            ExportNetwork(SourceNetwork, MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
            //将容器导出到文件
            ANNExporter OutFile(FilePath);
            OutFile.OutputFile(MyNeuroVector, MySynapseSet, MyLayerVector, NetworkName);
            break;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            bool WhetherContinue = IsToContinue();
            if (WhetherContinue == true) {
                continue;
            }
            else {
                std::cout << "We will be back to main interface. Press 'y' to continue, and press 'n' to exit the programme." << std::endl;
                bool WhetherNoExit = IsToContinue();
                if (WhetherNoExit == true) {
                    throw double(1.0);
                }
                else {
                    throw int(-1);              //如果不继续，则throw-1以退出程序
                }
            }
        }
        
    }
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
    try
    {
        std::cout << std::endl;
        std::cout << SourceNetwork.ToString_brief() << std::endl;
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteLayer
//函数功能：删除指定Layer 对象，同时删除此Layer 内部神经元及其关联的层间突触连接
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int LayerNumber        输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/30
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::DeleteLayer(Network& SourceNetwork, unsigned int LayerNumber) const {
    try
    {
        SourceNetwork.DeleteLayer(LayerNumber);
        std::cout << std::endl;
        std::cout << "Your layer is already deleted!" << std::endl;
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertLayer
//函数功能：添加⼀个Layer 对象，添加后内部没有Neuron 对象。
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int LayerNumber        输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InsertLayer(Network& SourceNetwork, unsigned int LayerNumber) const {
    try
    {
        Layer MyLayer;
        SourceNetwork.InsertLayer(MyLayer, LayerNumber);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ShowLayer
//函数功能：列出指定Layer 对象中的所有Neuron 对象，显示其序号和偏置
//参数：
/*
    *   const Layer& SourceLayer            输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ShowLayer(const Layer& SourceLayer) const {
    try
    {
        std::cout << std::endl;
        std::cout << SourceLayer.ToString_brief() << std::endl;
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ShowLayer
//函数功能：列出指定Layer 对象中的所有Neuron 对象，显示其序号和偏置
//参数：
/*
    *   const Network& SourceNetwork    输入参数
    *   unsigned int LayerNumber        输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ShowLayer(const Network& SourceNetwork, unsigned int LayerNumber) const {
    std::cout << std::endl;
    std::cout << "Layer NO." << LayerNumber << " :" << std::endl;
    std::cout << std::endl;
    const Layer& ThisLayer = SourceNetwork.MyLayers.at(LayerNumber);
    std::cout << ThisLayer.ToString_brief() << std::endl;
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertNeuro
//函数功能：为一层添加一个神经元
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int LayerNumber        输入参数
    *   double BiasSet                  输入参数
    *   unsigned int ActvtnFnctnSet     输入参数
    *   unsigned int NeuroIDSet         输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InsertNeuro(Network& SourceNetwork, unsigned int LayerNumber, double BiasSet, unsigned int ActvtnFnctnSet, unsigned int NeuroIDSet) const {
    try
    {
        if (SourceNetwork.QueryNeuro(NeuroIDSet) != nullptr) {  //如果原来神经网络中没有相同编号的神经元，则进行操作
            throw std::invalid_argument("Error: There is already a Neuro with the same ID.\n\tPlease change the NeuroID and try again.");
            exit(1);
        }
        else {
            Layer* pThisLayer = SourceNetwork.QueryLayer(LayerNumber);
            if (pThisLayer == nullptr) {
                throw std::invalid_argument("Error: Cannot find such Layer.\n\tPlease check your LayerNumber.");
                exit(1);
            }
            Neuro MyNeuro(BiasSet, ActvtnFnctnSet, 100, NeuroIDSet);
            pThisLayer->InsertNeuro(MyNeuro);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertNeuro
//函数功能：为一层添加一个神经元
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int LayerNumber        输入参数
    *   const Neuro& SourceNeuro        输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::InsertNeuro(Network& SourceNetwork, unsigned int LayerNumber, const Neuro& SourceNeuro) const {
    InsertNeuro(SourceNetwork, LayerNumber, SourceNeuro.MySoma.GetBias(), SourceNeuro.MySoma.GetActvtnFunc(), SourceNeuro.NeuroID);
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetBias
//函数功能：修改指定Neuron 对象包含的偏置。
//参数：
/*
    *   Neuro& SourceNeuro              输出参数
    *   double BiasSet                  输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::SetBias(Neuro& SourceNeuro, double BiasSet) const {
    try
    {
        SourceNeuro.SetSoma().SetBias(BiasSet);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetBias
//函数功能：修改指定Neuron 对象包含的偏置。
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int NeuroID            输入参数
    *   double BiasSet                  输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::SetBias(Network& SourceNetwork, unsigned int NeuroID, double BiasSet) const {
    Neuro* pMyNeuro = SourceNetwork.QueryNeuro(NeuroID);
    if (pMyNeuro == nullptr) {
        throw std::invalid_argument("Error: Cannot find the Neuro.\n\tPlease check your NeuroID");
        exit(1);
    }
    else {
        SetBias(*pMyNeuro, BiasSet);
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ShowNeuro
//函数功能：列出指定Neuron对象的突触连接关系信息。
//参数：
/*
    *   const Network& SourceNetwork    输出参数
    *   unsigned int NeuroID            输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ShowNeuro(const Network& SourceNetwork, unsigned int NeuroID) const {
    try
    {
        const Neuro* pThisNeuro = SourceNetwork.QueryNeuro_noset(NeuroID);
        if (pThisNeuro == nullptr) {
            std::ostringstream Stream;
            Stream << "Error: There is no neuro with id " << NeuroID << ".";
            throw std::invalid_argument(Stream.str());
        }
        std::cout << std::endl;
        std::cout << "----------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "  **Neuro**" << std::endl;
        std::cout << "  NeuroID: No." << NeuroID << " ." << std::endl;
        std::cout << std::endl;
        std::cout << "  Synapse from this neuron connect with:\n  ";
        MyDndrtType::const_iterator const_iter_Dndrts = pThisNeuro->MyDendrites.begin();
        while (const_iter_Dndrts != pThisNeuro->MyDendrites.end()) {
            if (const_iter_Dndrts->GetNeuro() != nullptr) { //如果另一端有神经元，则输出神经元编号
                std::cout << "No." << const_iter_Dndrts->GetNeuro()->NeuroID 
                          << ", weight: " << const_iter_Dndrts->GetWeight() << "; ";
            }
            else {                                          //如果另一端没有神经元，则输出-1
                std::cout << "-1(Dendrite), weight: " << const_iter_Dndrts->GetWeight() << "; ";
            }
            const_iter_Dndrts++;
        }
        /*判断神经元是否在最后一层，如果在，需要输出轴突*/
        const Layer& MyLastLayer = SourceNetwork.MyLayers.back();
        const Neuro* pTestNeuro = MyLastLayer.Query_noset(NeuroID);
        if (pTestNeuro != nullptr) {
            std::cout << "-1(Axon), weight: 1.0; ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "  Synapse connect with this neuron is located at:\n  ";
        for (const Layer& ThisLayer : SourceNetwork.MyLayers) {             //对层循环
            for (auto& ThisNeuroPair : ThisLayer.GetMyNeuros()) {           //对神经元循环
                const Neuro& ThisNeuro = ThisNeuroPair.second;
                for (auto& ThisDendrite : ThisNeuro.MyDendrites) {          //对树突循环
                    if (ThisDendrite.GetNeuro() != nullptr) {
                        if (ThisDendrite.GetNeuro()->NeuroID == NeuroID) {
                            std::cout << "No." << ThisNeuro.NeuroID << ", weight: " << ThisDendrite.GetWeight() << "; ";
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
        std::cout << "----------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteNeuro
//函数功能：删除指定Neuron 对象，同时删除关联的Synapse对象
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int NeuroID            输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::DeleteNeuro(Network& SourceNetwork, unsigned int NeuroID) const {
    try
    {
        /*先删除连接它的树突*/
        for (auto& ThisLayer : SourceNetwork.MyLayers) {
            for (auto& ThisNeuroPair : ThisLayer.GetMyNeuros()) {
                Neuro* pThisNeuro = SourceNetwork.QueryNeuro(ThisNeuroPair.first);
                pThisNeuro->DeleteDendrite(NeuroID);
                /*
                MyDndrtType::iterator iter_Dndrts = pThisNeuro->SetDendrites().begin();
                while (iter_Dndrts != pThisNeuro->SetDendrites().end()) {
                    if (iter_Dndrts->GetNeuro() != nullptr) {
                        if (iter_Dndrts->GetNeuro()->NeuroID == NeuroID) {
                            unsigned int iterPlace = iter_Dndrts - pThisNeuro->SetDendrites().begin();
                            pThisNeuro->DeleteDendrite(NeuroID);
                        }
                    }
                    iter_Dndrts++;
                }
                    */
            }
        }

        /*再删除它*/
        MyLayersType::const_iterator const_iter_Layers = SourceNetwork.MyLayers.begin();
        while (const_iter_Layers != SourceNetwork.MyLayers.end()) {
            const Layer& ThisLayer = *const_iter_Layers;
            if (ThisLayer.Query_noset(NeuroID) != nullptr) {    //如果找到了这个神经元
                Layer* pThisLayer = SourceNetwork.QueryLayer(const_iter_Layers - SourceNetwork.MyLayers.begin());
                pThisLayer->DeleteNeuro(NeuroID);
                break;
            }
            const_iter_Layers++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：CnnctNeuro
//函数功能：连接指定的Neuron 对象。要求连接相邻层，且没有突触连接的neuron对象
//参数：
/*
    *   Network& SourceNetwork          输出参数
    *   unsigned int FirstNeuroID       输入参数
    *   unsigned int SecondNeuroID      输入参数
    *   double WeightSet                输入参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::CnnctNeuro(Network& SourceNetwork, unsigned int FirstNeuroID, unsigned int SecondNeuroID, double WeightSet) const {
    if (SourceNetwork.QueryNeuro(FirstNeuroID) == nullptr) {
        throw std::invalid_argument("Error: Cannot find your first neuron.\n\tPlease check your neuron id.");
    }
    if (SourceNetwork.QueryNeuro(FirstNeuroID) == nullptr) {
        throw std::invalid_argument("Error: Cannot find your second neuron.\n\tPlease check your neuron id.");
    }
    int FirstLayer = -1;
    int SecondLayer = -1;
    MyLayersType::const_iterator const_iter_Layers = SourceNetwork.MyLayers.begin();
    while (const_iter_Layers != SourceNetwork.MyLayers.end()) {
        if (const_iter_Layers->Query_noset(FirstNeuroID) != nullptr) {
            FirstLayer = const_iter_Layers - SourceNetwork.MyLayers.begin();
        }
        if (const_iter_Layers->Query_noset(SecondNeuroID) != nullptr) {
            SecondLayer = const_iter_Layers - SourceNetwork.MyLayers.begin();
        }
        const_iter_Layers++;
    }
    if (FirstLayer != -1 && SecondLayer != -1) {
        if (SecondLayer - FirstLayer != 1) {
            throw std::invalid_argument("Error: Cannot connect two neurons because they are not in neighboring layers.");
        }
        else {
            SourceNetwork.CnnctNursByDndrt(FirstNeuroID, SecondNeuroID, WeightSet);
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ShowElementNumbers
//函数功能：显示统计信息
//参数：
/*
    *   const Network& SourceNetwork          输出参数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::ShowElementNumbers(const Network& SourceNetwork) const {
    try
    {
        std::cout << "**Network**" << std::endl;
        std::cout << "NetworkName: " << SourceNetwork.NetworkName << std::endl;
        std::cout << std::endl;
        std::cout << "Number of Layers: \t" << SourceNetwork.GetNumberOfLayers() << std::endl;
        std::cout << std::endl;
        std::cout << "Number of Neurons: \t" << SourceNetwork.GetNumberOfNeuros() << std::endl;
        std::cout << std::endl;
        std::cout << "Number of Synapses: \t" << SourceNetwork.GetNumberOfSynapses() << std::endl;
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "We will be back to main interface." << std::endl;
        throw double(1.0);
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：验证Network合理性
//参数：
/*
    *   const Network& SourceNetwork          输出参数
*/
//返回值：bool
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Controler::IsValid(const Network& SourceNetwork) const {
    try
    {
        bool WillBeValid = SourceNetwork.IsValid();
        return WillBeValid;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Inference
//函数功能：执行推理
//参数：
/*
    *   Network& SourceNetwork              输出参数
    *   const double* DataInput,            输入参数，进行数据的导入
    *   unsigned int SizeOfDataVector,      输入参数，提供导入数据的大小
    *   double* SignalOutput,               输出参数，提供输出数组的接口
    *   unsigned int SizeToReserve          输入参数，提供期望输出数组大小
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/8/1
//更改记录
//----------------------------------------------------------------------------------------------------------

void Controler::Inference(Network& SourceNetwork, const double* DataInput, unsigned int SizeOfDataVector, double* SignalOutput, unsigned int SizeToReserve) const {
    try
    {
        SourceNetwork.Inference(DataInput, SizeOfDataVector, SignalOutput, SizeToReserve);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}