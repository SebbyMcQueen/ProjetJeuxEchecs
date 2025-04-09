cmake_minimum_required(VERSION 3.10)
set(CMAKE_MESSAGE_LOG_LEVEL VERBOSE)
include(cmake_cours.cmake)

project(ProjetJeuxEchecs CXX)

afficher_infos_generateur()

set(BILIOTHEQUE_COURS
    "bibliotheque_cours/bibliotheque_cours.cpp"
    "include/bibliotheque_cours.hpp"
    "include/CodeCoverage_bugfix.h"
    "bibliotheque_cours/verification_allocation.cpp"
    "include/verification_allocation.hpp"
    "include/debogage_memoire.hpp"
)

# Ajout des nouveaux fichiers
set(MODEL_FILES
    "src/piece.cpp"
    "src/echiquier.cpp"
    "src/deplacement_temporaire.cpp"
    "include/piece.hpp"
    "include/echiquier.hpp"
    "include/deplacement_temporaire.hpp"
)

file(GLOB ALL_FILES
    *.cpp
    *.hpp
    ${BILIOTHEQUE_COURS}
    ${MODEL_FILES}
)

configurer_options_compilation_globales()
configurer_Qt_auto_tout()
add_executable(${PROJECT_NAME} ${ALL_FILES})

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
afficher_version_Qt()
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)
configurer_GoogleTest(${PROJECT_NAME})

ajouter_target_couverture(${PROJECT_NAME})

# Ajout des répertoires d'inclusion
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE 
    "include"
    "src"
)