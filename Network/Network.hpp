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
//接口： 待编写
//开发者：Jason Cheng   日期：2025/7/20
//更改记录：
//----------------------------------------------------------------------------------------------------------

//typedef std::map <unsigned int, Layer> MyLayersType;
typedef std::vector <Layer> MyLayersType;

class Network
{
    public:
        //构造函数
        Network(const char* NetworkName = "My Network", unsigned int NumOfNursInFstLyr = 1);
        //运算符重载
        Network& operator=(const Network& Source);
        //拷贝构造函数
        Network(const Network& Source);
        //析构函数
        ~Network();

        //判断第一层是否合理，即每个神经元是否只有一个树突，是否都指向空指针
        bool IsFirstLyrValid() const;
        //判断神经网络是否合理，包括：每个神经元是否都参与数据传递过程；是否有环状连接；
        bool IsValid() const;

        //输入参数，让神经网络进行计算
        int Inference(const double* DataInput, unsigned int SizeOfDataVector, double* SignalOutput, unsigned int& SizeofSgnl);
        
        //Getters
        //获取存储层的容器（不可修改）
        const MyLayersType& MyLayers {m_MyLayers};
        //获取层数
        unsigned int GetNumberOfLayers() const;
        //根据编号查找层
        Layer* Query(unsigned int NumberInput);
        //获取第一层神经元的数量
        unsigned int GetNmbrOfNursInFstLyr();

        //Setters
        //插入一层
        void InsertLayer(Layer& SourceLayer);
        //为相邻两层的神经元创造突触连接
        void CnnctNursByDndrt(unsigned int BackLayerID, unsigned int ForwdNeuroID, unsigned int BackNeuroID);
        //删除一层以及与其有关的所有突出连接
        void DeleteLayer(unsigned int LayerIDToDelete);
        //删除两神经元间的突触连接
        void DeleteDndrtBtwnNurs(unsigned int BackLayerID, unsigned int ForwdNeuroID, unsigned int BackNeuroID);

        //展示神经网络的信息
        std::string ToString() const;
        //展示神经网络的简要信息
        std::string ToString_brief() const;
    private:
        MyLayersType m_MyLayers;
        char m_cNetworkName[40];
};

#endif /*NETWORK_HPP*/