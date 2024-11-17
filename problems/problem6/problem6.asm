; 문제 6: 메모리에서 최대값을 찾아 R2에 저장하는 프로그램
; 목표: 메모리 접근과 비교 연산을 사용하여 최대값을 찾는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LD R1, ARRAYADR        ; R1에 배열의 시작 주소 로드
        LDR R2, R1, #0       ; R2 = 첫 번째 요소 (최대값 저장)
        ADD R1, R1, #1       ; R1 += 1 (다음 요소로 이동)

; R1에 ARRAY의 주소가 저장됨
; R2에 최댓값을 저장
; TODO: LOOP 내에서 비교 연산을 통해 최댓값을 찾기

LOOP    LDR R3, R1, #0       ; R3 = M[R1]








END     HALT                 ; 프로그램 종료

ARRAYADR .FILL ARRAY

        .ORIG x4000          ; 데이터 섹션 시작 주소
ARRAY   .FILL 10
        .FILL 25
        .FILL 15
        .FILL 30
        .FILL 5
        .FILL 0              ; 배열의 끝을 나타내는 0

        .END                 ; 프로그램 끝
