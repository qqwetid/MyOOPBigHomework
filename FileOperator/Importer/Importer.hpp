//----------------------------------------------------------------------------------------------------------
//Importer.hpp
//功能模块：Importer类；目的：作为所有导入器类的基类
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <set>

//----------------------------------------------------------------------------------------------------------
//类名：Importer
//功能：作为所有导入器类的母类
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
    *   virtual void ReadFile(std::vector<NeuroContainer>& MyNeuroVector,
    *                         std::set<SynapseContainer>&  MySynapseSet,
    *                         std::vector<LayerContainer>& MyLayerVector,
    *                         char* NetworkName) = 0; 
*/
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

class Importer
{
    public:
        //构造函数
        Importer(const char* SetFileName = "");
        //赋值运算符
        Importer& operator=(const Importer& Source);
        //拷贝构造函数
        Importer(const Importer& Source);
        //析构函数
        ~Importer();

        //导入文件路径（Setter）
        void AddPath(const char* SetFileName);
        //清除文件路径(Setter)
        void clear();
        //展示文件路径（Getter）
        const char* GetFileName() const;
        //判断文件是否合法的纯虚函数
        virtual bool IsValid() const = 0;
        //文件读取器的纯虚函数
        virtual void ReadFile(std::vector<NeuroContainer>& MyNeuroVector,
                              std::set<SynapseContainer>&  MySynapseSet,
                              std::vector<LayerContainer>& MyLayerVector,
                              char* NetworkName) = 0; 
    protected:
        char m_FileNamePath[100];
};

#endif /*IMPORTER_HPP*/