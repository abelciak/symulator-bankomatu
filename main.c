/* PROGRAM ZALICZENIOWY - ADRIAN BELCIAK */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include "biblioteka.h"
struct Klienci
{
    char id[30];
    char pin[50];
    float kwota;

};

int main(int argc, char **argv)
{

if (argc > 1){
int i;
for (i=1; i < argc; i++){
if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
printf("\nProgram symuluje działanie bankomatu. \n\nKlient ma możliwość:\n-wypłaty gotówki\n-wpłaty gotówki\n-sprawdzenia salda swojego konta\n-zmiany kodu pin\n\nAdministrator w trybie serwisowym ma możliwość:\n-zobaczenia listy klientów\n-dodania klienta\n-usunięcie klienta\n-zmiany hasła dostępu do trybu serwisowego.\n\nDane dostępowe klientów przechowywane są w pliku 'bankomat_klienci.txt'. Zamieszczona jest tam informacja o numerze klienta, jego pinie oraz stanie gotówki.\n\nDane dostępowe do trybu serwisowego przechowywane są w pliku 'bankomat_pass.txt'. Standardowe hasło do trybu serwisowego to: bankomat123\n\nPrzykładowe konto: ID: 1111 PIN: 1234\n\n");
}
}
return 0;
}

	system("clear"); 
	struct Klienci klient[50];
	int i=0, wyborA=0, wyborB=0, wyborADMIN=0, liczbaKlientow=0, check=0, istnieje, istniejePIN, aktualnyKlient;
	char id[20], pin[20], hasloORG[50], haslo[50];
	float nowaKwota;

sprawdzPlik("/bankomat_klienci.txt");	
sprawdzPlik("/bankomat_pass.txt");	
	
	/* START ODCZYT DANYCH KLIENTOW */
	FILE *plik;
    plik = fopen("bankomat_klienci.txt","r");
    if( plik == NULL)
    {
		printf("Bankomat nie może działać z powodu braku konfiguracji!\n");
		return(-1);
    }
	else
    {
        for (i=0; ( !feof(plik) ) ;i++)
        {
		fscanf(plik,"%s %s %f\n",klient[i].id, klient[i].pin, &klient[i].kwota);
		liczbaKlientow++;
		}
    }
    fclose(plik);   
	/* KONIEC ODCZYT DANYCH KLIENTOW */
	
	
wczytajStart();
printf("Twoj wybor: ");
scanf("%d",&wyborA);

if (wyborA!=1) { return(-1); }

wczytajWybor();

printf("Twoj wybor: ");
scanf("%d",&wyborB);

system("clear"); 
if (wyborB==1)
{ printf("\t\t* WYPŁATA GOTÓWKI *\n");
printf("\t\t*******************\n"); }
else if (wyborB==2)
{ printf("\t\t* WPŁATA GOTÓWKI *\n");
printf("\t\t*******************\n"); }
else if (wyborB==3)
{ printf("\t\t* SPRAWDZENIE SALDA *\n");
printf("\t\t*******************\n"); }
else if (wyborB==4)
{ printf("\t\t* ZMIANA PINU *\n");
printf("\t\t*******************\n"); }
else if (wyborB==9)
{ printf("\t\t* TRYB SERWISOWY *\n");
printf("\t\t*******************\n"); }
else
{ return(-1); }

if ((wyborB==1) || (wyborB==2) || (wyborB==3) || (wyborB==4))
{
printf("Podaj Twój ID klienta: ");
scanf("%s",id);


for (check=0;check<=liczbaKlientow;check++)
{
/* Sprawdzenie czy ID istnieje */
if (!(strcmp(klient[check].id,id))) { istnieje=1; aktualnyKlient=check; 	break; }
}
if (istnieje!=1) { printf("\n\tKonto o podanym identyfikatorze nie istnieje! Sprobuj ponownie!\n\n"); return -1; }


printf("Podaj Twój pin: ");
scanf("%s",pin);
hash(pin);

for (check=0;check<=liczbaKlientow;check++)
{
/* Sprawdzenie czy PIN jest ok */
if (!(strcmp(klient[check].pin,pin))) { istniejePIN=1; 	break; }
}
if (istniejePIN!=1) { printf("\n\tPodany kod pin jest błędny! Sprobuj ponownie!\n\n"); return -1; }
}

else if (wyborB==9)
{
/* WYBOR TRYBU SERWISOWEGO */

/* START ODCZYT HASLA */
	FILE *plik;
    plik = fopen("bankomat_pass.txt","r");
    if( plik == NULL)
    {
		printf("Nie mozesz przejsc do trybu serwisowego z powodu braku konfiguracji!\n");
		return(-1);
    }
	else
    {
        for (i=0; ( !feof(plik) ) ;i++)
        {
		fscanf(plik,"%s\n",hasloORG);
		}
    }
    fclose(plik);   
	/* KONIEC ODCZYT HASLA */



printf("Podaj hasło administratora: ");
scanf("%s",haslo);
hashPass(haslo);

if (!strcmp(hasloORG, haslo)) {  }
else { printf("\n\n\tNiepoprawne dane! Sprobuj ponownie!\n"); return(-1); }




/* KONIEC WYBORU TRYBU SERWISOWEGO */
}
else { 
return(-1); }




