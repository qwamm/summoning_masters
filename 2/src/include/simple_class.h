#ifndef LAB2_SIMPLE_CLASS_H
#define LAB2_SIMPLE_CLASS_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>

namespace simple_class
{
    template <class T>
    T getNum(std::istream &in, std::ostream &out, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
    {
        T a;
        while (true)
        {
            in >> a;
            if (in.eof()) //конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if (in.bad()) //невосстановимая ошибка входного потока
                throw  std::runtime_error(std::string("Failed to read number") + strerror(errno));
            else if (in.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std:: cout<<"You are wrong, repeat please!"<<std::endl;
            }
            else if (a>=min && a<=max)
                return a;
	    else
		out << "You are wrong! Repeat, please\n";
        }
    }


    class Dice
    {
    private:
        int value; //выпавшее значение
        double *probabilities; //веряотности
	int size; //кол-во граней кубика
    public:
	Dice (const Dice &d)
	{
		this->value = d.value;
		this->size = d.size;
		this->probabilities = new double[this->size];
		std::copy (d.probabilities, d.probabilities + d.size, this->probabilities);
	}

        Dice (const int cur_value, const int cur_size, double *&arr)
        {
            value = cur_value;
	    size = cur_size;
	    probabilities = new double[size];
            std::copy(arr, arr+cur_size, probabilities);
        }

        Dice (const int cur_size)
        {
                //srand(time(nullptr));
                this->size = cur_size;
                this->value = rand()%cur_size + 1;
                this->probabilities = new double[cur_size];
                for (int i = 0; i < cur_size; i++)
                {
                        this->probabilities[i] = 1.0 / (double) cur_size;
                }
        }

        Dice () : Dice(6) //конструктор по умолчанию (передавать выпавшее занчение) (инициализация перед основным конструктором вм>
        {
        	//std::cout << "Default constructor was activated" << std::endl;
        }

        ~Dice()
        {
		if (probabilities != nullptr)
		{
	        	delete[] probabilities;
			probabilities = nullptr;
		}
               //std::cout << "The dice was deleted" << std::endl;
        }

        void set_val (const int &cur_value) //изменение текущего значения игральной кости (сеттеры и геттеры должны переместиться в cpp-фвйл)
	{
            this->value = cur_value;
	}

        void set_probability_of_dropping (const double p, const int num) //изменение значения вероятности выпадения числа
	{
            this->probabilities[num-1] = p;
	}

	void set_size (int sz)
	{
		this->size = sz;
	}

        int get_val() const //изменение текущего значения игральной кости
	{
            return this->value;
	}

	double get_probability(int num) //изменение значения вероятности выпадения числа
        {
            return this->probabilities[num-1];
        }

	int get_size()
	{
		return this->size;
	}

	void resize (int sz); //изменение размера вектора вероятностей

        void generate_random_value(); //генерация рандомного значения игральной кости с учетом вероятностей

	Dice& operator = (const Dice &obj); //перегрузка оператора присваивания

	bool operator == (const Dice &other) const; //сравнивать только значения без вероятностей

        void set_state(std::istream &in, std::ostream &out); //ввод состояния класса через входной поток (передача потока в аргументы функции)

	std::string ascii_art(); //формирование строки(!) и ее вывод (должна возвращать string)

        void print(std::ostream &c); //вывод состояния игральной кости (переадча потока в аргументы)
    };

}

#endif //LAB2_SIMPLE_CLASS_H
