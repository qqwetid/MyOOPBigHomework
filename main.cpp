#include <iostream>

#include "./Network/ActivationFunction.hpp"   //导入激活函数类
#include "./Network/Soma.hpp"                 //导入细胞体Soma类
#include "./Network/Synapse.hpp"              //导入突触类
#include "./Network/Axon.hpp"                 //导入轴突类
#include "./Network/Dendrite.hpp"             //导入树突类
#include "./Network/Neuro.hpp"                //导入Neuro类的声明


/*
int main() {
    /*
    std::cout << Neuro::GetNeuroCount() << std::endl;
    Neuro n1(0.5, 1, 4);
    std::cout << Neuro::GetNeuroCount() << std::endl;
    Neuro n2 = n1;
    std::cout << Neuro::GetNeuroCount() << std::endl;
    Neuro n3(n1);
    std::cout << Neuro::GetNeuroCount() << std::endl;
    Neuro n4;
    n1.AddADendrite(1, &n1);
    n1.AddADendrite(1.5, &n2);
    n1.AddADendrite(0.3, &n3);
    std::cout << n1.ToString() << std::endl;
    
    return 0;
}
*/