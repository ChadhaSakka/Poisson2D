# Construction d'une bibliothèque contenant nos classes et fonctions
add_library(LinearSolversLib
    CSR-Matrix.cpp
    jacobi.cpp
    gauss_seidel.cpp
)

# Pour que l'inclusion "#include <CSR-Matrix.h>" fonctionne
target_include_directories(LinearSolversLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Création de l'exécutable principal
add_executable(mainExec main.cpp)

# Liaison de l'exécutable principal avec la bibliothèque
target_link_libraries(mainExec LinearSolversLib)