/* GDY WYBRANO WYPLATA GOTOWKI START */
if (wyborB==1)
{
nowaKwota=klient[aktualnyKlient].kwota;
float wyplata;

printf("Wpisz kwotę, jaką chcesz wypłacić: ");
scanf("%f",&wyplata);
	
if (wyplata>klient[aktualnyKlient].kwota)
{
printf("\n\tNie masz takiej kwoty na koncie! Spróbuj ponownie!\n");
return -1;
}
else if (fmod(wyplata,10)!=0)
{
printf("\n\tNie możesz wypłacić gotówki! Kwota musi być wielokrotnością 10 PLN.\n\t\t\t\t Spróbuj ponownie!\n");
return -1;
}
else
{
nowaKwota=klient[aktualnyKlient].kwota-wyplata;
printf("\n\n\t\tTwoja wypłata gotówki została zrealizowana!\n\t\tTwój aktualny stan konta: %.2f PLN\n\t\t\tZapraszamy ponownie!\n",nowaKwota);
}
}
/* GDY WYBRANO WYPLATA GOTOWKI KONIEC */


/* GDY WYBRANO WPLATA GOTOWKI START */
if (wyborB==2)
{
float wplata;
nowaKwota=klient[aktualnyKlient].kwota;
printf("Wpisz kwotę, jaką chcesz wpłacić: ");
scanf("%f",&wplata);

if (fmod(wplata,10)!=0)
{
printf("\n\tNie możesz wpłacić gotówki! Kwota musi być wielokrotnością 10 PLN.\n\t\t\t\t Spróbuj ponownie!\n");
return -1;
}
else
{
nowaKwota=klient[aktualnyKlient].kwota+wplata;
printf("\n\n\t\tTwoja wpłata gotówki została zrealizowana!\n\t\tTwój aktualny stan konta: %.2f PLN\n\t\t\tZapraszamy ponownie!\n",nowaKwota);
}

}
/* GDY WYBRANO WPLATA GOTOWKI KONIEC */

/* GDY WYBRANO SPRAWDZENIE STANU KONTA START */
if (wyborB==3)
{
nowaKwota=klient[aktualnyKlient].kwota;
printf("\n\n\t\tTwój aktualny stan konta to: %.2f PLN\n\t\t\tZapraszamy ponownie!\n",nowaKwota);
}
/* GDY WYBRANO SPRAWDZENIE STANU KONTA KONIEC */

/* GDY WYBRANO ZMIANE PINU START */
char nowyPIN[20]="";
if (wyborB==4)
{
printf("Podaj Twój nowy pin: ");
scanf("%s",nowyPIN);
double nowyPINspr=atof(nowyPIN);

if (protectPIN(nowyPIN)==1) { return(-1);  }  
else if ((nowyPINspr<10000) && (nowyPINspr>999)) { printf("\n\n\t\tTwój pin został zmieniony na %s!\n\t\tZapraszamy ponownie!\n",nowyPIN); }
else { printf("\n\tTwój pin musi być w przedziale od 1000 do 9999 !\n\t\tSpróbuj ponownie!\n"); }

}
/* GDY WYBRANO ZMIANE PINU KONIEC */


/* GENEREROWANIE ZAKTUALIZOWANYCH DANYCH - WPLATA I WYPLATA START*/
if ((wyborB==1) || (wyborB==2))
{
FILE *nowy;
int zz;
    nowy = fopen("bankomat_klienci.txt","w");
    if( nowy == NULL)
    {
		printf("Bankomat nie może działać z powodu bledu technicznego!\n");
		return(-1);
    }
	else
    {
        for (zz=0; zz<liczbaKlientow; zz++)
        {
		if (!strcmp(klient[zz].id, klient[aktualnyKlient].id))  { fprintf(nowy,"%s %s %.2f\r\n",klient[zz].id, klient[zz].pin, nowaKwota);	 }
		else { fprintf(nowy,"%s %s %.2f\r\n",klient[zz].id, klient[zz].pin, klient[zz].kwota);	 }
		}
    }
    fclose(nowy);
}	
/* GENEREROWANIE ZAKTUALIZOWANYCH DANYCH - WPLATA I WYPLATA KONIEC*/

/* GENEREROWANIE ZAKTUALIZOWANYCH DANYCH - ZMIANA PIN START*/
else if (wyborB==4)
{
FILE *nowy;
int zz;

    nowy = fopen("bankomat_klienci.txt","w");
    if( nowy == NULL)
    {
		printf("Bankomat nie może działać z powodu bledu technicznego!\n");
		return(-1);
    }
	else
    {
        for (zz=0; zz<liczbaKlientow; zz++)
        {
		
		if (!strcmp(klient[zz].id, klient[aktualnyKlient].id))  { fprintf(nowy,"%s %s %.2f\r\n",klient[zz].id, hash(nowyPIN), klient[zz].kwota);	 }
		else { fprintf(nowy,"%s %s %.2f\r\n",klient[zz].id, klient[zz].pin, klient[zz].kwota);	  }
		}
    }
    fclose(nowy);
}	
/* GENEREROWANIE ZAKTUALIZOWANYCH DANYCH - ZMIANA PIN KONIEC*/

