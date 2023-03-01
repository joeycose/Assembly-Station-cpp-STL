

#include <string>
#include "Utilities.h"

namespace sdds {
	//Initialize variable 
	char Utilities::m_delimiter = ' ';

	//constructor for Utilities sets width of feild upon being called
	Utilities::Utilities() {
		m_widthField = 1;
	}

	// sets width to newWidth, initalize variable to another variable
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	// returns the width field
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	//Sets delimeter to another state
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	//function returns delimeter
	char Utilities::getDelimiter() {
		return m_delimiter;
	}

	/*takes an input string, an initial position in the string, and a boolean value to check for more tokens.
	It then searches for the delimiter character in the string and extracts the token starting from the initial
	position. If a delimiter is found, the token is extracted up to the delimiter character, and the next 
	position is set to the position after the delimiter. If there is no delimiter, the token is extracted 
	from the initial position to the end of the string, and the more boolean is set to false. The length of
	the extracted token is then compared to the maximum field width and the maximum field width is updated 
	if the token is longer. Finally, the extracted token is returned.*/
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string temp;
		if (str.at(next_pos) == m_delimiter) {
			more = false;
			throw "Token found at position";
		}
		size_t index = str.find(m_delimiter, next_pos + 1);
		if (index != std::string::npos) {
			size_t pos = index - next_pos;
			temp = str.substr(next_pos, pos);
			next_pos = ++index;
			more = true;
		}
		else {
			more = false;
			temp = str.substr(next_pos);
		}
		if (m_widthField < temp.length()) {
			m_widthField = temp.length();
		}
		return temp;
	}
}
