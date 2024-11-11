#pragma once
#include <any>
#include <fstream>
#include <list>
#include "ActivationFunction.h"

namespace ai
{
    using DataConvertFunc = std::list<NWDT>(*)(std::any data, int maxBlocks);
    std::list<NWDT> DataFileConverter(std::any data, int maxBlocks);
    std::list<NWDT> DataBlockConverter(std::any data, int maxBlocks);
    extern std::vector<DataConvertFunc> ConvertFunctions;
}