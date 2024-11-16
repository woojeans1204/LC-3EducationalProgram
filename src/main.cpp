#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h> // 파일 존재 여부 확인
#ifdef _WIN32
#include <direct.h> // Windows에서 디렉토리 생성
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include "GradingModule.h"

bool fileExists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool copyFile(const std::string &srcPath, const std::string &destPath)
{
    std::ifstream src(srcPath, std::ios::binary);
    std::ofstream dest(destPath, std::ios::binary);
    if (!src.is_open() || !dest.is_open())
    {
        return false;
    }
    dest << src.rdbuf();
    return true;
}

int main()
{
    GradingModule grader;

    while (true)
    {
        // 문제 목록 표시
        std::cout << "\n===== LC-3 문제 기반 학습 프로그램 =====\n";
        std::cout << "1. R0에 R1 + R2의 값을 저장\n";
        std::cout << "2. R0에 R1 AND R2의 값을 저장\n";
        std::cout << "0. 종료\n";
        std::cout << "선택할 문제 번호를 입력하세요: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // 입력 버퍼 비우기

        if (choice == 0)
        {
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        std::string problemConfigPath;
        std::string skeletonPath;

        if (choice == 1)
        {
            problemConfigPath = "problems/problem1.json";
            skeletonPath = "problems/problem1.asm";
        }
        else if (choice == 2)
        {
            problemConfigPath = "problems/problem2.json";
            skeletonPath = "problems/problem2.asm";
        }
        else
        {
            std::cout << "유효하지 않은 선택입니다. 다시 시도하세요.\n";
            continue;
        }

        // 항상 스켈레톤 코드 복사
        if (!copyFile(skeletonPath, "answer.asm"))
        {
            std::cerr << "스켈레톤 코드를 복사하는 데 실패했습니다.\n";
            continue;
        }
        std::cout << "스켈레톤 파일이 answer.asm으로 복사되었습니다. 문제를 푸세요.\n";

        // 채점 실행
        grader.gradeSolution(problemConfigPath, "answer.asm");

        // 다시 문제를 풀지 여부 확인
        std::cout << "다른 문제를 푸시겠습니까? (y/n): ";
        char retry;
        std::cin >> retry;
        std::cin.ignore(); // 입력 버퍼 비우기
        if (retry == 'n' || retry == 'N')
        {
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }
    }

    return 0;
}
