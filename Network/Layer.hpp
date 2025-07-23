//----------------------------------------------------------------------------------------------------------
//Layer.hpp
//功能模块：Layer类；目的：神经元组合在一起构成类
//开发者：Jason Cheng   日期：2025/7/19
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>
#include <map>

//----------------------------------------------------------------------------------------------------------
//类名：Layer
//功能：批量管理神经元
//接口：     ForwardPropagation()进行前向传播
//          Query(unsigned int)查找神经元
//          InsertNeuro(Neuro& )添加神经元
//          DeleteNeuro(unsigned int)删除神经元
//          ToString()展示层的信息
//开发者：Jason Cheng   日期：2025/7/20
//更改记录：        2025/7/22增加静态成员函数HasConnection
//                  2025/7/23 增加带有参数的ForwardPropagation和输出当前信号的LayerSignalNow
//                  2025/7/23 增加清除所有神经元的函数ClearAllNeuros
//----------------------------------------------------------------------------------------------------------

//定义MyNeurosType, 用于储存一个层的神经元
typedef std::map <unsigned int, Neuro, std::less<unsigned int> > MyNeurosType;

class Layer
{
    public:
        //构造函数，创造一个空的Layer对象
        Layer();
        //重载赋值运算符
        Layer& operator=(const Layer& Source);
        //拷贝构造函数
        Layer(const Layer& Source);
        //析构函数
        ~Layer();

        //接受、处理上一层的信号并输出（将信号存储在每个神经元）
        void ForwardPropagation();
        //接受一个数组作为输入的信号，每个神经元都用第一个树突作用后输出
        void ForwardPropagation(const double* InputVector, unsigned int DimOfInput);
        //输出当前信号
        void LayerSignalNow(double* OutputVector, unsigned int DimToReserve) const;

        //Getters
        //获取存储神经元的容器（不可修改）
        const MyNeurosType& GetMyNeuros() const;
        //获取存储的神经元个数
        unsigned int GetNeuroNumber() const;
        //根据编号查找神经元
        Neuro* Query(unsigned int ID_input);
        //判断一个树突是否在一层里面有连接
        static bool HasConnection(const Layer& LayerToCheck, const Dendrite& DndrtToCheck);
        
        //Setters
        //插入一个神经元
        void InsertNeuro(Neuro& Neuro_set);
        //删除层中某一编号的所有神经元
        void DeleteNeuro(unsigned int IDToDelete);
        //删除层中的所有神经元
        void ClearAllNeuros();

        //展示层内所有神经元
        std::string ToString() const;
    private:
        MyNeurosType m_MyNeuros;
};



#endif /*LAYER_HPP*/