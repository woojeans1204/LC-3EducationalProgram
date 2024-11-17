; 문제 9: 함수 호출로 덧셈 구현
; 목표: R1과 R2의 값을 더한 결과를 R0에 저장합니다.
; 함수 호출 방식을 사용해 구현합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

START   JSR ADD_FUNC         ; ADD_FUNC 호출
        HALT                 ; 프로그램 종료


; JSR: 레이블로 PC를 이동시키고, 원래 PC값을 R7에 저장합니다
; RET: R7에 저장된 주소로 PC를 이동시킵니다
; TODO: ADD_FUNC를 구현하세요 (R0 = R1 + R2, 호출 위치로 복귀)

ADD_FUNC
        ADD R0, R1, R2
        RET


.END                 ; 프로그램 끝