//----------------------------------------------------------------------------------------------------------
//ANNExporter.hpp
//功能模块：ANNExporter类；目的：导出.ANN文件
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef ANNEXPORTER_HPP
#define ANNEXPORTER_HPP

//----------------------------------------------------------------------------------------------------------
//类名：ANNExporter
//功能：导出ANN文件
//接口： 
/*
    *   ANNExporter(const char* SetFileName = "");
    *   ANNExporter& operator=(const ANNExporter& Source);
    *   ANNExporter(const ANNExporter& Source);
    *   ~ANNExporter();
    *   
    *   Exporter中已定义:
    *   *   void Importfile(const char* FileName);
    *   *   void clear();
    *   *   const char* GetFileName() const;
    *   
    *   bool IsANNFile() const;
    *   virtual bool IsValid() const override;
    *   virtual void OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
    *                           const std::set<SynapseContainer>&  MySynapseSet,
    *                           const std::vector<LayerContainer>& MyLayerVector,
    *                           const char* NetworkName                          ) override;
*/
//开发者：Jason Cheng   日期：2025/7/26
//更改记录：
//----------------------------------------------------------------------------------------------------------

class ANNExporter: public Exporter
{
    public:
        //构造函数，输入文件路径
        ANNExporter(const char* SetFileName = "");
        //赋值运算符重载
        ANNExporter& operator=(const ANNExporter& Source);
        //拷贝构造函数
        ANNExporter(const ANNExporter& Source);
        //析构函数
        ~ANNExporter();

        /*
            Exporter中已定义:
            *   void Importfile(const char* FileName);
            *   void clear();
            *   const char* GetFileName() const;
        */
        //判断要写入的是不是.ANN文件
        bool IsANNFile() const;
        //判断文件是否合法
        virtual bool IsValid() const override;
        //导出文件
        virtual void OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
                                const std::set<SynapseContainer>&  MySynapseSet,
                                const std::vector<LayerContainer>& MyLayerVector,
                                const char* NetworkName                          ) override;
    private:
        //已在Exporter类中声明保护对象char m_FileNamePath[100];
};



#endif /*ANNEXPORTER_HPP*/