//----------------------------------------------------------------------------------------------------------
//Soma.hpp
//功能模块：Soma类；目的：定义细胞体
//开发者：Jason Cheng   日期：2025/7/16
//更改记录
//----------------------------------------------------------------------------------------------------------

#ifndef SOMA_HPP
#define SOMA_HPP

#include <stdexcept>
#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：Soma
//功能：定义细胞体
//接口：     Output()整合函数+激活函数后的输出；
//          ToString()获得Soma对象的信息
//开发者：Jason Cheng   日期：2025/7/16
//更改记录
//----------------------------------------------------------------------------------------------------------

class Soma
{
    public:
        //构造函数，赋值运算与拷贝构造函数
        Soma(const double Bias_set = 0.0, const int Num_set = 0);   //偏置默认值为0，激活函数默认为无激活函数
        Soma& operator=(const Soma& Source);
        Soma(const Soma& Source);
        //析构函数
        virtual ~Soma();

        //判断赋值是否合理的函数
        static bool IsValid(const int NumOfActvtnFunc);
        static bool IsValid(const Soma& Source);
        bool IsValid() const;

        /*
        //整合函数
        double SumFunc(const double& SumOfSignals) const;           //整合函数，接收输入信号的求和
        */
        //细胞体的输出函数
        double Output(const double& SumOfSignals) const;          //细胞体的输出，接收输入信号的求和，整合函数+激活函数

        //Getters
        double GetBias() const;                                     //获取细胞体的偏置
        int GetActvtnFunc() const;                                 //获取激活函数序号
        //Setters
        void SetBias(const double& Bias_set);                       //设置细胞体的偏置
        void SetActvtnFunc(const int& NumOfActvtnFunc_set);         //设置激活函数的序号
        //获取细胞体的信息ToString，带回车
        std::string ToString() const;   //末尾带回车

    private:
        double m_rBias;             //偏置
        int m_iNumOfActvtnFunc;     //激活函数的序号
};

#endif /*SOMA_HPP*/