; 문제 11: 문자열 길이 계산
; 목표: 메모리에서 문자열을 읽어 길이를 계산합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   LD R1, STRINGADR       ; R1 = 문자열 시작 주소
        AND R2, R2, #0       ; R2 = 0 (문자열 길이)

; TODO: 문자열의 길이를 LOOP을 이용해 구현합니다
; HINT: 문자열의 끝에는 NULL(0) 문자가 존재합니다








DONE    HALT                 ; 프로그램 종료

STRINGADR .FILL STRING
        .END
        .ORIG x4000          ; 데이터 섹션 시작 주소
STRING  .STRINGZ "HELLO"     ; 문자열 저장

        .END                 ; 프로그램 끝
