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


#ifndef SDDS_LINEMANAGER__
#define SDDS_LINEMANAGER__
#include <deque>
#include <vector>
#include "Workstation.h"

using namespace std;

namespace sdds {

	//class called LineManager that contains data related to
	//customer orders and the specified workstation
	class LineManager {

		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation;
	public:

		//Public functions that help run the LineManager
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif