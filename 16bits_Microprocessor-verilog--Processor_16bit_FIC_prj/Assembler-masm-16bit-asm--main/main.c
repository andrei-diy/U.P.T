#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i,cnt = 0;
char result[20];
typedef struct LABEL{
    char nume[10];
    int pc;
}LABEL;
typedef struct Instr
{
  char *nume;
  char *opcode;
}Instr;
LABEL Label[100];

Instr instructions[50] = {{"BRZ","0"},{"BRN","1"},{"BRC","2"},{"BR0","3"},{"BRA","4"},{"JMP","5"},{"RET","6"},{"LDR","7"},{"STR","8"},{"ADDXY","9"},{"SUBXY","10"},
                          {"LSRXY","11"},{"LSLXY","12"},{"RSRXY","13"},{"RSLXY","14"},{"MULXY","15"},{"DIVXY","16"},{"MODXY","17"},{"ANDXY","18"},{"ORXY","19"},
                          {"XORXY","20"},{"CMPXY","21"},{"TSTXY","22"},{"NOTXY","23"},{"ADDRI","24"},{"SUBRI","25"},{"LSRRI","26"},{"LSLRI","27"},{"RSRRI","28"},
                          {"RSLRI","29"},{"MULRI","30"},{"DIVRI","31"},{"MODRI","32"},{"ANDRI","33"},{"ORRI","34"},{"XORRI","35"},{"CMPRI","36"},{"TSTRI","37"},
                          {"NOTRI","38"},{"INC","39"},{"DEC","40"},{"MOVR","58"},{"MOVI","59"},{"PSH","60"},{"POP","61"},{"NOP","62"},{"HLT","63"},{"LOG2","41"},
                          {"MODULE","42"},{"FACTRL","43"}};
char *AllOperations[34] = { "BRZ","BRN","BRC","BRO","BRA","JMP","RET","LDR","STR","ADD","SUB","LSR","LSL","RSR","RSL","MUL",
                            "DIV","MOD","AND","OR","XOR","CMP","TST","NOT","INC","DEC","MOV","PSH","POP","NOP","HLT","LOG2","MODULE","FACTRL"};
char *Branch[7] = { "BRZ","BRN","BRC","BRO","BRA","JMP","RET"};
char *ALU[15] = {"ADD","SUB","LSR","LSL","RSR","RSL","MUL","DIV","MOD","AND","OR","XOR","CMP","TST","NOT"};
char *MEM[] = {"LDR","STR"};

int FindLabel_Address(char *nume)
{
    for(i=0;i<cnt;i++){
        if(strcmp(nume,Label[i].nume) == 0){
            return Label[i].pc;
        }
    }
    return -1;
}
void AddLabel(char *nume,int pc)
{
  Label[cnt].pc = pc;
  strcpy(Label[cnt].nume,nume);
  cnt++;
}
char* FindInstrCode(char *nume)
{
    for(i=0;i<50;i++){
        if(strcmp(nume,instructions[i].nume) == 0){
            return instructions[i].opcode;
        }
    }
    return NULL;
}
int IsAlu(char* sir)
{
  for(i=0;i<=14;i++)
    {
        if(strcmp(sir,ALU[i])==0) return 1;
    }
  return 0;
}
int IsMem(char* sir)
{
  if(strcmp(sir,MEM[0])==0 ||strcmp(sir,MEM[1])==0 ) return 1;
  return 0;
}
int IsBranch(char* sir)
{
  for(i=0;i<=6;i++)
    {
        if(strcmp(sir,Branch[i])==0) return 1;
    }
  return 0;
}
int IsOperation(char* sir)
{
  for(i=0;i<=33;i++)
    {
        if(strcmp(sir,AllOperations[i])==0) return 1;
    }
  return 0;
}
char* string_to_bin(char* sir,int nr_bits)
{

  i = nr_bits-1;
  if(sir==NULL) return NULL;
  int val = atoi(sir);
  while(i>=0)
    {
     result[i] = val%2 + '0';
     val /= 2;
     i--;
    }
    result[nr_bits]='\0';
    return result;
}
char* integer_to_bin(int n,int nr_bits)
{
  i = nr_bits-1;
  while(i>=0)
    {
     result[i] = n%2 + '0';
     n /= 2;
     i--;
    }
    result[nr_bits]='\0';
    return result;
}
unsigned long binary_to_hexa(char *s)
{
    unsigned long i = 0;
    int j=0;
    while (j<16)
     {
        i = i*2;
        i = i + s[j] - '0';
        j++;
     }
    return i;
}
void scan_labels()
{
   FILE *f;
   int lr=0;
   char line[20],*word;
   f = fopen("in.txt","rt");
   while (fscanf(f, "%[^\n]s", line) >0 )
    {
        fgetc(f);
        word = strtok(line, " ,:");
        if(!IsOperation(word) && FindLabel_Address(word) == -1) AddLabel(word,lr);
        else lr++;
    }
    fclose(f);
}
void removeLeadingSpaces(char str[20])
{
    int j, k = 0;
    int index = 0;
    char str1[20];
    while(str[index] == ' ' || str[index] == '\t')
        {
            index++;
        }
    for (j=index; str[j]!='\0';j++)
        {
           str1[k] = str[j];
            k++;
        }
    str1[k] = '\0';
    strcpy(str,str1);
}

