#ifndef GRADINGMODULE_H
#define GRADINGMODULE_H

#include <string>
#include <nlohmann/json.hpp>
#include "Controller.h"

class GradingModule
{
private:
    bool solutionCorrect; // 문제 정답 여부
    Controller controller;

public:
    GradingModule();

    // JSON 파일 로드
    bool loadConfig(const std::string &path, nlohmann::json &config);

    // 채점 수행
    void gradeSolution(const std::string &problemConfigPath, const std::string &userSolutionPath);

    // 정답 여부 확인
    bool isSolutionCorrect() const;

    // 테스트 케이스 실행
    bool runTestCase(Controller &controller, const nlohmann::json &testCase);
};

#endif // GRADINGMODULE_H
