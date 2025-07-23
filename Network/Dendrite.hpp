//----------------------------------------------------------------------------------------------------------
//Dendrite.hpp
//功能模块：Dendrite类；目的：定义树突，继承Synapse类并增加接受轴突输入的*Axon类型私有成员变量
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： 2025/7/19 将树突的私有成员中的轴突指针 Axon* 改成了神经元指针 Neuro*，并将Getter的返回值从 Neuro& 改成了 Neuro*
//----------------------------------------------------------------------------------------------------------

#ifndef DENDRITE_HPP
#define DENDRITE_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：Dendrite
//功能：定义树突类Dendrite，继承突触类Synapse；新增私有数据成员Axon* m_ConnectAxon
//接口：Signal()输出信号，
//开发者：Jason Cheng   日期：2025/7/18
//更改记录： 2025/7/19 将树突的私有成员中的轴突指针 Axon* 改成了神经元指针 Neuro*, 并将Getter的返回值从 Neuro& 改成了 Neuro*
//----------------------------------------------------------------------------------------------------------

class Neuro;
class Dendrite: public Synapse
{
    public:
        //构造函数，赋值运算符和拷贝构造函数
        Dendrite(double Weight_set = 1, Neuro* pConnetNeuro_set = nullptr);
        Dendrite& operator=(const Dendrite& Source);
        Dendrite(const Dendrite& Source);

        //析构函数
        virtual ~Dendrite();

        //Getters，新增神经元的Getter
        Neuro* GetNeuro() const;

        //Setters, 新增m_pConnectNeuro的Setter
        void SetNeuro(Neuro& pConnection_set);

        //获取树突信息的ToString函数，带回车
        std::string ToString() const override;
    private:
        Neuro* m_pConnectNeuro;    //用于接受神经元传来的信号
};

#endif /*DENDRITE_HPP*/