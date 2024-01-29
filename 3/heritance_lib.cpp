#include "include/classes.hpp"

std::unordred_map<std::string, Squad*>& Landscape::create_hash_map(Table_of_schools *t)
{
	School fire = t->get_school("Fire");
	std::vector<Skill> v = fire.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getCreatureName() == "Curse")
		{
			squad_map[v[i].getCreatureName()] = new Squad(v[i].getCreatureName(), fire, (ll) v[i].getHeadcountRatio(),  RED);
		}
		else if (v[i].getCreatureName() == "Executioner")
		{
			Squad *s = new Typical_Squad(v[i].getCreatureName(), fire, v[i].getHeadcountRatio(), RED, rand()%100);
			squad_map[v[i].getCreatureName()] = s;
		}
	}

	School water = t->get_school("Water");
	v = water.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Heal")
                {
                        squad_map[v[i].getCreatureName()] = new Reaurrecting_Squad(v[i].getCreatureName(), water, v[i].getHeadcountRatio(),  RED);
                }
                else if (v[i].getCreatureName() == "Water elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_Squad(v[i].getCreatureName(), water, v[i].getHeadcountRatio(), RED, rand()%100);
                }
	}

	School terra = t->get_school("Terra");
	v = terra.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Resurrection")
                {
                        squad_map[v[i].getCreatureName()] = new Resurrecting_squad_without_moral(
                        	v[i].getCreatureName(), terra, v[i].getHeadcountRatio(),  RED);
                }
                else if (v[i].getCreatureName() == "Earth elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_Squad(v[i].getCreatureName(), terra,
                         v[i].getHeadcountRatio(), RED, rand()%100);
                }
	}

	School air = t->get_school("Air");
	v = air.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Air elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_Squad(v[i].getCreatureName(), terra,
                         v[i].getHeadcountRatio(), RED, rand()%100);
                }
	}
	return squad_map;
}

void Landscape::add_squad_in_map(Squad *sq)
{
	squad_map[sq->get_name()] = sq;
}

Squad* Landscape::create_squad(Skill cur_skill, School school, COLOR s_color)
{
	std::unordred_map<std::string, Squad*> squad_map = create_hash_map(t);
	Squad *sq = NULL;
	if (squad_map.contains(cur_skill.getCreatureName()))
	{
		sq = squad_map[cur_skill.getCreatureName()];
		sq->set_color(s_color);
	}
	return sq;
}

