#include "AI.h"
namespace ai
{
	void AI::Initialization(frame type)
	{
        this->type = type;
		switch (type)
		{
		case 0: ai = std::make_shared<perceptron>(nameProjectFile, nameProjectLogFile); break;
		case 1: ai = std::make_shared<freeNetwork>(nameProjectFile, nameProjectLogFile); break;
		default:break;
		}
	}

    std::shared_ptr<Graf> AI::Initialization()
    {
        switch (type)
        {
        case 0: tryAi = std::make_shared<perceptron>(nameProjectFile, nameProjectLogFile); break;
        case 1: tryAi = std::make_shared<freeNetwork>(nameProjectFile, nameProjectLogFile); break;
        default:break;
        }
        tryAi->CreateNetwork(nameProjectFile);
        return tryAi;
    }

    void AI::CreateNetwork(size_t amountInVertex, size_t amountOutVertex)
    {
        if (doCreate)
            return;

        amountIn = amountInVertex;
        amountOut = amountOutVertex;
        ai->CreateNetwork(amountInVertex, amountOutVertex);

        doCreate = 1;
    }

    void AI::CreateNetwork(std::string nameFile)
    {
        if (doCreate)
            return;

        nameProjectFile = nameFile;

        ai->CreateNetwork(nameFile);

        doCreate = 1;
    }

	std::list<bool> AI::Computation(std::list<bool> vaules)
	{
		if (!doCreate)
		{
			std::list<bool> result;
			return result;
		}
		return ai->Computation(vaules);
	}

    float AI::testCycle(std::string nameFile)
    {
        float percentResult = 0;
        float counter = 0;
        std::string line;
        std::ifstream DATASetFile;
        DATASetFile.open(nameFile);
        while (std::getline(DATASetFile, line)) {
            std::string Value = line.substr(0, line.find(' '));
            std::string Result = line.substr(Value.size() + 1);
            std::list<bool> value;
            std::list<bool> result;
            for (char ch : Value)
            {
                if (ch == '0')
                    value.push_back(0);
                else
                    value.push_back(1);
            }
            for (char ch : Result)
            {
                if (ch == '0')
                    result.push_back(0);
                else
                    result.push_back(1);
            }
            auto res = ai->Computation(value);
            if (result == res)
            {
                ai->SelectionOfWeights(1);
                percentResult++;
            }
            else
            {
                ai->SelectionOfWeights(0);
            }
            counter++;
            Value.clear();
            Result.clear();
            value.clear();
            result.clear();
        }
        percentResult = (percentResult / counter) * 100;
        DATASetFile.close();
        return percentResult;
    }

    float AI::testCycle(std::shared_ptr<Graf> test, std::string nameFile)
    {
        float percentResult = 0;
        float counter = 0;
        std::string line;
        std::ifstream DATASetFile;
        DATASetFile.open(nameFile);
        while (std::getline(DATASetFile, line)) {
            std::string Value = line.substr(0, line.find(' '));
            std::string Result = line.substr(Value.size() + 1);
            std::list<bool> value;
            std::list<bool> result;
            for (char ch : Value)
            {
                if (ch == '0')
                    value.push_back(0);
                else
                    value.push_back(1);
            }
            for (char ch : Result)
            {
                if (ch == '0')
                    result.push_back(0);
                else
                    result.push_back(1);
            }
            auto res = test->Computation(value);
            if (result == res)
            {
                test->SelectionOfWeights(1);
                percentResult++;
            }
            else
            {
                test->SelectionOfWeights(0);
            }
            counter++;
            Value.clear();
            Result.clear();
            value.clear();
            result.clear();
        }
        percentResult = (percentResult / counter) * 100;
        DATASetFile.close();
        return percentResult;
    }

    //пересмотреть реализацию
    std::vector<std::shared_ptr<Graf>> AI::ArchitectureGenerator(std::shared_ptr<Graf> sampler, std::string nameFile)
    {
        auto amount = ai->CounterCombination();
        std::vector<std::shared_ptr<Graf>> vecAI;
        float theBestRes = 0;
        for (int i = amount; i > 1; --i)
        {
            for (size_t j = std::pow(i, activationFunctions.size()); j > 0; j--)
            {
                tryAi = Initialization();
                tryAi->TryArchitecture(i,j);

                float tempCycel = testCycle(tryAi, nameFile);
                for (size_t j = 0; j < 1000; j++)
                {
                    tempCycel = (tempCycel + testCycle(tryAi, nameFile)) / 2;
                }
                tryAi->Show();
                std::cout << "Res: " << tempCycel << "\n\n\n";
                if (theBestRes < tempCycel)
                {
                    theBestRes = tempCycel;
                    ai = tryAi;
                }
               // vecAI.push_back(tryAi);
            }
        }
        std::cout << "The Best res: " << theBestRes << '\n';
        ai->Show();
        ai->SaveNetwork("lalalala.txt");
        return vecAI;
    }

    //пересмотреть реализацию
    std::vector<std::shared_ptr<Graf>> AI::GenerationCF(std::shared_ptr<Graf> sampler)
    {
        std::vector<std::shared_ptr<Graf>> vecAI;
        auto amountInput = std::pow(activationFunctions.size(), amountIn);
        auto amountOutput = std::pow(activationFunctions.size(), amountOut);
        auto temp = ai;
        for (size_t i = amountInput; i > 0; i--)
        {
            for (size_t j = amountOutput; j > 0; j--)
            {
                tryAi = Initialization();
                //temp->GenerateCombinationFunctions(i, j);
                tryAi = temp;
                vecAI.push_back(tryAi);
            }
        }
        return vecAI;
    }

