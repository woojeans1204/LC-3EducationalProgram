; 문제 7: 팩토리얼 계산 (반복문)
; 목표: R0에 입력된 숫자의 팩토리얼을 계산하여 R1에 저장합니다.
; 곱셈 연산을 루프와 덧셈을 사용하여 구현합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   AND R1, R1, #0       ; R1 = 1 (결과 저장용)
        ADD R1, R1, #1       ; R1 = 1 (결과 저장용)
        AND R3, R1, R1       ; R3 = 1
        ADD R2, R0, #0       ; R2 = R0

; TODO: 팩토리얼 연산이 가능하게 빈칸을 채우세요 

LOOP    BRnz DONE            ; R2가 0이면 종료
                             ; R1 초기화
                             ; R4 = R2 (곱할 횟수)

MULTIPLY_LOOP                ; R1 = R3 * R4
        BRz MULTIPLY_DONE    ; R4가 0이면 곱셈 종료
        ADD R1, R1, R3       ; R1 += R3
        ADD R4, R4, #-1      ; R4 -= 1
        BR MULTIPLY_LOOP     ; 곱셈 루프 반복

MULTIPLY_DONE
                             ; R3 = R1 (곱셈 결과 저장)
                             ; R2 -= 1
        BR LOOP              ; 팩토리얼 루프 반복


DONE    HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
