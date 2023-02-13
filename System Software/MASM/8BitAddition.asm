ASSUME CS:CODE,DS:DATA

DATA SEGMENT
M1 DB 13,10,"ENTER 1st NO :$"
M2 DB 13,10,"ENTER 2nd NO :$"
M3 DB 13,10,"SUM :$"
DATA ENDS

PRTMSG MACRO MSG
LEA DX,MSG
MOV AH,09H
INT 21H
ENDM

CODE SEGMENT
START: MOV AX,DATA
        MOV DS,AX
        PRTMSG M1
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV BH,AL
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV BL,AL

        PRTMSG M2
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV CH,AL
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV CL,AL

        MOV AL,BL
        ADD AL,CL
        MOV AH,00
        AAA
        ADD AX,3030H
        MOV BL,AL
        MOV AL,AH

        ADD AL,BH
        ADD AL,CH
        MOV AH,00
        AAA
        ADD AX,3030H
        MOV CL,AH
        MOV BH,AL

        PRTMSG M3
        MOV DL,CL
        MOV AH,02H
        INT 21H

        MOV DL,BH
        MOV AH,02H
        INT 21H

        MOV DL,BL
        MOV AH,02H
        INT 21H

        MOV AH,4CH
        INT 21H

CODE    ENDS
        END START
