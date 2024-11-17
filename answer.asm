; 문제 12: 버블 정렬
; 목표: 배열을 오름차순으로 정렬합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LD R1, ARRADR        ; R1 = 배열 시작 주소
        LD R2, LENADR        ; R2 = 배열 길이
        LDR R2, R2, #0
        ADD R3, R2, #-1      ; R3 = R2 - 1 (최대 루프 횟수)

; 챌린지 문제
; TODO: 버블정렬을 이용해 ARRAY 배열을 정렬하는 코드를 구현하세요






OUTER   AND R4, R4, #0       ; R4 = 0 (교환 플래그)

INNER   LDR R5, R1, #0       ; R5 = M[R1]
        LDR R6, R1, #1       ; R6 = M[R1+1]
        
        NOT R6, R6
        ADD R6, R6, #1

        ADD R5, R5, R6       ; R5 = R5 - R6

        BRnz NOSWAP           ; R5 <= R6이면 교환하지 않음

        LDR R5, R1, #0
        LDR R6, R1, #1

        STR R6, R1, #0       ; M[R1] = R6
        STR R5, R1, #1       ; M[R1+1] = R5
        ADD R4, R4, #1       ; R4 = 1 (교환 발생)

NOSWAP  ADD R1, R1, #1       ; 다음 요소로 이동
        ADD R3, R3, #-1      ; 남은 요소 개수 감소
        BRp INNER            ; 내부 루프 반복

        LD R1, ARRADR        ; 배열 시작 주소로 복원
        LD R3, LENADR        ; 배열 길이 복원
        ADD R2, R2, #-1
        BRz DONE             ; 교환 없으면 정렬 완료
        ADD R3, R2, #-1      ; 최대 루프 횟수 감소
        BR OUTER             ; 외부 루프 반복















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