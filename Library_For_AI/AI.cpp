#include "AI.h"
namespace ai
{
	void AI::Initialization(frame type)
	{
        this->type = type;
		switch (type)
		{
		case 0: ai = std::make_shared<perceptron>(nameProjectFile); break;
		case 1: ai = std::make_shared<freeNetwork>(nameProjectFile); break;
		default:break;
		}
	}

    std::shared_ptr<Graf> AI::Initialization()
    {
        switch (type)
        {
        case 0: tryAi = std::make_shared<perceptron>(nameProjectFile); break;
        case 1: tryAi = std::make_shared<freeNetwork>(nameProjectFile); break;
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
        ai->SummarizeWeightSelection();
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
        test->SummarizeWeightSelection();
        return percentResult;
    }

    std::shared_ptr<Graf> AI::ArchitectureGenerator(std::shared_ptr<Graf> sampler, std::string nameFile)
    {
        auto amount = sampler->CounterCombination();
        float theBestRes = 0;
        std::vector<std::shared_ptr<Graf>> colisionesRes, tempColisionRes;
        std::shared_ptr<Graf> temp;
        for (int i = amount; i > 0; --i)
        {
            tryAi = Initialization();
            tryAi->TryArchitecture(i);

            float tempCycel = testCycle(tryAi, nameFile);
            for (size_t j = 0; j < amount; j++)
            {
                tempCycel = (tempCycel + testCycle(tryAi, nameFile)) / 2;
            }
            if (theBestRes < tempCycel)
            {
                theBestRes = tempCycel;
                temp = tryAi;
                colisionesRes.clear();
            }
            if (theBestRes == tempCycel)
            {
                colisionesRes.push_back(tryAi);
            }
        }

        while (colisionesRes.size() >= 1)
        {
            tempColisionRes = colisionesRes;
            for (auto pair : colisionesRes)
            {
                float tempCycel = testCycle(pair, nameFile);
                for (size_t j = 0; j < amount; j++)
                {
                    tempCycel = (tempCycel + testCycle(pair, nameFile)) / 2;
                }
                if (theBestRes < tempCycel)
                {
                    theBestRes = tempCycel;
                    temp = pair;
                    tempColisionRes.clear();
                }
                if (theBestRes == tempCycel)
                {
                    tempColisionRes.push_back(pair);
                }
            }
            colisionesRes = tempColisionRes;
        }

        return temp;
    }

    void AI::SelectionOfWeights(bool res)
    {
        if (!doCreate)
        {
            return;
        }
        ai->SelectionOfWeights(res);
    }

    void AI::DatasetTrainingDetailed(std::string nameFile, float percent)
    {
        //std::list<float> listValueForEditStruct;
        //listValueForEditStruct.push_front(controlChek);
        //сделать слияние разных вариантов файлов, так чтобы все ребра были средним значением
        //if (controlChekMaxValue < controlChek)
        //{
        //    std::shared_ptr<Graf> temp;
        //    std::cout << "=========================================================\nres: " << controlChek << "\t" << mainCounter << '\n' << "=========================================================\n";
        //    controlChekMaxValue = controlChek;
        //    std::string tempName;
        //    tempName = std::to_string(controlChek);
        //    tempName = tempName + ".txt";
        //    ai->SaveNetwork(tempName);
        //    ai->CreateNetwork(tempName);
        //}
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
        //std::cout << "res: " << controlChek << "\t" << mainCounter << '\n';

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
    }

	void AI::DatasetTrainingRough(std::string nameFile, float percent)
	{
        if (percent > 100 || percent == 0 || nameFile.size() == 0 || (!doCreate))
            return;

        unsigned int mainCounterForEditStruct = 0, mainCounter = 0;
        float controlChek = 0;

        ai = ArchitectureGenerator(ai, nameFile);

        while (percent > controlChek)
        {
            mainCounter++;
            controlChek = testCycle(nameFile);
            std::cout << mainCounter << '\t' << controlChek << '\n';
        }
        std::cout << "finsh: " << mainCounter << '\n';
	}

	AI::AI(std::string nameProject, frame type)
	{
        nameProjectFile = nameProject + ".txt";
		Initialization(type);

        //Открываем файлы с сформированными именами
        std::ofstream AIFile(nameProjectFile, std::ios::out);
        AIFile.close();
	}

    AI::AI(std::string AIFile)
    {
        std::ifstream File(AIFile);
        char type;
        //Проверка, открылся ли файл успешно
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
        log = std::make_shared<LogManager>("LOG" + nameProjectFile);
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