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