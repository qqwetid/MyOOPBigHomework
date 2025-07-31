//----------------------------------------------------------------------------------------------------------
//Controler.hpp
//功能模块：Controler类；目的：控制器
//开发者：Jason Cheng   日期：2025/7/28
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef CONTROLER_HPP
#define CONTROLER_HPP

//----------------------------------------------------------------------------------------------------------
//类名：Controler
//功能：控制器
//接口： 
/*
    *   待编写
*/
//开发者：Jason Cheng   日期：2025/7/28
//更改记录：
//----------------------------------------------------------------------------------------------------------

class Controler
{
    public:
        //删除拷贝构造函数
        Controler(const Controler& Source) = delete;    
        //删除赋值运算符
        Controler& operator=(const Controler& Source) = delete;

        //静态函数创建单例实例
        static Controler* GetInstance();

        /*人工神经网络模型导入*/
        //输入路径的函数
        void InputFilePath(char* FilePath, unsigned int PathLength) const;
        //根据容器创建神经网络
        Network* ImportNetwork(const std::vector<NeuroContainer>& MyNeuroVector,
                               const std::set<SynapseContainer>&  MySynapseSet,
                               const std::vector<LayerContainer>& MyLayerVector,
                               const char* NetworkName) const;
        //将.ANN文件导入成神经网络
        Network* ImportNetwork(const char* FilePath) const;

        /*人工神经网络模型导出*/
        //InputFilePath函数与导入相同
        //根据网络导出存储网络的容器
        void ExportNetwork(const Network& SourceNetwork,
                           std::vector<NeuroContainer>& MyNeuroVector,
                           std::set<SynapseContainer>&  MySynapseSet,
                           std::vector<LayerContainer>& MyLayerVector,
                           char* NetworkName) const;
        //根据网络导出.ANN文件
        void ExportNetwork(const Network& SourceNetwork, const char* FilePath) const;

        /*人工神经网络模型修改*/
        //列出所有Layer对象，显示其序号和内部神经元的数量、序号
        void ShowNetwork(const Network& SourceNetwork) const;
        //删除指定Layer 对象，同时删除此Layer 内部神经元及其关联的层间突触连接
        void DeleteLayer(Network& SourceNetwork, unsigned int LayerNumber) const;
        //添加⼀个Layer 对象，添加后内部没有Neuron 对象。
        void InsertLayer(Network& SourceNetwork, unsigned int LayerNumber) const;
        //列出指定Layer 对象中的所有Neuron 对象，显示其序号和偏置
        void ShowLayer(const Layer& SourceLayer) const;
        void ShowLayer(const Network& SourceNetwork, unsigned int LayerNumber) const;
        //为一层添加一个神经元
        void InsertNeuro(Network& SourceNetwork, unsigned int LayerNumber, double BiasSet, unsigned int ActvtnFnctnSet, unsigned int NeuroIDSet) const;
        void InsertNeuro(Network& SourceNetwork, unsigned int LayerNumebr, const Neuro& SourceNeuro) const;
        //修改指定Neuron 对象包含的偏置。
        void SetBias(Neuro& SourceNeuro, double BiasSet) const;
        void SetBias(Network& SourceNetwork, unsigned int NeuroID, double BiasSet) const;
        //列出指定Neuron对象的突触连接关系信息。
        void ShowNeuro(const Network& SourceNetwork, unsigned int NeuroID) const;
        //删除指定Neuron 对象，同时删除关联的Synapse对象
        void DeleteNeuro(Network& SourceNetwork, unsigned int NeuroID) const;
        //连接指定的Neuron 对象。要求连接相邻层，且没有突触连接的neuron对象
        void CnnctNeuro(Network& SourceNetwork, unsigned int FirstNeuroID, unsigned int SecondNeuroID, double WeightSet) const;

        /*显示统计信息*/
        void ShowElementNumbers(const Network& SourceNetwork) const;
    private:
        //定义私有的构造函数，防止外部代码直接实例化
        Controler();
        //私有静态指针，存储单例实例
        static Controler* m_pInstance_;
};

#endif /*CONTROLER_HPP*/