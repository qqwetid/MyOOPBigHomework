//----------------------------------------------------------------------------------------------------------
//Neuro.cpp
//功能模块与目的：定义Neuro类中的函数
//开发者：Jason Cheng   日期：2025/7/18
//更改记录      2025/7/20 添加神经元编号后对相应函数进行了一些修改。具体见函数注释
//              2025/7/21 更改了一些函数名。具体见函数注释
//----------------------------------------------------------------------------------------------------------

#include "ActivationFunction.hpp"   //导入激活函数类
#include "Soma.hpp"                 //导入细胞体Soma类
#include "Synapse.hpp"              //导入突触类
#include "Axon.hpp"                 //导入轴突类
#include "Dendrite.hpp"             //导入树突类
#include "Neuro.hpp"                //导入Neuro类的声明

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

//----------------------------------------------------------------------------------------------------------
//函数名称：Neuro（构造函数）
//函数功能：构造Neuro类
//参数：double bias_set = 0,设置偏置（默认为0），输入参数； 
//     int NumOfActvtnFunc_set = 0, 设置激活函数序号（默认为0），输入参数
//     int NumOfDndrts = 100, 设置初始树突个数（默认为100），输入参数
//返回值：无
//开发者：Jason Cheng   日期：2025/7/19
//更改记录：    2025/7/20   加入NeuroID的设置
//----------------------------------------------------------------------------------------------------------

Neuro::Neuro(double bias_set, int NumOfActvtnFunc_set, int NumOfDndrts , unsigned int NeuroID_set): 
                m_MySoma(bias_set, NumOfActvtnFunc_set),    //构造细胞体
                m_MyAxon()                                  //构造轴突
{
    m_MyDendrites.reserve(NumOfDndrts);
    m_rSignalNow = 0;
    m_uNeuroID   = NeuroID_set;         //设置编号
    s_uNeuroCount++;                    //神经元个数的计数器值+1
}

//----------------------------------------------------------------------------------------------------------
//函数名称：operator=
//函数功能：实现赋值运算符的重载
//参数：const Neuro& Source
//返回值：Neuro&
//开发者：Jason Cheng   日期：2025/7/19
//更改记录：    2025/7/20   加入NeuroID的设置
//              2025/7/21   加入是否是同一个对象的判断
//----------------------------------------------------------------------------------------------------------

