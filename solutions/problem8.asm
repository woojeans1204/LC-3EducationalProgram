; 문제 8: 피보나치 수열 계산
; 목표: R0에 입력된 N번째 피보나치 수를 계산하여 R1에 저장합니다.
; 두 개의 레지스터를 활용해 값 교체 방식을 사용합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   AND R1, R1, #0       ; R1 = 0 (첫 번째 피보나치 수)
        ADD R2, R1, #1       ; R2 = 1 (두 번째 피보나치 수)
        ADD R3, R0, #0       ; R3 = N (복사)

; TODO: R4 = R1+R2, R1=R2, R2=R4을 반복하는 코드를 구현하세요

LOOP    BRz DONE             ; R3가 0이면 종료
        ADD R4, R1, R2       ; R4 = R1 + R2
        ADD R1, R2, #0       ; R1 = R2
        ADD R2, R4, #0       ; R2 = R4
        ADD R3, R3, #-1      ; R3 = R3 - 1
        BR LOOP              ; LOOP로 이동

DONE    HALT                 ; 프로그램 종료
        .END                 ; 프로그램 끝
