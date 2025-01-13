#include <iostream>
#include <vector>
#include "CSR-Matrix.h"
#include "jacobi.h"

int main()
{
    // Construction d'une matrice 2x2 simple
    // [2 1]
    // [1 2]
    CSRMatrix A(2, 2);
    A.addValue(0, 0, 2.0);
    A.addValue(0, 1, 1.0);
    A.addValue(1, 0, 1.0);
    A.addValue(1, 1, 2.0);
    A.finalize();

    std::vector<double> b = {3.0, 3.0}; // A*x = b => solution théorique (1,1)
    std::vector<double> x = {0.0, 0.0}; // initial guess

    int iters = jacobi(A, b, x, 100, 1e-8);
    std::cout << "[TEST Jacobi] Nombre d'itérations = " << iters << "\n";
    std::cout << "Solution approx = (" << x[0] << ", " << x[1] << ")\n";
    return 0;
}
