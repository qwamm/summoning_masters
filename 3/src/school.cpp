#include "include/classes.hpp"

void School::change_creature (std::string creature_name, Skill &obj)
{
	for (int i=0; i<list_of_skills.size(); i++)
	{
		if(list_of_skills[i].getName() == creature_name)
		{
			list_of_skills[i] = obj;
		}
	}
}

Skill& School::find_creature(std::string skill_name)
{
            for (int i = 0; i < list_of_skills.size(); i++)
            {
		      //std::cout << list_of_skills[i].getName() << "\t" << skill_name << "\n";
                      if (list_of_skills[i].getName() == skill_name)
                                return list_of_skills[i];
            }
	    throw std::invalid_argument("List of skills doesn't contain given skill");
}
