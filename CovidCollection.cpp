

#include <iomanip>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "CovidCollection.h"
namespace sdds {
	void CovidCollection::sort(std::string str) {
		if (str == "country") {
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& lhs_covid,
				Covid& rhs_covid) { return lhs_covid.country < rhs_covid.country; });
		}
		else if (str == "variant") {
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& lhs_covid,
				Covid& rhs_covid) { return lhs_covid.variant < rhs_covid.variant; });
		}
		else if (str == "cases") {
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& lhs_covid,
				Covid& rhs_covid) { return lhs_covid.numberOfCases < rhs_covid.numberOfCases; });
		}
		else if (str == "deaths") {
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& lhs_covid,
				Covid& rhs_covid) { return lhs_covid.m_deaths < rhs_covid.m_deaths; });
		}
	}
	void CovidCollection::cleanList() {
		for_each(m_covid.begin(), m_covid.end(), [](Covid& c_covid)
			{ c_covid.variant = c_covid.variant == "[None]" ? " " :
			c_covid.variant; });
	}
	std::string sdds::CovidCollection::remove_space(std::string str) {
		std::string newStr = "";
		std::string spaces = "";
		for (unsigned int i = 0; i < str.length(); i++) {
			if (str[i] == ' ') {
				spaces += ' ';
			}
			else if (str[i] == '\r' || str[i] == '\n') {
				break;
			}
			else {
				newStr += spaces + str[i];
				spaces = "";
			}
		}
		return newStr;
		This study source was downloaded by 100000841261645 from CourseHero.com on 07 - 17 - 2022 19:26 : 30 GMT - 05 : 00
			https ://www.coursehero.com/file/140033232/CovidCollectioncpp/
	}
	bool CovidCollection::inCollection(std::string str) const {
		return std::any_of(m_covid.begin(), m_covid.end(), [str](const Covid&
			c_covid) {
				return c_covid.variant == str;
			});
	}
	std::list<Covid> CovidCollection::getListForCountry(std::string str) const {
		std::list<Covid> receiving;
		copy_if(m_covid.begin(), m_covid.end(), back_inserter(receiving), [str]
		(const Covid& c_covid) {
				return c_covid.country == str;
			});
		return receiving;
	}
	CovidCollection::CovidCollection(std::string filename) {
		std::ifstream readfile(filename);
		std::string line;
		if (readfile.is_open()) {
			while (std::getline(readfile, line)) {
				Covid tmp;
				tmp.country = remove_space(line.substr(0, 25));
				tmp.city = remove_space(line.substr(25, 25));
				tmp.variant = remove_space(line.substr(50, 25));
				tmp.year = (line.substr(75, 5));
				if (tmp.year.find_first_not_of('-')) {
					tmp.year = "";
				}
				tmp.numberOfCases = stoi(line.substr(80, 5));
				tmp.m_deaths = stoi(line.substr(85, 5));
				m_totalCases += tmp.numberOfCases;
				m_totalDeaths += tmp.m_deaths;
				m_covid.emplace_back(tmp);
			}
		}
		else {
			throw std::invalid_argument("Invalid file!");
		}
	}
	std::list<Covid> CovidCollection::getListForVariant(std::string str) const {
		std::list<Covid> receiving;
		copy_if(m_covid.begin(), m_covid.end(), back_inserter(receiving), [str]
		(const Covid& c_covid) {
				return c_covid.variant == str;
			});
		return receiving;
		
	}
	void CovidCollection::display(std::ostream& out) const {
		int totalCases = m_totalCases;
		int totalDeaths = m_totalDeaths;
		for_each(m_covid.begin(), m_covid.end(), [&out](const Covid&
			m_covid) /* using a lambda function */ {
				out << m_covid << std::endl;
			});
		out <<"----------------------------------------------------------------------------------------" << std::endl;
			out << "|" << std::right << std::setw(78) << std::setfill(' ') <<"Total Cases Around the World:" << std::right << std::setw(7) << totalCases << " |"<< std::endl;
		out << "|" << std::right << std::setw(78) << std::setfill(' ') <<"Total Deaths Around the World:" << std::right << std::setw(7) << totalDeaths << " |" << std::endl;
	}
	std::ostream& operator << (std::ostream& out, const Covid& theCovid) {
		out << "| " << std::left << std::setw(21) << theCovid.country << " | "
			<< std::left << std::setw(15)
			<< theCovid.city << " | " << std::left << std::setw(20) <<
			theCovid.variant << " | " << std::right << std::setw(7) << theCovid.year << "| " <<
			std::right << std::setw(4) << theCovid.numberOfCases << " | " << std::right <<
			std::setw(3) << theCovid.m_deaths << " |";
		return out;
	}
}