/* PROGRAM ZALICZENIOWY - ADRIAN BELCIAK */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteka.h"

double protectPIN(char a[])
{
int k;
for(k=0; k<strlen(a) ; k++)
{
if ((a[k]=='0') || (a[k]=='1') || (a[k]=='2') || (a[k]=='3') || (a[k]=='4') || (a[k]=='5') || (a[k]=='6') || (a[k]=='7') || (a[k]=='8') || (a[k]=='9')) 
	{ }
else
{
printf("\n\tBlad! Masz podac tylko liczbe! Inne znaki sa NIEDOZWOLONE!\n");
return 1;
} 
} 
} 

char *hash(char *string) {
int i;
for(i=0;string[i];i++){
string[i]= (65 + (string[i] - 62) % 14) ; /* string[i]+3; */
}
return (string);
}

char *hashPass(char *string) {
int i;
for(i=0;string[i];i++){
string[i]= (65 + (string[i] - 59) % 14) ; 
}
return (string);
}
   

void wczytajStart()
{
	printf("\n\t\t       WITAMY W BANKOMACIE!!!\n\n");
	printf("\t\t*******************************\n");
	printf("\t\t* NACIŚNIJ 1 BY PRZEJŚĆ DALEJ * \n");
	printf("\t\t*******************************\n\n\n\n");
}

void sprawdzPlik(char src[50])
{
int dlugosc = 140;
char path[dlugosc];
getcwd(path, dlugosc);
strcat(path, src);
 
   FILE *plik;
    plik = fopen(path,"r");
    if( plik == NULL)
    {
		printf("Bankomat nie może działać z powodu braku konfiguracji!\n");
		exit(-1);
    }
	else
    {
	
	}
	
}

void wczytajWybor()
{
	system("clear"); 
	printf("\n\t       NACISNIJ ODPOWIEDNI KLAWISZ BY WYKONAĆ OPERACJE!!!!\n\n");
	printf("*******************************\n");
	printf("* 1 *     WYPŁATA GOTÓWKI     * \n");
	printf("*******************************\n\n");
	
	printf("*******************************\n");
	printf("* 2 *      WPŁATA GOTÓWKI     * \n");
	printf("*******************************\n\n");
	
	printf("*******************************\n");
	printf("* 3 *    SPRAWDZENIE SALDA    * \n");
	printf("*******************************\n\n");
	
	printf("*******************************\n");
	printf("* 4 *       ZMIANA PINU       * \n");
	printf("*******************************\n\n");
	
	printf("*******************************\n");
	printf("* 9 *     TRYB SERWISOWY      * \n");
	printf("*******************************\n\n");
}

