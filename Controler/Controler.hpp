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

        //输入路径的函数
        void InputFilePath(char* FilePath, unsigned int PathLength) const;
        //根据容器创建神经网络
        Network* ImportNetwork(const std::vector<NeuroContainer>& MyNeuroVector,
                               const std::set<SynapseContainer>&  MySynapseSet,
                               const std::vector<LayerContainer>& MyLayerVector,
                               const char* NetworkName) const;
        //将.ANN文件导入成神经网络
        Network* ImportNetwork(const char* FilePath) const;
    private:
        //定义私有的构造函数，防止外部代码直接实例化
        Controler();
        //私有静态指针，存储单例实例
        static Controler* m_pInstance_;
};

#endif /*CONTROLER_HPP*/