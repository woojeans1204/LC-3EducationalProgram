#include "GradingModule.h"
#include <iostream>
#include <fstream>
#include <regex>

using json = nlohmann::json;

void GradingModule::gradeSolution(const std::string &problemConfigPath, const std::string &userSolutionPath)
{
    // 1. JSON 파일 로드
    json problemConfig;
    if (!loadConfig(problemConfigPath, problemConfig))
    {
        std::cerr << "문제 설정 파일 로드 실패: " << problemConfigPath << "\n";
        return;
    }

    // 2. 문제 설명 출력
    std::cout << "\n===== 문제 설명 =====\n"
              << std::regex_replace(problemConfig["description"].get<std::string>(), std::regex("\\\\n"), "\n")
              << "\n====================\n";
    std::cout << "문제를 풀기 위해 " << userSolutionPath << " 파일을 작성하세요.\n";

    // 3. 사용자에게 Enter 키를 눌러 채점을 시작하도록 안내
    std::cout << "코드를 작성한 후, Enter 키를 눌러 채점을 시작하세요...";
    std::cin.ignore();
    std::cin.get();

    // 4. 테스트 케이스 반복 실행
    bool allPassed = true;
    controller.assemble(userSolutionPath, "user_solution.obj");

    for (const auto &testCase : problemConfig["testCases"])
    {
        // 에뮬레이터 리셋 및 프로그램 재로드
        controller.reset();
        controller.disableDebugMode();
        controller.loadProgram("user_solution.obj");

        if (!controller.checkSuccess())
        {
            std::cerr << "어셈블 또는 실행 중 오류가 발생했습니다.\n";
            allPassed = false;
            break;
        }

        // 테스트 실행
        if (!runTestCase(controller, testCase))
        {
            allPassed = false;
        }
    }

    if (allPassed)
    {
        std::cout << "\033[1;32m모든 테스트 케이스를 통과했습니다!\033[0m\n";
    }
    else
    {
        std::cout << "\033[1;31m일부 테스트 케이스를 통과하지 못했습니다.\033[0m\n";
    }
}

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

bool GradingModule::runTestCase(Controller &controller, const json &testCase)
{
    // 레지스터 초기화
    if (testCase.contains("registers"))
    {
        for (auto it = testCase["registers"].begin(); it != testCase["registers"].end(); ++it)
        {
            std::string reg = it.key();
            unsigned short value = it.value().is_string()
                                       ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>(), nullptr, 16))
                                       : it.value().get<unsigned short>();
            unsigned short regIndex = std::stoi(reg.substr(1)); // "R1" -> 1
            controller.setRegister(regIndex, value);
        }
    }

    // 메모리 초기화 (필요 시)
    if (testCase.contains("memory"))
    {
        for (auto it = testCase["memory"].begin(); it != testCase["memory"].end(); ++it)
        {
            unsigned short addr = static_cast<unsigned short>(std::stoul(it.key(), nullptr, 16)); // "0x3000" -> 0x3000
            unsigned short value = it.value().is_string()
                                       ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>(), nullptr, 16))
                                       : it.value().get<unsigned short>();
            controller.setMemory(addr, value);
        }
    }

    // 프로그램 실행
    controller.runProgram();
    if (!controller.checkSuccess())
    {
        std::cerr << "프로그램 실행 중 오류가 발생했습니다.\n";
        return false;
    }

    // 결과 검증
    bool passed = true;
    for (auto it = testCase["expected"].begin(); it != testCase["expected"].end(); ++it)
    {
        std::string target = it.key();
        unsigned short expected = it.value().is_string()
                                      ? static_cast<unsigned short>(std::stoul(it.value().get<std::string>(), nullptr, 16))
                                      : it.value().get<unsigned short>();

        if (target[0] == 'R')
        { // 레지스터 값 검증
            unsigned short regIndex = std::stoi(target.substr(1));
            unsigned short actual = controller.getRegister(regIndex);
            if (actual != expected)
            {
                std::cerr << "테스트 실패: " << target << " 값이 예상(" << expected
                          << ")과 다릅니다. 실제 값: " << actual << "\n";
                passed = false;
            }
        }
        else
        { // 메모리 값 검증
            unsigned short addr = static_cast<unsigned short>(std::stoul(target, nullptr, 16));
            unsigned short actual = controller.getMemory(addr);
            if (actual != expected)
            {
                std::cerr << "테스트 실패: 메모리[" << target << "] 값이 예상(" << expected
                          << ")과 다릅니다. 실제 값: " << actual << "\n";
                passed = false;
            }
        }
    }

    return passed;
}
