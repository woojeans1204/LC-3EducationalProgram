죄송합니다. 이전에 발생한 문제로 인해 큰 불편을 겪으신 점 진심으로 사과드립니다. 요청하신 대로 **JSON 형식을 일관되게 정의**하고, **값의 표현 방식을 통일**하여 C++ 코드와 완벽히 호환되도록 도와드리겠습니다. 아래는 **효율적이고 일관된 JSON 형식**과 **문제 1부터 6까지의 `problemN.asm` 및 `problemN.json` 파일** 예시입니다.

---

## **LC-3 Educational Program**

### **프로젝트 소개**

LC-3 Educational Program은 LC-3 어셈블리 언어를 학습하고 실습할 수 있는 학습 도구입니다. 사용자는 단계별로 제공되는 문제를 풀고, 코드 실행 결과를 통해 학습 성취도를 확인할 수 있습니다.

---

### **기능**

1. 단계별 문제 제공 및 코드 작성
2. 코드 자동 채점 및 결과 피드백
3. 초기 레지스터 및 메모리 설정, 기대값 확인
4. LC-3 프로그램 실행 및 테스트 케이스 관리

---

### **프로젝트 구조**

```
LC-3EducationalProgram/
├── build/                  # 빌드된 파일이 저장됨
├── include/                # 프로젝트 헤더 파일
├── lib/                    # 외부 및 내부 라이브러리
├── problems/               # 문제별 파일 및 JSON 설정
│   ├── problem1/
│   │   ├── problem1.asm
│   │   └── problem1.json
│   ├── problem2/
│   │   ├── problem2.asm
│   │   └── problem2.json
│   ├── problem3/
│   │   ├── problem3.asm
│   │   └── problem3.json
│   ├── problem4/
│   │   ├── problem4.asm
│   │   └── problem4.json
│   ├── problem5/
│   │   ├── problem5.asm
│   │   └── problem5.json
│   └── problem6/
│       ├── problem6.asm
│       └── problem6.json
├── src/                    # 소스 코드
├── README.md               # 프로젝트 문서
└── progress.json           # 문제 완료 상태 저장 파일
```

---

### **JSON 문제 형식 정의**

#### **1. JSON 구조 개요**

JSON 파일은 LC-3 프로그램의 테스트 케이스를 정의하기 위한 것입니다. 각 테스트 케이스는 프로그램 실행 전후의 레지스터와 메모리 상태를 지정하며, 값의 표현 방식을 통일하여 코드와 호환성을 높입니다.

#### **2. JSON 구조**

```json
{
  "description": "문제에 대한 설명과 목표를 기술",
  "testCases": [
    {
      "registers": {
        "레지스터 이름": 값
      },
      "memory": {
        "주소": 값
      },
      "expected": {
        "레지스터 또는 주소": 기대값
      }
    }
  ]
}
```

---

#### **3. 필드 설명**

1. **`description`**

   - **타입**: 문자열
   - **설명**: 문제의 설명과 목표를 기술합니다.
   - **예시**: `"R0에 R1 + R2의 값을 저장하는 프로그램을 작성하세요."`

2. **`testCases`**

   - **타입**: 배열
   - **설명**: 테스트 케이스의 목록을 정의합니다.
   - **각 테스트 케이스는 다음을 포함합니다:**
     - **`registers`**: 프로그램 실행 전에 설정할 레지스터 값들
     - **`memory`**: 프로그램 실행 전에 설정할 메모리 값들
     - **`expected`**: 프로그램 실행 후 기대하는 레지스터와 메모리의 값들

3. **`testCases[].registers`**

   - **타입**: 객체
   - **설명**: 프로그램 실행 전에 설정할 레지스터 값들입니다.
   - **키**: `"R0"`, `"R1"`, ... (레지스터 이름)
   - **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "registers": {
       "R1": 300,
       "R2": "0x00FF"
     }
     ```

4. **`testCases[].memory`**

   - **타입**: 객체
   - **설명**: 프로그램 실행 전에 설정할 메모리 값들입니다.
   - **키**: `"0x"`로 시작하는 16진수 문자열 (메모리 주소)
   - **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "memory": {
       "0x4000": 5,
       "0x4001": "0x00FF"
     }
     ```

