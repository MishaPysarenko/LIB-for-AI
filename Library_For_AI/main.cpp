#include "AI.h"
//#include "CmdAndAPI.h"

int main(int argc, char* argv[])
{
    ai::AI graf("test", ai::PERCEPTRON);
    graf.CreateNetwork(4, 1);
    graf.DatasetTrainingRough("DataSet.txt", 100);
    return 0;
}
