; 문제 3: R0이 R1보다 크면 R2에 1을 저장하는 프로그램
; 목표: 조건부 분기 명령어를 사용하여 비교 연산을 구현하는 방법을 학습합니다.

        .ORIG x3000          ; 코드 섹션 시작 주소

        NOT R3, R1           ; R3 = ~R1
        ADD R3, R3, #1       ; R3 = -R1 (2의 보수)
        ADD R3, R0, R3       ; R3 = R0 - R1
; R3 = R0 - R1 으로 주어짐
; TODO: R0 > R1 이면 GREATER로 분기, 그렇지 않으면 ED로 분기하는 코드를 작성




; R0 > R1이면 GREATER로 분기
GREATER AND R2, R2, #0       ; R2 = 0
        ADD R2, R2, #1       ; R2 = 1 (R0 > R1)

ED     HALT                 ; 프로그램 종료

        .END                 ; 프로그램 끝
