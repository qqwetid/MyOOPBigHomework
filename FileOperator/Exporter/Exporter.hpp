//----------------------------------------------------------------------------------------------------------
//Exporter.hpp
//功能模块：Exporter类；目的：作为所有导出器类的基类
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef EXPORTER_HPP
#define EXPORTER_HPP

#include <vector>
#include <set>

//----------------------------------------------------------------------------------------------------------
//类名：Exporter
//功能：作为所有导出器类的母类
//接口： 
/*
    *   //导入文件路径（Setter）
    *   void AddPath(const char* SetFileName);
    *   //清除文件路径(Setter)
    *   void clear();
    *   //展示文件路径（Getter）
    *   const char* GetFileName() const;
    *   //判断文件是否合法的纯虚函数
    *   virtual bool IsValid() const = 0;
    *   //文件读取器的纯虚函数
    *   virtual void OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
    *                           const std::set<SynapseContainer>&  MySynapseSet,
    *                           const std::vector<LayerContainer>& MyLayerVector,
    *                           const char* NetworkName) = 0; 
*/
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

class Exporter
{
    public:
        //构造函数
        Exporter(const char* SetFileName = "");
        //赋值运算符
        Exporter& operator=(const Exporter& Source);
        //拷贝构造函数
        Exporter(const Exporter& Source);
        //析构函数
        ~Exporter();

        //导入文件路径（Setter）
        void AddPath(const char* SetFileName);
        //清除文件路径(Setter)
        void clear();
        //展示文件路径（Getter）
        const char* GetFileName() const;
        //判断文件是否合法的纯虚函数
        virtual bool IsValid() const = 0;
        //文件读取器的纯虚函数
        virtual void OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
                                const std::set<SynapseContainer>&  MySynapseSet,
                                const std::vector<LayerContainer>& MyLayerVector,
                                const char* NetworkName) = 0; 
    protected:
        char m_FileNamePath[100];
};

#endif /*EXPORTER_HPP*/