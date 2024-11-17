#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "GradingModule.h"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

using json = nlohmann::json;

const std::string PROGRESS_FILE = "progress.json";
const int NUM_PROBLEMS = 12; // 문제 개수 수정

// 진행 상태를 초기화하는 함수
void initializeProgress(std::vector<bool> &progress)
{
    progress.assign(NUM_PROBLEMS, false);
    std::ofstream file(PROGRESS_FILE);
    if (file.is_open())
    {
        json progressData = {{"completed", progress}};
        file << progressData.dump(4);
        file.close();
    }
}

// 진행 상태를 로드하는 함수
void loadProgress(std::vector<bool> &progress)
{
    std::ifstream file(PROGRESS_FILE);
    if (file.is_open())
    {
        json progressData;
        file >> progressData;
        if (progressData.contains("completed") && progressData["completed"].size() == NUM_PROBLEMS)
        {
            progress = progressData["completed"].get<std::vector<bool>>();
        }
        else
        {
            initializeProgress(progress);
        }
        file.close();
    }
    else
    {
        initializeProgress(progress);
    }
}

// 진행 상태를 저장하는 함수
void saveProgress(const std::vector<bool> &progress)
{
    std::ofstream file(PROGRESS_FILE);
    if (file.is_open())
    {
        json progressData = {{"completed", progress}};
        file << progressData.dump(4);
        file.close();
    }
}

// 파일 복사 함수
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
    std::vector<bool> progress;
    loadProgress(progress);

    while (true)
    {
        // 현재 진행 상태 출력
        std::cout << "\n"
                  << BOLD << CYAN << "===== LC-3 문제 기반 학습 프로그램 =====" << RESET << "\n";
        std::cout << "완료 상태:\n";
        for (size_t i = 0; i < NUM_PROBLEMS; ++i)
        {
            std::cout << (progress[i] ? GREEN : RED)
                      << "문제 " << (i + 1) << ": "
                      << (progress[i] ? "완료" : "미완료")
                      << RESET << "\n";
        }

        // 메뉴 출력
        std::cout << BOLD << CYAN << "\n[문제 목록]" << RESET << "\n";
        std::cout << YELLOW;
        std::cout << "1. R0에 R1 + R2의 값을 저장\n";
        std::cout << "2. R0에 R1 AND R2의 값을 저장\n";
        std::cout << "3. R0이 R1보다 크면 R2에 1을 저장\n";
        std::cout << "4. R0의 절댓값 계산\n";
        std::cout << "5. 배열의 합 계산\n";
        std::cout << "6. 메모리에서 최대값 찾기\n";
        std::cout << "7. 팩토리얼 계산\n";
        std::cout << "8. 피보나치 수열 계산\n";
        std::cout << "9. 함수 호출로 덧셈 구현\n";
        std::cout << "10. 재귀적 팩토리얼 계산\n";
        std::cout << "11. 문자열 길이 계산\n";
        std::cout << "12. 버블 정렬\n";
        std::cout << "99. 진행도 초기화\n";
        std::cout << "0. 종료\n"
                  << RESET;

        // 사용자 입력
        std::cout << BOLD << "선택할 옵션 번호를 입력하세요: " << RESET;
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0)
        {
            if (std::all_of(progress.begin(), progress.end(), [](bool p)
                            { return p; }))
            {
                std::cout << BOLD << GREEN << "모든 문제를 완료했습니다! 축하합니다!" << RESET << "\n";
            }
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        if (choice == 99)
        {
            initializeProgress(progress);
            std::cout << GREEN << "진행도를 초기화했습니다.\n"
                      << RESET;
            continue;
        }

        if (choice < 1 || choice > NUM_PROBLEMS)
        {
            std::cout << RED << "유효하지 않은 선택입니다. 다시 시도하세요.\n"
                      << RESET;
            continue;
        }

        int problemIndex = choice - 1;

        // 문제 경로
        std::string problemDir = "problems/problem" + std::to_string(choice);
        std::string problemConfigPath = problemDir + "/problem" + std::to_string(choice) + ".json";
        std::string skeletonPath = problemDir + "/problem" + std::to_string(choice) + ".asm";

        // 스켈레톤 코드 복사
        if (!copyFile(skeletonPath, "answer.asm"))
        {
            std::cerr << RED << "스켈레톤 코드를 복사하는 데 실패했습니다.\n"
                      << RESET;
            continue;
        }
        std::cout << GREEN << "스켈레톤 파일이 answer.asm으로 복사되었습니다. 문제를 푸세요.\n"
                  << RESET;

        // 채점 실행
        grader.gradeSolution(problemConfigPath, "answer.asm");

        // 문제 완료 상태 갱신
        if (grader.isSolutionCorrect())
        {
            progress[problemIndex] = true;
            saveProgress(progress);
        }
    }

    return 0;
}
