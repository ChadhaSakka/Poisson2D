#include "CSR-Matrix.h"

CSRMatrix::CSRMatrix(int rows, int cols)
    : rows(rows), cols(cols)
{
    // row_ptr a une taille = nombre de lignes + 1
    row_ptr.resize(rows + 1, 0);
}

CSRMatrix::CSRMatrix(int rows, int cols,
                     const std::vector<double>& vals,
                     const std::vector<int>& cols_idx,
                     const std::vector<int>& row_ptrs)
    : rows(rows), cols(cols), values(vals), col_indices(cols_idx), row_ptr(row_ptrs)
{
    // On suppose que l'utilisateur fournit déjà des données CSR cohérentes.
}

void CSRMatrix::addValue(int row, int col, double value)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Indices (row,col) invalides");
    }
    // On empile la valeur (approche type COO)
    values.push_back(value);
    col_indices.push_back(col);

    // On incrémente row_ptr[row+1] (on cumulera plus tard dans finalize())
    row_ptr[row + 1]++;
}

void CSRMatrix::finalize()
{
    // On rend row_ptr cumulatif
    // row_ptr[i] = row_ptr[i-1] + (nombre d'éléments ajoutés dans la ligne i-1)
    for (int i = 1; i <= rows; ++i) {
        row_ptr[i] += row_ptr[i - 1];
    }
}

double CSRMatrix::getValue(int row, int col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Indices (row,col) invalides");
    }
    // Recherche linéaire dans [row_ptr[row], row_ptr[row+1]) (pas optimal, mais simple)
    for (int idx = row_ptr[row]; idx < row_ptr[row + 1]; ++idx) {
        if (col_indices[idx] == col) {
            return values[idx];
        }
    }
    return 0.0; // Si absent, c'est 0
}

std::vector<double> CSRMatrix::matVecProduct(const std::vector<double>& vec) const
{
    if ((int)vec.size() != cols) {
        throw std::invalid_argument("Taille du vecteur incompatible avec la matrice");
    }
    std::vector<double> result(rows, 0.0);

    // Parcours des lignes
    for (int i = 0; i < rows; ++i) {
        // On somme values[idx] * vec[col_indices[idx]] pour idx dans [row_ptr[i], row_ptr[i+1])
        for (int idx = row_ptr[i]; idx < row_ptr[i + 1]; ++idx) {
            int j = col_indices[idx];
            result[i] += values[idx] * vec[j];
        }
    }
    return result;
}

void CSRMatrix::print() const
{
    std::cout << "=== CSR Matrix ===\n";
    std::cout << "rows = " << rows << ", cols = " << cols << "\n";

    std::cout << "values: ";
    for (auto v : values) {
        std::cout << v << " ";
    }
    std::cout << "\ncol_indices: ";
    for (auto c : col_indices) {
        std::cout << c << " ";
    }
    std::cout << "\nrow_ptr: ";
    for (auto r : row_ptr) {
        std::cout << r << " ";
    }
    std::cout << "\n==================\n";
}
