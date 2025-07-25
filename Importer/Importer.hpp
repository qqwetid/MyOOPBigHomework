//----------------------------------------------------------------------------------------------------------
//Importer.hpp
//功能模块：Importer类；目的：作为所有导入器类的基类
//开发者：Jason Cheng   日期：2025/7/24
//更改记录：
//----------------------------------------------------------------------------------------------------------

#ifndef IMPORTER_HPP
#define IMPORTER_HPP

//定义存放信息的结构体

struct NeuroContainer       //定义结构体存放Neuro的信息
{
    double Bias;                    //偏置
    int NumOfActvtnFctn;            //激活函数序号
};

struct SynapseContainer     //定义结构体存放树突Synapse信息
{
    int CnnctNeuro;                 //树突前端连接的神经元编号
    int LyingNeuro;                 //树突所在神经元编号
    double Weight;                  //树突的权重

    bool operator<(const SynapseContainer& Source) const {          //为了放在set中，需要定义比较大小的函数
        if (CnnctNeuro != Source.CnnctNeuro) {
            return (CnnctNeuro< Source.CnnctNeuro);    //优先比较所在神经元的序号大小
        }
        else if (LyingNeuro != Source.LyingNeuro) {
            return (LyingNeuro < Source.LyingNeuro);    //再比较连接的神经元的序号大小
        }
        else {
            return false;                               //如果两个神经元都相同，就认为两个树突一样，不允许同时出现
        }
    }

};

struct LayerContainer       //定义结构体存放层的信息
{
    unsigned int StartNeuro;        //此层中神经元最小索引号
    unsigned int EndNeuro;          //此层中神经元最大索引号
};

//----------------------------------------------------------------------------------------------------------
//类名：Importer
//功能：作为所有导入器类的母类
//接口： 待编写
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
        void ImportFile(const char* SetFileName);
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