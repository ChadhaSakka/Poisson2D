#include <iostream>
#include <vector>
#include <algorithm>   // std::shuffle
#include <random>      // std::random_device, std::mt19937
#include "CSR-Matrix.h"
#include "jacobi.h"
#include "gauss_seidel.h"

// Convertit (i, j) en indice linéaire : ordre "naturel" (row-major)
inline int to_mat_id(int i, int j, int N) {
    return i * N + j;
}

/**
 * @brief Construit la matrice du Laplacien 2D (Poisson) pour un maillage NxN
 *        et applique une permutation d'indices si souhaité.
 *
 * @param A        [out] Matrice CSR à remplir
 * @param N        Taille du maillage (NxN)
 * @param ordering Permutation de {0,...,N*N-1}, spécifiant l'ordre final
 */
void build_poisson_matrix(CSRMatrix &A, int N, const std::vector<int> &ordering)
{
    // Pour construire la matrice au format CSR, on appelle addValue(...)
    // On a le stencil : diagonale = 4, et -1 pour chaque voisin (gauche/droite/haut/bas).

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int natural_id = to_mat_id(i, j, N);    // Indice "naturel"
            int row        = ordering[natural_id];  // Indice final après permutation

            // Centre
            A.addValue(row, row, 4.0);

            // Voisin gauche
            if (j > 0) {
                int left_id = to_mat_id(i, j - 1, N);
                A.addValue(row, ordering[left_id], -1.0);
            }

            // Voisin droite
            if (j < N - 1) {
                int right_id = to_mat_id(i, j + 1, N);
                A.addValue(row, ordering[right_id], -1.0);
            }

            // Voisin bas
            if (i > 0) {
                int down_id = to_mat_id(i - 1, j, N);
                A.addValue(row, ordering[down_id], -1.0);
            }

            // Voisin haut
            if (i < N - 1) {
                int up_id = to_mat_id(i + 1, j, N);
                A.addValue(row, ordering[up_id], -1.0);
            }
        }
    }

    // Finalisation : row_ptr devient cumulatif
    A.finalize();
}

int main()
{
    // Exemple : N=7 => matrice de taille 49x49
    int N = 7;
    std::cout << "=== 2D Poisson - N=" << N << " ===\n";

    // 1) Ordre naturel
    std::vector<int> ordering_nat(N*N);
    for (int k = 0; k < N*N; k++) {
        ordering_nat[k] = k;
    }

    // Construction matrice A_nat
    CSRMatrix A_nat(N*N, N*N);
    build_poisson_matrix(A_nat, N, ordering_nat);

    // Second membre b = 1 partout (A_nat x = b)
    std::vector<double> b(N*N, 1.0);

    // Jacobi (ordre naturel)
    std::vector<double> x_jac_nat(N*N, 0.0);
    int iters_jac_nat = jacobi(A_nat, b, x_jac_nat, 2000, 1e-8);
    std::cout << "[Jacobi - ordre naturel] itérations = " << iters_jac_nat << "\n";

    // Gauss-Seidel (ordre naturel)
    std::vector<double> x_gs_nat(N*N, 0.0);
    int iters_gs_nat = gaussSeidel(A_nat, b, x_gs_nat, 2000, 1e-8);
    std::cout << "[Gauss-Seidel - ordre naturel] itérations = " << iters_gs_nat << "\n";

    // 2) Ordre aléatoire
    std::vector<int> ordering_rand(N*N);
    for (int k = 0; k < N*N; k++) {
        ordering_rand[k] = k;
    }
    // On mélange l'ordre
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ordering_rand.begin(), ordering_rand.end(), g);

    // Construction matrice A_rand
    CSRMatrix A_rand(N*N, N*N);
    build_poisson_matrix(A_rand, N, ordering_rand);

    // Jacobi (ordre aléatoire)
    std::vector<double> x_jac_rand(N*N, 0.0);
    int iters_jac_rand = jacobi(A_rand, b, x_jac_rand, 2000, 1e-8);
    std::cout << "[Jacobi - ordre aléatoire] itérations = " << iters_jac_rand << "\n";

    // Gauss-Seidel (ordre aléatoire)
    std::vector<double> x_gs_rand(N*N, 0.0);
    int iters_gs_rand = gaussSeidel(A_rand, b, x_gs_rand, 2000, 1e-8);
    std::cout << "[Gauss-Seidel - ordre aléatoire] itérations = " << iters_gs_rand << "\n";

    return 0;
}
