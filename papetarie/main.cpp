#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <stdio.h>
using namespace std;

struct obiect
{
    int pret,bucati,tip; /// 1 - caiet; 2 - instrument de scris
    char model[101], culoare[101], prod[101];
    obiect *urm;
};

obiect *stoc = NULL;

void scr_fisier ()
{
    ofstream fout ("date.in");
    obiect *a;
    for (a = stoc; a != NULL; a = a -> urm)
    {
        fout << a -> tip << " " << a -> model << " " << a -> culoare << " " << a -> prod << " " << a -> pret << " " << a -> bucati << " \n";
    }
}

void cit_fisier ()
{
    ifstream fin ("date.in");
    int tip,pret,bucati;
    char model[101], culoare[101], prod[101];
    while (fin >> tip >> model >> culoare >> prod >> pret >> bucati)
    {
        obiect *a = new obiect;
        a -> tip = tip;
        strcpy (a -> model, model);
        strcpy (a -> culoare, culoare);
        strcpy (a -> prod, prod);
        a -> pret = pret;
        a -> bucati = bucati;
        a -> urm = stoc;
        stoc = a;
    }
}

void CalculStoc ()
{
    int tip,pret,bucati,caiete = 0, instrumente_de_scris = 0;
    char model[101], culoare[101], prod[101];
    obiect *a = new obiect;
    for (a = stoc; a; a = a -> urm)
    {
        if (a -> tip == 1)  caiete += a -> bucati;
        if (a -> tip == 2)  instrumente_de_scris += a -> bucati;
    }
    if (caiete == 0 && instrumente_de_scris == 0) cout << "Nu mai avem nimic :/\n";
    else
    {
        if (caiete != 0) cout << "\nAvem "<< caiete << " produse de tipul 1 (caiete)\n";
            else cout << "Nu mai avem caiete :(\n";
        if (instrumente_de_scris != 0)cout << "Avem "<< instrumente_de_scris << " produse de tipul 2 (instrumente de scris)";
            else cout << "Nu mai avem instrumente de scris :(\n";
    }
    getch ();
}

void CalculMoney ()
{
    int tip,pret,bucati,caiete = 0, instrumente_de_scris = 0,money = 0;
    char model[101], culoare[101], prod[101];
    obiect *a = new obiect;
    for (a = stoc; a; a = a -> urm)
    {
        money += a -> pret * a -> bucati;
    }
    if (money != 0)
        cout << "\nSunt " << money << " lei in stocul papetariei";
    else cout << "Paptetaria a dat faliment :( \n'Be careful, you can go bankrupt'";

    getch ();
}

void Cautare ()
{
    int tip,pret,bucati,caiete = 0, instrumente_de_scris = 0,money = 0,p1,p2,ok = 0;
    char model[101], culoare[101], prod[101];
    obiect *a = new obiect;
    cout << "Alegeti tipul: \n1 - caiete\n2 - instrumente de scris\n";
    cin >> tip;
    cout << "Spuneti intervalul de pret: ";
    cin >> p1 >> p2;
    cout << "\n";
    if (p1 > p2) swap (p1, p2);
    for (a = stoc; a; a = a -> urm)
    {
        if (tip == 1)
        {
            if (a -> tip == 1)
                if (a -> pret >= p1 && a -> pret <= p2)
                    cout << "Avem: " <<  a -> model << " " << a -> culoare << " " << a -> prod << " " << a -> pret << " lei " << a -> bucati << " bucati" << "\n", ok ++;
        }
        else if (tip == 2)
        {
            if (a -> tip == 2)
                if (a -> pret >= p1 && a -> pret <= p2)
                    cout << "Avem :" << a -> model << " " << a -> culoare << " " << a -> prod << " " << a -> pret << " lei " << a -> bucati << " bucati" << "\n", ok ++;
        }
    }
    if (ok == 0)
    {
        cout << "Nu am gasit modele in intervalul corespunzator";
    }
    getch ();
}

int meniu ()
{
    system("cls");
    cout << "Alegeti optiunea:\n\n";
    cout << "1 - Adaugare produs in stoc\n";
    cout << "2 - Stergere produs din stoc\n";
    cout << "3 - Calcul stoc pe tip produs\n";
    cout << "4 - Calcul bani blocati in stoc\n";
    cout << "5 - Cautare tip produs cuprind intr-un interval de pret\n";
    cout << "0 - Iesire\n\n";
    int optiune;
    cin >> optiune;
    if (optiune < 0 || optiune > 5) cout << "Optiunea trebuie sa fie cuprinsa intre 0 si 5, mai citeste o data",getch ();
    return optiune;
}

void adaugare ()
{
    int tip,pret,bucati,ok = 1;
    char model[101], culoare[101], prod[101];
    obiect *a = new obiect;
    cout << "Alegeti tipul: \n1 - caiete\n2 - instrumente de scris\n";
    cin >> tip;
    if (tip > 2 || tip < 1)
    {cout << "Tipul trebuie sa fie 1 sau 2, nu merge mintea? Mai incearca";
    getch ();
    return;}
    cout << "Alegeti un model, o culoare, un producator\n";
    cin >> model >> culoare >> prod;
    cout << "Spuneti pret, numar bucati\n";
    cin >> pret >> bucati;
    for (a = stoc; a != NULL; a = a -> urm)
    {
        if (a -> tip == tip)
            if (strcmp (a -> model, model) == 0)
                if (strcmp (a -> culoare, culoare) == 0)
                    if (strcmp (a -> prod, prod) == 0)
                        if (a -> pret == pret)
                        {
                            a -> bucati += bucati;
                            ok = 0;
                        }
    }
    if (ok == 1)
    {
        obiect *a = new obiect;
        a -> tip = tip;
        strcpy (a -> model, model);
        strcpy (a -> culoare, culoare);
        strcpy (a -> prod, prod);
        a -> pret = pret;
        a -> bucati = bucati;
        a -> urm = stoc;
        stoc = a;
    }
    scr_fisier ();
}

void stergere ()
{

}

int main()
{
    system ("color 0B");
    int optiune;
    cit_fisier ();
    do
    {
        optiune = meniu();
        if (optiune == 1)
        {
            adaugare ();
        }
        else if (optiune == 2)
        {
            stergere ();
        }
        else if (optiune == 3)
        {
            CalculStoc ();
        }
        else if (optiune == 4)
        {
            CalculMoney ();
        }
        else if (optiune == 5)
        {
            Cautare ();
        }
    }
    while (optiune);
    scr_fisier ();
}
