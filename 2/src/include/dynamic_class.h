#ifndef COMPLEX_CLASS
#define COMPLEX_CLASS

#include <iostream>
#include <compare>
#include <cstring>
#include "simple_class.h"

namespace dynamic_class
{
	class Dices
	{
	private:
		int arr_size; //размер массива
		simple_class::Dice *arr; //массив игральных костей
        public:
	    Dices (Dices &&moved) : arr_size(moved.arr_size), arr(moved.arr)
	    {
		moved.arr = nullptr;
		moved.arr_size = 0;
	    }

	    Dices (const Dices &obj) //копирующий конструктор
	    {
		this->arr_size = obj.arr_size;
		this->arr = new simple_class::Dice[obj.arr_size];
		for (int i = 0; i < this->arr_size; i++)
		{
			this->arr[i] = obj[i];
		}
	    }

            explicit Dices(int honest) //инициализаця массива кол-вом честных костей с заполнением их случайными числами
            {
                this->arr_size = honest;
                this->arr = new simple_class::Dice[this->arr_size];
            }

            Dices (int honest, int *values) //инициализация массива кол-вом честных костей и массивом их значений
            {
                this->arr_size = honest;
                this->arr = new simple_class::Dice[this->arr_size];
                for (int i=0; i < this->arr_size; i++)
                {
                    this->arr[i].set_val(values[i]);
                }
            }

            Dices() : Dices(0) {}

            ~Dices()
            {
		delete[] arr;
                //std::cout << "Group of dices was destroyed\n";
            }

	    void set_size(int sz)
	    {
		this->arr_size = sz;
	    }

	    void set_arr(simple_class::Dice *cur_arr)
	    {
		if (this->arr == nullptr)
			delete[] this->arr;
		this->arr = cur_arr;
	    }

	    int get_size() const
	    {
		return this->arr_size;
	    }

	    simple_class::Dice* get_arr() const
	    {
		return this->arr;
	    }

	    //Dices operator + (const Dices& lhs, const Dices& rhs);
	    Dices operator - () const;
	    Dices& operator + ();
	    Dices& operator = (Dices &&obj); //перемещающий оператор присваивания
	    Dices& operator = (const Dices &obj); //копирующий оператор присваивания
            Dices& operator += (const simple_class::Dice &obj); //прибавление кости с заданным номером к группе
	    Dices& operator -= (const simple_class::Dice &obj); //удаление кости из группы костей
	    Dices& operator ++ (); //перегрузка оператора инкремента (постфикс)
	    Dices operator ++ (int); //перегрузка оператора инкремента (префикс)
	    Dices& operator -- (int); //перегрузка оператора декремента
	    simple_class::Dice& operator [] (const int ind);
	    const simple_class::Dice& operator [] (const int ind) const;
	    bool operator () (); //подбросить кости
	    bool operator () (int num); //подбросить кость с заданным номером
	    std::strong_ordering operator <=> (const Dices &obj) const; //перегрузка оператора spaceship
	    void input (std::istream &in);
            bool check(int num) const; //проверка, есть ли кость с заданным номером в массиве
            int sum() const; //подсчет суммы очков в группе костей
            void print(std::ostream &out); //вывод характеристик каждой кости из группы игральных костей
	    void ascii_art();
	};
}

#endif

