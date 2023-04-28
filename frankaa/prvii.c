/*1. Potrebno je iz datoteke osobe.txt proèitati podatke o osobama (ime, prezime),
za svaku osobu nasumièno izgenerirati temperaturu tijela te
navedene podatke zapisati u jednostruko vezanu listu struktura.
Zatim je u konzoli potrebno ispisati ispisati sve osobe kao i njihovu temperaturu
tijela.
Ocjena 2: Iz postojeæe liste izbrisati sve osobe èija je temperatura iznad 37.0 i
ispisati novu listu.
Napomena 1: format zapisa podataka u datoteci je "<ime> <prezime>", npr:
Ivan Ivic
Jure Juric
Napomena 2: temperatura tijela mora biti decimalan broj s 1 decimalnom znamenkom (npr.
37.2) te mora biti u rasponu
od 35.0 do 41.0
Napomena 3: nasumièno generiranje temperature može se odraditi na sljedeæi naèin:
- Izgenerirajte nasumièni broj izmeðu 350 i 410 i zapišite ga u varijablu tipa int
- int varijablu podijelite sa 10 (pripazite da ne doðe do gubitka informacije)
Napomena 4: strukturu možete nazvati Osoba a mora sadržavati ime, prezime i
temperaturu
------osobe.txt ima 48 ljudi napisane <ime> <prezime>
------osobe2.txt u nju zapisujes ljude i njihovu temperaturu <ime> <prezime>
<temperatura>
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _osoba;
typedef struct _osoba osoba;
typedef osoba* position;

struct _osoba {

	char ime[20];
	char prezime[20];
	float temperatura;

	position next;
};

int CitanjeDat(position head);
int GeneriranjeTemp();
int SpremanjeUListu(position head, char ime[20], char prezime[20], float temperatura);
int IspisListe(position head);
int SpremanjeUDat(position head);
int BrisanjeSumnjivih(position head);




int main() {

	osoba head;
	srand((unsigned int)(time));
	int result;

	head.next = NULL;

	result = CitanjeDat(&head);
	result = SpremanjeUDat(&head);

	printf("svi studenti: \n");

	result = IspisListe(&head);

	result = BrisanjeSumnjivih(&head);

	printf("\nsvi studenti koji nisu sumnjivi: \n");
	printf("\n");
	result = IspisListe(&head);

	return 0;
}

int CitanjeDat(position head) 
{
	char buffer[1024] = "\0";
	char ime[20] = "\0";
	char prezime[20] = "\0";
	float temperatura;
	int result = 0;

	FILE* file;
	file = fopen("osobe.txt", "r");
	if (file == NULL)
	{
		printf("nije se otvorila");
		return -1;
	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		strcpy(ime, "\0");
		strcpy(prezime, "\0");
		temperatura = 0;

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
			{
				sscanf(buffer, "%s %s", ime, prezime);
				temperatura = GeneriranjeTemp();
			}
		result = SpremanjeUListu(head, ime, prezime, temperatura);
		if (result == -1)
		{
			fclose(file);
			return -1;
		}
	}
	fclose(file);
	return 0;
}

int GeneriranjeTemp()
{
	float x;

	x = (rand() % (410 - 350 + 1)) + 350;

	x = x / 10.0f;

	return x;

}

int SpremanjeUListu(position head, char ime[20], char prezime[20], float temperatura)
	{
		position temp;
		temp = (position)malloc(sizeof(osoba));

		if (temp == NULL)
		{
			printf("nije se alocirala");
			return -1;

		}

		strcpy(temp->ime, ime);
		strcpy(temp->prezime, prezime);
		temp->temperatura = temperatura;

		while (head->next != NULL)
		{
			head = head->next;
		}
		temp->next = NULL;
		head->next = temp;

		return 0;
	}

int IspisListe(position head)
{
	head = head->next;
	while (head != NULL)
	{
		printf("%s %s \t%.1f \n", head->ime, head->prezime, head->temperatura);
		head = head->next;

	}



	return 0;
}

int SpremanjeUDat(position head)
{
	FILE* file;
	file = fopen("osobe1.txt", "w");
	head = head->next;
	if (file == NULL)
	{
		printf("nije se otvorila!");
		return -1;
	}

	while (head != NULL)
	{
		fprintf(file, "%s %s\t %.1f\n", head->ime, head->prezime, head->temperatura);
		head = head->next;
	}

	fclose(file);
	return 0;
}

int BrisanjeSumnjivih(position head)
{

	position temp;

	while (head->next !=NULL)
	{
		temp = head->next;
		if (temp->temperatura > 37.0)
		{
			head->next = temp->next;
			free(temp);
		}
		else
		{
			head = head->next;
		}
	}
	return 0;
}