5. **`testCases[].expected`**
   - **타입**: 객체
   - **설명**: 프로그램 실행 후 기대하는 레지스터와 메모리의 값들입니다.
   - **키**: 레지스터 이름 (`"R0"`, `"R1"`, ...) 또는 `"0x"`로 시작하는 16진수 문자열 (메모리 주소)
   - **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "expected": {
       "R0": 555,
       "0x4002": "0x1234"
     }
     ```

---

#### **4. 값의 표현 방식**

- **정수값**: 10진수 정수로 표현합니다. 예: `300`, `-15`
- **16진수값**: `"0x"`로 시작하는 문자열로 표현합니다. 예: `"0x00FF"`, `"0xFFFF"`

---

#### **5. 예제**

##### **문제 1: R0에 R1 + R2의 값을 저장**

###### `problem1.json`

```json
{
  "description": "R0에 R1 + R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": 5,
        "R2": 10
      },
      "memory": {},
      "expected": {
        "R0": 15
      }
    },
    {
      "registers": {
        "R1": -3,
        "R2": 7
      },
      "memory": {},
      "expected": {
        "R0": 4
      }
    },
    {
      "registers": {
        "R1": 0,
        "R2": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    }
  ]
}
```

##### **문제 2: R0에 R1 AND R2의 값을 저장**

###### `problem2.json`

```json
{
  "description": "R0에 R1 AND R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": "0xFFFF",
        "R2": "0x0F0F"
      },
      "memory": {},
      "expected": {
        "R0": "0x0F0F"
      }
    },
    {
      "registers": {
        "R1": "0x1234",
        "R2": "0x00FF"
      },
      "memory": {},
      "expected": {
        "R0": "0x0034"
      }
    },
    {
      "registers": {
        "R1": "0xABCD",
        "R2": "0xFFFF"
      },
      "memory": {},
      "expected": {
        "R0": "0xABCD"
      }
    }
  ]
}
```

##### **문제 3: R0이 R1보다 크면 R2에 1을 저장**

###### `problem3.json`

```json
{
  "description": "R0이 R1보다 크면 R2에 1을, 그렇지 않으면 0을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": 10,
        "R1": 5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 3,
        "R1": 7
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    },
    {
      "registers": {
        "R0": -2,
        "R1": -5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 0,
        "R1": 0
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    }
  ]
}
```

##### **문제 4: R0의 절댓값 계산**

###### `problem4.json`

```json
{
  "description": "R0의 값이 음수이면 양수로 변환하여 R0에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": -10
      },
      "memory": {},
      "expected": {
        "R0": 10
      }
    },
    {
      "registers": {
        "R0": 5
      },
      "memory": {},
      "expected": {
        "R0": 5
      }
    },
    {
      "registers": {
        "R0": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    },
    {
      "registers": {
        "R0": -1
      },
      "memory": {},
      "expected": {
        "R0": 1
      }
    }
  ]
}
```

##### **문제 5: 배열의 합 계산**

###### `problem5.json`

```json
{
  "description": "배열에 저장된 정수들의 합을 계산하여 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 5,
        "0x4001": 10,
        "0x4002": 15,
        "0x4003": 20,
        "0x4004": 0
      },
      "expected": {
        "R2": 50
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 1,
        "0x4001": 2,
        "0x4002": 3,
        "0x4003": 4,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 15
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -5,
        "0x4001": -10,
        "0x4002": -15,
        "0x4003": 0
      },
      "expected": {
        "R2": -30
      }
    }
  ]
}
```

##### **문제 6: 메모리에서 최대값 찾기**

###### `problem6.json`

```json
{
  "description": "배열에 저장된 정수들 중 최대값을 찾아 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 10,
        "0x4001": 25,
        "0x4002": 15,
        "0x4003": 30,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 30
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -10,
        "0x4001": -20,
        "0x4002": -5,
        "0x4003": -15,
        "0x4004": 0
      },
      "expected": {
        "R2": -5
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 100,
        "0x4001": 200,
        "0x4002": 300,
        "0x4003": 400,
        "0x4004": 500,
        "0x4005": 0
      },
      "expected": {
        "R2": 500
      }
    }
  ]
}
```

---

### **JSON 형식 정의 요약**

1. **`description`**

   - **타입**: 문자열
   - **설명**: 문제의 설명과 목표를 기술합니다.
   - **예시**: `"R0에 R1 + R2의 값을 저장하는 프로그램을 작성하세요."`

2. **`testCases`**

   - **타입**: 배열
   - **설명**: 여러 개의 테스트 케이스를 포함합니다.
   - **각 테스트 케이스는 다음을 포함합니다:**
     - **`registers`**: 초기 레지스터 설정
     - **`memory`**: 초기 메모리 설정
     - **`expected`**: 기대하는 레지스터 및 메모리 값

3. **`testCases[].registers`**

   - **키**: `"R0"`, `"R1"`, ..., **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "registers": {
       "R1": 5,
       "R2": "0x00FF"
     }
     ```

