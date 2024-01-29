#include <iostream>
#include <algorithm>
#include <array>
#include <climits>
#include "func.h"

namespace sparse_matrix
{
    int compare(Element *a, Element *b)
    {
        int arg1 = a->val;
        int arg2 = b->val;
        if (arg1 > arg2)
        {
            return 1;
        }
        else if (arg2 > arg1)
        {
            return -1;
        }
        return 0;
    }

    int compare_indeces (Element *a, Element *b)
    {
        int arg1 = a->ind;
        int arg2 = b->ind;
        if (arg1 > arg2)
        {
            return 1;
        }
        else if (arg2 > arg1)
        {
            return -1;
        }
        return 0;
    }

    Matrix input()
    {
        Matrix matrix;
        try {
            std::cout<<"Enter number of lines: --> ";
            matrix.m = getNum<int>(0);

            matrix.lines = new Line[matrix.m];

            for (int i=0; i < matrix.m; i++)
            {
                Line& line = matrix.lines[i];

                std::cout<<"Enter number of items in line #"<<(i+1)<<" --> ";
                line.n = getNum<int>(0);
                line.a = new Element[line.n];
                std::cout<<"Enter items for line #"<<(i+1)<<":"<<std::endl;
                int k = 0;
                for (int j=0; j<line.n; j++)
                {
                    double cur = getNum<double>(-INT_MAX, INT_MAX);
                    if (cur != 0)
                    {
                        line.a[k].val = cur;
                        line.a[k].ind = j;
                        k++;
                    }
                }
                Line modificated_line;
                modificated_line.source_n = line.n;
                modificated_line.n = k;
                modificated_line.a = new Element[k];
                std::copy(line.a, line.a + k, modificated_line.a);
                delete[] line.a;
                line = modificated_line;
            }
        }
        catch(...)
        {
            erase(matrix);
            throw;
        }
        return matrix;
    }

    void output(const char *msg, const Matrix& matrix)
    {
        std::cout<<msg<<":"<<std::endl;
        for (int i=0; i<matrix.m; i++)
        {
            Line& line = matrix.lines[i];
            for (int j=0, k = 0; j<line.source_n; j++)
            {
                if (k < line.n && line.a[k].ind == j)
                {
                    std::cout<<line.a[k].val << " ";
                    k++;
                }
                else
                {
                    std::cout<< 0 << " ";
                }
            }
            std::cout<<std::endl;
        }
    }

    void erase (Matrix& matrix)
    {
        if (matrix.lines != nullptr)
        {
            for (int i=0; i<matrix.m; i++)
                delete[] matrix.lines[i].a;
        }
        delete[] matrix.lines;
        matrix.lines = nullptr;
        matrix.m = 0;
    }

    Matrix modification_of_matrix (const Matrix& matrix)
    {
        Matrix new_matrix;
        try {
            for (int i=0; i<matrix.m; i++)
            {
                Line &line = matrix.lines[i];
                std::qsort(line.a, line.n, sizeof(Element), reinterpret_cast<int (*)(const void *, const void *)>(compare));
            }
            new_matrix.m = matrix.m;
            new_matrix.lines = new Line[new_matrix.m];
            for (int i=0; i<matrix.m; i++)
            {
                Line& new_line = new_matrix.lines[i];
                Line& line = matrix.lines[i];
                new_line.n = line.n;
                new_line.source_n = line.source_n;
                new_line.a = new Element[new_line.n];
                int k = 0, mn = line.n, cnt=0;
                int *indeces = new int[new_line.n];
                for (int j=0; j<line.n;)
                {
                    if ( (j+1) < line.n && line.a[j].val == line.a[j+1].val)
                    {
                        new_line.a[k].val = line.a[j].val;
                        new_line.a[k].ind = line.a[j].ind;
                        j++;
                        k++;
                        while (j < line.n && line.a[j].val == line.a[j-1].val)
                        {
                            new_line.a[k].val = line.a[j].val;
                            new_line.a[k].ind = line.a[j].ind;
                            j++;
                            k++;
                        }
                    }
                    else
                    {
                        (new_line.source_n)--;
                        mn = std::min(mn,j);
                        indeces[cnt] = line.a[j].ind;
                        cnt++;
                        j++;
                    }
                }
                Line temp;
                temp.n = k;
                temp.a = new Element[temp.n];
                temp.source_n = new_line.source_n;
                std::copy(new_line.a, new_line.a+k, temp.a);
                delete[] new_line.a;
                new_line.a = nullptr;
                new_line = temp;
                qsort(new_line.a, new_line.n, sizeof(Element),
                      reinterpret_cast<int (*)(const void *, const void *)>(compare_indeces));
                std::sort(indeces, indeces + cnt);
                if (cnt !=0)
                {
                int t = indeces[0];
                for (int u = 0, c = 0, cur = 1; u < cnt && c < new_line.n; u++)
                {
                    if ((u+1) < cnt)
                    {
                        while (new_line.a[c].ind <= indeces[u+1])
                        {
                            if (new_line.a[c].ind > t) {
                                (new_line.a[c].ind) -= cur;
                            }
                            c++;
                        }
                        t = indeces[u+1];
                    }
                    else
                    {
                        while (c < new_line.n)
                        {
                            if (new_line.a[c].ind > t)
                            {
                                (new_line.a[c].ind) -= cur;
                            }
                            c++;
                        }
                        c++;
                    }
                    cur++;
                }
                }
                delete[] indeces;
            }
            return new_matrix;
        }
        catch(...)
        {
            erase(new_matrix);
            throw;
        }
    }
}