/* TRYB ADMINA START */
else if (wyborB==9)
{
int yy;
printf("\nLista klientów(%d)\n\n",liczbaKlientow);

/* wypisanie */
printf(" ID\t|  Stan konta\n");
printf("-------\t| ------------\n");
for (yy=0; yy<liczbaKlientow; yy++)
{
printf(" %s\t| %.2f PLN\n",klient[yy].id,klient[yy].kwota);
}

/* wybor */
printf("\n\nMożesz wykonać następujące operacje: 1 - dodaj klienta, 2 - usuń klienta, 3 -zmiana hasła trybu serwisowego, 0 - wyjście\n\nTwój wybór: ");
scanf("%d",&wyborADMIN);

if (wyborADMIN==0)
{
	printf("\n\tTryb serwisowy zakończony! Do zobaczenia!\n");
}
else if (wyborADMIN==1)
{
char dodajPIN[30];
float dodajKWOTA;

printf("Podaj pin dla klienta: " );
scanf("%s",dodajPIN);

double dodajPINspr=atof(dodajPIN);
if (protectPIN(dodajPIN)==1) { return(-1);  }  
else if ((dodajPINspr<10000) && (dodajPINspr>999)) {  }
else { printf("\n\tPin musi być w przedziale od 1000 do 9999 !\n\t\tSpróbuj ponownie!\n"); return(-1); }

printf("Podaj kwotę dla klienta(w PLN): " );
scanf("%f",&dodajKWOTA);

int max, kk;

for (kk=0; kk<(liczbaKlientow);kk++) 
if (atof(klient[kk].id)>max) 
{
   max=(atof(klient[kk].id))+1;
} 
printf("\n\n\t\tKlient został dodany!!!\n\t\tID Klienta: %d\n\t\tPIN Klienta: %s\n\t\tKwota Klienta: %.2f PLN\n",max,dodajPIN, dodajKWOTA); 

/* DODANIE KLIENTA START */
FILE *nowy;
int zz;

    nowy = fopen("bankomat_klienci.txt","w");
    if( nowy == NULL)
    {
		printf("Bankomat nie może działać z powodu bledu technicznego!\n");
		return(-1);
    }
	else
    {
		fprintf(nowy,"%d %s %.2f\r\n",max, hash(dodajPIN), dodajKWOTA);
        for (zz=0; zz<liczbaKlientow; zz++)
        {
		fprintf(nowy,"%s %s %.2f\r\n",klient[zz].id, klient[zz].pin, klient[zz].kwota);	  
		}
		
			 
    }
    fclose(nowy);
/* DODANIE KLIENTA KONIEC*/
}
else if (wyborADMIN==2)
{
char podajID[20];
int uu, istniejeD=0;
printf("Podaj ID klienta do usunięcia: ");
scanf("%s",podajID);

for (uu=0;uu<=liczbaKlientow;uu++)
{
if (!(strcmp(klient[uu].id,podajID))) {  aktualnyKlient=check; istniejeD=1;	


FILE *nowy;
int aa;
    nowy = fopen("bankomat_klienci.txt","w");
    if( nowy == NULL)
    {
		printf("Bankomat nie może działać z powodu bledu technicznego!\n");
		return(-1);
    }
	else
    {
        for (aa=0; aa<liczbaKlientow; aa++)
        {
		if (!strcmp(klient[aa].id, podajID))  { 	 }
		else { fprintf(nowy,"%s %s %.2f\r\n",klient[aa].id, klient[aa].pin, klient[aa].kwota);	 }
		}
    }
    fclose(nowy);
printf("\n\n\t\tKlient został usunięty!!!\n");	
break;


}

} /* koniec for */
if (istniejeD!=1) { printf("\n\tKlient o podanym identyfikatorze nie istnieje! Sprobuj ponownie!\n\n"); return -1; }

}

else if (wyborADMIN==3)
{
char noweHaslo[50];
printf("Podaj Twoje nowe hasło: ");
scanf("%s",noweHaslo);

hashPass(noweHaslo);

FILE *nowyPass;
int zz;

    nowyPass = fopen("bankomat_pass.txt","w");
    if( nowyPass == NULL)
    {
		printf("Hasło nie może zostać zapisane z powodu braku pliku konfiguracyjnego !\n");
		return(-1);
    }
	else
    {
        for (zz=0; zz<1; zz++)
        {
		fprintf(nowyPass,"%s",noweHaslo);	  
		}
    }
    fclose(nowyPass);
	
	printf("\n\tHasło do trybu serwisowego zostało zmienione!\n\tOd tego momentu logujesz się tylko nowym hasłem!\n");
}


else
{
printf("Niepoprawny wybór. Spróbuj ponownie\n"); return(-1);
}


}
/* TRYB ADMINA KONIEC */



}