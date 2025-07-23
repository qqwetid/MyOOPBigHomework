//----------------------------------------------------------------------------------------------------------
//Network.hpp
//功能模块：Network类的成员函数；目的：定义Network类的成员函数
//开发者：Jason Cheng   日期：2025/7/21
//更改记录：
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>

#include "ActivationFunction.hpp"
#include "Soma.hpp"
#include "Synapse.hpp"
#include "Axon.hpp"
#include "Dendrite.hpp"
#include "Soma.hpp"
#include "Neuro.hpp"
#include "Layer.hpp"
#include "Network.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：Network（构造函数）
//函数功能：构造一个Network类对象，并构造第一层
//参数：const char* NetworkName, unsigned int NumOfNursInFstLyr
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

Network::Network(const char* NetworkName, unsigned int NumOfNursInFstLyr) {
    //先给神经网络名字
    if (strlen(NetworkName) >= 40)      //若NetworkName过长，则throw错误信息，并将名字赋成错误信息
    {
        throw std::invalid_argument("Error: Your Network Name is too long!\n\tFailed to set the name, please change another name with no longer than 40 characters.");
        strcpy_s(m_cNetworkName, 40, "Error: Failed to set the name.");
    }
    else
    {
    strcpy_s(m_cNetworkName, 40, NetworkName);
    }
    Layer FirstLayer;                                   //创建第一层
    for (int i = 0; i < NumOfNursInFstLyr; i++) {       //为第一层添加编号为0~NumOfNursInFstLyr-1，1个树突的神经元
        Neuro NeuroToInsert(0, 0, 1, i);                //为第一层的神经元开辟空间
        try
        {
            FirstLayer.InsertNeuro(NeuroToInsert);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Continue to the next Neuro." << std::endl;
        }
    }
    m_MyLayers.push_back(FirstLayer);   //将第一层添加到网络中
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= (赋值运算符重载)
//函数功能：将一个Network类对象中的内容复制到另一个类对象
//参数：const Network& Source
//返回值：Network&
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

Network& Network::operator=(const Network& Source) {
    //需要把每个神经元的树突连接的神经元进行重新连接
    if (this != &Source)    //避免不必要的拷贝
    {
        this->m_MyLayers = Source.m_MyLayers;               //将存储层的容器进行复制，但是需要手动将树突重新连接
        
        //以层为单位进行循环
        MyLayersType::iterator iter_Layer_forward = m_MyLayers.begin(); //前面的指针
        MyLayersType::iterator iter_layer_back = m_MyLayers.begin();    //后面的指针
        //神经网络至少需要有1层，因此不用担心没有层的情形
        iter_Layer_forward++;                                       //第一层不用重新连接
        while (iter_Layer_forward != m_MyLayers.end())              //以层为单位循环
        {
            if (iter_Layer_forward->GetNeuroNumber() == 0) //若这一层没有神经元，则跳过这一层
            {
                iter_layer_back = iter_Layer_forward;
                iter_Layer_forward++;
                continue;
            }

            //以神经元为单位循环，至少有一个神经元
            const MyNeurosType& NeurosInThisLayer = iter_Layer_forward->GetMyNeuros();
            MyNeurosType::const_iterator const_iter_Neuro = NeurosInThisLayer.begin();
            while (const_iter_Neuro != NeurosInThisLayer.end())
            {
                if ((const_iter_Neuro->second).MyDendrites.size() == 0) //如果这个神经元没有连树突，则跳过去
                {
                    const_iter_Neuro++;
                    continue;
                }
                
                //以树突为单位进行循环，给树突重新连接神经元
                //用ID查找当前const_iter_Neuro指向的神经元，进行修改
                try
                {
                    Neuro* pNeuroToSetDndrts = iter_Layer_forward->Query((const_iter_Neuro->second).NeuroID);  //当前神经元的指针
                    MyDndrtType& MyDndrtsInNeuro = pNeuroToSetDndrts->SetDendrites();       //获取当前神经元存储树突的容器（可修改）
                    MyDndrtType::iterator iter_Dndrts = MyDndrtsInNeuro.begin();
                    while (iter_Dndrts != MyDndrtsInNeuro.end())
                    {
                        if (iter_Dndrts->GetNeuro() == nullptr) {                           //若当前树突没有连接神经元，就换到下一个树突
                            iter_Dndrts++;
                            continue;
                        }

                        try                                                                 //查找对应的ID
                        {
                            unsigned int CnnctNeuroID = (iter_Dndrts->GetNeuro())->NeuroID; //获取当前树突连接的神经元ID
                            Neuro* pGetNewCnnctNeuro = iter_layer_back->Query(CnnctNeuroID);//根据ID查找上一层的神经元
                            iter_Dndrts->SetNeuro(*pGetNewCnnctNeuro);                      //连接查找到的神经元
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                            std::cout << "Continue to the next Dendrite." << std::endl;
                            iter_Dndrts++;
                            continue;
                        }
                        iter_Dndrts++;
                    }
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    std::cout << "Continue to the next Neuro." << std::endl;
                    const_iter_Neuro++;
                    continue;
                }
                const_iter_Neuro++;
            }
            iter_layer_back = iter_Layer_forward;
            iter_Layer_forward++;
        }
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Network (构造函数)
//函数功能：将一个Network类对象中的内容复制到另一个类对象
//参数：const Network& Source
//返回值：Network&
//开发者：Jason Cheng   日期：2025/7/22
//更改记录              完全拷贝自operator=，删除了一开始判断的部分
//----------------------------------------------------------------------------------------------------------

Network::Network(const Network& Source) {
    this->m_MyLayers = Source.m_MyLayers;               //将存储层的容器进行复制，但是需要手动将树突重新连接
    
    //以层为单位进行循环
    MyLayersType::iterator iter_Layer_forward = m_MyLayers.begin(); //前面的指针
    MyLayersType::iterator iter_layer_back = m_MyLayers.begin();    //后面的指针
    //神经网络至少需要有1层，因此不用担心没有层的情形
    iter_Layer_forward++;                                       //第一层不用重新连接
    while (iter_Layer_forward != m_MyLayers.end())              //以层为单位循环
    {
        if (iter_Layer_forward->GetNeuroNumber() == 0) //若这一层没有神经元，则跳过这一层
        {
            iter_layer_back = iter_Layer_forward;
            iter_Layer_forward++;
            continue;
        }
        //以神经元为单位循环，至少有一个神经元
        const MyNeurosType& NeurosInThisLayer = iter_Layer_forward->GetMyNeuros();
        MyNeurosType::const_iterator const_iter_Neuro = NeurosInThisLayer.begin();
        while (const_iter_Neuro != NeurosInThisLayer.end())
        {
            if ((const_iter_Neuro->second).MyDendrites.size() == 0) //如果这个神经元没有连树突，则跳过去
            {
                const_iter_Neuro++;
                continue;
            }
            
            //以树突为单位进行循环，给树突重新连接神经元
            //用ID查找当前const_iter_Neuro指向的神经元，进行修改
            try
            {
                Neuro* pNeuroToSetDndrts = iter_Layer_forward->Query((const_iter_Neuro->second).NeuroID);  //当前神经元的指针
                MyDndrtType& MyDndrtsInNeuro = pNeuroToSetDndrts->SetDendrites();       //获取当前神经元存储树突的容器（可修改）
                MyDndrtType::iterator iter_Dndrts = MyDndrtsInNeuro.begin();
                while (iter_Dndrts != MyDndrtsInNeuro.end())
                {
                    if (iter_Dndrts->GetNeuro() == nullptr) {                           //若当前树突没有连接神经元，就换到下一个树突
                        iter_Dndrts++;
                        continue;
                    }
                    try                                                                 //查找对应的ID
                    {
                        unsigned int CnnctNeuroID = (iter_Dndrts->GetNeuro())->NeuroID; //获取当前树突连接的神经元ID
                        Neuro* pGetNewCnnctNeuro = iter_layer_back->Query(CnnctNeuroID);//根据ID查找上一层的神经元
                        iter_Dndrts->SetNeuro(*pGetNewCnnctNeuro);                      //连接查找到的神经元
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        std::cout << "Continue to the next Dendrite." << std::endl;
                        iter_Dndrts++;
                        continue;
                    }
                    iter_Dndrts++;
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                std::cout << "Continue to the next Neuro." << std::endl;
                const_iter_Neuro++;
                continue;
            }
            const_iter_Neuro++;
        }
        iter_layer_back = iter_Layer_forward;
        iter_Layer_forward++;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~Network (析构函数)
//函数功能：析构神经网络
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

Network::~Network() {
    m_MyLayers.clear();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsFirstLyrValid
//函数功能：判断第一层是否合理，即每个神经元是否只有一个树突，是否都指向空指针
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Network::IsFirstLyrValid() const {
    const MyNeurosType& NeurosInMyFirstLayer = m_MyLayers.begin()->GetMyNeuros();   //第一层存储神经元的容器
    if (NeurosInMyFirstLayer.size() == 0)       //如果第一层中没有神经元，返回错误信息
    {
        throw std::invalid_argument("Error: There is no neuron in the first layer.");
    }
    MyNeurosType::const_iterator const_iter = NeurosInMyFirstLayer.begin();
    while (const_iter != NeurosInMyFirstLayer.end()) {
        if ((const_iter->second).MyDendrites.size() != 1)   //如果神经元树突的数量不为1，则返回错误信息
        {
            throw std::invalid_argument("Error: Number of dendrites does not equal to 1.");
        }
        if((const_iter->second).MyDendrites.begin()->GetNeuro() != nullptr) //如果树突数量为1，但是连接的不是空指针，则返回错误信息
        {
            throw std::invalid_argument("Error: The dendrite in a neuron of the first layer does not connect to nullptr.");
        }
        const_iter++;
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：IsValid
//函数功能：判断神经网络是否合理，包括：每个神经元是否都参与数据传递过程；是否有环状连接；
//参数：无
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Network::IsValid() const {
    IsFirstLyrValid();                                          //判断第一层是否合法，如果不合法会返回错误信息
    MyLayersType::const_iterator const_iter_layers = m_MyLayers.begin();
    const_iter_layers++;                                        //从第二层开始判断
    while (const_iter_layers != m_MyLayers.end()) {
        const MyNeurosType& NeurosInThisLayer = const_iter_layers->GetMyNeuros();   //本层存储神经元的容器
        if (NeurosInThisLayer.size() == 0)                      //如果本层没有神经元，则返回错误信息
        {
            std::ostringstream Stream;
            Stream << "Error: There is no Neuro in Layer " << (const_iter_layers - m_MyLayers.begin()) << "." << std::endl;
            throw std::invalid_argument(Stream.str());          //抛出错误信息
        }

        MyNeurosType::const_iterator const_iter_Neuros = NeurosInThisLayer.begin();
        while (const_iter_Neuros != NeurosInThisLayer.end()) {  //遍历层内的神经元查找错误
            bool HasDndrtCnnctCrrct = 0;                        //判断是否有合法的树突
            const MyDndrtType&  DndrtsInThisNeuro = (const_iter_Neuros->second).MyDendrites;
            MyDndrtType::const_iterator const_iter_Dndrts = DndrtsInThisNeuro.begin();
            while (const_iter_Dndrts != DndrtsInThisNeuro.end()) {  //遍历神经元内所有树突
                if (const_iter_Dndrts->GetNeuro() == nullptr)       //若这个树突指向空指针，则输出警告信息
                {
                    std::cout << "Warning: Neuro (ID: " << const_iter_Dndrts->GetNeuro()->NeuroID << ") in Layer "
                              << (const_iter_layers - m_MyLayers.begin()) << " has a Dendrite which doesn't connect with any Neuro." << std::endl;
                    const_iter_Dndrts++;
                    continue;
                }
                bool HasCrrctCnnctn = Layer::HasConnection(*(const_iter_layers-1), *const_iter_Dndrts); //判断这个树突跟上一个神经元有无连接
                if (HasCrrctCnnctn == 0)                            //如果没有合法连接，throw错误信息
                {
                    std::ostringstream Stream;
                    Stream << "Error: Neuro (ID: " << const_iter_Dndrts->GetNeuro()->NeuroID << ") in Layer ";
                    Stream << (const_iter_layers - m_MyLayers.begin()) << " has a Dendrite which doesn't connect with a correct Neuro.";
                    throw std::invalid_argument(Stream.str());
                }
                else                                                //若有合法连接，则将计数器设为1
                {
                    HasDndrtCnnctCrrct = true;
                }
                const_iter_Dndrts++;
            }
            if (HasDndrtCnnctCrrct == 0)                            //如果整个神经元树突没有连接，throw错误信息
            {
                std::ostringstream Stream;
                Stream << "Error: All Dendrites in Neuro (ID: " << const_iter_Dndrts->GetNeuro()->NeuroID << ") in Layer ";
                Stream << (const_iter_layers - m_MyLayers.begin()) << " connect with nullptr.";
                throw std::invalid_argument(Stream.str());
            }
            //如果没问题，说明这个神经元合法
            const_iter_Neuros++;
        }
        //如果没问题，说明这个层内的神经元都合法
        const_iter_layers++;
    }
    return true;
}


//----------------------------------------------------------------------------------------------------------
//函数名称：Inference   
//函数功能：    让神经网络执行推理
//参数：
/*          const double* DataInput,            输入参数，进行数据的导入
            unsigned int SizeOfDataVector,      输入参数，提供导入数据的大小
            double* SignalOutput,               输出参数，提供输出数组的接口
            unsigned int& SizeofSgnl            输出参数，提供期望输出数组大小
*/
//返回值：int （用于返回程序是否正确），返回0时函数正确
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

int Network::Inference(const double* DataInput, unsigned int SizeOfDataVector, double* SignalOutput, unsigned int& SizeofSgnl) {
    /*
    std::vector<double> TrueDataInput(m_MyLayers.begin()->GetNeuroNumber());    //创建向量存放输入的信息
    if (SizeOfDataVector > m_MyLayers.begin()->GetNeuroNumber())                //若输入的数据多于第一层神经元的数量，throw警告信息
    {
        try
        {
            std::ostringstream Stream;
            Stream << "WARNING: The number of your data point is **GREATER** than the number of your neurons." << std::endl;
            Stream << "\tYour DataVector will be cut to size " << m_MyLayers.begin()->GetNeuroNumber() << ".";
            throw std::invalid_argument(Stream.str());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Whether to continue?  (y/n)"  << std::endl;
            //然后用户执行判断程序，如果用户愿意继续，则程序继续
            char ToContinue;
            std::cin >> ToContinue;
            fflush(stdin);          //清空缓冲区
            switch (ToContinue)
            {
                case 'y':           //若用户继续
                    for (int i = 0; i < m_MyLayers.begin()->GetNeuroNumber(); i++) {        //将数据导入vector容器
                        TrueDataInput.push_back(DataInput[i]);
                    }
                    break;
                case 'n':
                    std::cout << "Inference break with return 1." << std::endl;
                    return 1;       //程序结束
                    break;
                default:
                    std::cout << "Error: You've input an invalid character!" << std::endl;
                    std::cout << "Inference break with return 1." << std::endl;
                    return 1;       //程序结束
                    break;
            }
        }
    }
    else if (SizeOfDataVector < m_MyLayers.begin()->GetNeuroNumber())           //若输入的数据少于第一层神经元的数量，throw警告信息
    {
        try
        {
            std::ostringstream Stream;
            Stream << "WARNING: The number of your data point is **LESS** than the number of your neurons." << std::endl;
            Stream << "\tThis program will fill in the missed data with 0.";
            throw std::invalid_argument(Stream.str());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Whether to continue?  (y/n)"  << std::endl;
            //然后用户执行判断程序，如果用户愿意继续，则程序继续
            char ToContinue;
            std::cin >> ToContinue;
            fflush(stdin);          //清空缓冲区
            switch (ToContinue)
            {
                case 'y':           //若用户继续
                    for (int i = 0; i < m_MyLayers.begin()->GetNeuroNumber(); i++) {        //将数据导入vector容器
                        if (i < SizeOfDataVector)
                        {
                            TrueDataInput.push_back(DataInput[i]);
                        }
                        else
                        {
                            TrueDataInput.push_back(0.0);
                        }
                    }
                    break;
                case 'n':
                    std::cout << "Inference break with return 1." << std::endl;
                    return 1;       //程序结束
                    break;
                default:
                    std::cout << "Error: You've input an invalid character!" << std::endl;
                    std::cout << "Inference break with return 1." << std::endl;
                    return 1;       //程序结束
                    break;
            }
        }

        
    }
    else        //对于输入的向量维数和第一层神经元数量相同的情形
    {
        for (int i = 0; i < SizeOfDataVector; i++) {
            TrueDataInput.push_back(DataInput[i]);
        }
    }
    */
    if (SizeOfDataVector != m_MyLayers.begin()->GetNeuroNumber()) {     //如果数组大小和第一层不匹配，则输出错误信息
        throw std::invalid_argument("Dimension of the input vector does not fit the number of neurons in the first layer.");
    }
    //待编写
}

int main() {
    Neuro n1, n2, n3, n4;
    Layer l1;
    l1.InsertNeuro(n1);
    l1.InsertNeuro(n2);
    l1.InsertNeuro(n3);
    l1.InsertNeuro(n4);
    Layer l2;
    l2 = l1;
    std::cout << "l1:" << std::endl;
    std::cout << l1.ToString() << std::endl;
    std::cout << "l2:" << std::endl;
    std::cout << l2.ToString() << std::endl;
    Network N1("Network1", 2);
    Network N2("Network2");
    N2 = N1;
    return 0;
}