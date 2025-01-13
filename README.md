Voici une version **plus concise** de votre `README.md`, qui reste claire et informative sans être trop détaillée.

---

# Projet : **Résolution de l'équation de Poisson 2D**

## Description

Ce projet implémente la résolution de l’équation de Poisson en 2D sur un maillage \(N \times N\), en utilisant les **méthodes de Jacobi et Gauss-Seidel**. La matrice du système linéaire est construite au format **CSR (Compressed Sparse Row)** pour une gestion efficace des matrices creuses. 

Le programme permet de comparer la convergence des deux solveurs selon différents ordres de numérotation des inconnues (naturel et aléatoire).

---

## Fonctionnalités

- Discrétisation de l'équation de Poisson 2D avec un stencil à 5 points.
- Implémentation de solveurs :
  - **Jacobi** (mise à jour indépendante).
  - **Gauss-Seidel** (mise à jour séquentielle).
- Analyse des performances :
  - Test de convergence avec ordres naturel et aléatoire.
- Tests unitaires sur des matrices simples avec solutions exactes connues.

---

## Organisation du projet

```
.
├── src/                   # Fichiers sources
│   ├── CSR-Matrix.h       # Classe CSR pour matrices creuses
│   ├── jacobi.cpp         # Méthode Jacobi
│   ├── gauss_seidel.cpp   # Méthode Gauss-Seidel
│   └── main.cpp           # Programme principal
├── tests/                 # Tests unitaires
│   ├── test_jacobi.cpp    # Tests pour Jacobi
│   ├── test_gauss_seidel.cpp # Tests pour Gauss-Seidel
└── CMakeLists.txt         # Configuration CMake
```

---

## Compilation et Exécution

### 1. Cloner et configurer le projet
```bash
git clone https://github.com/votre-repo/ProjetPoisson2D.git
cd ProjetPoisson2D
mkdir build && cd build
cmake ..
```

### 2. Compiler
```bash
cmake --build .
```

### 3. Exécuter
- **Programme principal** :
  ```bash
  ./src/mainExec
  ```
- **Tests unitaires** :
  ```bash
  ./tests/test_jacobi
  ./tests/test_gauss_seidel
  ```

---

## Auteur

**Chadha Sakka**  
Étudiante en **Master 2 HPC & Simulation**  
Université Paris-Saclay
