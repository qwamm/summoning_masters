#include <iostream>
#include "include/complex_class.h"
#include "include/simple_class.h"

using namespace complex_class;

Dices& Dices::operator - ()
{
	for (int i=0; i<arr_size; i++)
	{
		arr[i].set_val(arr[i].get_size() + 1 - arr[i].get_val());
	}
	return *this;
}

Dices& Dices::operator + ()
{
	return *this;
}

Dices& Dices::operator = (Dices &obj)
{
	this->arr_size = obj.arr_size;
        for (int i = 0; i < this->arr_size; i++)
        {
              this->arr[i] = obj[i];
        }
}

int Dices::operator <=> (Dices &obj)
{
	if (this->sum() < obj.sum())
		return -1;
	else if (this->sum() == obj.sum())
		return 0;
	return 1;
}

std::istream & operator >> (std::istream& in, Dices &d)
{
	int honest; //кол-во честных костей
	in >> honest;
	d.set_size(honest);
	for (int i=0; i<honest; i++)
	{
		int sz, val;
		in >> sz;
		in >> val;
		d[i].resize(sz);
		d[i].set_size(sz);
		d[i].set_val(val);
		for (int j = 0; j < sz; j++)
		{
			double p;
			in >> p;
			d[i].set_probability_of_dropping(p, j+1);
		}
	}
}

std::ostream & operator << (std::ostream& out, Dices &d)
{
         for (int j=0; j < d.get_size(); j++)
         {
              d[j].print(out);
         }
	 return out;
}

void Dices::input (std::istream &in)
{
        in >> *this;
}

bool Dices::operator -- (int)
{
	if (this->arr_size == 0)
		return false;
	(this->arr_size)--;
	return true;
}

bool Dices::operator ++ (int)
{
	if (this->arr_size == 100)
		return false;
	simple_class::Dice obj;
	*this += obj;
	return true;
}

simple_class::Dice& Dices::operator [] (const int ind)
{
	simple_class::Dice &ref = this->arr[ind];
	return ref;
}

void Dices::ascii_art()
{
	for (int i=0; i < this->arr_size; i++)
	{
        	std::string res = this->arr[i].ascii_art();
        	for (int i=0; i < res.length(); i++)
        	{
                	if (i>=9 && i%9 == 0)
                	{
                        	std :: cout << "\n";
                	}
                        std :: cout << res[i];
        	}
        	std::cout << "\n\n";
	}
}

bool Dices::operator -= (simple_class::Dice &obj)
{
	bool cond = false;
	for (int i=0; i < this->arr_size; i++)
	{
		while (obj.get_val() == this->arr[i].get_val())
		{
			this->arr[i].set_val(this->arr[this->arr_size - 1].get_val());
			this->arr[i].resize(this->arr[this->arr_size - 1].get_size());
			this->arr[i].set_size(this->arr[this->arr_size - 1].get_size());
			for (int j=0; j < this->arr[this->arr_size - 1].get_size(); j++)
        		{
                		this->arr[i].set_probability_of_dropping(this->arr[this->arr_size - 1].get_probability(j+1), j+1);
        		}
			//this->arr[i] = this->arr[this->arr_size - 1];
			(this->arr_size)--;
			cond = true;
			if (i >= this->arr_size)
			{
				break;
			}
		}
	}
	return cond;
}

bool Dices::operator () (int num)
{
	if (this->arr_size + 1 < num)
		return false;
	this->arr[num-1].generate_random_value();
	return true;
}

bool Dices::operator () ()
{
	for (int i = 0; i < arr_size; i++)
	{
		this->arr[i].generate_random_value();
	}
	return true;
}

bool Dices::check(int num) //проверка, есть ли кость с заданным номером в массиве
{
         for (int i=0; i< this->arr_size; i++)
         {
              if (this->arr[i].get_val() == num)
              {
                      return true;
              }
         }
         return false;
}

int Dices::sum() //подсчет суммы очков в группе костей
{
         int res = 0;
         for (int i=0; i < this->arr_size; i++)
         {
               res += this->arr[i].get_val();
         }
         return res;
}

bool Dices::operator += (simple_class::Dice &obj)
{
	if (this->arr_size == 100)
	{
		return false;
	}
	this->arr[this->arr_size].set_val(obj.get_val());
	this->arr[this->arr_size].resize(obj.get_size());
	this->arr[this->arr_size].set_size(obj.get_size());
	for (int i=0; i < obj.get_size(); i++)
	{
		this->arr[this->arr_size].set_probability_of_dropping(obj.get_probability(i+1), i+1);
	}
	(this->arr_size) ++;
	obj.~Dice();
	return true;
}

void Dices::print(std::ostream &out) //вывод характеристик каждой кости из группы игральных костей
{
         out << *this;
}
