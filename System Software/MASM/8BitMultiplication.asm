ASSUME CS:CODE,DS:DATA
DATA SEGMENT
M1 DB 10,13 ,"Enter 1st no :$"
M2 DB 10,13 ,"Enter 2nd no :$"
M3 DB 10,13, "Product :$"
DATA ENDS

PRTMSG MACRO MSG
LEA DX,MSG
MOV AH,09H
INT 21H
ENDM

GETM MACRO
MOV AH,01H
INT 21H
SUB AL,30H
ENDM

CODE SEGMENT
START:  MOV AX,DATA
        MOV DS,AX

        PRTMSG M1
        GETM
        MOV BL,AL
        PRTMSG M2
        GETM
        MUL BL
        AAM
        MOV BX,AX

        PRTMSG M3
        MOV DL,BH
        OR DL,30H
        MOV AH,02H
        INT 21H
        MOV DL,BL
        OR DL,30H
        MOV AH,02H
        INT 21H

        MOV AH,4CH
        INT 21H
CODE    ENDS
END START        
