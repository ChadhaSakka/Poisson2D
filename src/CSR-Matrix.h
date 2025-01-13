#ifndef CSR_MATRIX_H
#define CSR_MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>

/**
 * @brief Classe représentant une matrice creuse au format CSR (Compressed Sparse Row).
 *
 * rows, cols : dimensions de la matrice
 * values     : valeurs non nulles
 * col_indices: indices de colonnes correspondant aux valeurs
 * row_ptr    : row_ptr[i] = index dans values/col_indices où commence la ligne i
 */
class CSRMatrix {
private:
    int rows;                       ///< Nombre de lignes
    int cols;                       ///< Nombre de colonnes
    std::vector<double> values;     ///< Valeurs non nulles
    std::vector<int> col_indices;   ///< Indices des colonnes pour chaque valeur
    std::vector<int> row_ptr;       ///< Indices de début de chaque ligne

public:
    // --- Constructeurs ---
    CSRMatrix(int rows, int cols);
    CSRMatrix(int rows, int cols,
              const std::vector<double>& vals,
              const std::vector<int>& cols_idx,
              const std::vector<int>& row_ptrs);

    // --- Méthodes pour construire la matrice avant finalisation ---
    /**
     * @brief Ajoute une valeur dans la ligne 'row', la colonne 'col'
     *        (stockage type COO avant de convertir en CSR via finalize()).
     */
    void addValue(int row, int col, double value);

    /**
     * @brief Convertit row_ptr (remplie incrémentalement) en véritable structure CSR.
     *        i.e. on rend row_ptr cumulatif.
     */
    void finalize();

    // --- Getters pour un accès direct (utile pour des solveurs optimisés) ---
    int numRows() const { return rows; }
    int numCols() const { return cols; }
    const std::vector<double>& getValues()     const { return values; }
    const std::vector<int>&    getColIndices() const { return col_indices; }
    const std::vector<int>&    getRowPtr()     const { return row_ptr; }

    // --- Récupérer un coefficient donné (méthode pas optimale pour de grosses matrices) ---
    double getValue(int row, int col) const;

    // --- Produit matrice-vecteur ---
    std::vector<double> matVecProduct(const std::vector<double>& vec) const;

    // --- Affichage (debug) ---
    void print() const;
};

#endif // CSR_MATRIX_H
