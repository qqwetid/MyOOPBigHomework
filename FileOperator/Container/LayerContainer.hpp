//----------------------------------------------------------------------------------------------------------
//LayerContainer.hpp
//功能模块：LayerContainer类；目的：定义存放层信息的容器
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef LAYER_CONTAINER_HPP
#define LAYER_CONTAINER_HPP

#include <string>

//----------------------------------------------------------------------------------------------------------
//类名：LayerContainer
//功能：存放一个层的信息
//接口： 
/*
    *   unsigned int& StartNeuro {m_uStartNeuro};
    *   unsigned int& EndNeuro   {m_uEndNeuro};
    *   
    *   void SetStartNeuro(unsigned int SetStartNeuro);
    *   void SetEndNeuro(unsigned int SetEndNeuro);
    *   
    *   std::string ToString() const;
*/
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

class LayerContainer
{
    public:
        //构造函数
        LayerContainer(unsigned int SetStartNeuro = 0, unsigned int SetEndNeuro = 0);
        //拷贝构造函数
        LayerContainer(const LayerContainer& Source);
        //赋值运算符重载
        LayerContainer& operator=(const LayerContainer& Source);
        //析构函数
        ~LayerContainer();

        //Getters
        const unsigned int& StartNeuro {m_uStartNeuro};
        const unsigned int& EndNeuro   {m_uEndNeuro};

        //Setters
        void SetStartNeuro(unsigned int SetStartNeuro);
        void SetEndNeuro(unsigned int SetEndNeuro);

        //展示信息
        std::string ToString() const;
    private:
        unsigned int m_uStartNeuro;        //此层中神经元最小索引号
        unsigned int m_uEndNeuro;          //此层中神经元最大索引号
};


#endif /*LAYER_CONTAINER_HPP*/