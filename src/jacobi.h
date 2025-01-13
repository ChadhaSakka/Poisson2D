#ifndef JACOBI_H
#define JACOBI_H

#include "CSR-Matrix.h"
#include <vector>

/**
 * @brief Résout A x = b via la méthode de Jacobi.
 *
 * @param A       Matrice CSR carrée
 * @param b       Vecteur second membre
 * @param x       Vecteur initial, modifié en place
 * @param maxIter Nombre maximum d'itérations
 * @param tol     Tolérance de convergence (norme du résidu)
 * @return        Nombre d'itérations effectuées
 */
int jacobi(const CSRMatrix &A,
           const std::vector<double> &b,
           std::vector<double> &x,
           int maxIter,
           double tol);

#endif // JACOBI_H
