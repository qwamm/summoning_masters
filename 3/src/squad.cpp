#include "include/classes.hpp"
#include <cmath>

bool Squad::is_reachable(Squad *s)
{
	std::pair<int,int> p1 = this->get_coordinats(), p2 = s->get_coordinats();
	double ro = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
	//std::cout << "\n\nDISTANCE: " << (ll)ro << "\n\n";
	if ((ll)ro - 1 <= speed)
	{
		return true;
	}
	return false;
}

void Squad::make_damage(ll _damage)
{
         if (_damage > this->get_cur_health())
         {
                    this->set_cur_health(0);
                    //squad has died
         }
         else
         {
                   damage -= _damage;
         }
}

void Squad::attack (Squad *enemy)
{
	double moral_coef = 1.0, enemy_coef = 1.0;
	if (name == "Earth elemental" || name == "Air elemental" || name == "Water elemental" || name == "Heal" || name == "Executinoer")
	{
		//moral_coef += (double) (this->get_moral() / 100);
	}
	if (enemy->get_name() == "Earth elemental" || enemy->get_name() == "Air elemental" || enemy->get_name() == "Water elemental" ||
	enemy->get_name() == "Heal" || enemy->get_name() == "Executioner")
	{
		//enemy_coef += (double) (enemy->get_moral() / 100);
	}
	if (squad_school.get_name() == enemy->get_school().get_name())
	{
                if(enemy->get_cur_health() + enemy->get_defence() < damage)
		{
                        enemy->set_cur_health(0);
		}
                else
		{
                        enemy->set_cur_health(enemy->get_cur_health()*enemy_coef + enemy->get_defence()*enemy_coef - (ll)damage*moral_coef);
			enemy->set_quantity (enemy->get_cur_health());
		}
		return;
	}
	for (int i = 0; i < squad_school.get_quantity_of_weaker_schools(); i++)
	{
		if (enemy->get_school().get_name() == squad_school.get_weaker_school(i))
		{
                	if(enemy->get_cur_health() + enemy->get_defence() < (ll)damage*0.8)
			{
                        	enemy->set_cur_health(0);
			}
                	else
			{
                        	enemy->set_cur_health(enemy->get_cur_health()*enemy_coef + enemy->get_defence()*enemy_coef - (ll)damage*0.8*moral_coef);
				enemy->set_quantity (enemy->get_cur_health());
			}
			return;
		}
	}

	for (int i = 0; i < enemy->get_school().get_quantity_of_weaker_schools(); i++)
	{
                if (squad_school.get_name() == enemy->get_school().get_weaker_school(i))
                {
                 	if(enemy->get_cur_health() + enemy->get_defence() < (ll)damage*1.2)
			{
                        	enemy->set_cur_health(0);
			}
                 	else
			{
                        	enemy->set_cur_health(enemy->get_cur_health()*enemy_coef + enemy->get_defence()*enemy_coef - (ll)damage*1.2*moral_coef);
				enemy->set_quantity (enemy->get_cur_health());
			}
                        return;
                }
	}
}

Squad::Squad(std::string _name, School &_squad_school, ll _head_count_ratio, COLOR c)
{
	this->set_color(c);
	name = _name;
	squad_school = _squad_school;
	initiative = rand()%100;
	this->set_cur_health(100);
	this->set_max_health(100);
	if (_name == "Curse")
	{
		speed = 2;
		damage = 5;
		defence = 2;
		experience_for_destroying = 5;
	}
	else if (_name == "Executioner")
	{
		speed = 2;
		damage = 15;
		defence = 3;
		experience_for_destroying = 12;
	}
	else if (_name == "Water elemental")
	{
		speed = 5;
		damage = 8;
		defence = 4;
		experience_for_destroying = 10;
	}
	else if (_name == "Heal")
	{
		speed = 3;
		damage = 1;
		defence = 0;
		experience_for_destroying = 3;
	}
	else if (_name == "Earth elemental")
	{
		speed = 3;
		damage = 24;
		defence = 3;
		experience_for_destroying = 25;
	}
	else if (_name == "Resurrection")
	{
		speed = 3;
		damage = 1;
		defence = 0;
		experience_for_destroying = 3;
	}
	else if (_name == "Air elemental")
	{
		speed = 3;
		damage = 13;
		defence = 4;
		experience_for_destroying = 20;
	}
	quantity = 10*_head_count_ratio;
}
