//----------------------------------------------------------------------------------------------------------
//SynapseContainer.hpp
//功能模块：SynapseContainer类；目的：定义存放神经元信息的容器
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef SYNAPSE_CONTAINER_HPP
#define SYNAPSE_CONTAINER_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：SynapseContainer
//功能：存放一个神经元的信息
//接口： 
/*

*/
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

class SynapseContainer
{
    public:
        //构造函数
        SynapseContainer(int SetCnnctNeuro = -1, int SetLyingNeuro = -1, double SetWeight = 1);
        //拷贝构造函数
        SynapseContainer(const SynapseContainer& Source);
        //赋值运算符重载
        SynapseContainer& operator=(const SynapseContainer& Source);
        //析构函数
        ~SynapseContainer();

        //比较运算符重载
        bool operator<(const SynapseContainer& Source) const;

        //Getters
        const int& CnnctNeuro {m_iCnnctNeuro};
        const int& LyingNeuro {m_iLyingNeuro};
        const double& Weight  {m_rWeight};

        //Setters
        void SetCnnctNeuro(int SetCnnctNeuro);
        void SetLyingNeuro(int SetLyingNeuro);
        void SetWeight(double SetWeight);

        //展示信息
        std::string ToString() const;
    private:
        int m_iCnnctNeuro;              //树突前端连接的神经元编号
        int m_iLyingNeuro;              //树突所在神经元编号
        double m_rWeight;               //树突的权重
};


#endif /*SYNAPSE_CONTAINER_HPP*/