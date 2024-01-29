#include "include/classes.hpp"
#include "include/matrix.hpp"
#include <iostream>
#include <utility>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <future>
#include <mutex>

static std::mutex mut;
static std::mutex mut_1;

int comp(Squad *s1, Squad *s2)
{
	if (s1->get_initiative() > s2->get_initiative())
		return 1;
	else if (s1->get_initiative() < s2->get_initiative())
		return -1;
	return 0;
}

bool Landscape::valid_enemy_coordinats (COLOR enemy_color, std::pair <int,int> c_enemy, std::pair<int,int> c_squad, ll sq_speed, std::pair<int,int> &prev)
{
	bool cond = enemy_color == COLOR::red ? c_enemy == std::make_pair(0,0) : c_enemy == std::make_pair(5,5);
	if (cond && this->distance_between_units(c_squad, c_enemy, prev) - 1 <= sq_speed)
	{
		return true;
	}
	for (int i = 0; i < list_of_squads.size(); i++)
	{
		if (list_of_squads[i]->get_coordinats() == c_enemy)
		{
			if (list_of_squads[i]->get_color() == enemy_color && this->distance_between_units(c_squad, c_enemy, prev) - 1 <= sq_speed)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool Landscape::summoner_attack (const int screenWidth, const int screenHeight, COLOR summoner_color, Squad *sq, bool &is_dead, ll &before, ll &after)
{
	Summoner *cur = summoner_color == red ? s1 : s2;
	std::string sq_name = sq->get_name();
	double moral_coef = 1.0;
	if (sq_name == "Water elemental" || sq_name == "Heal" ||  sq_name == "Executioner" || sq_name == "Earth elemental" || sq_name == "Air elemental")
	{
			//moral_coef += ((double)sq->get_moral()) / 100;
	}
	ll x = cur->get_cur_health();
	if (cur->get_cur_health() > (ll)moral_coef*sq->get_damage())
	{
		cur->set_cur_health(cur->get_cur_health() - (ll)moral_coef*sq->get_damage());
	}
	else
	{
		cur->set_cur_health(0);
		is_dead = true;
	}
	before = x;
	after = cur->get_cur_health();
}

bool Landscape::summon_squad(Summoner *cur, std::pair <int,int> sq_coordinats, std::string skill_name, std::string school_name)
{
	//mut.lock();
	Landscape *game_field = this;
	if (is_squad_in_cell(sq_coordinats))
	{
		//std::cout << "MARKERN\n";
		return false;
	}
        try
        {
                 Skill& cur_skill = game_field->get_table()->get_creature(school_name, skill_name);
		 /*std::cout << cur->get_possession_of_school(school_name) << " " << cur_skill.getMinKnowledge()
		 << "\n";*/
                 if (cur->get_possession_of_school(school_name) >= cur_skill.getMinKnowledge())
                 {
                          COLOR s_color = cur->get_color();
                          bool c = false;
                          // Squad *s = this->create_squad(cur_skill, game_field->get_table()->get_school(school_name), s_color);
                          // c = game_field->set_squad_in_free_cell(s, sq_coordinats);

                          	                               if (cur_skill.getCreatureName() == "Executioner" ||
                                               cur_skill.getCreatureName() == "Water elemental" ||
                                               cur_skill.getCreatureName() == "Earth elemental" || cur_skill.getCreatureName() == "Air elemental")
                                 {
                                             Squad *s = new Typical_squad(cur_skill.getCreatureName(),
                                             game_field->get_table()->get_school(school_name),
                                             cur_skill.getHeadcountRatio(), s_color, rand()%100);
                                             c = game_field->set_squad_in_free_cell(s,
                                             sq_coordinats);
                                 }
                                 else if (cur_skill.getCreatureName() == "Heal")
                                 {
                                            Squad *s = new Resurrecting_squad(cur_skill.getCreatureName(),
                                            game_field->get_table()->get_school(school_name), cur_skill.getHeadcountRatio(), s_color);
                                            c = game_field->set_squad_in_free_cell(s, sq_coordinats);
                                 }
                                 else if (cur_skill.getCreatureName() == "Resurrection")
                                 {
                                            Squad *s = new Resurrecting_squad_without_moral (cur_skill.getCreatureName(),
                                            game_field->get_table()->get_school(school_name),
                                            cur_skill.getHeadcountRatio(), s_color);
                                            c = game_field->set_squad_in_free_cell(s,
                                            sq_coordinats);
                                }
                                else
                                {
                                           Squad *s = new Squad(cur_skill.getCreatureName(),
                                           game_field->get_table()->get_school(school_name), cur_skill.getHeadcountRatio(), s_color);
                                           c = game_field->set_squad_in_free_cell(s, sq_coordinats);
                                }

                                cur-> reduce_energy(cur_skill.getEnergyExpended());
                                return c;
                        }
                        return false;
                }
                catch(...)
                {
                        throw;
                }
		//mut.unlock();
}


bool Landscape::squad_attack(std::pair<int,int> c_enemy, Squad *sq, bool& is_dead, ll &before, ll &after)
{
	COLOR enemy_color = sq->get_color() == COLOR::red ? COLOR::blue : COLOR::red;
	for (int i = 0; i < list_of_squads.size(); i++)
	{
		if (list_of_squads[i]->get_coordinats() == c_enemy)
		{
				before = list_of_squads[i]->get_cur_health();
				sq->attack(list_of_squads[i]);
				after = list_of_squads[i]->get_cur_health();
				if (list_of_squads[i]->get_cur_health() == 0)
				{
					if (sq->get_color() == COLOR::red)
					{
						s1->increase_experience(list_of_squads[i]->
						get_experience_for_destroying());
					}
					else if (sq->get_color() == COLOR::blue)
					{
                                                s2->increase_experience(list_of_squads[i]->
                                                get_experience_for_destroying());
					}
					std::erase(list_of_squads, list_of_squads[i]);
					is_dead = true;
				}
				return true;
		}
	}
	return false;
}

int Landscape::print_squads(COLOR c) noexcept
{
	int mx = 1000000;
	for (int i = 0, j = 0; i < list_of_squads.size(); i++)
	{
		if (list_of_squads[i]->get_color() == c)
		{
			std::pair <int,int> p = list_of_squads[i]->get_coordinats();
			std::cout << j+1 << "." << " Squad of " << list_of_squads[i]->get_name() << " located in cell with coordinats " << "(" <<
			 p.first << "," << p.second << ")" << "\n";
			mx =j+1;
			j++;
		}
	}
	return mx;
}

[[nodiscard]] Squad* Landscape::get_squad_with_given_index(int ind)
{
	if (ind < list_of_squads.size() && ind >= 0)
		return list_of_squads[ind];
	else
		return NULL;
}

bool Landscape::set_squad_in_free_cell(Squad *sq, std::pair<int,int> c)
{
	if (!is_squad_in_cell(c) && (*m)[c.first][c.second] != 1)
	{
		sq->set_coordinats(c);
		this->add_squad(sq);
		return true;
	}
	return false;
}

Squad* Landscape::is_squad_in_cell(std::pair <int,int> c)
{
	    //mut.lock();
            for (int i = 0; i < list_of_squads.size(); i++)
            {
                     if (list_of_squads[i]->get_coordinats() == c)
                     {
                                 return list_of_squads[i];
                     }
            }
	    //mut.unlock();
            return NULL;
}

bool Landscape::move_to_cell (Squad *sq, std::pair <int, int> c)
{
              if (!is_squad_in_cell(c) && (*m)[c.first][c.second] != 1)
              {
                                std::pair <int, int> cur = sq->get_coordinats(),  prev;
				//std::cout << "DISTANCE: " << this->distance_between_units(cur, c, prev) << "\n";
                                if (this->distance_between_units(cur, c, prev) <=  sq->get_speed())
                                {
                                        sq->set_coordinats(c);
                                        return true;
                                }
                                else
                                {
                                        return false;
                                }
             }
             else
             {
                                return false;
             }
}

void Landscape::sort_list_of_squads() noexcept
{
          std::sort(list_of_squads.begin(), list_of_squads.end(), comp);
}

[[nodiscard]] Squad* Landscape::get_squad_with_highest_initiation()
{
	if (list_of_squads.empty())
	{
		return NULL;
	}
	else
	{
		this->sort_list_of_squads();
		return list_of_squads.back();
	}
}

[[nodiscard]] std::pair<int, int> Landscape::get_size_of_field() const
{
	return std::make_pair(m->getM(),m->getN());
}

[[nodiscard]] CELL_TYPE Landscape::get_type_of_cell (int i, int j) const
{
	if (i>=m->getM() || j >=m->getN())
	{
		throw std::invalid_argument("Indeces are out of matrix bounds");
	}
	else
	{
		bool v = (*m)[i][j];
		return v == 1 ? CELL_TYPE::obstacle : CELL_TYPE::ground;
	}
}

void Landscape::set_type_of_cell (CELL_TYPE type, int i, int j)
{
	if (i>=m->getM() || j >=m->getN())
                throw std::invalid_argument("Indeces are out of matrix bounds");
        else
                if (type == CELL_TYPE::obstacle)
			(*m)[i][j] = 1;
		else
			(*m)[i][j] = 0;
}

Landscape::Landscape(std::pair <int,int> map_size)
{
	m = new matr<bool>(map_size.first, map_size.second);
	(*m)[1][1] = 1;
	(*m)[0][1] = 1;
	(*m)[1][4] = 1;
	(*m)[3][0] = 1;
	(*m)[3][2] = 1;
	(*m)[3][3] = 1;
	(*m)[5][1] = 1;
	(*m)[5][3] = 1;
	t = new Table_of_schools();

	School fire("Fire"), water("Water"), terra("Terra"), air("Air");
	fire.add_weaker_school("Water");
	fire.add_weaker_school("Terra");
	fire.add_weaker_school("Air");
	water.add_weaker_school("Terra");
	water.add_weaker_school("Air");
	terra.add_weaker_school("Air");

	//shool of fire skills
	Skill curse("Curses", "Curse", 0, 10, 1.5);
	Skill executioner("Executioners", "Executioner", 50, 40, 1.2);
	fire.add_skill(curse);
	fire.add_skill(executioner);

	//school of water skills
	Skill heal("Heal", "Heal", 10, 20, 1);
	Skill water_elemental("Water elementals", "Water elemental", 25, 30, 2);
	water.add_skill(heal);
	water.add_skill(water_elemental);

	//school of terra skills
	Skill earth_elemental("Earth elementals", "Earth elemental", 0, 15, 2);
	Skill resurrection("Resurrection", "Resurrection", 0, 25, 1.7);
	terra.add_skill(earth_elemental);
	terra.add_skill(resurrection);

	//school of air skills
	Skill air_elemental("Air elementals", "Air elemental", 0, 15, 2);
	air.add_skill(air_elemental);

	t->add_school(fire);
	t->add_school(water);
	t->add_school(terra);
	t->add_school(air);

	ll mx = std::numeric_limits<ll>::max() - 1;

	s1 = new Summoner("Red", 100, 100, 0, mx, 50, 1.3, rand()%100, COLOR::red);
	s2 = new Summoner("Blue", 100, 100, 0, mx, 50, 1.3, rand()%100, COLOR::blue);
	s1->set_possession_of_school("Fire", 0);
	s1->set_possession_of_school("Water", 0);
	s1->set_possession_of_school("Terra", 0);
	s1->set_possession_of_school("Air", 0);
	s2->set_possession_of_school("Fire", 0);
	s2->set_possession_of_school("Water", 0);
	s2->set_possession_of_school("Terra", 0);
	s2->set_possession_of_school("Air", 0);
	s1->set_coordinats(std::make_pair(0,0));
	s2->set_coordinats(std::make_pair(5,5));

	this->create_hash_map(t);
}
