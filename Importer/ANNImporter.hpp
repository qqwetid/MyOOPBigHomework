//----------------------------------------------------------------------------------------------------------
//ANNImporter.hpp
//功能模块：ANNImporter类；目的：导入.ANN文件
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef ANNIMPORTER_HPP
#define ANNIMPORTER_HPP

//----------------------------------------------------------------------------------------------------------
//类名：ANNImporter
//功能：导入ANN文件
//接口： 
/*
    *   virtual void ImportFile(const char* FileName, 
                                std::vector<NeuroContainer> MyNeuroVector,
                                std::set<SynapseContainer>  MySynapseSet,
                                std::vector<LayerContainer> MyLayerVector) = 0;
*/
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

class ANNImporter: public Importer
{
    public:
        //构造函数，输入文件路径
        ANNImporter(const char* SetFileName = "");
        //赋值运算符重载
        ANNImporter& operator=(const ANNImporter& Source);
        //拷贝构造函数
        ANNImporter(const ANNImporter& Source);
        //析构函数
        ~ANNImporter();

        /*
            Importer中已定义:
            *   void Importfile(const char* FileName);
            *   void clear();
            *   const char* GetFileName() const;
        */
        //判断文件是否合法
        virtual bool IsValid() const override;
        //判断文件是否合法，并查看路径中的.ANN文件中神经元、层的数量
        virtual bool IsValid(int& NumOfNeuros, int& NumOfLayers) const;
        //导入文件
        virtual void ReadFile(std::vector<NeuroContainer>& MyNeuroVector,
                              std::set<SynapseContainer>&  MySynapseSet,
                              std::vector<LayerContainer>& MyLayerVector,
                              char* NetworkName                             ) override;
    private:
        //已在Importer类中声明保护对象char FileNamePath[100];
};



#endif /*ANNIMPORTER_HPP*/