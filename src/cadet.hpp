//  ===== Date Created: 18 July, 2020 ===== 

#if !defined(CADET_HPP)
#define CADET_HPP

/*
 * Holds all the information to uniquely identify a cadet at the squadron.
 *
 * The serviceNumber is a unique ID number assigned by the AAFC.
 * The rankAbbrev is a string representing the rank of the cadet (e.g "CCPL").
 */
struct Cadet
{
	unsigned int serviceNumber = 0;
	std::string rankAbbrev = "";
	std::string firstName = ""; // Will contain all parts of the name except for the last name
	std::string lastName = "";
};

#endif
