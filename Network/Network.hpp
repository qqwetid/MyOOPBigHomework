//----------------------------------------------------------------------------------------------------------
//Network.hpp
//功能模块：Network类；目的：层组合在一起构成类
//开发者：Jason Cheng   日期：2025/7/21
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------------
//类名：Network
//功能：批量管理层
//接口： 
/*
    *   void Inference(const double* DataInput, unsigned int SizeOfDataVector, double* SignalOutput, unsigned int SizeToReserve);
    *
    *   const MyLayersType& MyLayers {m_MyLayers};
    *   unsigned int GetNumberOfLayers() const;
    *   Layer* QueryLayer(unsigned int NumberInput);
    *   Neuro* QueryNeuro(unsigned int NumberInput);
    *   unsigned int GetNmbrOfNursInFstLyr() const;
    * 
    *   void InsertLayer(Layer& SourceLayer);
    *   void InsertLayer(Layer& SourceLayer, unsigned int LayerNumber);
    *   void CnnctNursByDndrt(double WeightToSet, unsigned int CnnctLayerID, unsigned int CnnctNeuroID, unsigned int LyingLayerID, unsigned int LyingNeuroID);
    *   void DeleteLayer(unsigned int LayerIDToDelete);
    *   void DeleteDndrtBtwnNurs(unsigned int CnnctNeuroID, unsigned int MyNeuroID);
    * 
    *   std::string ToString() const;
    *   std::string ToString_brief() const;
*/
//开发者：Jason Cheng   日期：2025/7/20
//更改记录：
//----------------------------------------------------------------------------------------------------------

//typedef std::map <unsigned int, Layer> MyLayersType;
typedef std::vector <Layer> MyLayersType;

class Network
{
    public:
        //构造函数
        Network(const char* NetworkName = "My Network", unsigned int NumOfNursInFstLyr = 1, unsigned int NumberOfLayers = 2);
        //运算符重载，不能复制跨层的连接
        Network& operator=(const Network& Source);
        //拷贝构造函数，不能复制跨层的连接
        Network(const Network& Source);
        //析构函数
        ~Network();

        //判断第一层是否合理，即每个神经元是否只有一个树突，是否都指向空指针
        bool IsFirstLyrValid() const;
        //判断神经网络是否合理，包括：每个神经元是否都参与数据传递过程；是否有环状连接；
        bool IsValid() const;

        //输入参数，让神经网络进行计算
        void Inference(const double* DataInput, unsigned int SizeOfDataVector, double* SignalOutput, unsigned int SizeToReserve);
        
        //Getters
        //获取神经网络名称
        const char* NetworkName {m_cNetworkName};
        //获取存储层的容器（不可修改）
        const MyLayersType& MyLayers {m_MyLayers};
        //获取层数
        unsigned int GetNumberOfLayers() const;
        //获取神经元的数量
        unsigned int GetNumberOfNeuros() const;
        //获取突触的数量（树突+轴突）
        unsigned int GetNumberOfSynapses() const;
        //根据编号查找层
        Layer* QueryLayer(unsigned int NumberInput);
        //根据编号查找神经元
        Neuro* QueryNeuro(unsigned int NumberInput);
        const Neuro* QueryNeuro_noset(unsigned int NumberInput) const;
        //获取第一层神经元的数量
        unsigned int GetNmbrOfNursInFstLyr() const;

        //Setters
        //在末尾插入一层
        void InsertLayer(Layer& SourceLayer);
        //在指定的位置插入一层
        void InsertLayer(Layer& SourceLayer, unsigned int LayerNumber);
        //为两层的神经元创造突触连接
        void CnnctNursByDndrt(double WeightToSet, unsigned int CnnctLayerID, unsigned int CnnctNeuroID, unsigned int LyingLayerID, unsigned int LyingNeuroID);
        //只用神经元编号的索引为两层神经元创造突触连接（适用于神经网络内神经元序号没有重复的情况）
        void CnnctNursByDndrt(int FirstNeuro, int SecondNeuro, double Weight);
        //删除一层以及与其有关的所有突出连接
        void DeleteLayer(unsigned int LayerIDToDelete);
        //删除两神经元间的突触连接
        void DeleteDndrtBtwnNurs(unsigned int CnnctNeuroID, unsigned int MyNeuroID);

        //展示神经网络的信息
        std::string ToString() const;
        //展示神经网络的简要信息
        std::string ToString_brief() const;
    private:
        MyLayersType m_MyLayers;
        char m_cNetworkName[40];
};

#endif /*NETWORK_HPP*/