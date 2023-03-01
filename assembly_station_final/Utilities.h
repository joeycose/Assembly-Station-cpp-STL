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


#ifndef SDDS_UTILITIES__
#define SDDS_UTILITIES__
#include <string>

namespace sdds {

	//Class alled Utilities containing spacing helpers
	class Utilities {
		size_t m_widthField;
		static char m_delimiter;

	//Public functions contianing fucntions related to spacing
	//sizing
	public:
		Utilities();
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}
#endif