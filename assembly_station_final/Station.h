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


#ifndef SDDS_STATION__
#define SDDS_STATION__

#include <string>

namespace sdds {

	class Station {

		//encapsulated private variables related 
		//to Station.
		int m_id;
		std::string m_name;
		std::string m_description;
		unsigned int m_serialNum;
		unsigned int m_numOfItems;
		static size_t m_widthField;
		static unsigned int id_generator;

	public:

		//Public functions pertaining to a specified station
		Station(const std::string& str);
		const std::string& getItemName() const;
		unsigned int getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		std::string removeSpaces(const std::string& oldstr);

	};

}

#endif