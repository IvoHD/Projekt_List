#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include<conio.h>
//Definition der structs "data" und "list"
typedef struct data
{
	char bez[2];
	double preis;
} strudata;


typedef struct list
{
	struct list* pNext;
	struct data* pData;
	bool sorted;
} strulist;

int getAnzahl(strulist*);

//Funktion zum zurückgehen inkl. Textübergabe
void zurueck(const char* pFormat = NULL, ...)
{
	char OutText[255];
	va_list args;

	va_start(args, pFormat);

	if (pFormat != NULL) {
		vsprintf_s(OutText, pFormat, args);
		printf("%s\n", OutText);
	}
	printf("Druecke eine beliebige Taste um zurueck ins Hauptmenu zu kommen.");
	system("pause > nul");
}

void ausgabelist(strulist** list, int size, bool t)
{
	if (t) {
		for (int i = 0; i < size; i++) {
			if (list[i] != NULL) printf("Liste %i:\tAnzahl Elemente:  %i\t Liste Sortiert: %s\n", (i + 1), getAnzahl(list[i]), list[i]->sorted ? "Ja" : "Nein");
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			if (list[i] != NULL) printf("Liste %i:\tAnzahl Elemente:  %i\t Liste Sortiert: %s\n", (i + 1), getAnzahl(list[i]), list[i]->sorted ? "Ja" : "Nein");
			else printf("Liste %i:\tAnzahl Elemente:  NULL\n", (i+1));
		}
	}
	zurueck();
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
	return Anzahl;
}
strulist* ListCompare(strulist* list1, strulist* list2) 
{
	return 0;//Muss noch ausprogrammiert werden.
}
strulist* EditList(strulist* list)
{
	return 0;//Muss noch ausprogrammiert werden.
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
	if (value == 0) zurueck("Es wurden keine Elemente erstellt.\n");
	else if (value > 10000000 || value < 0) zurueck("Eingabe ungueltig, bitte geben Sie eine Nummer zwischen 0 und 10000000 ein.\n\n");
	else {
		strulist* pLast = NULL;

		srand((unsigned)time(NULL));

		//Startpunkt Zeit
		clock_t StartZeit = clock();

		for (int i = 0; i < value; i++)
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

			pNew->pData->preis = rand() % (999 - 10 + 1) + 10 + rand() % (10) / 10.0;
			pNew->sorted = false;
			if (pStart == NULL) pStart = pNew;
			if (pLast != NULL) pLast->pNext = pNew;
			pLast = pNew;
		}
		printf("Es wurden %i Elemente generiert.\n", value);

		clock_t EndZeit = clock();
		double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;

		//Rückkehr Menu
		zurueck("Die Generierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", value, Dauer);
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

	//Abfrage aufsteigen, abgsteigend oder abbrechen
	do
	{
		printf("Bitte geben Sie 1 fuer numerisch sortiert, 2 fuer alphabetisch sortiert und 3 fuer abbrechen ein: ");
		Auswahl2 = _getche() - 48;
		printf("\n");
	} while (Auswahl2 != 1 && Auswahl2 != 2 && Auswahl2 != 3);


	if (Auswahl2 == 1)
	{
		do
		{
			printf("Bitte geben Sie 1 fuer aufsteigend sortiert, 2 fuer absteigend sortiert und 3 fuer abbrechen ein: ");
			Auswahl = _getche() - 48;
			printf("\n");
		} while (Auswahl != 1 && Auswahl != 2 && Auswahl != 3);

		//Je nach Auswahl Sortierung oder zurück ins Hauptmenu
		if (Auswahl == 1) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (list->pData->preis <= list->pNext->pData->preis) list = list->pNext;
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			list->sorted = true;
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			zurueck("Die Sortierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", Anzahl, Dauer);
		}
		else if (Auswahl == 2) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (list->pData->preis >= list->pNext->pData->preis) list = list->pNext;
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			list->sorted = true;
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			zurueck("Die Sortierung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else if (Auswahl == 3) zurueck("Sortierung wurde abgebrochen.\n");
	}
	else if (Auswahl2 == 2)
	{
		//Auswahl aufsteigend, absteigen oder abbrechen
		do
		{
			printf("Bitte geben Sie 1 fuer aufsteigend sortiert, 2 fuer absteigend sortiert und 3 fuer abbrechen ein: ");
			Auswahl = _getche() - 48;
			printf("\n");
		} while (Auswahl != 1 && Auswahl != 2 && Auswahl != 3);
		//Je nach Auswahl Sortierung oder zurück ins Hauptmenu
		if (Auswahl == 1) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (strcmp(list->pData->bez, list->pNext->pData->bez) < 0) list = list->pNext;
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			list->sorted = true;
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			zurueck("Die Sortierung von %i von Elementen hat %.3lf Sekunden gedauert.\n", Anzahl, Dauer);
		}
		else if (Auswahl == 2) {
			//Startpunkt Zeit
			clock_t StartZeit = clock();

			while (list->pNext != NULL)
			{
				if (strcmp(list->pData->bez, list->pNext->pData->bez) > 0) list = list->pNext;
				else {
					strudata* temp = list->pData;

					list->pData = list->pNext->pData;
					list->pNext->pData = temp;
					list = reset;
				}
			}
			//Endpunkt & Ausgabe Zeit
			clock_t EndZeit = clock();
			list->sorted = true;
			double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
			zurueck("Die Sortierung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else if (Auswahl == 3) zurueck("Sortierung wurde abgebrochen.\n");
	}
	else if (Auswahl2 == 3) zurueck("Sortierung wurde abgebrochen.\n");
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
		printf("Preis=%7.1f	 Bez=%s\n", i->pData->preis, i->pData->bez);
		/*
		if (i->pData->preis < 100) printf("Preis=00%.1f  Bez=%s\n", i->pData->preis, i->pData->bez);
		else if (i->pData->preis >= 1000) printf("Preis=%.1f  Bez=%s\n", i->pData->preis, i->pData->bez);
		else printf("Preis=0%.1f  Bez=%s\n", i->pData->preis, i->pData->bez); */
	}
	//Endpunkt, Ausgabe Zeit & zurück ins Menu
	clock_t EndZeit = clock();
	double Dauer = ((double)EndZeit - (double)StartZeit) / (double)CLOCKS_PER_SEC;
	zurueck("Die Ausgabe von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
}

//Funktion zum löschen von Menu
void dellist(strulist* list, int* Auswahl)
{
	int Anzahl = getAnzahl(list);

	//"Sind Sie sicher"-Warnung
	if (*Auswahl != 3) {
		//Warnung und Abfrage Auswahl
		printf("Sind Sie sicher, dass sie alle Elemente aus der Liste loeschen wollen? Die Elemente werden unwiederruflich geloescht.\n\n1) Ja\n2) Nein\n3) Ja und nicht mehr anzeigen\n");
		*Auswahl = _getche() - 48;
		printf("\n");

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
			zurueck("Die loeschung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else if (*Auswahl == 2) zurueck("Es wurden keine Elemente geloescht.\n");
		else if (*Auswahl == 3) {
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
			zurueck("Die loeschung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
		}
		else zurueck("Auswahl ungueltig, bitte geben Sie eine Zahl zwischen 1 und ein.\n");
	}
	else if (*Auswahl == 3) {
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
		zurueck("Die loeschung von %i Elementen hat %.3lf Sekunden gedauert.\n\n", Anzahl, Dauer);
	}
}


//Funktion zum Aufruf von Menu
strulist* menu(strulist* list)
{
	//Definition aller nötigen Variabeln
	int delAuswahl = 0;
	int* pdelAuswahl = &delAuswahl;
	bool Erfolgreich = false;
	int Auswahl = 0;

	do
	{
		//Menuinhalt
		system("CLS");
		printf("******************** Hauptmenu ********************\n");
		printf("Folgende Optionen stehen zur Verfuegung: \n\t1) Liste erstellen \n\t2) Liste sortieren\n\t3) Liste ausgeben\n\t4) Liste loeschen\n\t5) Zum Listenmenu\n\nWaehlen Sie einer der aufgelisteten Optionen auf, indem Sie die zugewiesenen Zahlen eingeben.\n");
		printf("***************************************************\n");
		//Abfrage Auswahl
		Auswahl = _getche() - 48;
		printf("\n");
		//Weiterleiung zu den jeweiligen Funktionen
		if (Auswahl == 1) {
			if (list == NULL) list = createList();
			else zurueck("Um eine neue Liste zu erstellen, muss die alte erst geloescht werden.\n\n");
		}
		else if (Auswahl == 2) {
			if (list != NULL) sortlist(list);
			else zurueck("Sie muessen erst eine Liste erstellen, damit sie sortiert werden kann.\n\n");
		}
		else if (Auswahl == 3) {
			if (list != NULL) printlist(list);
			else zurueck("Sie muessen erst eine Liste erstellen, damit sie ausgegeben werden kann.\n\n");
		}
		else if (Auswahl == 4) {
			if (list != NULL) {
				dellist(list, pdelAuswahl);

				//setzt list auf NULL, falls nicht "1) Ja" ausgewählt wurde.
				if (*pdelAuswahl == 1 || *pdelAuswahl == 3) list = NULL;
			}
			else zurueck("Sie muessen erst eine Liste erstellen, damit sie geloescht werden kann.\n\n");
		}
		else if (Auswahl == 5) Erfolgreich = true;
		else if (Auswahl == 6) zurueck("Herzlichen Glueckwunsch, sie haben ein Easteregg endeckt!\n\n");
		else zurueck("Auswahl ungueltig, bitte geben Sie einen Wert zwischen 1 und 5 ein.\n\n");
	} while (!Erfolgreich);

	return list;
}

void Hauptmenu(strulist** pStartList)
{
	bool Erfolgreich = false;
	bool Erfolgreich2 = false;
	bool start = true;
	int size;
	int Auswahl;

	//Abfrage Auswahl 
	if (start) {
		Erfolgreich = false;
		do
		{
			printf("\nWie viele listen wollen Sie erstellen?\n");
			scanf_s("%i", &size);

			if (size > 0 && size < 100000) {
				pStartList = (strulist * *)malloc(size * sizeof(strulist*)); //strulist
				if (pStartList == NULL) exit(-1);
				for (int i = 0; i <= size; i++) pStartList[i] = NULL;
				Erfolgreich = true; 
			}
			else {
				printf("Auswahl ungueltig, bitte geben Sie einen Wert zwischen 1 und 100000 ein.\n");
			}
		} while (!Erfolgreich);
		start = false;
	}

	do {
		system("CLS");
		printf("******************** Hauptmenu ********************\n");
		printf("Folgende Optionen stehen zur Verfuegung: \n\t1) Liste bearbeiten \n\t2) Liste Ausgeben\n\t3) Liste vergleichen\n\t4) Elemente bearbeiten\n\t5) Programm beenden\nWaehlen Sie einer der aufgelisteten Optionen auf, indem Sie die zugewiesenen Zahlen eingeben.\n");
		printf("***************************************************\n");

		Auswahl = _getche() - 48;
		int* pAuswahl = &Auswahl;
		printf("\n");

		if (Auswahl == 1) {
			Erfolgreich = false;
			do {
				printf("\nWelche Liste moechten sie bearbeiten?\n");
				Auswahl = _getche() - 48;
				if (Auswahl <= size && Auswahl >= 0)
				{
					pStartList[(Auswahl - 1)] = menu(pStartList[(Auswahl - 1)]);
					Erfolgreich = true;
				}
				else printf("Bitte geben sie einen gueltigen Wert ein.\n");
			} while (!Erfolgreich);
		}

		else if (Auswahl == 2) {
			/*if (pStartList[] == NULL) printf("Keine Listen generiert.\n");
			*/
			ausgabelist(pStartList, size, false); //printf Anzahl Liste + Status...
			
		}
		else if (Auswahl == 3) {
			int compA1 = 0;
			int compA2 = 0;
			if (pStartList[0] == NULL) printf("Keine Listen generiert.\n");
			else
			{
				Erfolgreich = false;
				do {
					printf("Waehlen Sie die erste Liste, die Sie vergleichen wollen. Geben Sie -1 ein, um zurück ins Hauptmenu zu kommen.\n");
					compA1 = _getche() - 48;
					if (compA1 >= -1 && compA1 < size) Erfolgreich = true;
					else zurueck("Bitte geben Sie einen gültigen Wert ein.\n");
				} while (!Erfolgreich);
				if (compA1 != -1) {
					Erfolgreich = false;
					do {
						printf("Waehlen Sie die zweite Liste, die Sie vergleichen wollen. Geben Sie -1 ein, um zurück ins Hauptmenu zu kommen.\n");
						compA2 = _getche() - 48;
						if (compA2 >= -1 && compA2 < size) Erfolgreich = true;
						else zurueck("Bitte geben Sie einen gültigen Wert ein.\n");
					} while (!Erfolgreich);
				}
				if  (compA1 == -1 || compA2 == -1) zurueck("Es wurden keine Listen verglichen.\n");
				
			}
		}
		else if (Auswahl == 4) {
				Erfolgreich = false;
				ausgabelist(pStartList, Auswahl, true); //printf Anzahl Liste + Status...
			do {
				printf("\nWelche Elemente von welcher Liste möchten Sie bearbeiten? Falls keine Listen aufgeführt werden, müssen Sie erst eine Liste bearbeite. Geben Sie 0 ein, um zurueck ins Hauptmenu zu kommen.");
				Auswahl = _getche() - 48;
				if (Auswahl >= 0 && Auswahl < size) {
					Erfolgreich = true;
					EditList(pStartList[Auswahl]->pNext);	//muss ausprogrammiert werden
				}
				else zurueck("Bitte geben Sie einen gültigen Wert ein.\n");
			} while (Erfolgreich);
		}
		else if (Auswahl == 5) Erfolgreich2 = true;
	} while (!Erfolgreich2);
}

int main()
{
	strulist** pStartList = NULL; //strulist
	Hauptmenu(pStartList);
}