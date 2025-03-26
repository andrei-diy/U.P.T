#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
FILE *out;
char fileName2[50] = "program.txt";
const char branchInstructions[100] = "BRZ, BRN, BRC, BRO, BRA, JMP";
const char noLabelInstructions[50] = "NOP, HLT, RET";
const char oneParamALUInstructions[100] = "INC, DEC, PSH, POP, LOG2, MODULE, FACTRL, NOT";

typedef struct branch
{
    char name[20];
    int line;
} branch;

branch labels[50];
int labelsCount = 0;

int show_output()
{
    FILE *file;
    char str[6];
    int reg = 0;
    int exitcode = system("path-to-modelsim/vsim -c path-to-library/work.cpu_tb -do \"run -all \" > /dev/null 2>&1");

    file = fopen("outputs.txt", "r");
    if (file == NULL)
    {
        printf("can not output!");
        exit(EXIT_FAILURE);
    }

    while (fgets(str, 6, file) != NULL)
    {
        reg++;
        if (reg == 1)
            printf("X: ");
        else if (reg == 3)
            printf("Y: ");
        else if (reg == 5)
            printf("ACC: ");
        printf("%s", str);
    }

    fclose(file);
    return exitcode;
}

void computeLabel(char *line, int lineNr)
{

    char separatori[] = ":";
    char aux[150];
    strcpy(aux, line);
    char *p = strtok(aux, separatori);

    if (p && strchr(line, ':'))
    {
        labels[labelsCount].line = lineNr;
        strcpy(labels[labelsCount].name, p);
        labelsCount++;
    }
}

int createOpCode(char *instr, int imm)
{
    if (strcmp(instr, "BRZ") == 0)
    {
        return 0b000000; // 0
    }
    else if (strcmp(instr, "BRN") == 0)
    {
        return 0b000001; // 1
    }
    else if (strcmp(instr, "BRC") == 0)
    {
        return 0b000010; // 2
    }
    else if (strcmp(instr, "BRO") == 0)
    {
        return 0b000011; // 3
    }
    else if (strcmp(instr, "BRA") == 0)
    {
        return 0b000100; // 4
    }
    else if (strcmp(instr, "JMP") == 0)
    {
        return 0b000101; // 5
    }
    else if (strcmp(instr, "RET") == 0)
    {
        return 0b000110; // 6
    }
    else if (strcmp(instr, "LDR") == 0)
    {
        return 0b000111; // 7
    }
    else if (strcmp(instr, "STR") == 0)
    {
        return 0b001000; // 8
    }
    else if (strcmp(instr, "ADD") == 0)
    {
        if (imm)
            return 0b011000; // 24
        return 0b001001;     // 9
    }
    else if (strcmp(instr, "SUB") == 0)
    {
        if (imm)
            return 0b011001; // 25
        return 0b001010;     // 10
    }
    else if (strcmp(instr, "LSR") == 0)
    {
        if (imm)
            return 0b011010; // 26
        return 0b001011;     // 11
    }
    else if (strcmp(instr, "LSL") == 0)
    {
        if (imm)
            return 0b011011; // 27
        return 0b001100;     // 12
    }
    else if (strcmp(instr, "RSR") == 0)
    {
        if (imm)
            return 0b011100; // 28
        return 0b001101;     // 13
    }
    else if (strcmp(instr, "RSL") == 0)
    {
        if (imm)
            return 0b011101; // 29
        return 0b001110;     // 14
    }
    else if (strcmp(instr, "MUL") == 0)
    {
        if (imm)
            return 0b011110; // 30
        return 0b001111;     // 15
    }
    else if (strcmp(instr, "DIV") == 0)
    {
        if (imm)
            return 0b011111; // 31
        return 0b010000;     // 16
    }
    else if (strcmp(instr, "MOD") == 0)
    {
        if (imm)
            return 0b100000; // 32
        return 0b010001;     // 17
    }
    else if (strcmp(instr, "AND") == 0)
    {
        if (imm)
            return 0b100001; // 33
        return 0b010010;     // 18
    }
    else if (strcmp(instr, "OR") == 0)
    {
        if (imm)
            return 0b100010; // 34
        return 0b010011;     // 19
    }
    else if (strcmp(instr, "XOR") == 0)
    {
        if (imm)
            return 0b100011; // 35
        return 0b010100;     // 20
    }
    else if (strcmp(instr, "CMP") == 0)
    {
        if (imm)
            return 0b100100; // 36
        return 0b010101;     // 21
    }
    else if (strcmp(instr, "TST") == 0)
    {
        if (imm)
            return 0b100100; // 37
        return 0b010101;     // 22
    }
    else if (strcmp(instr, "MOV") == 0)
    {
        if (imm)
            return 0b111011; // 59
        return 0b111010;     // 58
    }
    else if (strcmp(instr, "NOT") == 0)
    {
        return 0b010111; // 23
    }
    else if (strcmp(instr, "INC") == 0)
    {
        return 0b100111; // 39
    }
    else if (strcmp(instr, "DEC") == 0)
    {
        return 0b101000; // 40
    }
    else if (strcmp(instr, "LOG2") == 0)
    {
        return 0b101001; // 41
    }
    else if (strcmp(instr, "MODULE") == 0)
    {
        return 0b101010; // 42
    }
    else if (strcmp(instr, "FACTRL") == 0)
    {
        return 0b101011; // 43
    }
    else if (strcmp(instr, "PSH") == 0)
    {
        return 0b111100; // 60
    }
    else if (strcmp(instr, "POP") == 0)
    {
        return 0b111101; // 61
    }
    else if (strcmp(instr, "NOP") == 0)
    {
        return 0b111110; // 62
    }
    else if (strcmp(instr, "HLT") == 0)
    {
        return 0b111111; // 63
    }
    return -1;
}

