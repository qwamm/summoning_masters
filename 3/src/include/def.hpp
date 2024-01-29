#ifndef DEF_HPP
#define DEF_HPP

#include <iostream>
//#include<pair>

enum class CELL_TYPE {ground, obstacle};

template<typename T>
class matr;

std::pair<int,int> find_closest_obstacle(matr<bool> *m, std::pair<int,int> c, int r, int k);

#endif
