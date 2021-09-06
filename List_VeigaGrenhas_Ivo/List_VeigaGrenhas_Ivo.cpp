#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>

//Definition der structs "data" und "list"
typedef struct data
{
	char bez[50];
	double preis;
} strudata;


typedef struct list
{
	struct list* pNext;
	struct data* pData;
} strulist;

//Funktion zum zurückgehen
void zurueck()
{
	printf("Druecke eine beliebige Taste um zurueck ins Hauptmenu zu kommen.");
	system("pause > nul");
}

//Funktion zum Zählen der Elemente
int getAnzahl(strulist* list)
{
	int Anzahl = 0;

	while (list != NULL)
	{
		list = list->pNext;
		Anzahl++;
	}
	return(Anzahl);
}

//Funktion zum Erstellen der Liste
strulist* createList()
{
	strulist* pStart = NULL;

	//Abfrage Anzahl Elemente
	int value;
	printf("Bitte geben Sie die Anzahl Elemente zum erstellen ein, geben Sie 0 ein, um zurueck ins Hauptmenu zu kommen: ");
	scanf_s("%i", &value);

	// Liste erstellen
	if (value == 0) {
		printf("Es wurden keine Elemente erstellt.\n");
		zurueck();
	}
	else if (value > 10000000 || value < 0) { 
		printf("Eingabe ungueltig, bitte geben Sie eine Nummer zwischen 0 und 10000000 ein.\n\n");
		zurueck();
	}
	else {
		strulist* pLast = NULL;

		srand((unsigned)time(NULL));

		//Startpunkt Zeit
		clock_t StartZeit = clock();

		for (int Index = 0; Index < value; Index++)
		{
			//Erstellt Liste
			strulist* pNew = (strulist*)malloc(sizeof(strulist));
			if (pNew == NULL) exit(-1);

			pNew->pData = (strudata*)malloc(sizeof(strudata));
			if (pNew->pData == NULL) exit(-1);

			pNew->pNext = NULL;

			//Festlegung Bezeichnung
			for (int i = 0; i < 3; i++) pNew->pData->bez[i] = rand() % 26 + 'A';
			pNew->pData->bez[3] = '\0';

			//Elementgenerierung 

			pNew->pData->preis = rand() % (1000 - 10 + 1) + 10 + rand() % (10) / 10.0;

			if (pStart == NULL) pStart = pNew;
			if (pLast != NULL) pLast->pNext = pNew;
			pLast = pNew;
		}
		printf("Es wurden %i Elemente generiert.\n", value);

		clock_t EndZeit = clock();
		double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
		printf("Die Generierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", value, Dauer);

		//Rückkehr Menu
		zurueck();
	}
	return pStart;
}

//Sortierung der Liste
void sortlist(strulist* list)
{
	//Definition aller nötigen Variabeln
	int Auswahl;
	int Auswahl2;
	int Anzahl = getAnzahl(list);
	strulist* reset = list;

	do
	{
		printf("Bitte geben Sie 1 fuer numerisch sortiert, 2 fuer alphabetisch sortiert und 3 fuer abbrechen ein: ");
		scanf_s("%i", &Auswahl2);

	} while (Auswahl2 != 1 && Auswahl2 != 2 && Auswahl2 != 3);
	//Abfrage aufsteigen, abgsteigend oder abbrechen

	
	if (Auswahl2 == 1)
	{
		do
		{
			printf("Bitte geben Sie 1 fuer aufsteigend sortiert, 2 fuer absteigend sortiert und 3 fuer abbrechen ein: ");
			scanf_s("%i", &Auswahl);

		} while (Auswahl != 1 && Auswahl != 2 && Auswahl != 3);

		//Je nach Auswahl Sortierung oder zurück ins Hauptmenu
		if (Auswahl == 1) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (list->pData->preis <= list->pNext->pData->preis) {
					list = list->pNext;
				}
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			printf("Die Sortierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", Anzahl, Dauer);
		}
		else if (Auswahl == 2) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (list->pData->preis >= list->pNext->pData->preis) {
					list = list->pNext;
				}
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			printf("Die Sortierung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else if (Auswahl == 3) {
			printf("Sortierung wurde abgebrochen.\n");
		}
	}
	else if (Auswahl2 == 2)
	{
		do
		{
			printf("Bitte geben Sie 1 fuer aufsteigend sortiert, 2 fuer absteigend sortiert und 3 fuer abbrechen ein: ");
			scanf_s("%i", &Auswahl);

		} while (Auswahl != 1 && Auswahl != 2 && Auswahl != 3);
		//Je nach Auswahl Sortierung oder zurück ins Hauptmenu
		if (Auswahl == 1) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();
			
			while (list->pNext != NULL)
			{
				if (strcmp(list->pData->bez,list->pNext->pData->bez) < 0){
					list = list->pNext;
				}
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			printf("Die Sortierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", Anzahl, Dauer);
		}
		else if (Auswahl == 2) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (strcmp(list->pData->bez, list->pNext->pData->bez) > 0) {
					list = list->pNext;
				}
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			printf("Die Sortierung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else if (Auswahl == 3) {
			printf("Sortierung wurde abgebrochen.\n");
		}
	}
	else if (Auswahl2 == 3) {
	printf("Sortierung wurde abgebrochen.\n");
}
	
	//Rückkehr Menu
	zurueck();
}

