#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_symtab(char *label)
{
    FILE *fptr = fopen("symtab.txt", "r");
    if (fptr == NULL)
    {
        printf("no such file.");
        return 0;
    }
    char temp1[100], temp2[100];
    while (fscanf(fptr, "%s %s", temp1, temp2) == 2)
    {
        if (strcmp(temp1, label) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int search_optab(char *opcode)
{
    FILE *fptr = fopen("optab.txt", "r");
    char temp1[100], temp2[1000];

    if (fptr == NULL)
    {
        printf("no such file.");
        return 0;
    }

    fscanf(fptr, "%s %s", temp1, temp2);

    while (fscanf(fptr, "%s %s", temp1, temp2) == 2)
    {
        if (strcmp(temp1, opcode) == 0)
        {
            return 1;
        }
    }
    return 0;
}
void main()
{
    char add1[50];
    int i, len, address, start_add, act_len, tcount = 0xf;
    char label[10], a[10], ad[10], oprnd[10], code[3], add[7], opcode[10], mnemonic[10], symbol[10];
    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
    fp1 = fopen("asmlist.txt", "w");
    fp2 = fopen("symtab.txt", "r");
    fp3 = fopen("intermediate.txt", "r");
    fp4 = fopen("optab.txt", "r");
    fp5 = fopen("out.txt", "w");
    fp6 = fopen("object.txt", "w");

    fscanf(fp3, "%s%s%s", label, opcode, oprnd);
    if (strcmp(opcode, "START") == 0)
    {
        fprintf(fp1, "\t%s\t%s\t%s\n", label, opcode, oprnd);
        fprintf(fp5, "H%s %06s000012\n", label, oprnd);
        fprintf(fp5, "T%06s0F", oprnd);
        fscanf(fp3, "%s\t%s\t%s\t%s", add1, label, opcode, oprnd);
        sscanf(add1, "%x", &address);
        address -= 3096;
        start_add = address;
    }
    while (strcmp(opcode, "END") != 0)
    {
        if (strcmp(opcode, "BYTE") == 0)
        {
            fprintf(fp1, "%d\t%s\t%s\t%s\t", address, label, opcode, oprnd);
            len = strlen(oprnd);
            act_len = len - 3;
            for (i = 2; i < (act_len + 2); i++)
            {
                itoa(oprnd[i], ad, 16);
                fprintf(fp1, "%06s", ad);
            }
            fprintf(fp1, "\n");
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            len = strlen(oprnd);
            itoa(atoi(oprnd), a, 10);
            fprintf(fp6, "%06s\n", a);
            fprintf(fp1, "%d\t%s\t%s\t%s\t%06s\n", address, label, opcode, oprnd, a);
            fprintf(fp5, "%06s", a);
        }
        else if ((strcmp(opcode, "RESB") == 0) || (strcmp(opcode, "RESW") == 0))
        {
            fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, oprnd);
        }
        else
        {
            char s1[100] = "", s2[100] = "";
            rewind(fp4);
            fscanf(fp4, "%s%s", mnemonic, code);
            while (strcmp(opcode, mnemonic) != 0)
                fscanf(fp4, "%s%s", mnemonic, code);

            fprintf(fp6, "%s", code);
            strcpy(s1, code);

            rewind(fp2);
            fscanf(fp2, "%s%s", symbol, add);
            while (strcmp(oprnd, symbol) != 0)
            {
                fscanf(fp2, "%s%s", symbol, add);
            }
            fprintf(fp6, "%s\n", add);
            strcat(s1, add);

            fprintf(fp1, "%d\t%s\t%s\t%s\t%s\n", address, label, opcode, oprnd, s1);

            if (strcmp(oprnd, "~") != 0)
            {
                if (tcount == 0xf)
                {
                    fprintf(fp5, "%s", s1);
                    tcount = 0;
                }
                else
                {
                    fprintf(fp5, "%s", s1);
                    tcount++;
                }
            }
        }
        fscanf(fp3, "%s\t%s\t%s\t%s", add1, label, opcode, oprnd);

        sscanf(add1, "%x", &address);
        address -= 3096;
    }
    fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, oprnd);
    fprintf(fp5, "\nE%6d\n", start_add);
    printf("Finished\n");
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}
