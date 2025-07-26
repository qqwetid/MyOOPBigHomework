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
        //判断文件是否合法
        virtual bool IsValid() const override;
        //判断文件是否合法，并查看路径中的.ANN文件中神经元、层的数量
        virtual bool IsValid(int& NumOfNeuros, int& NumOfLayers) const;
        //导出文件
        virtual void OutputFile(const std::vector<NeuroContainer>& MyNeuroVector,
                                const std::set<SynapseContainer>&  MySynapseSet,
                                const std::vector<LayerContainer>& MyLayerVector,
                                const char* NetworkName                          ) override;
    private:
        //已在Exporter类中声明保护对象char m_FileNamePath[100];
};



#endif /*ANNEXPORTER_HPP*/