#include "include/classes.hpp"

Skill::Skill(std::string _name, std::string _creature_name, unsigned int _min_knowledge, unsigned int _energy_expended, double _headcount_ratio)
{
            	name = _name;
                creature_name = _creature_name;
                min_knowledge = _min_knowledge;
                energy_expended = _energy_expended;
                headcount_ratio = _headcount_ratio;
}

