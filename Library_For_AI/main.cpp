#include "AI.h"
//#include "CmdAndAPI.h"

int main(int argc, char* argv[])
{
    ai::AI graf("1", ai::PERCEPTRON, ai::DATA_DATA);
    graf.CreateNetwork(100, 50);

    //ai::AI graf("test.txt");
    //graf.DatasetTraining("TestDATASet/DATA.txt", "TestDATASet/DATA.txt", 100);

    std::cout << '\n';
    return 0;
}