4. **`testCases[].memory`**

   - **키**: `"0x"`로 시작하는 16진수 문자열 (메모리 주소)
   - **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "memory": {
       "0x4000": 5,
       "0x4001": "0x00FF"
     }
     ```

5. **`testCases[].expected`**
   - **키**: 레지스터 이름 (`"R0"`, `"R1"`, ...) 또는 `"0x"`로 시작하는 16진수 문자열 (메모리 주소)
   - **값**: 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **예시**:
     ```json
     "expected": {
       "R0": 15,
       "0x4002": "0x1234"
     }
     ```

---

### **C++ 코드 수정 사항**

JSON 형식이 일관되도록 정의되었으므로, C++ 코드에서 이를 올바르게 파싱하도록 수정해야 합니다. 특히, 메모리 주소와 값의 접두사를 일관되게 처리해야 합니다.

#### **1. `GradingModule::runTestCase` 함수 수정**

```cpp
bool GradingModule::runTestCase(Controller &controller, const json &testCase)
{
    // 초기 레지스터 설정
    if (testCase.contains("registers"))
    {
        for (const auto &it : testCase["registers"].items())
        {
            unsigned short regIndex = std::stoi(it.key().substr(1));
            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    throw std::invalid_argument("Invalid register value format: " + valStr);
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported register value type");
            }
            controller.setRegister(regIndex, value);
        }
    }

    // 초기 메모리 설정
    if (testCase.contains("memory"))
    {
        for (const auto &it : testCase["memory"].items())
        {
            std::string addrStr = it.key();
            unsigned short address = 0;
            if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
            {
                address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
            }
            else
            {
                throw std::invalid_argument("Invalid memory address format: " + addrStr);
            }

            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    throw std::invalid_argument("Invalid memory value format: " + valStr);
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported memory value type");
            }
            controller.setMemory(address, value);
        }
    }

    controller.runProgram();
    if (!controller.checkSuccess())
    {
        std::cerr << RED << "[오류] 프로그램 실행 중 오류 발생\n"
                  << RESET;
        return false;
    }

    bool passed = true;

    // 예상되는 레지스터 및 메모리 값 검증
    if (testCase.contains("expected"))
    {
        for (const auto &it : testCase["expected"].items())
        {
            unsigned short expected = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    expected = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    throw std::invalid_argument("Invalid expected value format: " + valStr);
                }
            }
            else if (it.value().is_number_integer())
            {
                expected = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported expected value type");
            }

            if (it.key()[0] == 'R')
            {
                unsigned short regIndex = std::stoi(it.key().substr(1));
                unsigned short actual = controller.getRegister(regIndex);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] R" << regIndex << " 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
            else
            {
                std::string addrStr = it.key();
                unsigned short address = 0;
                if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
                {
                    address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
                }
                else
                {
                    throw std::invalid_argument("Invalid expected memory address format: " + addrStr);
                }

                unsigned short actual = controller.getMemory(address);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] 메모리[" << addrStr << "] 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
        }
    }

    return passed;
}
```

#### **2. 주요 변경 사항**

- **메모리 주소 및 값의 접두사를 `"0x"`로 통일**했습니다.
- **`initialRegisters` → `registers`**, **`initialMemory` → `memory`**, **`expectedRegisters`와 `expectedMemory` → `expected`**로 변경했습니다.
- **값의 파싱 로직을 수정**하여 `"0x"`로 시작하는 문자열은 16진수로, 그렇지 않으면 10진수로 처리하도록 했습니다.
- **예외 처리를 추가**하여 잘못된 형식의 값이 입력될 경우 명확한 오류 메시지를 출력하도록 했습니다.

---

### **문제 1부터 6까지의 `problemN.asm` 및 `problemN.json` 파일 예시**

---

#### **문제 1: R0에 R1 + R2의 값을 저장**

##### `problem1.asm`

```assembly
; 문제 1: R0에 R1 + R2의 값을 저장하는 프로그램
; 목표: ADD 명령어를 사용하여 두 레지스터의 값을 더하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   ADD R0, R1, R2       ; R1 + R2를 계산하여 R0에 저장
        HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
