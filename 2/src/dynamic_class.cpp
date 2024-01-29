#include <iostream>
#include "include/dynamic_class.h"
#include "include/simple_class.h"

using namespace dynamic_class;

Dices operator + (const Dices& lhs, const Dices& rhs)
{
	Dices var;
	int sum_size = rhs.get_size() + lhs.get_size();
	simple_class::Dice *buf = new simple_class::Dice[sum_size];
	simple_class::Dice *l = lhs.get_arr(), *r = rhs.get_arr();
	std::copy(l, l + lhs.get_size(), buf);
	std::copy(r, r + rhs.get_size(), buf);
	var.set_size(sum_size);
	var.set_arr(buf);
	return var;
}

Dices Dices::operator - () const
{
	Dices res = *this;
        for (int i=0; i<arr_size; i++)
        {
                res.arr[i].set_val(res.arr[i].get_size() + 1 - res.arr[i].get_val());
        }
        return res;
}

Dices& Dices::operator + ()
{
        return *this;
}

Dices& Dices::operator = (Dices &&obj)
{
	if (this->arr != nullptr)
	{
		delete[] this->arr;
	}
	this->arr_size = obj.arr_size;
	this->arr = obj.arr;
	obj.arr_size = 0;
	obj.arr = nullptr;
	return *this;
}

Dices& Dices::operator = (const Dices &obj)
{
	this->arr_size = obj.arr_size;
	if (this->arr != nullptr)
	{
		delete[] this->arr;
	}
	this->arr = new simple_class::Dice[obj.arr_size];
	//this->arr = new simple_class::Dice[obj.arr_size];
        for (int i = 0; i < this->arr_size; i++)
        {
              this->arr[i] = obj[i];
        }
}

std::strong_ordering Dices::operator <=> (const Dices &obj) const
{
	if (this->sum() < obj.sum())
		return std::strong_ordering::less;
	else if (this->sum() == obj.sum())
		return std::strong_ordering::equal;
	return std::strong_ordering::greater;
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
		//std::cout<<"MARKER\n";
              d[j].print(out);
         }
	 return out;
}

void Dices::input (std::istream &in)
{
        in >> *this;
}

Dices& Dices::operator -- (int)
{
	if (this->arr_size == 0)
		return *this;
	(this->arr_size)--;
	simple_class::Dice *buf = new simple_class::Dice[this->arr_size];
	for (int i=0; i < this->arr_size; i++)
	{
		buf[i] = this->arr[i];
	}
	delete[] this->arr;
	this->arr = buf;
	return *this;
}

Dices& Dices::operator ++ ()
{
	simple_class::Dice obj;
        return *this;
}

Dices Dices::operator ++ (int)
{
	simple_class::Dice obj;
	*this += obj;
	return *this;
}

simple_class::Dice& Dices::operator [] (const int ind)
{
	simple_class::Dice &ref = this->arr[ind];
	return ref;
}

const simple_class::Dice& Dices::operator [] (const int ind) const
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

Dices& Dices::operator -= (const simple_class::Dice &obj)
{
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
			if (i >= this->arr_size)
			{
				break;
			}
		}
	}
	return *this;
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

bool Dices::check(int num) const //проверка, есть ли кость с заданным номером в массиве
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

int Dices::sum() const //подсчет суммы очков в группе костей
{
         int res = 0;
         for (int i=0; i < this->arr_size; i++)
         {
               res += this->arr[i].get_val();
         }
         return res;
}

Dices& Dices::operator += (const simple_class::Dice &obj)
{
	simple_class::Dice *buf = new simple_class::Dice[this->arr_size+1];
	for (int i=0; i < this->arr_size; i++)
	{
		buf[i] = this->arr[i];
	}
	buf[this->arr_size] = obj;
	(this->arr_size) ++;
	delete[] this->arr;
	this->arr = buf;
	//obj.~Dice();
	return *this;
}

void Dices::print(std::ostream &out) //вывод характеристик каждой кости из группы игральных костей
{
         out << *this;
}
