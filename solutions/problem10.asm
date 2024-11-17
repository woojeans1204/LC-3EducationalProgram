; 문제 10: 재귀적으로 팩토리얼 계산
; 목표: 서브루틴과 스택을 사용하여 팩토리얼을 재귀적으로 계산하고 R2에 저장합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

MAIN    LD R6, STACKADR        ; R6 = 스택 포인터 초기화 (스택은 xFE00부터)
        JSR FACTORIAL        ; 팩토리얼 서브루틴 호출
        HALT                 ; 프로그램 종료


; 팩토리얼 서브루틴
; R0번째 factorial 계산 후 R2에 저장
; 즉, R2 = FACTORIAL(R0) 
FACTORIAL 
        ; 스택에 현재 상태 저장
        STR R3, R6, #-1
        STR R4, R6, #-2
        STR R5, R6, #-3
        STR R7, R6, #-4
        ADD R6, R6, #-4

        ; 기본 케이스: R0 == 0 인 경우
        ADD R0, R0, #0
        BRz BASECASE

; R6: 스택 포인터, 함수 호출 시 R3, R4 등 레지스터의 값을 복원합니다
; LC-3에서는 xF000 ~ xFe00을 일반적으로 스택 영역으로 지정합니다
; BASECASE: R0 = 0인 경우 R2 = 1을 반환합니다
; TODO: FACTORIAL의 남은 재귀함수 부분을 구현하세요

; R0 > 0 일 때
        ADD R5, R0, #0        ; R5 = R0 (현재 값 저장)
        ADD R0, R0, #-1       ; R0 = R0 - 1
        JSR FACTORIAL         ; 재귀 호출

        ; 곱셈 구현: R2 = R2 * R5
        ADD R1, R2, #0        ; R1 = R2 (곱셈 결과 저장용)
        AND R2, R2, #0        ; R2 = 0 (곱셈 결과 초기화)
        ADD R3, R5, #0        ; R3 = R5 (곱할 값)
        BRz MULTIPLY_DONE      ; R5 == 0 이면 끝

MULTIPLY_LOOP
        ADD R2, R2, R1        ; R2 += R1
        ADD R3, R3, #-1       ; R3 = R3 - 1
        BRp MULTIPLY_LOOP      ; R3 > 0 이면 반복

MULTIPLY_DONE
        BR DONE_FACTORIAL

BASECASE
        AND R2 R2 #0            ; R2 = 1 (팩토리얼 0! = 1)
        ADD R2 R2 #1

DONE_FACTORIAL        
        ; 스택에서 이전 상태 복원
        LDR R7, R6, #0
        LDR R5, R6, #1        ; R5 복원
        LDR R4, R6, #2
        LDR R3, R6, #3
        ADD R6, R6, #4        ; SP 복원 (R6 += 5)
        RET                   ; 서브루틴 반환

STACKADR .FILL STACK
        .END
.ORIG xFE00
STACK  

        .END                 ; 프로그램 끝
