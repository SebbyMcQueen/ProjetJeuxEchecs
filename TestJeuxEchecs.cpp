// Fichier de test pour le projet Jeux d'échecs
// Ce fichier contient les tests unitaires pour le projet Jeux d'échecs.
// Pour le moment, il y a seulement des tests d'exemple.
// Vous devez ajouter vos propres tests pour vérifier le bon fonctionnement de votre code.

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif

#ifdef TEST

TEST(Test, exempleDeTest)
{
	EXPECT_EQ(1, 1);
}

TEST(Test, exempleDeTest2)
{
	EXPECT_FALSE(1 == 2);
}

#endif
