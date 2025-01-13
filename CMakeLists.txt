cmake_minimum_required(VERSION 3.10)
project(LinearSolvers LANGUAGES C CXX)

# Définit la norme C++17 (facultatif, si on compile en C++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajoute les dossiers 'src' et 'tests'
add_subdirectory(src)
add_subdirectory(tests)