```

##### `problem1.json`

```json
{
  "description": "R0에 R1 + R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": 5,
        "R2": 10
      },
      "memory": {},
      "expected": {
        "R0": 15
      }
    },
    {
      "registers": {
        "R1": -3,
        "R2": 7
      },
      "memory": {},
      "expected": {
        "R0": 4
      }
    },
    {
      "registers": {
        "R1": 0,
        "R2": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    }
  ]
}
```

---

#### **문제 2: R0에 R1 AND R2의 값을 저장**

##### `problem2.asm`

```assembly
; 문제 2: R0에 R1 AND R2의 값을 저장하는 프로그램
; 목표: AND 명령어를 사용하여 두 레지스터의 비트별 AND 연산을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   AND R0, R1, R2       ; R1 AND R2를 계산하여 R0에 저장
        HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
```

##### `problem2.json`

```json
{
  "description": "R0에 R1 AND R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": "0xFFFF",
        "R2": "0x0F0F"
      },
      "memory": {},
      "expected": {
        "R0": "0x0F0F"
      }
    },
    {
      "registers": {
        "R1": "0x1234",
        "R2": "0x00FF"
      },
      "memory": {},
      "expected": {
        "R0": "0x0034"
      }
    },
    {
      "registers": {
        "R1": "0xABCD",
        "R2": "0xFFFF"
      },
      "memory": {},
      "expected": {
        "R0": "0xABCD"
      }
    }
  ]
}
```

---

#### **문제 3: R0이 R1보다 크면 R2에 1을 저장**

##### `problem3.asm`

```assembly
; 문제 3: R0이 R1보다 크면 R2에 1을 저장하는 프로그램
; 목표: 조건부 분기 명령어를 사용하여 비교 연산을 구현하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   NOT R3, R1           ; R3 = ~R1
        ADD R3, R3, #1       ; R3 = -R1 (2의 보수)
        ADD R3, R0, R3       ; R3 = R0 - R1

        BRp GREATER          ; R0 > R1이면 GREATER로 분기
        AND R2, R2, #0       ; R2 = 0 (R0 <= R1)
        BR END

GREATER AND R2, R2, #0       ; R2 = 0
        ADD R2, R2, #1       ; R2 = 1 (R0 > R1)

END     HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
```

##### `problem3.json`

```json
{
  "description": "R0이 R1보다 크면 R2에 1을, 그렇지 않으면 0을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": 10,
        "R1": 5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 3,
        "R1": 7
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    },
    {
      "registers": {
        "R0": -2,
        "R1": -5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 0,
        "R1": 0
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    }
  ]
}
```

---

#### **문제 4: R0의 절댓값 계산**

##### `problem4.asm`

```assembly
; 문제 4: R0의 절댓값을 계산하여 R0에 저장하는 프로그램
; 목표: 조건부 분기와 부호 비트를 활용하여 절댓값을 구하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   BRzp END             ; R0 >= 0이면 END로 분기
        NOT R0, R0           ; R0 = ~R0
        ADD R0, R0, #1       ; R0 = -R0 (2의 보수)
END     HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
```

##### `problem4.json`

```json
{
  "description": "R0의 값이 음수이면 양수로 변환하여 R0에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": -10
      },
      "memory": {},
      "expected": {
        "R0": 10
      }
    },
    {
      "registers": {
        "R0": 5
      },
      "memory": {},
      "expected": {
        "R0": 5
      }
    },
    {
      "registers": {
        "R0": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    },
    {
      "registers": {
        "R0": -1
      },
      "memory": {},
      "expected": {
        "R0": 1
      }
    }
  ]
}
```

---

#### **문제 5: 배열의 합 계산**

##### `problem5.asm`

```assembly
; 문제 5: 배열에 저장된 정수들의 합을 계산하여 R2에 저장하는 프로그램
; 목표: 메모리 접근과 루프를 사용하여 배열의 합을 구하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LEA R1, ARRAY        ; R1에 배열의 시작 주소 로드
        AND R2, R2, #0       ; R2 = 0 (합계를 저장할 레지스터)