void convertLine(char *line)
{

    int instrOpCode;
    int operand1, operand2;
    int imm = 0, i, negative = 0;
    char separatori[] = "# ,:";
    char aux[150];
    strcpy(aux, line);
    char *p = strtok(aux, separatori);

    int instructionCode = 0b0000000000000000;

    if (strchr(line, ':'))
    {
        p = strtok(NULL, separatori); // sar peste label
    }
    if (strchr(line, '#'))
    {
        imm = 1;
    }

    instrOpCode = createOpCode(p, imm);

    instrOpCode = instrOpCode << 10;

    if (strstr(noLabelInstructions, p))
    {
        instructionCode = instructionCode | instrOpCode;
    }

    else if (strstr(oneParamALUInstructions, p) && strcmp(p, "MOD"))
    { // daca avem instructiunea module, nu vrem sa intram

        p = strtok(NULL, separatori);

        if (strcmp(p, "X") == 0)
            operand1 = 0b0;
        else if (strcmp(p, "Y") == 0)
            operand1 = 0b1;
        operand1 = operand1 << 9;
        instructionCode = instructionCode | instrOpCode | operand1;
    }
    else if (strstr(branchInstructions, p))
    {

        p = strtok(NULL, separatori); // labelul de branch

        for (i = 0; i < labelsCount; i++)
        {
            if (strcmp(p, labels[i].name) == 0)
            {
                instructionCode = instructionCode | instrOpCode | labels[i].line;
            }
        }
    }
    else
    { // cazurile cu doi parametrii, ex ADD X, #20
        p = strtok(NULL, separatori);

        if (strcmp(p, "X") == 0)
            operand1 = 0b0;
        else if (strcmp(p, "Y") == 0)
            operand1 = 0b1;
        operand1 = operand1 << 9;

        p = strtok(NULL, separatori);

        if (strcmp(p, "X") == 0)
            operand2 = 0b000000000;
        else if (strcmp(p, "Y") == 0)
            operand2 = 0b000000001;
        else if (strcmp(p, "ACC") == 0)
            operand2 = 0b000000000;
        else
        {
            if (p[0] == '-')
            {
                strcpy(p, p + 1);
                negative = 1;
            }
            operand2 = atoi(p);
            if (negative)
            {
                operand2 = ~operand2 + 1;
                operand2 = 0b111111111 & operand2;
            }
        }

        instructionCode = instructionCode | instrOpCode | operand1 | operand2;
    }
    fprintf(out, "%.4X ", instructionCode);
}

void readLines(char *fileName)
{

    char line[150];
    char lines[150][150];
    int lineNumber = 0, i;

    if ((file = fopen(fileName, "rt")))
    {

        if ((out = fopen("instructions.mem", "w")))
        {
            while (fgets(line, 150, file))
            {
                line[strlen(line) - 1] = '\0';
                strcpy(lines[lineNumber++], line);
            }

            for (i = 0; i < lineNumber; i++)
            {
                computeLabel(lines[i], i);
            }

            for (i = 0; i < lineNumber - 1; i++)
            {
                convertLine(lines[i]);
            }
        }
        else
        {
            printf("Error when opening file\n");
        }
    }
    else
    {
        printf("Error when opening file\n");
    }

    fclose(file);
    fclose(out);
}

int main(int argc, char *argv[])
{
    readLines(fileName2);
    if (argc > 1)
        if (strcmp(argv[1], "-output") == 0)
            show_output();
    return 0;
}
