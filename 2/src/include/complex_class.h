#ifndef COMPLEX_CLASS
#define COMPLEX_CLASS

#include <iostream>
#include <cstring>
#include "simple_class.h"

namespace complex_class
{
	class Dices
	{
	private:
		int arr_size; //размер массива
		simple_class::Dice arr[100]; //массив игральных костей
        public:
	    Dices (Dices &obj) //параметр должеен быть const
	    {
		this->arr_size = obj.arr_size;
		for (int i = 0; i < this->arr_size; i++)
		{
			this->arr[i] = obj[i];
		}
	    }

            explicit Dices(int honest) //инициализаця массива кол-вом честных костей с заполнением их случайными числами
            {
                this->arr_size = honest;
                //this->arr = new simple_class::Dice[this->arr_size];
            }

            Dices (int honest, int *values) //инициализация массива кол-вом честных костей и массивом их значений
            {
                this->arr_size = honest;
                //this->arr = new simple_class::Dice[this->arr_size];
                for (int i=0; i < this->arr_size; i++)
                {
                    this->arr[i].set_val(values[i]);
                }
            }

            Dices() : Dices(0) {}

            ~Dices()
            {
		//delete[] arr;
                //std::cout << "Group of dices was destroyed\n";
            }

	    void set_size(int sz)
            {
                this->arr_size = sz;
            }


            int get_size() const
            {
                return this->arr_size;
            }

	    Dices& operator = (Dices &obj);
	    Dices& operator + ();
	    Dices& operator - ();
            bool operator += (simple_class::Dice &obj); //прибавление кости с заданным номером к группе
	    bool operator -= (simple_class::Dice &obj); //удаление кости из группы костей
	    bool operator ++ (int); //перегрузка оператора инкремента
	    bool operator -- (int); //перегрузка оператора декремента
	    simple_class::Dice& operator [] (const int ind);
	    bool operator () (); //подбросить кости
	    bool operator () (int num); //подбросить кость с заданным номером
	    int operator <=> (Dices &obj); //перегрузка оператора spaceship
	    void input (std::istream &in);
            bool check(int num); //проверка, есть ли кость с заданным номером в массиве (must be const)
            int sum(); //подсчет суммы очков в группе костей (must be const)
            void print(std::ostream &out); //вывод характеристик каждой кости из группы игральных костей
	    void ascii_art();
	};
}

#endif