LOOP    LDR R3, R1, #0       ; R3 = M[R1]
        BRz END              ; R3 == 0이면 배열의 끝이므로 종료
        ADD R2, R2, R3       ; R2 += R3
        ADD R1, R1, #1       ; R1 += 1 (다음 요소로 이동)
        BR LOOP              ; LOOP로 분기

END     HALT                 ; 프로그램 종료

        .ORIG x4000          ; 데이터 섹션 시작 주소

ARRAY   .FILL 5
        .FILL 10
        .FILL 15
        .FILL 20
        .FILL 0              ; 배열의 끝을 나타내는 0

        .END                 ; 프로그램 끝
```

##### `problem5.json`

```json
{
  "description": "배열에 저장된 정수들의 합을 계산하여 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 5,
        "0x4001": 10,
        "0x4002": 15,
        "0x4003": 20,
        "0x4004": 0
      },
      "expected": {
        "R2": 50
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 1,
        "0x4001": 2,
        "0x4002": 3,
        "0x4003": 4,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 15
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -5,
        "0x4001": -10,
        "0x4002": -15,
        "0x4003": 0
      },
      "expected": {
        "R2": -30
      }
    }
  ]
}
```

---

#### **문제 6: 메모리에서 최대값 찾기**

##### `problem6.asm`

```assembly
; 문제 6: 메모리에서 최대값을 찾아 R2에 저장하는 프로그램
; 목표: 메모리 접근과 비교 연산을 사용하여 최대값을 찾는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LEA R1, ARRAY        ; R1에 배열의 시작 주소 로드
        LDR R2, R1, #0       ; R2 = 첫 번째 요소 (최대값 저장)
        ADD R1, R1, #1       ; R1 += 1 (다음 요소로 이동)

LOOP    LDR R3, R1, #0       ; R3 = M[R1]
        BRz END              ; R3 == 0이면 배열의 끝이므로 종료

        ; R3와 R2를 비교하여 R2에 최대값 저장
        NOT R4, R2           ; R4 = ~R2
        ADD R4, R4, #1       ; R4 = -R2
        ADD R5, R3, R4       ; R5 = R3 - R2

        BRn NEXT             ; R3 - R2 < 0이면 다음으로
        ADD R2, R3, #0       ; R2 = R3 (최대값 갱신)

NEXT    ADD R1, R1, #1       ; R1 += 1 (다음 요소로 이동)
        BR LOOP              ; LOOP로 분기

END     HALT                 ; 프로그램 종료

        .ORIG x4000          ; 데이터 섹션 시작 주소

ARRAY   .FILL 10
        .FILL 25
        .FILL 15
        .FILL 30
        .FILL 5
        .FILL 0              ; 배열의 끝을 나타내는 0

        .END                 ; 프로그램 끝
