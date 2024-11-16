// src/main.cpp
#include "Controller.h"
#include <iostream>

int main()
{
    std::string sourceFile = "sample/sample.asm";
    std::string objFile = "sample/sample.obj";
    bool debugMode = false;

    Controller controller;
    controller.assembleAndRun(sourceFile, objFile, debugMode);

    return 0;
}
