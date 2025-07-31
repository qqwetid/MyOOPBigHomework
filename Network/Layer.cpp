//----------------------------------------------------------------------------------------------------------
//Layer.cpp
//功能模块：Layer类的成员函数；目的：定义类的成员函数
//开发者：Jason Cheng   日期：2025/7/120
//更改记录：2025/7/23 增加带有参数的ForwardPropagation和输出当前信号的LayerSignalNow
//----------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>

#include "ActivationFunction.hpp"
#include "Synapse.hpp"
#include "Dendrite.hpp"
#include "Axon.hpp"
#include "Soma.hpp"
#include "Neuro.hpp"
#include "Layer.hpp"

//----------------------------------------------------------------------------------------------------------
//函数名称：Layer（构造函数）
//函数功能：构造一个空的Layer类
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/20
//更改记录
//----------------------------------------------------------------------------------------------------------

Layer::Layer() {
    //空函数体，无需构造
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator= 赋值运算符重载
//函数功能：用=实现赋值
//参数：const Layer& Source
//返回值：Layer&
//开发者：Jason Cheng   日期：2025/7/20
//更改记录
//----------------------------------------------------------------------------------------------------------

Layer& Layer::operator=(const Layer& Source) {
    if (this != &Source)    //判断Source和this是否是同一个对象，避免不必要的运算
    {
        this->m_MyNeuros = Source.m_MyNeuros;
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Layer （拷贝构造函数）
//函数功能：拷贝构造
//参数：const Layer& Source
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

Layer::Layer(const Layer& Source) {
    m_MyNeuros = Source.m_MyNeuros;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~Layer （析构函数）
//函数功能：析构Layer中的神经元
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

Layer::~Layer() {
    m_MyNeuros.clear();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ForwardPropagation
//函数功能：以层为单位进行前向传播
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::ForwardPropagation() {
    if (m_MyNeuros.size() == 0)         //若层内没有神经元，throw错误信息
    {
        throw std::invalid_argument("Error: There is no Neuro in this Layer!\n\tFailed to do the forward propagation!");
    }
    else                                //若层内有神经元，则进行传播
    {
        MyNeurosType::iterator iter = m_MyNeuros.begin();
        for (; iter != m_MyNeuros.end(); iter++)
        {
            (iter->second).Signal();    //对每个神经元分别计算传播
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ForwardPropagation
//函数功能：接受一个信号数组，数组个数需与层内神经元数量相同。经过每个神经元第一个树突运算后，以层为单位进行前向传播
//参数：const double* InputVector, unsigned int DimOfInput, 均为输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/23
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::ForwardPropagation(const double* InputVector, unsigned int DimOfInput) {
    if (GetNeuroNumber() == 0) {            //若这一层没有神经元，throw错误信息
        throw std::invalid_argument("Error: No Neuro in this Layer!");
    }
    if (GetNeuroNumber() != DimOfInput) {   //若维数不匹配，throw错误信息
        throw std::invalid_argument("Error: Dimension of your input vector does not fit the number of neurons in this Layer.");
    }
    MyNeurosType::iterator iter_Neuros = m_MyNeuros.begin();//遍历所有神经元
    int i = 0;
    while (iter_Neuros != m_MyNeuros.end()) {
        (iter_Neuros->second).Signal(*(InputVector + i));   //在每个神经元内分别传播
        i++;
        iter_Neuros++;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：LayerSignalNow
//函数功能：输出当前信号
//参数：
/*      double* OutputVector            输出参数，接收当前信号
        unsigned int DimToReserve       输入参数，表示接收的信号个数
*/
//返回值：无
//开发者：Jason Cheng   日期：2025/7/23
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::LayerSignalNow(double* OutputVector, unsigned int DimToReserve) const {
    if (DimToReserve > m_MyNeuros.size()) { //如果向量的维数比神经元数量多，输出警告
        std::cout << "Warning: There are only " << m_MyNeuros.size() 
                  << " Neuros, and dimension of your vector is " << DimToReserve << "." << std::endl;
    }
    else if (DimToReserve < m_MyNeuros.size()) {    //如果向量维数比神经元数量少，输出警告
        std::cout << "Warning: There are " << m_MyNeuros.size() << " Neuros, but dimension of your vecotr is not enough." << std::endl;
        std::cout << "Signal of the output will be cut off." << std::endl;
    }
    MyNeurosType::const_iterator const_iter_Neuros = m_MyNeuros.begin();
    int i = 0;
    while (i < DimToReserve) {
        if(const_iter_Neuros != m_MyNeuros.end())   //当神经元还没用完时，用神经元赋值
        {
            *(OutputVector + i) = (const_iter_Neuros->second).SignalNow;
            const_iter_Neuros++;
        }
        else
        {
            *(OutputVector + i) = 0;
        }
        i++;
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetMyNeuros
//函数功能：获取存储神经元的容器，不可修改
//参数：无
//返回值：const MyNeurosType&
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

const MyNeurosType& Layer::GetMyNeuros() const {
    return m_MyNeuros;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetNeuroNumber
//函数功能：获取存储神经元的个数
//参数：无
//返回值：unsigned int
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

unsigned int Layer::GetNeuroNumber() const {
    return m_MyNeuros.size();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Query
//函数功能：根据编号查找神经元
//参数：unsigned int ID_input
//返回值：Neuro*
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

Neuro* Layer::Query(unsigned int ID_input) {
    if(m_MyNeuros.size() == 0)                                  //如果这一层没有神经元，返回错误信息
    {
        return nullptr;
    }
    else
    {
        MyNeurosType::iterator iter = m_MyNeuros.find(ID_input);    //查找序号为ID_input的神经元
        if (iter == m_MyNeuros.end())                               //若没找到，则返回空指针
        {
            return nullptr;
        }
        else                                                        //若找到，则返回神经元对应的指针
        {
            return &(iter->second);
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Query_noset
//函数功能：根据编号查找神经元（不可修改）
//参数：unsigned int ID_input
//返回值：const Neuro*
//开发者：Jason Cheng   日期：2025/7/31
//更改记录
//----------------------------------------------------------------------------------------------------------

const Neuro* Layer::Query_noset(unsigned int ID_input) const {
    if(m_MyNeuros.size() == 0)                                  //如果这一层没有神经元，返回错误信息
    {
        return nullptr;
    }
    else
    {
        MyNeurosType::const_iterator const_iter = m_MyNeuros.find(ID_input);    //查找序号为ID_input的神经元
        if (const_iter == m_MyNeuros.end())                               //若没找到，则返回空指针
        {
            return nullptr;
        }
        else                                                        //若找到，则返回神经元对应的指针
        {
            return &(const_iter->second);
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：HasConnection       静态成员函数
//函数功能：判断一个树突是否在一层中有连接
//参数：const Layer& LayerToCheck, const Dendrite& DndrtToCheck
//返回值：bool
//开发者：Jason Cheng   日期：2025/7/22
//更改记录
//----------------------------------------------------------------------------------------------------------

bool Layer::HasConnection(const Layer& LayerToCheck, const Dendrite& DndrtToCheck) {
    if (LayerToCheck.GetNeuroNumber() == 0)     //如果层中没有神经元，throw错误信息
    {
        throw std::invalid_argument("Error: There is no Neuro in this Layer.");
    }
    if (DndrtToCheck.GetNeuro() == nullptr)     //如果该树突指向空指针，throw错误信息
    {
        throw std::invalid_argument("Error: This Dendrite doesn't connect with any Neuro.");
    }
    MyNeurosType::const_iterator const_iter_Neuros = LayerToCheck.GetMyNeuros().begin();
    while (const_iter_Neuros != LayerToCheck.GetMyNeuros().end()) {
        if(&(const_iter_Neuros->second) == DndrtToCheck.GetNeuro()) //如果找到了连接的神经元，返回true
        {
            return true;
        }
        const_iter_Neuros++;
    }
    return false;                               //如果没有找到连接的神经元，则返回 false
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertNeuro
//函数功能：插入一个神经元
//参数：Neuro& Neuro_set
//返回值：void
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::InsertNeuro(Neuro& Neuro_set) {
    std::pair result = m_MyNeuros.insert(std::make_pair(Neuro_set.NeuroID, Neuro_set));
    if (result.second == 1)     //如果插入成功，返回插入成功的信息
    {
        std::cout << "A neuro (ID = " << Neuro_set.NeuroID <<") is successfully inserted." << std::endl;
    }
    else                        //若插入失败，则返回错误信息
    {
        throw std::invalid_argument("Error: There is already another Neuro with the same ID.\n\tFail to insert the Neuro.");
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteNeuro
//函数功能：删除一个神经元
//参数：unsigned int IDToDelete
//返回值：void
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::DeleteNeuro(unsigned int IDToDelete) {
    if(m_MyNeuros.size() == 0)                                  //如果这一层没有神经元，返回错误信息
    {
        throw std::invalid_argument("Error: There is no Neuro to delete!\n\tFailed to erase the Neuro.");
    }
    else
    {
        MyNeurosType::iterator iter = m_MyNeuros.find(IDToDelete);      //寻找要删除的神经元
        if (iter == m_MyNeuros.end())
        {
            throw std::invalid_argument("Error: Cannot find the Neuro!\n\tFailed to erase the Neuro");
        }
        else
        {
            m_MyNeuros.erase(IDToDelete);
            std::cout << "Successfully delete the Neuro (ID = " << IDToDelete << ")." << std::endl;
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ClearAllNeuros
//函数功能：清除层内所有神经元
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/23
//更改记录
//----------------------------------------------------------------------------------------------------------

void Layer::ClearAllNeuros() {
    m_MyNeuros.clear();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：获取当前层的信息
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

std::string Layer::ToString() const {
    std::ostringstream Stream;
    Stream << "**Layer**" << std::endl;
    MyNeurosType::const_iterator const_iter = m_MyNeuros.begin();
    while (const_iter != m_MyNeuros.end())
    {
        Stream << " ############################### Neuros in Layer ###################################" << std::endl;
        Stream << (const_iter->second).ToString() << std::endl;
        const_iter++;
    }
    return Stream.str();
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString_brief
//函数功能：展示层内所有神经元（简洁版）
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/24
//更改记录
//----------------------------------------------------------------------------------------------------------

std::string Layer::ToString_brief() const {
    std::ostringstream Stream;
    Stream << "**Layer**" << std::endl;
    MyNeurosType::const_iterator const_iter_Neuros = m_MyNeuros.begin();
    while (const_iter_Neuros != m_MyNeuros.end()) {
        Stream << "  ------------------------------Neurons in Layer-------------------------------" << std::endl;
        Stream << std::endl;
        Stream << "  NeuroID: __" << (const_iter_Neuros->second).NeuroID <<"__." << std::endl;
        Stream << "  Bias: __" << (const_iter_Neuros->second).MySoma.GetBias() << "__;" << std::endl;
        Stream << "  Activation Function: __No." << (const_iter_Neuros->second).MySoma.GetActvtnFunc() << " ";
        switch ((const_iter_Neuros->second).MySoma.GetActvtnFunc()) {
            case 0:
                Stream << "f(x) = x";
                break;
            case 1:
                Stream << "Sigmoid()";
                break;
            case 2:
                Stream << "Tanh()";
                break;
            case 3:
                Stream << "ReLU()";
                break;
            default:
                Stream << "Unknown Type";
                break;
        }
        Stream << "__;" << std::endl;
        Stream << std::endl;
        const_iter_Neuros++;
    }
    return Stream.str();
}








/*
int main()  {
    Neuro n1(0.5, 1, 3, 1658);
    Neuro n2(0, 0, 4, 2);       //编号为2
    Neuro n3(0, 0, 5, 3);
    Neuro n4(0, 0, 0, 1658);
    n1.InsertADendrite(1.1, &n2);
    n1.InsertADendrite(2.2, &n3);
    Layer l1;
    try
    {
        l1.InsertNeuro(n1);
        l1.InsertNeuro(n2);
        l1.InsertNeuro(n3);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
    std::cout << l1.ToString() << std::endl;
    return 0;
}
*/