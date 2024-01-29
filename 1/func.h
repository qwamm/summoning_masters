#ifndef LAB1_OOP_FUNC_H
#define LAB1_OOP_FUNC_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>

namespace sparse_matrix
{
    struct Element
    {
        double val;
        int ind;
    };
    struct Line
    {
        Element *a = nullptr;
        int n;
    };
    struct Matrix
    {
        Line *lines = nullptr;
        int m;
    };
    template <class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
    {
        T a;
        while (true)
        {
            std:: cin >> a;
            if (std::cin.eof()) //конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if (std::cin.bad()) //невосстановимая ошибка входного потока
                throw  std::runtime_error(std::string("Failed to read number") + strerror(errno));
            else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std:: cout<<"You are wrong, repeat please!"<<std::endl;
            }
            else if (a>=min && a<=max)
                return a;
        }
    }
    
    Matrix input();
    void output (const char *msg, const Matrix &matrix);
    void erase (Matrix &matrix);
    Matrix modification_of_matrix(const Matrix& matrix);
    int compare(Element *a, Element *b);
}

#endif //LAB1_OOP_FUNC_H
