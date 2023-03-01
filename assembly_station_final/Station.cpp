/*
*****************************************************************************
							ms3
Full Name  Giuseppe Cosentino:
Student ID #184801215:
Email      gcosentino1@myseneca.ca:
Section    NBB:

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation with some help from the internet.
*****************************************************************************
*/


#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	unsigned int Station::id_generator = 0;

	/*constructor for the Station class. It takes a string as a parameter, which represents a single station. 
	The constructor uses the Utilities class to extract the name, serial number, number of items, and description from the string.
	It then stores each value in the appropriate member variables. The constructor also keeps track of the width of the name field, 
	which is used for displaying a table of stations. Lastly, it increments the static ID generator to assign a unique ID to the station instance.*/
	Station::Station(const std::string& str) {
		Utilities tempUtilities;
		bool more = false;
		size_t index = 0;
		m_id = ++id_generator;
		m_name = tempUtilities.extractToken(str, index, more);
		m_name = removeSpaces(m_name);
		m_serialNum = std::stoi(tempUtilities.extractToken(str, index, more));
		m_numOfItems = std::stoi(tempUtilities.extractToken(str, index, more));
		if (m_widthField < m_name.length()) {
			m_widthField = m_name.length();
		}
		m_description = tempUtilities.extractToken(str, index, more);
		m_description = removeSpaces(m_description);

	}

	//returns the item name
	const std::string& Station::getItemName() const {
		return m_name;
	}

	// unsigned integer that returns the next serial number and increments at compile time
	unsigned int Station::getNextSerialNumber() {
		return this->m_serialNum++;
	}

	//returns the number of items in the station
	size_t Station::getQuantity() const {
		return m_numOfItems;
	}

	//Updates items depending on if the num of items are greater than 0, decrements
	void Station::updateQuantity() {
		if (m_numOfItems > 0) {
			m_numOfItems--;
		}
	}

	//Displays function accorrding to the specified master output
	void Station::display(std::ostream& os, bool full) const {
		os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setfill(' ')
			<< std::setw(15) << std::left << m_name << std::setfill(' ')
			<< " | " << std::setw(6) << std::setfill('0') << std::right << m_serialNum << " | ";
		if (full == false) {
			os << std::endl;
		}
		else {
			os << std::setfill(' ') << std::setw(4) << std::right << m_numOfItems << " | " << m_description << std::endl;
		}
	}

	//removes white spaces, blanks
	std::string Station::removeSpaces(const std::string& oldStr) {
		int start = 0;
		for (int i = 0; isspace(oldStr[i]) && i < (int)oldStr.size(); i++) {
			start++;
		}
		std::string newStr = oldStr.substr(start, oldStr.size());
		for (int i = (int)oldStr.size() - 1; isspace(oldStr[i]) && i >= 0; i--) {
			newStr.pop_back();
		}
		return newStr;
	}
}