//Funktion zum Ausgeben der Liste
void printlist(strulist* list)
{
	//Definition aller nötigen Variabeln
	printf("Alle Elemente: \n");
	int Anzahl = getAnzahl(list);

	//Startpunkt Zeit
	clock_t StartZeit = clock();

	//Eigentliche Ausgabe mit Formatierung 
	for (strulist* i = list; i != NULL; i = i->pNext)
	{
		if (i->pData->preis < 100) {
			printf("Preis=00%.1f  Bez=%s\n", i->pData->preis, i->pData->bez);
		}
		else if (i->pData->preis >= 1000) {
			printf("Preis=%.1f  Bez=%s\n", i->pData->preis, i->pData->bez);
		}
		else {
			printf("Preis=0%.1f  Bez=%s\n", i->pData->preis, i->pData->bez);
		}
	}
	//Endpunkt & Ausgabe Zeit
	clock_t EndZeit = clock();
	double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
	printf("Die Ausgabe von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);

	//Rückkehr Menu
	zurueck();
}

//Funktion zum löschen von Menu
void dellist(strulist* list, int* Auswahl)
{
	int Anzahl = getAnzahl(list);

	//"Sind Sie sicher"-Warnung
	if (*Auswahl != 4) {
		//Warnung und Abfrage Auswahl
		printf("Sind Sie sicher, dass sie alle Elemente aus der Liste loeschen wollen, die Elemente werden unwiederruflich gelöscht?\n\n1) Ja\n2) Nein\n3/4) Ja und nicht mehr anzeigen\n");
		scanf_s("%i", Auswahl);

		if (*Auswahl == 1) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				strulist* temp = list;
				list = list->pNext;
				free(temp->pData);
				free(temp);
			}
			printf("Die Liste wurde Erfolgreich geloescht.\n");

			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			printf("Die loeschung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);

			zurueck();
		}
		else if (*Auswahl == 2 ) {
			printf("Es wurden keine Elemente geloescht.\n");
			zurueck();
		}
		else if (*Auswahl == 3) {
			*Auswahl = 4;
		}
		else if (*Auswahl == 4) {

		}
		else {
			printf("Auswahl ungueltig, bitte geben Sie eine Zahl zwischen 1 und 4 ein.\n");
			//Rückkehr Menu
			zurueck();
		}
	}

	if (*Auswahl == 4) {

		//Startpunkt Zeit wenn "nicht mehr Anzeigen" ausgewählt wurde
		clock_t StartZeit = clock();

		while (list->pNext != NULL)
		{
			strulist* temp = list;
			list = list->pNext;
			free(temp->pData);
			free(temp);
		}

		printf("Die Liste wurde Erfolgreich geloescht.\n");
		//Endpunkt & Ausgabe Zeit
		clock_t EndZeit = clock();
		double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
		printf("Die loeschung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		//Rückkehr Menu
		zurueck();
	}

}

//Funktion zum Aufruf von Menu
void menu()
{
	//Definition aller nötigen Variabeln
	strulist* list = NULL;
	int delAuswahl = 0;
	int* pdelAuswahl = &delAuswahl;
	bool Erfolgreich = false;
	int Auswahl = 0;

	do
	{
		//Menuinhalt
		system("CLS");
		printf("******************** Hauptmenu ********************\n");
		printf("Folgende Optionen stehen zur Verfuegung: \n\t1) Liste erstellen \n\t2) Liste sortieren\n\t3) Liste ausgeben\n\t4) Liste loeschen\n\t5) Programm beenden\n\nWaehlen Sie einer der aufgelisteten Optionen auf, indem Sie die zugewiesenen Zahlen eingeben.\n");
		printf("***************************************************\n");
		//Abfrage Auswahl
		scanf_s("%i", &Auswahl);
		//Weiterleiung zu den jeweiligen Funktionen
		if (Auswahl == 1) {
			if (list == NULL) {
				list = createList();
			}
			else {
				printf("Um eine neue Liste zu erstellen, muss die alte erst geloescht werden.\n\n");
				zurueck();
			}
		}
		else if (Auswahl == 2) {
			if (list != NULL) {
				sortlist(list);
			}
			else {
				printf("Sie muessen erst eine Liste erstellen, damit sie sortiert werden kann.\n\n");
				zurueck();
			}
		}
		else if (Auswahl == 3) {
			if (list != NULL) {
				printlist(list);
			}
			else {
				printf("Sie muessen erst eine Liste erstellen, damit sie ausgegeben werden kann.\n\n");
				zurueck();
			}

		}
		else if (Auswahl == 4) {
			if (list != NULL) {
				dellist(list, pdelAuswahl);

				//setzt list auf NULL, falls nicht "2) Nein" ausgewählt wurde.
				if (*pdelAuswahl != 2 && *pdelAuswahl <= 4) {
					list = NULL;
				}
			}
			else {
				printf("Sie muessen erst eine Liste erstellen, damit sie geloescht werden kann.\n\n");
				zurueck();
			}
		}
		else if (Auswahl == 5) {
			Erfolgreich = true;
		}
		else if (Auswahl = 6) {
			printf("Herzlichen Glueckwunsch, sie haben ein Easteregg endeckt!\n\n");
			zurueck();
		}
		else {
			if (Auswahl != 1 || Auswahl != 2 || Auswahl != 3 || Auswahl != 4 || Auswahl != 5 || Auswahl != 6) {
				printf("Auswahl ungueltig, bitte geben Sie einen Wert zwischen 1 und 5 ein.\n\n");
				zurueck();
			}
		}
	} while (Erfolgreich == false);
}

int main()
{
	menu();
}