//----------------------------------------------------------------------------------------------------------
//Axon.hpp
//功能模块：Axon类，继承于Synapse；目的：声明轴突，增加IsValid()判断函数；为树突提供连接
//开发者：Jason Cheng   日期：2025/7/18
//更改记录
//----------------------------------------------------------------------------------------------------------

#ifndef AXON_HPP
#define AXON_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：Axon
//功能：声明轴突类Axon，继承于Synapse，权重恒为1；作为树突类Dendrite的连接
//接口：Signal()输出信号（继承于Synapse），作为输出
//开发者：Jason Cheng   日期：2025/7/17
//更改记录
//----------------------------------------------------------------------------------------------------------

class Axon: public Synapse
{
    public:
        //构造函数，赋值运算符和拷贝构造函数
        Axon();
        Axon& operator=(const Axon& Source);
        Axon(const Axon& Source);

        //析构函数
        ~Axon();

        //IsValid函数，判断轴突的权重是否为1
        static bool IsValid(const Axon& Source);
        static bool IsValid(double Weight);
        bool IsValid() const;

        //删除SetWeight()函数
        void SetWeight() = delete;

        //重写ToString()函数，带回车
        virtual std::string ToString() const override;
    private:
        //m_dWeight 为Synapse中已有的保护成员变量
};


#endif /*AXON_HPP*/