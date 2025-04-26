/**
* Programme permettant d'impl�manter des tests d'exceptions
* \file TestJeuxEchecs.cpp
* \author Sebastian Cr�te et Stella Pastor
* \date 26 avril 2025
* Cr�� le 3 avril 2025
**/

#include "piece.hpp"
#include "RAII.hpp"
#include "gtest/gtest.h"

TEST(TestRoi, TestCompteurInstances) {
    try {
        modele::Roi roi1(modele::Couleur::BLANC, 0, 0);
        modele::Roi roi2(modele::Couleur::NOIR, 7, 7);
        EXPECT_THROW({
            modele::Roi roi3(modele::Couleur::BLANC, 0, 1);
            }, modele::TropDeRois);
    }
    catch (...) {
        FAIL() << "Exception inattendue";
    }
}

TEST(TestDeplacementTemporaire, TestRAII) {
    modele::Roi roi(modele::Couleur::BLANC, 0, 0);
    auto positionInitiale = roi.getPosition();

    {
        modele::RAII dt(roi, 1, 1);
        EXPECT_EQ(roi.getPosition(), std::make_pair(1, 1));
    }

    EXPECT_EQ(roi.getPosition(), positionInitiale);
}