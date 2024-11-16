#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Controller.h"

class GradingModule
{
public:
    void gradeSolution(const std::string &problemConfigPath, const std::string &userSolutionPath);

private:
    bool loadConfig(const std::string &path, nlohmann::json &config);
    bool runTestCase(Controller &controller, const nlohmann::json &testCase);
    Controller controller;
};
