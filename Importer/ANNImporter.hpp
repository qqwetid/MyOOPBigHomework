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
        virtual void ImportFile(const char* FileNamePath, 
                                std::vector<NeuroContainer> MyNeuroVector,
                                std::set<SynapseContainer>  MySynapseSet,
                                std::vector<LayerContainer> MyLayerVector,
                                char* NetworkName) override;
};



#endif /*ANNIMPORTER_HPP*/