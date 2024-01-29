#include "include/classes.hpp"
#include <boost/dll/import.hpp>

std::unordered_map<std::string,  Squad*>& Landscape::create_hash_map(Table_of_schools *t)
{
	//boost::dll::fs::path lib_path("/home/fdfdas/oop2023/3/libs/libdynamic_lib.so");
	School fire = t->get_school("Fire");
	std::vector<Skill> v = fire.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getCreatureName() == "Curse")
		{
			squad_map[v[i].getCreatureName()] = new Squad(v[i].getCreatureName(), fire, (ll) v[i].getHeadcountRatio(),  COLOR::red);
		}
		else if (v[i].getCreatureName() == "Executioner")
		{
			squad_map[v[i].getCreatureName()] = new Typical_squad(v[i].getCreatureName(), fire, v[i].getHeadcountRatio(), COLOR::red, rand()%100);;
		}
	}

	School water = t->get_school("Water");
	v = water.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Heal")
                {
                        squad_map[v[i].getCreatureName()] = new Resurrecting_squad(v[i].getCreatureName(), water, v[i].getHeadcountRatio(),  COLOR::red);
                }
                else if (v[i].getCreatureName() == "Water elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_squad(v[i].getCreatureName(), water, v[i].getHeadcountRatio(), COLOR::red, rand()%100);
                }
	}

	School terra = t->get_school("Terra");
	v = terra.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Resurrection")
                {
                	 	/*boost::shared_ptr <Squad> plugin;
						plugin = boost::dll::import<Squad> (
						lib_path,
						"squad"
						//boost::dll::load_mode::append_decorations
						);
			plugin->set_name(v[i].getCreatureName());
			plugin->set_school(terra);
			plugin->set_quantity(v[i].getHeadcountRatio() * 10);
			plugin->set_color(COLOR::red);
			plugin_vector.push_back(plugin);
			                        squad_map[v[i].getCreatureName()] = plugin.get();*/
                }
                else if (v[i].getCreatureName() == "Earth elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_squad(v[i].getCreatureName(), terra,
                         v[i].getHeadcountRatio(), COLOR::red, rand()%100);
                }
	}

	School air = t->get_school("Air");
	v = air.get_list_of_skills();
	for (int i = 0; i < v.size(); i++)
	{
                if (v[i].getCreatureName() == "Air elemental")
                {
                        squad_map[v[i].getCreatureName()] = new Typical_squad(v[i].getCreatureName(), terra,
                         v[i].getHeadcountRatio(), COLOR::red, rand()%100);
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
	Squad *sq = NULL;
	if (squad_map.contains(cur_skill.getCreatureName()))
	{
		sq = squad_map[cur_skill.getCreatureName()];
		sq->set_color(s_color);
	}
	else
	{
		std::cout << "MARKERN\n";
	}
	return sq;
}

