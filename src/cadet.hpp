//  ===== Date Created: 18 July, 2020 ===== 

#if !defined(CADET_HPP)
#define CADET_HPP

struct Cadet
{
	unsigned int serviceNumber = 0;
	std::string rankAbbrev = "";
	std::string firstName = ""; // Will contain all parts of the name except for the last name
	std::string lastName = "";
};

#endif
