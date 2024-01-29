#include "matrix.hpp"
#include <vector>
template<>
                bool matr<bool>::destination(std::pair <int,int> c1, std::pair<int,int> c2, int *dest, std::pair <int,int> &prev,
                    std::vector<std::pair<int,int>> v)
                {
                        int grid[m][n];
                        for (int i = 0; i < m; i++)
                        {
                                for (int j = 0; j < n; j++)
                                {
                                        if (arr[i][j] == 1)
                                        {
                                                grid[i][j] = -1; //непроходимая ячейка
                                        }
                                        else
                                        {
                                                grid[i][j] = -2; //свободная ячейка
                                  	}
                                }
                        }
                        for (int k = 0; k < v.size(); k++)
                        {
                            if (v[k] != c2)
                                grid[v[k].first][v[k].second] = -1;
                        }
			/*for (int i = 0; i <m; i++)
                        {
                                for (int j=0; j <n; j++)
                                {
                                        std::cout << grid[i][j] << " ";
                                }
                                std::cout << "\n";
                        }*/
                        //int px[m*n], py[m*n]; //координаты ячеек входящих в путь
                        int len; //длина пути

                        int dx[4] = {1, 0, -1, 0}; //смещения, соответствующие соседям ячейки
                        int dy[4] = {0, 1, 0, -1}; //справа, снизу, слева и сверху
                        int d, x, y, k;
                        bool stop;

                        if ((*this)[c1.first][c1.second] == 1 || (*this)[c2.first][c2.second] == 1)
                                return false;

                        //распространение волны
                        d = 0;
                        grid[c1.first][c1.second] = 0;
                        do
                        {
                                stop = true; //предполагаем, что все свободные клетки уже помечены
                                for (y = 0; y < m; ++y)
                                        for (x = 0; x < n; ++x)
                                                if (grid[y][x] == d)
                                                {
								matr *m1 = this;
                                                                Cell_Iterator it = this->find(1,std::make_pair(y,x),
                                                                 [m1](matr *mt, std::pair <int,int> c, int r, int k) -> std::pair<int,int>
                                                                {return m1->next_cell(mt, c, r, k);});
                                                        for (std::pair <int,int> i = it.begin(); i != it.end(); ++it)
                                                        {
								i = *it;

                                                                if (i.first >= 0 && i.first < m && i.second >= 0 && i.second < n
                                                                && grid[i.first][i.second] == -2)
                                                                {
                                                        if (i == c2)
                                                        {
                                                            prev = std::make_pair(y,x);
                                                        }
                                                                        stop = false;
                                                                        grid[i.first][i.second] = d+1;
                                                                }
                                                        }
                                                }
			d++;
                        } while (!stop && grid[c2.first][c2.second] == -2);

			/*for (int i = 0; i <m; i++)
			{
				for (int j=0; j <n; j++)
				{
					std::cout << grid[i][j] << " ";
				}
				std::cout << "\n";
			}*/

                        if (grid[c2.first][c2.second] == -2) return false;

                        //восстановление пути
                        len = grid[c2.first][c2.second];
                        *dest = len;
                        return true;
                }
