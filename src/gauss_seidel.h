#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "CSR-Matrix.h"
#include <vector>

/**
 * @brief Résout A x = b via la méthode de Gauss-Seidel.
 *
 * @param A       Matrice CSR carrée
 * @param b       Vecteur second membre
 * @param x       Vecteur initial, modifié en place (mise à jour in place)
 * @param maxIter Nombre maximum d'itérations
 * @param tol     Tolérance de convergence (norme L2 du résidu)
 * @return        Nombre d'itérations effectuées
 */
int gaussSeidel(const CSRMatrix &A,
                const std::vector<double> &b,
                std::vector<double> &x,
                int maxIter,
                double tol);

#endif // GAUSS_SEIDEL_H
