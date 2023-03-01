


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
