#include "AI.h"
namespace ai
{
	void AI::Initialization(frame type)
	{
		switch (type)
		{
		case 0: ai = std::make_shared<perceptron>(nameProjectFile, nameProjectLogFile); break;
		case 1: ai = std::make_shared<freeNetwork>(nameProjectFile, nameProjectLogFile); break;
		default:break;
		}
	}

    void AI::CreateNetwork(size_t amountInVertex, size_t amountOutVertex, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
    {
        if (doCreate)
            return;

        ai->CreateNetwork(amountInVertex, amountOutVertex, activationFuncPtr, activationOutFuncPtr);

        doCreate = 1;
    }

    void AI::CreateNetwork(std::string nameFile, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
    {
        if (doCreate)
            return;

        nameProjectFile = nameFile;
        nameProjectLogFile = "AI-" + nameFile + " LOG " + GetLocalTime() + ".txt";

        ai->CreateNetwork(nameFile, activationFuncPtr, activationOutFuncPtr);

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

	void AI::DatasetTraining(std::string nameFile, float percent)
	{
        if (percent > 100 || percent == 0 || nameFile.size() == 0 || (!doCreate))
            return;

        float percentResult = 0;
        std::ifstream DATASetFile;
        std::string line;
        while (percent > percentResult)
        {
            DATASetFile.open(nameFile);
            float counter = 0;
            percentResult = 0;
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
                auto res = Computation(value);
                if (result == res)
                {
                    ai->Training(1);
                    percentResult++;
                }
                else
                {
                    ai->Training(0);
                }
                counter++;
                Value.clear();
                Result.clear();
                value.clear();
                result.clear();
            }
            percentResult = (percentResult / counter) * 100;
            DATASetFile.close();
            ai->Logging(nameProjectLogFile);
        }
	}

	AI::AI(std::string nameProject, frame type)
	{
        std::string time = GetLocalTime();
        nameProjectFile = "AI-" + nameProject + ".txt";
        nameProjectLogFile = "AI-" + nameProject + " LOG " + time + ".txt";

		Initialization(type);

        // Открываем файлы с сформированными именами
        std::ofstream AIFile(nameProjectFile, std::ios::out);
        std::ofstream LogFile(nameProjectLogFile, std::ios::out);
        AIFile.close();
        LogFile.close();
	}

    AI::AI(std::string AIFile, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
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
        CreateNetwork(AIFile, activationFuncPtr, activationOutFuncPtr);
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