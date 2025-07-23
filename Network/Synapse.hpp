//----------------------------------------------------------------------------------------------------------
//Synapse.hpp
//功能模块：Synapse类；目的：定义突触
//开发者：Jason Cheng   日期：2025/7/17
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：Synapse
//功能：定义突触类Synapse，作为树突类Dendrite和轴突类Axon的基类
//接口：Signal()输出信号
//开发者：Jason Cheng   日期：2025/7/17
//更改记录：
//----------------------------------------------------------------------------------------------------------

class Synapse
{
    public:
        //构造函数，赋值和拷贝构造函数
        Synapse(double weight = 1);     //默认权重为1
        Synapse& operator=(const Synapse& Source);
        Synapse(const Synapse& Source);
        //虚析构函数
        virtual ~Synapse();

        //输出信号的函数
        double Signal(double Input) const;  //Signal = Input * Weight

        //Getters
        double GetWeight() const;           //获取m_dWeight成员变量

        //Setters
        void SetWeight(double Weight_set);  //设置m_dWeight的值

        //获取突触信息的ToString函数，带回车
        virtual std::string ToString() const;   //末尾带回车；虚的ToString函数，方便继承后重写

    private:
        double m_rWeight;      //权重
};

#endif /*SYNAPSE_HPP*/