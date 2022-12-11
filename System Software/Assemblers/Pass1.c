/*AUTHOR : Navya.s.Raj */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *f1, *f2, *f3, *f4;
    int i, locctr = 0x0, start_add, flag = 0;
    char label[7], opcode[7], oprnd[7], code[7], mnemonic[7], ad[7];
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("intermediate.txt", "w");
    fscanf(f1, "%s\t%s\t%s\n", label, opcode, oprnd);
    if (strcmp(opcode, "START") == 0)
    {
        start_add = strtol(oprnd, NULL, 16);
        locctr = (0x1) * start_add;
        int len = sizeof(oprnd) / sizeof(oprnd[0]);
        for (i = 0; i < len; i++)
            ad[i] = oprnd[i];
        fprintf(f4, "\t%s\t%s\t%s\n", label, opcode, oprnd);
        fscanf(f1, "%s\t%s\t%s", label, opcode, oprnd);
    }
    else
    {
        locctr = 0;
    }
    while (strcmp(opcode, "END") != 0)
    {

        // transfer address
        fprintf(f4, "%x\t%s\t%s\t%s\n", locctr, label, opcode, oprnd);

        // make symtab
        if (strcmp(label, "~") != 0)
        {
            fprintf(f3, "%s\t%x\n", label, locctr);
        }

        // read from optab
        fscanf(f2, "%s\t%s", code, mnemonic);
        while (strcmp(code, "END") != 0)
        {
            if (strcmp(code, opcode) == 0)
            {
                locctr += 0x3;
                break;
            }
            fscanf(f2, "%s\t%s", code, mnemonic);
        }

        // search opcode for WORD,BYTE,RESW,RESB
        if (strcmp(opcode, "WORD") == 0)
        {
            locctr += 0x3;
        }
        else if (strcmp(opcode, "RESW") == 0)
        {
            locctr += ((0x3) * atoi(oprnd));
        }
        else if (strcmp(opcode, "RESB") == 0)
        {
            locctr += ((0x1) * atoi(oprnd));
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            locctr += 0x1;
        }

        fscanf(f1, "%s\t%s\t%s", label, opcode, oprnd);
    }
    fprintf(f4, "\t\t%s\t%s", opcode, ad);

    rewind(f1);
    rewind(f2);
    fclose(f3);
    fclose(f4);
    f3 = fopen("symtab.txt", "r");
    f4 = fopen("intermediate.txt", "r");

    // Display Input file
    printf("\nINPUT FILE :\n");
    char str;
    str = fgetc(f1);
    while (str != EOF)
    {
        printf("%c", str);
        str = fgetc(f1);
    }
    fclose(f1);

    // Display Intermediate file
    printf("\n\nINTERMEDIATE FILE :\n");
    str = fgetc(f4);
    while (str != EOF)
    {
        printf("%c", str);
        str = fgetc(f4);
    }
    fclose(f4);

    // Display Optab
    printf("\n\nOPTAB :\n");
    str = fgetc(f2);
    while (str != EOF)
    {
        printf("%c", str);
        str = fgetc(f2);
    }
    fclose(f2);

    // Display Symtab
    printf("\n\nSYMTAB :\n");
    str = fgetc(f3);
    while (str != EOF)
    {
        printf("%c", str);
        str = fgetc(f3);
    }
    fclose(f3);

    // length of program
    printf("Length of code :%x\n", locctr - start_add);
}
