#include <iostream>
#include "func.h"

using namespace sparse_matrix;

int main() {
    Matrix matrix = input();
    Matrix new_matrix = modification_of_matrix(matrix);
    output("Source matrix: ", matrix);
    output("Modificated matrix: ", new_matrix);
    erase(matrix);
    erase (new_matrix);
}
