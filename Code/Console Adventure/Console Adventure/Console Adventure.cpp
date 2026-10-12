// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <random>

using namespace std;

struct Tiles {
    int X;
    int Y;
    bool isMountain;
    bool isWater;
    bool hasPlayer;
    bool hasEnemy;
    bool isAttacked;
};
struct Player {
    int x;
    int y;
};

Tiles map[15][15];

void makeMap(int lengthX, int heightY, Tiles* map) {
    int maxMountain = 0;
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            map[x, y].X = x;
            map[x, y].Y = y;
            if (maxMountain > 3 && x > 5) {
                map[x, y].isMountain = true;
            }
        }
    }
}

void visualiseMap(int lengthX, int heightY, Tiles* map) {
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            if (map[x, y].isMountain) {
                cout << "A ";
            }
            else if (map[x, y].isWater) {
                cout << "~ ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    Tiles* mapPtr = *map;
    makeMap(15, 15, mapPtr);
    visualiseMap(15, 15, mapPtr);
    cout << "Hello World!\n";
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
