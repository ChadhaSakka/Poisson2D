#include "jacobi.h"
#include <cmath>  // sqrt

int jacobi(const CSRMatrix &A,
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

    std::vector<double> x_new(n, 0.0);

    for (int iter = 0; iter < maxIter; ++iter) {
        // Calcul du résidu (norme L2)
        std::vector<double> Ax = A.matVecProduct(x);
        double res2 = 0.0;
        for (int i = 0; i < n; i++) {
            double ri = b[i] - Ax[i];
            res2 += ri * ri;
        }
        double res = std::sqrt(res2);
        if (res < tol) {
            return iter + 1;
        }

        // Mise à jour x_new
        for (int i = 0; i < n; i++) {
            // Somme (L+U)*x = somme sur j != i de A[i,j]*x[j]
            double sum = 0.0;
            for (int idx = A.getRowPtr()[i]; idx < A.getRowPtr()[i+1]; ++idx) {
                int j = A.getColIndices()[idx];
                if (j != i) {
                    sum += A.getValues()[idx] * x[j];
                }
            }
            if (std::fabs(diag[i]) > 1e-14) {
                x_new[i] = (b[i] - sum) / diag[i];
            } else {
                x_new[i] = x[i]; // Évite division par zéro si diag nulle
            }
        }

        x = x_new; // Copie de x_new dans x
    }

    return maxIter;
}
