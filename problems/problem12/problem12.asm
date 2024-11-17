; 문제 12: 버블 정렬
; 목표: 배열을 오름차순으로 정렬합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LD R1, ARRADR        ; R1 = 배열 시작 주소
        LD R2, LENADR        ; R2 = 배열 길이
        LDR R2, R2, #0
        ADD R3, R2, #-1      ; R3 = R2 - 1 (최대 루프 횟수)

; 챌린지 문제
; TODO: 버블정렬을 이용해 ARRAY 배열을 정렬하는 코드를 구현하세요




















DONE    HALT                 ; 프로그램 종료
ARRADR .FILL ARRAY
LENADR .FILL LENGTH
        .END
        .ORIG x4000          ; 데이터 섹션 시작 주소

ARRAY   .FILL 5
        .FILL 1
        .FILL 4
        .FILL 2
        .FILL 3
LENGTH  .FILL 5              ; 배열 길이

        .END                 ; 프로그램 끝