    void AI::SelectionOfWeights(bool res)
    {
        if (!doCreate)
        {
            return;
        }
        ai->SelectionOfWeights(res);
    }

    //пересмотреть реализацию
	void AI::DatasetTraining(std::string nameFile, float percent)
	{
        if (percent > 100 || percent == 0 || nameFile.size() == 0 || (!doCreate))
            return;

        #define counterForEditStruct 5
        #define counterIteration 1000
        unsigned int mainCounterForEditStruct = 0, mainCounter = 0;
        std::list<float> listValueForEditStruct;
        float controlChek = testCycle(nameFile), controlChekMaxValue = 0;
        unsigned int generation = 0;
        /*float TheBestRes = 0,TheBestForItAi = 0, averageValue;
        auto arrAi = ai->GenerateCombinationFunctions();
        for (auto pair : arrAi)
        {
            pair->Show();
            averageValue = testCycle(pair, nameFile);
            for (size_t j = 0; j < counterIteration; j++)
            {
                averageValue = testCycle(pair, nameFile);
                if (averageValue > TheBestForItAi)
                {
                    TheBestForItAi = averageValue;
                }
            }
            std::cout << "Res: " << TheBestForItAi << "\n\n\n";
            if (TheBestRes < TheBestForItAi)
            {
                ai = pair;
                TheBestRes = TheBestForItAi;
                if (TheBestRes == 100)
                {
                    break;
                }
            }
            TheBestForItAi = 0;
        }
        std::cout << "\n\n\n";
        ai->Show();
        std::cout << "The Best res: " << TheBestRes << '\n';
        SaveNetwork();*/

        controlChekMaxValue = controlChek;
        while (percent > controlChek)
        {
            //if (areAllValuesEqual(listValueForEditStruct) && listValueForEditStruct.size() == counterForEditStruct)
            //{
            //    generation++;
            //    listValueForEditStruct.clear();
            //    std::cout << "ArchitectureGenerator\n";
            //    std::vector<std::shared_ptr<Graf>> arrAI = ArchitectureGenerator(ai, nameFile);
            //    std::vector<float> res;
            //    std::shared_ptr<Graf> temp;
            //    float theBestRes = 0;
            //    std::cout << "Number Generation: " << mainCounterForEditStruct << "\n\n";
            //    for (size_t i = 0; i < arrAI.size(); i++)
            //    {
            //        float tempCycel = testCycle(arrAI[i], nameFile);
            //        for (size_t j = 0; j < counterIteration; j++)
            //        {
            //            tempCycel = (tempCycel + testCycle(arrAI[i], nameFile)) / 2;
            //        }
            //        arrAI[i]->Show();
            //        std::cout << "Res: " << tempCycel << "\n\n\n";
            //        res.push_back(tempCycel);
            //    }
            //    for (size_t i = 0; i < res.size(); i++)
            //    {
            //        std::cout << "res: " << res[i] << '\t' << i << '\n';
            //        if (theBestRes < res[i])
            //        {
            //            theBestRes = res[i];
            //            temp = arrAI[i];
            //        }
            //    }
            //    std::cout << "\n\n\n";
            //    temp->Show();
            //    temp->SaveNetwork("lalalala.txt");
            //    std::cout << "The Best res: " << theBestRes << '\n';
            //    ai = temp;
            //    res.clear();
            //    SaveNetwork();
            //    mainCounter = 0;
            //    mainCounterForEditStruct++;
            //}
            mainCounter++;
            controlChek = testCycle(nameFile);
            listValueForEditStruct.push_front(controlChek);
            if (controlChekMaxValue < controlChek)
            {
                std::shared_ptr<Graf> temp;
                std::cout << "=========================================================\nres: " << controlChek << "\t" << mainCounter << '\n' << "=========================================================\n";
                controlChekMaxValue = controlChek;
                std::string tempName;
                tempName = std::to_string(controlChek);
                tempName = tempName + ".txt";
                ai->SaveNetwork(tempName);
                ai->ClearMapTraing();
                ai->Clear();
                ai->CreateNetwork(tempName);
            }
            //else if (controlChekMaxValue == controlChek)
            //{
            //    std::cout << "res: " << controlChek << "\t" << mainCounter << '\n';
            //    controlChekMaxValue = controlChek;
            //    std::string tempName;
            //    tempName = std::to_string(controlChek);
            //    tempName = std::to_string(mainCounter)+ "-" + tempName + ".txt";
            //    ai->SaveNetwork(tempName);
            //}
            //if (listValueForEditStruct.size() > counterForEditStruct)
            //{
            //    listValueForEditStruct.pop_back();
            //}
            std::cout << "res: " << controlChek << "\t" << mainCounter << '\n';
        }
        std::cout << "finsh: " << mainCounter << '\n';
	}

	AI::AI(std::string nameProject, frame type)
	{
        nameProjectFile = nameProject + ".txt";
		Initialization(type);

        // Открываем файлы с сформированными именами
        std::ofstream AIFile(nameProjectFile, std::ios::out);
        AIFile.close();
	}

    AI::AI(std::string AIFile)
    {
        std::ifstream File(AIFile);
        char type;
        // Проверка, открылся ли файл успешно
        if (!File) {
            return;//Выход из функции
        }

        File.get(type);

        switch (type)
        {
        case 'P': Initialization(PERCEPTRON); break;
        case 'F':Initialization(FREENETWORK); break;
        default:return; break;
        }
        CreateNetwork(AIFile);
    }

    void AI::Logging()
    {

    }

    void AI::Test()
    {
        ai->Test();
    }
    
    std::string AI::getNameProject()
    {
        return nameProjectFile;
    }

	void AI::SaveNetwork()
	{
        if (!doCreate)
        {
            return;
        }
        ai->SaveNetwork();
	}
}