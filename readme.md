# LC-3 Educational Program

## 프로젝트 개요

**LC-3 Educational Program**은 LC-3 어셈블리 언어 학습을 위한 단계적 문제 풀이 환경을 제공합니다. 이 프로젝트는 LC-3 명령어 집합과 메모리 구조를 기반으로, 사용자가 문제를 해결하며 어셈블리 언어의 기본 개념과 고급 프로그래밍 기법을 자연스럽게 익힐 수 있도록 설계되었습니다.

주요 목표는 사용자 친화적인 학습 환경을 제공하고, 자동 채점 시스템을 통해 효율적인 학습 진행을 관리하며, 학습자의 코드 디버깅과 개선을 돕는 것입니다.

---

## 주요 기능

1. **문제 기반 학습**

   - 문제마다 스켈레톤 코드와 테스트 케이스 제공.
   - 단계별 학습 목표에 맞춘 문제 구성.

2. **자동 채점 시스템**

   - 사용자가 작성한 코드를 테스트 케이스와 비교하여 결과를 평가.
   - 예상 출력과 실제 결과를 비교해 디버깅 정보 제공.

3. **학습 진행 관리**

   - 학습 진행 상태를 `progress.json`에 저장하여 추적 가능.
   - 완료된 문제는 UI 상에서 "완료"로 표시.

4. **LC-3 시뮬레이션 및 어셈블링**
   - LC-3 어셈블리 코드를 어셈블, 실행 및 디버깅 가능.

---

## 디렉터리 구조

```
📁 LC-3EducationalProgram
├── 📁 .git                     # Git 관련 파일
├── 📁 build                   # 빌드된 실행 파일 및 객체 파일
├── 📁 include                 # 프로젝트 헤더 파일
├── 📁 lib                     # LC-3 어셈블러 및 시뮬레이터 라이브러리
├── 📁 problems                # 문제와 테스트 케이스
├── 📁 solutions               # 문제별 솔루션 코드
├── 📁 src                     # 소스 코드
├── answer.asm                 # 사용자가 작성한 답안 코드
├── CMakeLists.txt             # CMake 빌드 설정 파일
├── LC3EducationalProgram.exe  # 실행 파일
├── progress.json              # 학습 진행 상태 저장 파일
└── readme.md                  # 프로젝트 설명 파일
```

---

## 디렉터리 설명

### 📁 `problems`

- **문제별 폴더 구성**
  - 각 폴더는 하나의 문제와 관련된 파일을 포함합니다:
    - `problemX.asm`: 스켈레톤 코드. 학습자가 작성해야 할 부분이 주석으로 표시되어 있습니다.
    - `problemX.json`: 문제의 테스트 케이스를 정의.

### 📁 `solutions`

- **문제 정답 코드**
  - 각 문제의 솔루션 코드가 포함되어 있으며, 채점 기준 설정 및 디버깅 시 참고 자료로 활용.

### 📁 `src`

- **핵심 소스 파일**
  - `Controller.cpp`: LC-3 어셈블러와 시뮬레이터의 인터페이스를 담당.
  - `GradingModule.cpp`: 문제 자동 채점 및 테스트 케이스 실행 로직.
  - `main.cpp`: 프로그램의 진입점.

### 📁 `lib`

- **LC-3 어셈블러 및 시뮬레이터 라이브러리**
  - LC-3 명령어 집합과 메모리 구조를 구현한 라이브러리.

---

## 빌드 및 실행

### **빌드**

- **CMake**를 사용하여 프로젝트를 빌드합니다:
  ```bash
  mkdir build
  cmake build
  cmake --build build
  ```

### **실행**

- 빌드된 실행 파일을 실행하여 학습 환경에 진입합니다:
  ```bash
  ./LC3EducationalProgram.exe
  ```

---

## 개발 중점 사항

1. **모듈화된 구조**

   - `Controller`, `GradingModule`, `LC3Simulator` 등으로 분리하여 유지보수성과 확장성 확보.

2. **사용자 편의성**

   - 스켈레톤 코드를 통해 학습자가 집중해야 할 영역을 명확히 구분.
   - 실패한 테스트 케이스의 디버깅 정보를 상세히 제공.

3. **테스트 케이스 기반 채점**

   - JSON 형식으로 테스트 케이스를 정의하여 간결하고 확장 가능한 구조 설계.
   - 초기 레지스터 값, 메모리 상태, 예상 출력 등을 명시적으로 관리.

4. **학습 진행 관리**
   - 사용자의 학습 상태를 `progress.json`에 저장하여 학습 경과를 추적.

---

## 향후 개선 방향

1. **GUI 지원**

   - 터미널 기반 환경에서 벗어나 GUI 환경을 추가하여 사용자 경험 개선.

2. **문제 난이도 분류**

   - 문제를 난이도별로 분류하여 학습 경로를 개인화.

3. **사용자 정의 문제 추가**

   - 사용자가 직접 문제와 테스트 케이스를 추가하고 채점 가능하도록 개선.

4. **코드 최적화 평가**
   - 작성된 코드의 효율성을 분석하고 피드백 제공.
