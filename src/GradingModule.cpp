#include "GradingModule.h"
#include <fstream>
#include <iostream>
#include <regex>

using json = nlohmann::json;

GradingModule::GradingModule() : solutionCorrect(false) {}

bool GradingModule::loadConfig(const std::string &path, json &config)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        return false;
    }
    file >> config;
    return true;
}

void GradingModule::gradeSolution(const std::string &problemConfigPath, const std::string &userSolutionPath)
{
    json problemConfig;
    if (!loadConfig(problemConfigPath, problemConfig))
    {
        std::cerr << "[오류] 문제 설정 파일 로드 실패: " << problemConfigPath << std::endl;
        solutionCorrect = false;
        return;
    }

    std::cout << "\n[문제 설명]\n"
              << std::regex_replace(problemConfig["description"].get<std::string>(), std::regex("\\\\n"), "\n")
              << "\n";

    std::cout << "코드를 작성한 후 Enter 키를 눌러 채점을 시작합니다...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    controller.assemble(userSolutionPath, "user_solution.obj");

    solutionCorrect = true;
    for (const auto &testCase : problemConfig["testCases"])
    {
        controller.reset();
        controller.disableDebugMode();
        controller.loadProgram("user_solution.obj");

        if (!controller.checkSuccess())
        {
            std::cerr << "[오류] 어셈블 또는 실행 중 오류 발생\n";
            solutionCorrect = false;
            break;
        }

        if (!runTestCase(controller, testCase))
        {
            solutionCorrect = false;
        }
    }

    if (solutionCorrect)
    {
        std::cout << "\n모든 테스트 케이스를 통과했습니다! 잘하셨습니다!\n";
    }
    else
    {
        std::cout << "\n일부 테스트 케이스를 통과하지 못했습니다.\n";
    }
}

bool GradingModule::runTestCase(Controller &controller, const json &testCase)
{
    // 초기 레지스터 설정
    if (testCase.contains("registers"))
    {
        for (const auto &it : testCase["registers"].items())
        {
            unsigned short regIndex = std::stoi(it.key().substr(1));
            unsigned short value = it.value().is_string() && it.value().get<std::string>().substr(0, 2) == "0x"
                                       ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>().substr(2), nullptr, 16))
                                       : static_cast<unsigned short>(it.value().get<int>());
            controller.setRegister(regIndex, value);
        }
    }

    // 초기 메모리 설정
    if (testCase.contains("memory"))
    {
        for (const auto &it : testCase["memory"].items())
        {
            unsigned short address = static_cast<unsigned short>(std::stoul(it.key().substr(2), nullptr, 16));
            unsigned short value = it.value().is_string() && it.value().get<std::string>().substr(0, 2) == "0x"
                                       ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>().substr(2), nullptr, 16))
                                       : static_cast<unsigned short>(it.value().get<int>());
            controller.setMemory(address, value);
        }
    }

    controller.runProgram();

    if (!controller.checkSuccess())
    {
        std::cerr << "[오류] 프로그램 실행 중 오류 발생\n";
        return false;
    }

    // 예상값 검증
    bool passed = true;
    if (testCase.contains("expected"))
    {
        for (const auto &it : testCase["expected"].items())
        {
            unsigned short expected = it.value().is_string() && it.value().get<std::string>().substr(0, 2) == "0x"
                                          ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>().substr(2), nullptr, 16))
                                          : static_cast<unsigned short>(it.value().get<int>());

            if (it.key()[0] == 'R')
            {
                unsigned short regIndex = std::stoi(it.key().substr(1));
                unsigned short actual = controller.getRegister(regIndex);
                if (actual != expected)
                {
                    std::cerr << "[테스트 실패] R" << regIndex << " 예상 값: " << expected
                              << " 실제 값: " << actual << "\n";
                    passed = false;
                }
            }
            else
            {
                unsigned short address = static_cast<unsigned short>(std::stoul(it.key().substr(2), nullptr, 16));
                unsigned short actual = controller.getMemory(address);
                if (actual != expected)
                {
                    std::cerr << "[테스트 실패] 메모리[" << it.key() << "] 예상 값: " << expected
                              << " 실제 값: " << actual << "\n";
                    passed = false;
                }
            }
        }
    }

    return passed;
}

bool GradingModule::isSolutionCorrect() const
{
    return solutionCorrect;
}