int main()
{
    FILE *fin;                    //
    FILE *fout;                   //
    char code[16];                //
    char line[30];                //
    char Line[30];                // declarare date
    char* word;                   //
    char* p;                      //
    char  op1[20];                //
    char  op2[20];                //
    int indicator;                //

    //SCANAREA ETICHETELOR SI MEMORAREA ACESTORA//
    scan_labels();   /////
    /////////////////////

    fin  = fopen("in.txt","rt");   //
    fout = fopen("out.txt","wt");  //  deschidere fisiere

    while (fscanf(fin, "%[^\n]s", line) > 0)
    {
        fgetc(fin); indicator = 0;                           //
        removeLeadingSpaces(line);                           //
        strcpy(Line,line);                                   // Prelucrare linie din fisier
        word = strtok(Line, " :,");                          //
        if ((p = strtok(NULL," ,"))!= NULL) strcpy(op1,p);   //
        if ((p = strtok(NULL, " ,"))!= NULL) strcpy(op2,p);  //

        if(FindLabel_Address(word)!=-1 &&!IsOperation(word))
            {
                removeLeadingSpaces(op1);
                strcpy(word,op1);
                strcpy(op1,op2);
                if ((p = strtok(NULL, " "))!= NULL) strcpy(op2,p);
            }
        if(IsAlu(word))
            {
                indicator ++;
                if(strcmp(op2,"X")==0||strcmp(op2,"Y")==0) strcat(word,"XY");
                    else strcat(word,"RI");
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                if(strcmp(op1,"X")==0) strcat(code,"0");
                   else strcat(code,"1");
                if(strcmp(op2,"X")==0) strcat(code,string_to_bin("0",9));
                else if(strcmp(op2,"Y")==0) strcat(code,string_to_bin("1",9));
                     else if(atoi(op2)!=0)
                            {
                              if(atoi(op2)>0){  strcat(code,string_to_bin(op2,9));  }
                              else { strcat(code,integer_to_bin(512+atoi(op2),9));  }
                            }
            }

        if(IsBranch(word))
            {   indicator ++;
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                if(FindLabel_Address(op1)!= -1) strcat(code,integer_to_bin(FindLabel_Address(op1),10));
                else indicator --;
            }
        if(IsMem(word))
            {
                indicator ++;
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                if(strcmp(op1,"X")==0) strcat(code,"0");
                  else strcat(code,"1");
                if(atoi(op2)>0) strcat(code,string_to_bin(op2,9));
            }

        if(strcmp(word,"DEC")==0 ||strcmp(word,"INC")==0 ||strcmp(word,"PSH")==0 ||strcmp(word,"POP")==0 || strcmp(word,"LOG2")==0 ||strcmp(word,"MODULE")==0 ||strcmp(word,"FACTRL")==0 )
            {
                indicator ++;
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                if(strcmp(op1,"X")==0) strcat(code,"0000000000");
                  else strcat(code,"1000000000");
            }

        if(strcmp(word,"NOP")==0 ||strcmp(word,"HLT")==0 )
            {
                indicator ++;
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                strcat(code,"0000000000");
            }

        if(strcmp(word,"MOV")==0)
            {
                indicator ++;
                if(strcmp(op2,"X")==0||strcmp(op2,"Y")==0) strcat(word,"R");
                    else strcat(word,"I");
                strcpy(code,string_to_bin(FindInstrCode(word),6));
                if(strcmp(op1,"X")==0) strcat(code,"0");
                   else if(strcmp(op1,"Y")==0) strcat(code,"1");
                if(op2==NULL) strcat(code,"000000000");
                   else if (atoi(op1)>=0) strcat(code,string_to_bin(op2,9));
                            else strcat(code,integer_to_bin(512+atoi(op2),9));
            }

        if(indicator) //fprintf(fout,"%s ",code);
            fprintf(fout,"%.4lX ",binary_to_hexa(code));
    }
    printf("\tDONE!\t\n");
    fclose(fin);
    fclose(fout);
    system("pause");
    return 0;
}
/*___________________________________________________________________________
  tipuri de operatii:  X [0 sau 1]

 LDR R,IMM(address)  => 000000_X_000000000
 STR R,IMM(address)  => 000000_X_000000000

 BRZ IMM(pc_address) => 000000_1111111111
 ........................................
 JMP IMM(pc_address) => 000000_1111111111

 ADD R,IMM(number)   => 000000_X_000000000
 .........................................
 CMP R,IMM(number)   => 000000_X_000000000   // x/y cmp cu imm //
 CMP R,R( number )   => 000000_X_000000000   // doar x cu y //

 NOT R               => 000000_X_000000000   // ir[9] sel X sau Y //
 DEC R               => 000000_X_000000000   // ir[9] sel X sau Y //
 INC R               => 000000_X_000000000   // ir[9] sel X sau Y //

 MOV R,Acc           => 000000_X_000000000   // pt opcode movrr => x/y = acc
 MOV R,IMM           => 000000_X_000000000   // pt opcode movri => x/y = imm

 PSH                 => 000000_00000000000
 POP                 => 000000_00000000000
_______________________________________________________________________________
 "
 000000   .........
 000011   .........
 000100   ADD X,Y
 000101   Label
 000110   ADD X,2
 ..................
 ..................
 ..................
 010000   JMP Label ---> salt la adresa 000110
 "
*/
