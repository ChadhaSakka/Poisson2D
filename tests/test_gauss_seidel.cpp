#include <iostream>
#include <vector>
#include "CSR-Matrix.h"
#include "gauss_seidel.h"

int main()
{
    // Matrice 2x2 : [ 4 -1 ]
    //               [ -1 4 ]
    // b = (3, 7) => solution ?
    // Juste un test
    CSRMatrix A(2, 2);
    A.addValue(0, 0, 4.0);
    A.addValue(0, 1, -1.0);
    A.addValue(1, 0, -1.0);
    A.addValue(1, 1, 4.0);
    A.finalize();

    std::vector<double> b = {3.0, 7.0};
    std::vector<double> x = {0.0, 0.0};

    int iters = gaussSeidel(A, b, x, 100, 1e-8);
    std::cout << "[TEST Gauss-Seidel] Nombre d'itérations = " << iters << "\n";
    std::cout << "Solution approx = (" << x[0] << ", " << x[1] << ")\n";
    return 0;
}
