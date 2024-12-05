#include "AI.h"
namespace ai
{
	void AI::Initialization(frame type, howOpen typeConvert)
	{
        typeArchitecture = type;
		switch (type)
		{
		case 0: ai = std::make_shared<perceptron>(nameProjectFile, typeConvert); break;
		case 1: ai = std::make_shared<freeNetwork>(nameProjectFile, typeConvert); break;
		default:break;
		}
	}

    std::shared_ptr<Graf> AI::Initialization()
    {
        switch (typeArchitecture)
        {
        case 0: tryAi = std::make_shared<perceptron>(nameProjectFile, openingType); break;
        case 1: tryAi = std::make_shared<freeNetwork>(nameProjectFile, openingType); break;
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

	std::list<NWDT> AI::Computation(std::list<NWDT> vaules)
	{
		if (!doCreate)
		{
			std::list<NWDT> result;
			return result;
		}
		return ai->Computation(vaules);
	}

    float AI::testCycle(std::list<std::list<NWDT>> DataSetList, std::list<std::list<NWDT>> Answer)
    {
        if (DataSetList.size() != Answer.size())
            return -1;

        float percentResult = 0;
        float counter = 0;
        bool isNotEnd = true;
        for (std::list<std::list<NWDT>>::iterator data = DataSetList.begin(),
            answer = Answer.begin(); isNotEnd; data++, answer++)
        {
            auto temp = Computation(*data);
            if (temp == *answer)
            {
                counter++;
                ai->SelectionOfWeights(1);
            }
            else
            {
                counter = 0;
                answer = Answer.begin();
                data = DataSetList.begin();
                ai->SelectionOfWeights(0);
            }

            //выход из алгоритма если все совпадает
            if (counter == DataSetList.size())
            {
                isNotEnd = false;
            }
        }
        percentResult = (counter / DataSetList.size()) * 100;
        return percentResult;
    }

    float AI::testCycle(std::shared_ptr<Graf> test, std::list<std::list<NWDT>> DataSetList, std::list<std::list<NWDT>> Answer)
    {
        return 0;
    }

    //void AI::DataSetFolder(std::string nameFolder, float percent)
    //{
    //    std::list<std::list<NWDT>> DataSetList, AnswerList;
    //    std::filesystem::path folderPath(nameFolder);
    //    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath))
    //    {
    //        std::cerr << "Folder does not exist or is not a directory" << std::endl;
    //        return;
    //    }
    //    // Итерируемся по файлам в папке
    //    for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    //    {
    //        std::filesystem::path filePath = entry.path();
    //        std::string fileName = filePath.filename().string();
    //        // Проверка, что файл начинается с "Data-" для датасета
    //        if (fileName.find("Data-") == 0)
    //        {
    //            // Создаем путь для файла ответа
    //            std::filesystem::path answerFilePath = folderPath / ("Answ-" + filePath.stem().string().substr(5) + filePath.extension().string());
    //            // Читаем файлы побитово как данные для DataSet и Answer
    //            auto dataList = DataFileConverter(filePath.string(), amountIn);
    //            auto answerList = DataFileConverter(answerFilePath.string(), amountOut);
    //            DataSetList.push_back(dataList);
    //            AnswerList.push_back(answerList);
    //        }
    //    }
    //    // Проводим тестирование на основе прочитанных данных
    //    auto temp = testCycle(DataSetList, AnswerList);
    //    while (percent > temp)
    //    {
    //        temp = testCycle(DataSetList, AnswerList);
    //    }
    //}

    void AI::DataSetFolder(std::string nameFolder, std::list<std::list<NWDT>>& Data)
    {
        std::filesystem::path folderPath(nameFolder);
        if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath))
        {
            std::cerr << "Folder does not exist or is not a directory" << std::endl;
            return;
        }
        // Итерируемся по файлам в папке
        for (const auto& entry : std::filesystem::directory_iterator(folderPath))
        {
            std::filesystem::path filePath = entry.path();
            std::string fileName = filePath.filename().string();
            // Проверка, что файл начинается с "Data-" для датасета
            if (fileName.find("Data-") == 0)
            {
                // Читаем файлы побитово как данные для DataSet и Answer
                auto dataList = DataFileConverter(filePath.string(), amountIn);
                Data.push_back(dataList);
            }
        }
    }

    //void AI::DataSetFile(std::string nameFile, float percent)
    //{
    //    std::string line;
    //    std::ifstream DATASetFile;
    //    DATASetFile.open(nameFile);
    //    std::list<std::list<NWDT>> DataSetList, AnswerList;
    //    while (std::getline(DATASetFile, line)) {
    //        std::string Value = line.substr(0, line.find(' '));
    //        std::string Result = line.substr(Value.size() + 1);
    //        std::vector<char> tempV(Value.begin(), Value.end()), tempA(Result.begin(), Result.end());
    //        DataSetList.push_back(DataBlockConverter(tempV, amountIn));
    //        AnswerList.push_back(DataBlockConverter(tempA, amountOut));
    //    }
    //    auto temp = testCycle(DataSetList, AnswerList);
    //    while (percent > temp)
    //    {
    //        temp = testCycle(DataSetList, AnswerList);
    //    }
    //}

