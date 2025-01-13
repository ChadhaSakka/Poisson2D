#include "gauss_seidel.h"
#include <cmath>   // sqrt, fabs
#include <iostream>

int gaussSeidel(const CSRMatrix &A,
                const std::vector<double> &b,
                std::vector<double> &x,
                int maxIter,
                double tol)
{
    int n = A.numRows();
    if (n != A.numCols()) {
        // On suppose A carrée
        return 0;
    }

    // Pré-calcul de la diagonale
    std::vector<double> diag(n, 0.0);
    for (int i = 0; i < n; i++) {
        diag[i] = A.getValue(i, i);
    }

    std::vector<double> Ax(n, 0.0);

    for (int iter = 0; iter < maxIter; ++iter) {
        // Gauss-Seidel : on met à jour x[i] en utilisant la ligne i
        for (int i = 0; i < n; ++i) {
            double Aii = diag[i];
            if (std::fabs(Aii) < 1e-14) {
                // Si Aii quasi nul, on peut ignorer ou faire autrement
                continue;
            }

            double sum = 0.0;
            // Parcours des éléments de la ligne i
            int rowStart = A.getRowPtr()[i];
            int rowEnd   = A.getRowPtr()[i + 1];
            for (int idx = rowStart; idx < rowEnd; ++idx) {
                int j = A.getColIndices()[idx];
                double val = A.getValues()[idx];
                if (j != i) {
                    sum += val * x[j];
                }
            }
            x[i] = (b[i] - sum) / Aii;
        }

        // Calcul de la norme du résidu pour vérifier la convergence
        Ax = A.matVecProduct(x);
        double res2 = 0.0;
        for (int i = 0; i < n; i++) {
            double ri = b[i] - Ax[i];
            res2 += ri * ri;
        }
        double res = std::sqrt(res2);
        if (res < tol) {
            return iter + 1; // Convergence atteinte
        }
    }

    return maxIter; // Max itérations atteint sans convergence
}