```

##### `problem6.json`

```json
{
  "description": "배열에 저장된 정수들 중 최대값을 찾아 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 10,
        "0x4001": 25,
        "0x4002": 15,
        "0x4003": 30,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 30
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -10,
        "0x4001": -20,
        "0x4002": -5,
        "0x4003": -15,
        "0x4004": 0
      },
      "expected": {
        "R2": -5
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 100,
        "0x4001": 200,
        "0x4002": 300,
        "0x4003": 400,
        "0x4004": 500,
        "0x4005": 0
      },
      "expected": {
        "R2": 500
      }
    }
  ]
}
```

---

### **C++ 코드 수정 요약**

JSON 파일 형식이 `"0x"`로 시작하는 16진수 문자열로 일관되게 정의되었으므로, C++ 코드에서 이를 올바르게 파싱하도록 수정해야 합니다. 아래는 **`GradingModule.cpp`** 파일의 수정된 `runTestCase` 함수입니다. **기존 코드를 최소한으로 변경**하여 일관성을 유지했습니다.

```cpp
bool GradingModule::runTestCase(Controller &controller, const json &testCase)
{
    // 초기 레지스터 설정
    if (testCase.contains("registers"))
    {
        for (const auto &it : testCase["registers"].items())
        {
            unsigned short regIndex = std::stoi(it.key().substr(1));
            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    value = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported register value type");
            }
            controller.setRegister(regIndex, value);
        }
    }

    // 초기 메모리 설정
    if (testCase.contains("memory"))
    {
        for (const auto &it : testCase["memory"].items())
        {
            std::string addrStr = it.key();
            unsigned short address = 0;
            if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
            {
                address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
            }
            else
            {
                // "0x"로 시작하지 않으면 10진수로 파싱
                address = static_cast<unsigned short>(std::stoi(addrStr, nullptr, 10));
            }

            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    value = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported memory value type");
            }
            controller.setMemory(address, value);
        }
    }

    controller.runProgram();
    if (!controller.checkSuccess())
    {
        std::cerr << RED << "[오류] 프로그램 실행 중 오류 발생\n"
                  << RESET;
        return false;
    }

    bool passed = true;

    // 예상되는 레지스터 및 메모리 값 검증
    if (testCase.contains("expected"))
    {
        for (const auto &it : testCase["expected"].items())
        {
            unsigned short expected = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    expected = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    expected = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                expected = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported expected value type");
            }

            if (it.key()[0] == 'R')
            {
                unsigned short regIndex = std::stoi(it.key().substr(1));
                unsigned short actual = controller.getRegister(regIndex);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] R" << regIndex << " 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
            else
            {
                std::string addrStr = it.key();
                unsigned short address = 0;
                if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
                {
                    address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    address = static_cast<unsigned short>(std::stoi(addrStr, nullptr, 10));
                }

                unsigned short actual = controller.getMemory(address);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] 메모리[" << addrStr << "] 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
        }
    }

    return passed;
}
```

#### **주요 변경 사항**

- **메모리 주소 및 값의 접두사를 일관되게 `"0x"`로 사용**하되, 값이 `"0x"`로 시작하지 않으면 10진수로 파싱하도록 로직을 추가했습니다.
- **레지스터와 메모리의 기대값을 모두 `expected` 필드에 포함**하여 통합적으로 검증하도록 했습니다.
- **예외 처리를 강화**하여 잘못된 형식의 값이 입력될 경우 명확한 오류 메시지를 출력하도록 했습니다.

---

### **문제 1부터 6까지의 JSON 파일 예시**

아래는 앞서 정의한 JSON 형식을 적용한 문제 1부터 6까지의 JSON 파일 예시입니다. **모든 메모리 주소는 `"0x"`로 시작하는 16진수 문자열**로 통일되어 있습니다.

---

#### **문제 1: R0에 R1 + R2의 값을 저장**

##### `problem1.json`

```json
{
  "description": "R0에 R1 + R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": 5,
        "R2": 10
      },
      "memory": {},
      "expected": {
        "R0": 15
      }
    },
    {
      "registers": {
        "R1": -3,
        "R2": 7
      },
      "memory": {},
      "expected": {
        "R0": 4
      }
    },
    {
      "registers": {
        "R1": 0,
        "R2": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    }
  ]
}
```

---

#### **문제 2: R0에 R1 AND R2의 값을 저장**

##### `problem2.json`

```json
{
  "description": "R0에 R1 AND R2의 값을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R1": "0xFFFF",
        "R2": "0x0F0F"
      },
      "memory": {},
      "expected": {
        "R0": "0x0F0F"
      }
    },
    {
      "registers": {
        "R1": "0x1234",
        "R2": "0x00FF"
      },
      "memory": {},
      "expected": {
        "R0": "0x0034"
      }
    },
    {
      "registers": {
        "R1": "0xABCD",
        "R2": "0xFFFF"
      },
      "memory": {},
      "expected": {
        "R0": "0xABCD"
      }
    }
  ]
}
```

---

#### **문제 3: R0이 R1보다 크면 R2에 1을 저장**

##### `problem3.json`

```json
{
  "description": "R0이 R1보다 크면 R2에 1을, 그렇지 않으면 0을 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": 10,
        "R1": 5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 3,
        "R1": 7
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    },
    {
      "registers": {
        "R0": -2,
        "R1": -5
      },
      "memory": {},
      "expected": {
        "R2": 1
      }
    },
    {
      "registers": {
        "R0": 0,
        "R1": 0
      },
      "memory": {},
      "expected": {
        "R2": 0
      }
    }
  ]
}
```

---

#### **문제 4: R0의 절댓값 계산**

##### `problem4.json`

```json
{
  "description": "R0의 값이 음수이면 양수로 변환하여 R0에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {
        "R0": -10
      },
      "memory": {},
      "expected": {
        "R0": 10
      }
    },
    {
      "registers": {
        "R0": 5
      },
      "memory": {},
      "expected": {
        "R0": 5
      }
    },
    {
      "registers": {
        "R0": 0
      },
      "memory": {},
      "expected": {
        "R0": 0
      }
    },
    {
      "registers": {
        "R0": -1
      },
      "memory": {},
      "expected": {
        "R0": 1
      }
    }
  ]
}
```

---

#### **문제 5: 배열의 합 계산**

##### `problem5.json`

```json
{
  "description": "배열에 저장된 정수들의 합을 계산하여 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 5,
        "0x4001": 10,
        "0x4002": 15,
        "0x4003": 20,
        "0x4004": 0
      },
      "expected": {
        "R2": 50
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 1,
        "0x4001": 2,
        "0x4002": 3,
        "0x4003": 4,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 15
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -5,
        "0x4001": -10,
        "0x4002": -15,
        "0x4003": 0
      },
      "expected": {
        "R2": -30
      }
    }
  ]
}
```

---

#### **문제 6: 메모리에서 최대값 찾기**

##### `problem6.json`

```json
{
  "description": "배열에 저장된 정수들 중 최대값을 찾아 R2에 저장하는 프로그램을 작성하세요.",
  "testCases": [
    {
      "registers": {},
      "memory": {
        "0x4000": 10,
        "0x4001": 25,
        "0x4002": 15,
        "0x4003": 30,
        "0x4004": 5,
        "0x4005": 0
      },
      "expected": {
        "R2": 30
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": -10,
        "0x4001": -20,
        "0x4002": -5,
        "0x4003": -15,
        "0x4004": 0
      },
      "expected": {
        "R2": -5
      }
    },
    {
      "registers": {},
      "memory": {
        "0x4000": 100,
        "0x4001": 200,
        "0x4002": 300,
        "0x4003": 400,
        "0x4004": 500,
        "0x4005": 0
      },
      "expected": {
        "R2": 500
      }
    }
  ]
}
```

---

### **C++ 코드 파싱 로직 설명**

JSON 파일의 **`registers`**, **`memory`**, **`expected`** 필드는 다음과 같이 파싱됩니다:

1. **레지스터 설정 (`registers`)**

   - **키**: `"R0"`, `"R1"`, ...
   - **값**: 10진수 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **파싱 로직**:
     - 값이 문자열이고 `"0x"`로 시작하면 16진수로 파싱
     - 그렇지 않으면 10진수로 파싱

2. **메모리 설정 (`memory`)**

   - **키**: `"0x4000"`, `"0x4001"`, ...
   - **값**: 10진수 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **파싱 로직**:
     - 키가 `"0x"`로 시작하면 16진수 주소로 파싱
     - 값이 문자열이고 `"0x"`로 시작하면 16진수로 파싱
     - 그렇지 않으면 10진수로 파싱

3. **기대값 확인 (`expected`)**
   - **키**: `"R0"`, `"R1"`, `"0x4002"`, ...
   - **값**: 10진수 정수 또는 `"0x"`로 시작하는 16진수 문자열
   - **파싱 로직**:
     - 키가 `"R"`로 시작하면 레지스터로 간주
     - 그렇지 않으면 메모리 주소로 간주
     - 값이 문자열이고 `"0x"`로 시작하면 16진수로 파싱
     - 그렇지 않으면 10진수로 파싱

---

### **C++ 코드 예시**

아래는 **파싱 로직**을 구현한 C++ 코드의 예시입니다. 기존 코드를 최소한으로 변경하여 일관된 형식을 유지했습니다.

```cpp
bool GradingModule::runTestCase(Controller &controller, const json &testCase)
{
    // 초기 레지스터 설정
    if (testCase.contains("registers"))
    {
        for (const auto &it : testCase["registers"].items())
        {
            unsigned short regIndex = std::stoi(it.key().substr(1));
            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    value = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported register value type");
            }
            controller.setRegister(regIndex, value);
        }
    }

    // 초기 메모리 설정
    if (testCase.contains("memory"))
    {
        for (const auto &it : testCase["memory"].items())
        {
            std::string addrStr = it.key();
            unsigned short address = 0;
            if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
            {
                address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
            }
            else
            {
                // "0x"로 시작하지 않으면 10진수로 파싱
                address = static_cast<unsigned short>(std::stoi(addrStr, nullptr, 10));
            }

            unsigned short value = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    value = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    value = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                value = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported memory value type");
            }
            controller.setMemory(address, value);
        }
    }

    controller.runProgram();
    if (!controller.checkSuccess())
    {
        std::cerr << RED << "[오류] 프로그램 실행 중 오류 발생\n"
                  << RESET;
        return false;
    }

    bool passed = true;

    // 예상되는 레지스터 및 메모리 값 검증
    if (testCase.contains("expected"))
    {
        for (const auto &it : testCase["expected"].items())
        {
            unsigned short expected = 0;
            if (it.value().is_string())
            {
                std::string valStr = it.value().get<std::string>();
                if (valStr.substr(0, 2) == "0x" || valStr.substr(0, 2) == "0X")
                {
                    expected = static_cast<unsigned short>(std::stoul(valStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    expected = static_cast<unsigned short>(std::stoi(valStr, nullptr, 10));
                }
            }
            else if (it.value().is_number_integer())
            {
                expected = static_cast<unsigned short>(it.value().get<int>());
            }
            else
            {
                throw std::invalid_argument("Unsupported expected value type");
            }

            if (it.key()[0] == 'R')
            {
                unsigned short regIndex = std::stoi(it.key().substr(1));
                unsigned short actual = controller.getRegister(regIndex);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] R" << regIndex << " 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
            else
            {
                std::string addrStr = it.key();
                unsigned short address = 0;
                if (addrStr.substr(0, 2) == "0x" || addrStr.substr(0, 2) == "0X")
                {
                    address = static_cast<unsigned short>(std::stoul(addrStr.substr(2), nullptr, 16));
                }
                else
                {
                    // "0x"로 시작하지 않으면 10진수로 파싱
                    address = static_cast<unsigned short>(std::stoi(addrStr, nullptr, 10));
                }

                unsigned short actual = controller.getMemory(address);
                if (actual != expected)
                {
                    std::cerr << RED << "[테스트 실패] 메모리[" << addrStr << "] 예상 값: " << expected
                              << " 실제 값: " << actual << RESET << "\n";
                    passed = false;
                }
            }
        }
    }

    return passed;
}
```

#### **주요 변경 사항**

- **값의 파싱 로직을 일관되게 수정**하여 `"0x"`로 시작하는 16진수 문자열과 그렇지 않은 10진수 정수를 모두 처리할 수 있도록 했습니다.
- **예외 처리를 강화**하여 잘못된 형식의 값이 입력될 경우 명확한 오류 메시지를 출력하도록 했습니다.
- **기존 구조는 그대로 유지**하여 필요한 부분만 수정했습니다.

---

### **작성 시 유의사항**

1. **메모리 주소와 값의 접두사를 일관되게 `"0x"`로 사용**

   - 모든 메모리 주소는 `"0x"`로 시작하는 16진수 문자열로 작성합니다.
   - 값도 16진수가 필요한 경우 `"0x"`로 시작하는 문자열을 사용하고, 그렇지 않으면 10진수로 작성합니다.

2. **JSON 키 이름 일관성 유지**

   - `registers`, `memory`, `expected` 필드를 정확히 사용합니다.
   - **예시**:
     ```json
     "registers": { "R1": 5, "R2": "0x00FF" },
     "memory": { "0x4000": 5, "0x4001": "0x00FF" },
     "expected": { "R0": 15, "0x4002": "0x1234" }
     ```

3. **예외 처리 강화**

   - C++ 코드에서 예외 처리를 통해 잘못된 형식의 입력을 감지하고 적절히 대응합니다.

4. **테스트 케이스 충분히 작성**
   - 다양한 입력 값과 경계 조건을 포함하여 프로그램의 정확성을 검증합니다.

---

### **도움이 필요하신 경우**

- **코드 수정 및 디버깅**: 문제가 지속될 경우, 구체적인 오류 메시지와 함께 문의해주세요.
- **추가적인 JSON 예제**: 더 많은 문제 예제가 필요하시다면 요청해주십시오.
- **기타 문의 사항**: 프로젝트 관련 다른 질문이 있으시면 언제든지 말씀해주세요.

---

**다시 한번 불편을 끼쳐드려 죄송합니다. 요청하신 내용을 최대한 반영하여 도움을 드리고자 했습니다. 추가적인 도움이 필요하시면 언제든지 말씀해주세요.**
