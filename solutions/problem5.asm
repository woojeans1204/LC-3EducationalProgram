; 문제 5: 배열에 저장된 정수들의 합을 계산하여 R2에 저장하는 프로그램
; 목표: 메모리 접근과 루프를 사용하여 배열의 합을 구하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LD R1, ARRAYADR        ; R1에 배열의 시작 주소 로드
        AND R2, R2, #0       ; R2 = 0 (합계를 저장할 레지스터)

LOOP    LDR R3, R1, #0       ; R3 = M[R1]
        BRz END              ; R3 == 0이면 배열의 끝이므로 종료
        ADD R2, R2, R3       ; R2 += R3
        ADD R1, R1, #1       ; R1 += 1 (다음 요소로 이동)
        BR LOOP              ; LOOP로 분기

END     HALT                 ; 프로그램 종료

ARRAYADR .FILL ARRAY
        .ORIG x4000          ; 데이터 섹션 시작 주소

ARRAY   .FILL 5
        .FILL 10
        .FILL 15
        .FILL 20
        .FILL 0              ; 배열의 끝을 나타내는 0

        .END                 ; 프로그램 끝
