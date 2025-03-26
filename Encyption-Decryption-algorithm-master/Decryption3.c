/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define red SetColor(36);
#define green SetColor(34);
#define blue SetColor(35);
#define reset SetColor(31);
#define i_t 0.5
#define i_p 0.4

void delay(float number_of_seconds)
{int milli_seconds = 1000 * number_of_seconds;
 clock_t start_time = clock();
 while (clock() < start_time + milli_seconds);}
void SetColor(int ForgC)
{WORD wColor;
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 { wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
   SetConsoleTextAttribute(hStdOut, wColor);}
 return;
}
int main()
{ 	
    red
    delay(i_t);											          //
    printf(" #  \"Hello World\"  # \n");		                 //
	green                                                       //
	delay(i_t);									               //
    printf("\n | Starting program");				          // Interface
	delay(i_p); printf(".");						         //
	delay(i_p); printf(".");					            //
	delay(i_p); printf(".");                               //
	delay(i_p); printf(" |\n");					          //
    delay(i_t);                                          //
    printf(" | Reverse Encryption initialized | \n\n"); //

    char input[1000000];      //
    int length;              // variable declaration
    int i,j,ok;             //
    FILE* in;              //
    FILE* out;            //
    char filein[200];    //
    char fileout[200];  //
    char aux[51];      //

    strcpy(filein,"C:\\Users\\lenovo\\Desktop\\");
    strcpy(fileout,"C:\\Users\\lenovo\\Desktop\\");
    blue
    printf("  Meniu 1 [console]| 2 [file]: ");
    scanf("%d",&i);
    printf("\n");

    switch(i){  
      case 1 : {    delay(i_t); ok=0;							    //
                    reset                                          //
                    getchar();  			                      //
                    printf("  Introduceti text cryptat : ");     //
                    scanf("%[^\n]s",input);                     // taking input
	                green								       //
	                delay(i_t);                               //
                    printf("\n | Decryption started | \n");  //
                    delay(i_t);                             //

                    length = strlen(input);				       //
                	blue									   //
                    printf(" < Encryption result >");          //
                    delay(i_p); printf(" < ");                 //
                    char *p = input;
                    while (*p) {
                        if (isdigit(*p)){
                                delay(0.02);
                                int val = strtol(p, &p, 10);
                                if (p[1]=='.')
                                {
                                    if (p[2]=='.')
                                        {
                                            if(p[3]=='.')
                                            {
                                                if(p[4]=='.'){
                                                    if(p[5]=='.')
                                                    {
                                                        printf("%c?", val);
                                                    }
                                                    else printf("%c!", val);
                                                }
                                                else printf("%c.", val);

                                            } else printf("%c,", val);
                                        } else printf("%c ", val);
                                } else printf("%c", val);
                        } else p++;
                    }										       
                    printf(" >\n"); break;
               }
                    
      case 2 : {    printf("  Nume fisier citire: ");scanf("%s",aux);ok=1;
                    strcpy(filein,aux);
                    printf("  Nume fisier scriere: ");scanf("%s",aux);
                    strcpy(fileout,aux);
                    in = fopen(filein,"rt");
                    out = fopen(fileout,"wt");
                    out = fopen(fileout,"at");
                    green
	                delay(i_t);                             
                    printf("\n | Decryption started | \n"); 
                    fgets(aux,50,in);
                    fprintf(out,aux);
                    aux[strcspn(aux,"\n")] = '\0';
                    blue
                    printf("\n | Decrypting \" %s \" \n\n",aux); 
                    while( fgets(input,10000,in) ){
                        char *p = input;
                        while (*p) {
                            if (isdigit(*p)){
                                int val = strtol(p, &p, 10);
                                if (p[1]=='.')
                                 {
                                    if (p[2]=='.')
                                     {
                                        if(p[3]=='.')
                                         {
                                            if(p[4]=='.'){
                                                if(p[5]=='.')
                                                {

                                                    fprintf(out,"%c?", val);
                                                }
                                                else fprintf(out,"%c!", val);
                                             }
                                            else fprintf(out,"%c.", val);
                                         } else fprintf(out,"%c,", val);
                                      } else fprintf(out,"%c ", val);
                                } else fprintf(out,"%c", val);
                         } else p++;
                       } fprintf(out,"\n");				
                    }
                   break;
               }                

    }
    green
    delay(i_t);
    printf(" | Decryption stopped | \n");
	delay(i_t);
	printf(" | Program stopping");
	delay(i_p); printf(".");
    delay(i_p); printf(".");
	delay(i_p); printf(".");
    delay(i_p); printf(" |\n");
    delay(i_p);
    reset
    if (ok==1){
        printf("    Continut output[1/0]: ");scanf("%d",&j);
        if (j==1)
         {  fclose(out);
            out = fopen(fileout,"rt");
            char output[10000];
            while(fgets(output,9999,out))
             {
                printf("  %s",output);
             }
        }
    }
    system("pause");
    return 0;
}
