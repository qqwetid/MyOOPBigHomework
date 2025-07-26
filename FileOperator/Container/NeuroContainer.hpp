//----------------------------------------------------------------------------------------------------------
//NeuroContainer.hpp
//功能模块：NeuroContainer类；目的：定义存放神经元信息的容器
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef NEURO_CONTAINER_HPP
#define NEURO_CONTAINER_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：NeuroContainer
//功能：存放一个神经元的信息
//接口： 
/*
    *   double& rBias {m_rBias};
    *   int& iNumOfActvtnFnctn {m_iNumOfActvtnFnctn};
    * 
    *   void SetBias(double SetBias);
    *   void SetActvtnFnctn(int SetActvtnFnctn);
    *
    *   std::string ToString() const;
*/
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

class NeuroContainer
{
    public:
        //构造函数
        NeuroContainer(double SetBias = 0, int SetActvtnFnctn = 0);
        //拷贝构造函数
        NeuroContainer(const NeuroContainer& Source);
        //赋值运算符重载
        NeuroContainer& operator=(const NeuroContainer& Source);
        //析构函数
        ~NeuroContainer();

        //Getters
        const double& Bias {m_rBias};
        const int& NumOfActvtnFnctn {m_iNumOfActvtnFnctn};

        //Setters
        void SetBias(double SetBias);
        void SetActvtnFnctn(int SetActvtnFnctn);

        //展示信息
        std::string ToString() const;
    private:
        double m_rBias;                 //偏置
        int m_iNumOfActvtnFnctn;        //激活函数序号
};


#endif /*NEURO_CONTAINER_HPP*/