    void AI::DataSetFile(std::string nameFile, std::list<std::list<NWDT>>& Data)
    {
        std::string line;
        std::ifstream DATASetFile;
        DATASetFile.open(nameFile);
        while (std::getline(DATASetFile, line)) {
            std::vector<char> tempV(line.begin(), line.end());
            Data.push_back(DataBlockConverter(tempV, amountIn));
        }
    }

    std::list<NWDT> AI::DataFileConverter(std::string nameFile, int maxBlocks)
    {
        std::ifstream file(nameFile, std::ios::binary);
        std::list<NWDT> doubles;

        if (!file)
            return doubles;

        const std::size_t blockSize = sizeof(NWDT);
        std::vector<char> buffer(blockSize);
        unsigned int blocksRead = 0;
        std::streamsize bytesRead;
        double value;
        while (file.read(buffer.data(), blockSize) && blocksRead < maxBlocks) {
            bytesRead = file.gcount();
            if (bytesRead == blockSize) {
                std::memcpy(&value, buffer.data(), blockSize);
                doubles.push_back(value);
            }
            else {
                std::vector<char> incompleteBlock(blockSize, 0);
                std::memcpy(incompleteBlock.data(), buffer.data(), bytesRead);

                std::memcpy(&value, incompleteBlock.data(), blockSize);
                doubles.push_back(value);
                break;
            }
            ++blocksRead;
        }
        return doubles;
    }

    std::list<NWDT> AI::DataBlockConverter(std::vector<char> data, int maxBlocks)
    {
        std::list<NWDT> doubles;

        const std::size_t blockSize = sizeof(NWDT);
        unsigned int blocksRead = 0;
        std::streamsize bytesRead;
        double value;
        std::size_t totalSize = data.size();
        std::size_t currentPos = 0;

        while (currentPos + blockSize <= totalSize && blocksRead < maxBlocks) {
            std::vector<char> buffer(data.begin() + currentPos, data.begin() + currentPos + blockSize);
            std::memcpy(&value, buffer.data(), blockSize);
            doubles.push_back(value);

            currentPos += blockSize;
            ++blocksRead;
        }

        if (currentPos < totalSize && blocksRead < maxBlocks) {
            std::size_t remainingBytes = totalSize - currentPos;
            std::vector<char> incompleteBlock(blockSize, 0); 
            std::memcpy(incompleteBlock.data(), data.data() + currentPos, remainingBytes);

            std::memcpy(&value, incompleteBlock.data(), blockSize);
            doubles.push_back(value);
        }

        return doubles;
    }

    void ai::AI::DatasetTraining(std::string dataIn, std::string dataOut, float percent, howOpen type)
    {
        std::list<std::list<NWDT>> DataSetList, AnswerList;
        type = openingType;
        switch (type)
        {
        case ai::DATA_DATA:DataSetFile(dataIn, DataSetList); DataSetFile(dataOut, AnswerList);break;
        case ai::DATA_FILE:DataSetFile(dataIn, DataSetList); DataSetFolder(dataOut, AnswerList);break;
        case ai::FILE_DATA:DataSetFolder(dataIn, DataSetList); DataSetFile(dataOut, AnswerList);break;
        case ai::FILE_FILE:DataSetFolder(dataIn, DataSetList); DataSetFolder(dataOut, AnswerList);break;
        default:break;
        }
        auto temp = testCycle(DataSetList, AnswerList);
        while (percent > temp)
        {
            temp = testCycle(DataSetList, AnswerList);
        }
    }

	AI::AI(std::string nameProject, frame type, howOpen typeConvert)
	{
        nameProjectFile = nameProject + ".txt";
        openingType = typeConvert;
		Initialization(type, typeConvert);

        //Открываем файлы с сформированными именами
        std::ofstream AIFile(nameProjectFile, std::ios::out);
        AIFile.close();
	}

    AI::AI(std::string AIFile)
    {
        std::ifstream File(AIFile);

        
        char type, typeOpen;
        //Проверка, открылся ли файл успешно
        if (!File) {
            return;//Выход из функции
        }

        File.get(typeOpen);

        switch (typeOpen)
        {
        case '1': openingType = DATA_DATA; break;
        case '2': openingType = DATA_FILE; break;
        case '3': openingType = FILE_DATA; break;
        case '4': openingType = FILE_FILE; break;
        default: break;
        }
        File.get(type);//пропустить символ перехода на новою строку
        File.get(type);

        switch (type)
        {
        case 'P': Initialization(PERCEPTRON, openingType); break;
        case 'F':Initialization(FREENETWORK, openingType); break;
        default:return; break;
        }
        CreateNetwork(AIFile);
        amountIn = ai->amountIn;
        amountOut = ai->amountOut;
    }

    void AI::Logging()
    {
        log = std::make_shared<LogManager>("LOG" + nameProjectFile);
    }

    void AI::Test()
    {
        ai->Test();
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