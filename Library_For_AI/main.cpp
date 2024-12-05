#include "AI.h"
//#include "CmdAndAPI.h"

int main(int argc, char* argv[])
{
    ai::AI graf("1", ai::FREENETWORK, ai::DATA_DATA);
    //graf.CreateNetwork(6, 7);
    graf.Test();

    //std::list<long double> data = { 0.5, 0.5 };
    //for (auto pair : graf.Computation(data))
    //{
    //    std::cout << pair << '\n';
    //}

    //ai::AI graf("test.txt");
    //graf.DatasetTraining("TestDATASet/DATA.txt", "TestDATASet/DATA.txt", 100);

    std::cout << '\n';
    return 0;
}