Neuro& Neuro::operator=(const Neuro& Source) {
    if (this != &Source)    //避免不必要的拷贝
    {
        m_MySoma = Source.MySoma;
        m_MyAxon = Source.MyAxon;
        m_MyDendrites.clear();                                      //清除本对象的所有树突
        m_MyDendrites.reserve(Source.MyDendrites.capacity());       //将本对象的capacity设置成Source中树突数组的capacity
        m_MyDendrites.assign(Source.MyDendrites.begin(), 
                             Source.MyDendrites.end()    );         //拷贝Source中的所有树突
        m_rSignalNow = Source.SignalNow;                            //将Source现在存储的信号传递给本对象
        m_uNeuroID = Source.NeuroID;                                //将ID进行拷贝
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Neuro （拷贝构造函数）
//函数功能：实现拷贝构造
//参数：const Neuro& Source
//返回值：无
//开发者：Jason Cheng   日期：2025/7/19
//更改记录：    2025/7/20   加入NeuroID的设置
//----------------------------------------------------------------------------------------------------------

Neuro::Neuro(const Neuro& Source) :
                m_MySoma(Source.MySoma),         //拷贝构造m_MySoma
                m_MyAxon(Source.MyAxon),         //拷贝构造m_MyAxon
                m_MyDendrites(Source.MyDendrites)//拷贝构造m_MyDendrites
{
    m_rSignalNow = Source.SignalNow;
    m_uNeuroID   = Source.NeuroID;      //拷贝Source的ID
    s_uNeuroCount++;                    //神经元的数量+1
}

//----------------------------------------------------------------------------------------------------------
//函数名称：~Neuro （析构函数）
//函数功能：对Neuro类完成析构
//参数：无
//返回值：无
//开发者：Jason Cheng   日期：2025/7/19
//更改记录：    2025/7/20 加上“析构完成后神经元数量-1”一行语句
//----------------------------------------------------------------------------------------------------------

Neuro::~Neuro() {
    m_MyDendrites.clear();          //保证向量中的对象被释放
    m_MyDendrites.shrink_to_fit();
    s_uNeuroCount--;                //析构完成后神经元数量-1
}

//----------------------------------------------------------------------------------------------------------
//函数名称：Signal
//函数功能：接受树突的输入，并实现输出
//参数：无  （但是会改变m_dSignalNow的值）
//返回值：double
//开发者：Jason Cheng   日期：2025/7/19
//更改记录
//----------------------------------------------------------------------------------------------------------

double Neuro::Signal() {
    double MySignal = 0;                            //存储当前信号
    MyDndrtType::iterator iter;                     //定义迭代器，遍历vector中的树突
    for (iter = m_MyDendrites.begin(); iter != m_MyDendrites.end(); iter++) //遍历vector中元素
    {
        if (iter->GetNeuro() == nullptr)            //若该树突连接神经元的指针是空指针，则跳过这一树突
        {
            continue;
        }
        double AxonInput;                           //接收上一个神经元的轴突传下来的信号
        AxonInput = (iter->GetNeuro()/* 类型为Neuro*，为该树突指向的神经元 */)->SignalNow;
        MySignal = iter->Signal(AxonInput);         //信号经过树突后存储到MySignal中
    }
    MySignal = (this->m_MySoma).Output(MySignal);   //信号经过胞体运算后存到MySignal
    MySignal = (this->m_MyAxon).Signal(MySignal);   //信号经过轴突运算后存到MySignal
    m_rSignalNow = MySignal;                        //将信号存到m_dSignalNow
    return MySignal;                                //返回MySignal的值作为信号的输出
}

//----------------------------------------------------------------------------------------------------------
//函数名称：GetNeuroCount
//函数功能：获取当前神经元的数量
//参数：无
//返回值：unsigned int
//开发者：Jason Cheng   日期：2025/7/20
//更改记录
//----------------------------------------------------------------------------------------------------------

unsigned int Neuro::GetNeuroCount() {
    return s_uNeuroCount;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetSoma
//函数功能：获取Soma成员，可以调用其Setter进行修改
//参数：无
//返回值：Soma&
//开发者：Jason Cheng   日期：2025/7/19
//更改记录
//----------------------------------------------------------------------------------------------------------

Soma& Neuro::SetSoma() {
    return m_MySoma;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetAxon
//函数功能：获取对象的m_MyAxon成员，可以调用其Setter进行修改
//参数：无
//返回值：Axon&
//开发者：Jason Cheng   日期：2025/7/19
//更改记录
//----------------------------------------------------------------------------------------------------------

Axon& Neuro::SetAxon() {
    return m_MyAxon;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetDendrites
//函数功能：获得对象的m_MyDendrites成员，是一个存储树突的向量
//参数：无
//返回值：MyDndrtType&
//开发者：Jason Cheng   日期：2025/7/19
//更改记录
//----------------------------------------------------------------------------------------------------------

MyDndrtType& Neuro::SetDendrites() {
    return m_MyDendrites;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetSignalNow
//函数功能：修改对象的m_dSignalNow，即现在所存储的信号
//参数：无
//返回值：double
//开发者：Jason Cheng   日期：2025/7/19
//更改记录
//----------------------------------------------------------------------------------------------------------

void Neuro::SetSignalNow(double Signal_set) {
    m_rSignalNow = Signal_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：SetID
//函数功能：修改对象的m_uNeuroID，即现在神经元的ID
//参数：unsigned int ID_set
//返回值：无
//开发者：Jason Cheng   日期：2025/7/20
//更改记录
//----------------------------------------------------------------------------------------------------------

void Neuro::SetID(unsigned int ID_set) {
    m_uNeuroID = ID_set;
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertDendrite
//函数功能：加入一个树突
//参数：const Dendrite& Source
//返回值：无
//开发者：Jason Cheng   日期：2025/7/19
//更改记录      2025/7/21 将函数名从AddDendrite改为InsertDendrite
//----------------------------------------------------------------------------------------------------------

void Neuro::InsertADendrite(const Dendrite& Source) {
    m_MyDendrites.push_back(Source);    //将Source拷贝到vector的末尾
}

//----------------------------------------------------------------------------------------------------------
//函数名称：InsertDendrite
//函数功能：加入一个树突
//参数：double Weight_set, Neuro* pConnectedNeuro_set
//返回值：无
//开发者：Jason Cheng   日期：2025/7/19
//更改记录      2025/7/21 将函数名从AddDendrite改为InsertDendrite
//----------------------------------------------------------------------------------------------------------

void Neuro::InsertADendrite(double Weight_set, Neuro* pConnectedNeuro_set) {
    Dendrite d1(Weight_set, pConnectedNeuro_set);       //建立一个临时的d1对象，存储输入的信息
    m_MyDendrites.push_back(d1);                        //将d1的信息拷贝到m_MyDendrites
    //d1的空间在函数结束后释放
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteDendrite
//函数功能：删除一个连接Source神经元的树突
//参数：const Neuro& Source
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

void Neuro::DeleteDendrite(const Neuro& Source) {
    if (m_MyDendrites.size() == 0)
    {
        throw std::invalid_argument("Error: There is no Dendrite!\n\tFail to erase the dendrite.");
    }
    else        //若树突数量不为0
    {
        MyDndrtType::const_iterator iter;
        for (iter = m_MyDendrites.begin(); iter != m_MyDendrites.end();)
        {
            if (iter->GetNeuro() == &Source)    //若存在连接Source的神经元
            {
                m_MyDendrites.erase(iter);                  //删除这个树突
                break;
            }
            iter++;
            if (iter == m_MyDendrites.end())                //若未找到，返回错误信息
            {
                throw std::invalid_argument("Error: Cannot find this Dendrite!\n\tFail to erase the dendrite.");
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：DeleteDendrite
//函数功能：删除一个连接编号为IDToDelete的神经元的树突
//参数：unsigned int IDToDelete
//返回值：无
//开发者：Jason Cheng   日期：2025/7/21
//更改记录
//----------------------------------------------------------------------------------------------------------

void Neuro::DeleteDendrite(unsigned int IDToDelete) {
    if (m_MyDendrites.size() == 0)
    {
        throw std::invalid_argument("Error: There is no Dendrite!\n\tFail to erase the dendrite.");
    }
    else        //若树突数量不为0
    {
        MyDndrtType::const_iterator iter;
        for (iter = m_MyDendrites.begin(); iter != m_MyDendrites.end();)
        {
            if (iter->GetNeuro()->NeuroID == IDToDelete)    //若存在连接Source的神经元
            {
                m_MyDendrites.erase(iter);                  //删除这个树突
                break;
            }
            iter++;
            if (iter == m_MyDendrites.end())                //若未找到，返回错误信息
            {
                throw std::invalid_argument("Error: Cannot find this Dendrite!\n\tFail to erase the dendrite.");
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------
//函数名称：ToString
//函数功能：将神经元的信息整合成字符串
//参数：无
//返回值：std::string
//开发者：Jason Cheng   日期：2025/7/19
//更改记录:     2025/7/21   对输出界面做了稍微的修改
//----------------------------------------------------------------------------------------------------------

std::string Neuro::ToString() const {
    std::ostringstream Stream;
    Stream << "**Neuro**" << std::endl;
    Stream << "NeuroID:\t" << m_uNeuroID << std::endl;
    Stream << "Address:\t" << this << std::endl;
    Stream << "------------------------------- Elements in Neuro -------------------------------" << std::endl;
    Stream << "MySoma:\t" << m_MySoma.ToString();
    Stream << "------------------------------- Elements in Neuro -------------------------------" << std::endl;
    Stream << "MyAxon:\t" << m_MyAxon.ToString();
    Stream << "------------------------------- Elements in Neuro -------------------------------" << std::endl;
    Stream << "MyDendrites:\t" << std::endl;
    Stream << std::endl;
    MyDndrtType::const_iterator iter;
    for (iter = m_MyDendrites.begin(); iter != MyDendrites.end(); iter++) {
        Stream << iter->ToString();
        Stream << std::endl;
    }
    Stream << "------------------------------- Elements in Neuro -------------------------------" << std::endl;
    Stream << "Signal now:\t" << m_rSignalNow << std::endl;
    return Stream.str();
}

//初始化一开始神经元的数量为0
unsigned int Neuro::s_uNeuroCount = 0;

/*
int main() {
    const Neuro n1;
}
*/
