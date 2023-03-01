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


#ifndef SDDS_WORKSTATION__
#define SDDS_WORKSTATION__
#include <deque>
#include <string>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	//extern variables related to templated CustomerOrder
	//Specified variables are called. 
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	//class Workstation created with the public functions
	//Station being in scope as well. 
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{};

	//Public functions that edit the workstation dependning upon
	//the change
	public:
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif
