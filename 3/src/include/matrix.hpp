#ifndef MATRIX_HPP
#define MATRIX_HPP

//#include "classes.hpp"
#include <iostream>
#include <vector>
#include <functional>

enum class CELL_TYPE {ground, obstacle};

template<typename T>

class matr ///матрицы
{
	private:
		T **arr;
		unsigned int m, n;

	public:

		class Iterator ///итератор по строкам матрицы
		{
			private:
				T *pRow;
				matr *m;
			public:
				T operator [] (int j) const
				{
					if (j < m->getN())
						return pRow[j];
					else
						throw std::invalid_argument("index j is out of matrix bounds");
				}

				T& operator [] (int j)
                                {
                                        if (j < m->getN())
                                                return pRow[j];
                                        else
                                                throw std::invalid_argument("index j is out of matrix bounds");
                                }

				Iterator(T *pRow, matr *m) : pRow(pRow), m(m) {}
				~Iterator()
				{
					m = NULL;
					pRow = NULL;
				}
		};

		bool destination(std::pair <int,int> c1, std::pair<int,int> c2, int *dest, std::pair <int,int> &prev,
		 std::vector<std::pair<int,int>> v)
		{
			throw std::runtime_error("Method is not defined for nont boolean matrices");
			return false;
		}

		class Cell_Iterator ///клеточный итератор
                {
                        private:
                                int cur_ind;
				std::pair <int, int> sq_coordinats;
				int r;
                                matr *m;
				std::function<std::pair <int,int> (matr*, std::pair<int,int>, int, int)> lambda;
                        public:
                                Cell_Iterator(matr *m1)
                                {
                                        cur_ind = 0;
                                        m = m1;
					r = 0;
					sq_coordinats = std::make_pair(0,0);
                                }

				~Cell_Iterator()
				{
					m = NULL;
				}

				Cell_Iterator(int _r, std::pair<int,int> c,  std::function<std::pair <int,int> (matr*, std::pair<int,int>, int, int)> &f,
				matr *_m)
				{
					cur_ind = 0;
					r = _r;
					sq_coordinats = c;
					lambda = f;
					m = _m;
				}

				Cell_Iterator(const Cell_Iterator &obj)
				{
					cur_ind = obj.cur_ind;
					sq_coordinats = obj.sq_coordinats;
					r = obj.r;
					m = obj.m;
					lambda = obj.lambda;
				}

				void set_lambda( std::function<std::pair <int,int> (matr*, std::pair<int,int>,
				 int, int)> &_lambda)
				{
					lambda = _lambda;
				}

				std::pair <int,int> begin()
				{
					return lambda(m, sq_coordinats, r, 0);
				}

				std::pair <int,int> end()
				{
					return lambda(m, sq_coordinats, r, r*8);
				}

				Cell_Iterator& operator ++ ()
				{
					cur_ind++;
					return *this;
				}

				std::pair<int,int> operator * ()
				{
					return lambda(m, sq_coordinats,r,cur_ind);
				}

				Cell_Iterator& operator = (const Cell_Iterator& x)
				{
					cur_ind = x.cur_ind;
				}

                                template<typename F>
                                [[nodiscard]] std::pair<int,int> return_next_cell(F _lambda, std::pair<int,int> sq_coordinats, int r)
                                {
                                        std::pair <int, int> res = _lambda(m, sq_coordinats, r, cur_ind);
                                        cur_ind++;
                                        return res;
                                }
                };

		//Cell_Iterator *it;

		Cell_Iterator find(int r,  std::pair <int,int> c, std::function<std::pair <int,int> (matr*, std::pair<int,int>, int, int)> lambda)
		{
			return Cell_Iterator(r, c, lambda, this);
		}

		matr(int m, int n, const T *_arr) : m(m), n(n)
		{
			arr = new T*[m];
			for (int i = 0; i<m; i++)
			{
				arr[i] = new T[n];
			}
			for (int i = 0; i<m; i++)
			{
				for (int j = 0; j<n; j++)
				{
					arr[i][j] = _arr[i][j];
				}
			}
			//Cell_Iterator *it = new Cell_Iterator(this);
		}

		matr(int m, int n)
		{
			this->m = m;
			this->n = n;
			arr =new T*[m];
			for (int i=0; i<m; i++)
			{
				arr[i] = new T[n];
			}
			for (int i=0; i<m; i++)
				for (int j=0; j<n; j++)
					arr[i][j] = 0;
			//Cell_Iterator *it = new Cell_Iterator(this);
		}

		~matr()
		{
			for (int i = 0; i<m; i++)
			{
				delete[] arr[i];
			}
			delete[] arr;
			//delete it;
			//it = NULL;
		}


		void add_element (int i, int j, T cell)
		{
			if (i >= m || j >= n)
				return;
			arr[i][j] = cell;
		}

		[[nodiscard]] unsigned int getN() const
		{
			return n;
		}

		[[nodiscard]] unsigned int getM() const
		{
			return m;
		}

		void setN (unsigned int n)  {this->n = n;}

		void setM (unsigned int m)  {this->m = m;}

		Iterator operator [](int i)
		{
			if (i<m)
				return Iterator(arr[i], this);
			else
				throw std::invalid_argument("index i is out of matrix bounds");
		}

		std::pair<int,int> next_cell (matr *m, std::pair<int,int> c, int r, int k)
                {
                        int cnt = 0;
                        for (int i = -1; i < r + 1; i++)
                        {
                                for (int j = -1; j < r + 1; j++)
                                {
					std::pair<int, int> cur_coordinats = std::make_pair(c.first + i, c.second + j);
					if (cnt == k)
						return cur_coordinats;
                                        /*if ((i != 0 || j != 0) && (c.first + i > 0 && c.second + j > 0) && (c.first + i < m->getN() && c.second + j <
                                        m->getM()))
                                        {
                                                std::pair<int, int> cur_coordinats = std::make_pair(c.first + i, c.second + j);
                                                if ((*m)[cur_coordinats.first][cur_coordinats.second] == 0)
                                                {
                                                        if (cnt == k)
                                                        {
                                                                return cur_coordinats;
                                                        }
                                                    	//cnt ++;
                                                }
						//cnt++;
                                        }*/
					cnt++;
                                }
                        }
             	}
};

template<>
                bool matr<bool>::destination(std::pair <int,int> c1, std::pair<int,int> c2, int *dest, std::pair<int,int> &prev,
                std::vector<std::pair<int,int>> v);

#endif
