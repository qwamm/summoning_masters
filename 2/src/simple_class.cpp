#include <iostream>
#include "include/simple_class.h"

using namespace simple_class;

std::istream& operator >> (std::istream &in, Dice d)
{
                        int cur_size = getNum<int>(std::cin, std::cout, 0);
                        d.set_size(cur_size);
                        d.resize(cur_size);
                        int val = getNum<int>(std::cin, std::cout,1,cur_size);
                        d.set_val(val);
                        double sum = 1.0, epsilon = 0.000000001;
                        while (sum > epsilon)
                        {
                                sum = 1.0;
                                for (int i=0; i<cur_size; i++)
                                {
                                        double cur = getNum<double>(std::cin, std::cout, 0,sum + epsilon);
                                        d.set_probability_of_dropping(cur, i+1);
                                        sum -= cur;
                                }
                        }
}

std::ostream& operator << (std::ostream& out, Dice d)
{
	d.print(out);
	return out;
}

Dice& Dice::operator = (const Dice &obj)
{
	this->value = obj.value;
	this->resize(obj.size);
	this->size = obj.size;
	for (int i=0; i < obj.size; i++)
	{
		this->probabilities[i] = obj.probabilities[i];
	}
	return *this;
}

void Dice::resize(int sz)
{
	if (this->probabilities == nullptr)
	{
		this->probabilities = new double[sz];
	}
        else if (sz <= this->size)
        {
		double *buf =  new double[sz];
        	std::copy(this->probabilities, this->probabilities + sz, buf);
		delete[] this->probabilities;
        	this->probabilities = buf;
	}
	else
	{
        	double *buf =  new double[sz];
        	std::copy(this->probabilities, this->probabilities + this->size, buf);
        	delete[] this->probabilities;
        	this->probabilities = buf;
	}
}

void Dice::print(std::ostream &c) //вывод состояния игральной кости (переадча потока в аргументы)
{
            c << "Current value of dice: " << this->value << std::endl;
            for (int i = 0; i < this->size; i++)
            {
                c << "Probability of dropping value " << (i+1) << ": " << this->probabilities[i] << std::endl;
            }
}

void Dice::set_state(std::istream &in, std::ostream &out) //ввод состояния класса через входной поток (передача потока в аргументы функции)
{
			out << "Enter number of faces of cube:\n";
			int cur_size = getNum<int>(std::cin, std::cout, 0);
			this->size = cur_size;
			delete[] this->probabilities;
			this->probabilities = new double[cur_size];
                	out << "Enter dropped value of dice:\n";
                	int val = getNum<int>(std::cin, std::cout,1,cur_size);
                	this->value = val;
                	double sum = 1.0, epsilon = 0.000000001;
                	while (sum > epsilon)
                	{
                		sum = 1.0;
                		for (int i=0; i<cur_size; i++)
                		{
                        		out << "Enter probability of dropping number #" << (i+1) << ":\n";
                        		double cur = getNum<double>(std::cin, std::cout, 0,sum + epsilon);
                        		this->probabilities[i] = cur;
                        		sum -= cur;
					out << sum << "\n";
                		}
                		if (sum > epsilon)
                		{
					out << sum << "\n";
                        		out << "Sum of probabilities must be equal to 1.0. Repeat, pleace\n";
                		}
                	}
}

void Dice::generate_random_value() //генерация рандомного значения игральной кости с учетом вероятностей
{
            //srand(time(nullptr));
            int p = rand()%101;
            double cnt = (int) (this->probabilities[0]*100);
            for (int i = 0; i<6; i++)
            {
                if (this->probabilities[i] != 0 && cnt > p)
                {
                        this->value = i + 1;
                        break;
                }
                else if (i < 5)
                {
                        cnt += (int) (this->probabilities[i+1]*100);
                }
            }
}

bool Dice::operator == (const Dice &other) const //сравнивать только значения без вероятностей
{
                if (this->value == other.value)
                {
                        return true;
                }
                return false;
}

std::string Dice::ascii_art() //формирование строки(!) и ее вывод (должна возвращать string)
{
                std::string s = ".-------.|       |";
                if (this->value == 1)
                {
                        s += "|   *   |";
                }
                else if (this->value == 2)
                {
                        s += "|  **   |";
                }
                else if (this->value == 3)
                {
                        s += "|  ***  |";
                }
                else if (this->value == 4)
                {
                        s += "| ****  |";
                }
                else if (this->value == 5)
                {
                        s += "| ***** |";
                }
                else if (this->value == 6)
                {
                        s += "| ******|";
                }
		else
		{
			std::string buf = "|   " + std::to_string(this->value) + "   |";
			s += buf;
		}
                s += "|       |";
                s += "'-------'";
                return s;
}
