//----------------------------------------------------------------------------------------------------------
//Neuro.hpp
//功能模块：Neuro类；目的：定义神经元
//开发者：Jason Cheng   日期：2025/7/18
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef NEURO_HPP
#define NEURO_HPP

#include <string>
#include <vector>

//定义一个类型MyDndrtType, 它属于容器vector，用来存放这个神经元的树突
typedef std::vector<Dendrite> MyDndrtType;  

//----------------------------------------------------------------------------------------------------------
//类名：Neuro
//功能：组合胞体Soma，树突Dendrite和轴突Axon，作为神经网络的单位
//接口： Signal() 与 SignalNow 作为这个神经元的输出，其中前者需要参与运算，后者直接调用之前的运算结果
//开发者：Jason Cheng   日期：2025/7/18
//更改记录：    2025/7/21   添加删除树突的函数
//              2025/7/21   将AddDendrite的函数名修改为InsertDendrite
//----------------------------------------------------------------------------------------------------------

class Neuro
{
    public:
        //构造函数，赋值运算符重载，拷贝构造函数
        //构造函数设置偏置（默认为0），激活函数序号（默认为0）；树突后面再添加
        Neuro(double bias_set = 0, int NumOfActvtnFunc_set = 0, int NumOfDndrts = 100, unsigned int NeuroID_set = s_uNeuroCount + 1);
        //赋值运算符重载
        Neuro& operator=(const Neuro& Source);
        //拷贝构造函数
        Neuro(const Neuro& Source);

        //析构函数
        ~Neuro();

        //接受树突的信息，并进行整合和输出
        double Signal();            //对私有数据成员 m_dSignalNow 进行了修改，所以不加const

        //Getters
        const Soma& MySoma {m_MySoma};                  //获取细胞体Soma
        const Axon& MyAxon {m_MyAxon};                  //获取轴突Axon
        const MyDndrtType& MyDendrites {m_MyDendrites}; //获取存储树突的向量
        const double& SignalNow {m_rSignalNow};         //获取当前存储的信号
        const unsigned int& NeuroID {m_uNeuroID};       //获取神经元的ID
        static unsigned int GetNeuroCount();            //获取神经元的数量

        //Setters
        //获取神经元的细胞体，可以修改
        Soma& SetSoma();
        //获取神经元的轴突，可以修改
        Axon& SetAxon();
        //获取神经元存放树突的向量，可以修改
        MyDndrtType& SetDendrites();
        //修改现在存储的信号
        void SetSignalNow(double Signal_set);
        //修改当前神经元的ID
        void SetID(unsigned int ID_set);
        //加入一个树突
        void InsertADendrite(const Dendrite& Source);
        //加入一个树突
        void InsertADendrite(double Weight_set, Neuro* pConnectedNeuro_set);
        //删除一个连接Source神经元的树突
        void DeleteDendrite(const Neuro& Source);
        //删除一个编号为IDToDelete的神经元的树突
        void DeleteDendrite(unsigned int IDToDelete);

        //将信息编成字符串
        std::string ToString() const;
    private:
        Soma m_MySoma;                      //私有数据成员细胞体Soma
        Axon m_MyAxon;                      //私有数据成员轴突MyAxon
        MyDndrtType m_MyDendrites;          //树突存放库
        double m_rSignalNow;                //用于存储现在的信号
        unsigned int m_uNeuroID;            //存放神经元的编号
        static unsigned int s_uNeuroCount;  //计数器，存储当前神经元的数量，默认为0
};


#endif /*NEURO_HPP*/