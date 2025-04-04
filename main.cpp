// Fichier : main.cpp
// Description :
// Programme principal de l'application de jeux d'échecs
//
// Ce fichier est le point d'entrée de l'application Qt.
// Il initialise la bibliothèque de cours et démarre l'application Qt.
// Il inclut également la bibliothèque de vérification de fuites de mémoire et d'autres bibliothèques nécessaires.
//
// Remarque :
// - La versoion de Qt utilisée est la version 6.8.1 vous pouvez la changer dans les properties du projet.
// - La version de C++ utilisée est la version 20 vous pouvez la changer dans les properties du projet.
// - Le Cmake utilisé provient du projet Calculatrice disponible sur la page Moodle du cours, il etait pas tester donc il est possible qu'il ne fonctionne pas.
// - Le projet est configuré pour utiliser le compilateur MSVC 2022, vous pouvez le changer dans les properties du projet.

#include "ProjetJeuxEchecs.h"
#include <QtWidgets/QApplication>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut.

	// cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.

	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.
}


int main(int argc, char *argv[])
{
    bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
    QApplication app(argc, argv);
    initialiserBibliothequeCours(argc, argv);
    ProjetJeuxEchecs w;
    w.show();
    return app.exec();
}
