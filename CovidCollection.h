#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <iostream>
#include <vector>
#include <list>
namespace sdds {
	struct Covid {
		std::string country{};
		std::string city{};
		std::string variant;
		int numberOfCases{};
		std::string year{};
		int m_deaths{};
	};
	class CovidCollection {
		std::vector<Covid> m_covid;
		std::string remove_space(std::string);
		// part 2
		int m_totalCases{ 0 };
		int m_totalDeaths{ 0 };
	public:
		CovidCollection(std::string name);
		void display(std::ostream& out)const;
		//part 2
		void sort(std::string str);
		void cleanList();
		bool inCollection(std::string str)const;
		std::list<Covid> getListForCountry(std::string str) const;
		std::list<Covid> getListForVariant(std::string str) const;
	};
	std::ostream& operator << (std::ostream& out, const Covid& theCovid);
}
#endif