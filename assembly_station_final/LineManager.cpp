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


#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	/*constructor of the LineManager class. It takes a file name and a vector of type Workstation as parameters.
The constructor first opens the file and reads each line of the file. It uses Utilities to extract the tokens for each line. It 
then checks if the station is available in the vector of Workstations passed as parameter. It stores the station in its member variable m_activeLine. It then sets the 
next station for the station that was read from the file and stored in m_activeLine. 
The code then iterates through the m_activeLine vector to find the first station. It does this by checking if the station name matches the name of the station in the
next station of the current station. If no match is found then it sets m_firstStation to the current station.
Finally, the code sets the m_cntCustomerOrder member variable to the size of the g_pending vector.*/
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		size_t index;
		bool more;
		Utilities tempUtil{};
		Utilities::setDelimiter('|');
		std::string currentStation;
		std::string nextStation;
		std::string currentRecord;
		std::fstream f(file);
		if (!f) {
			throw "Could not open file";
		}
		while (f) {
			getline(f, currentRecord);
			if (f) {
				index = 0;
				more = true;
				currentStation = tempUtil.extractToken(currentRecord, index, more);
				auto it = std::find_if(stations.cbegin(), stations.cend() - 1, [currentStation](const Workstation* ws) { return ws->getItemName() == currentStation; });
				m_activeLine.push_back(*it);
				if (more) {
					nextStation = tempUtil.extractToken(currentRecord, index, more);
					auto it = std::find_if(stations.cbegin(), stations.cend() - 1, [nextStation](const Workstation* ws) { return ws->getItemName() == nextStation; });
					m_activeLine.back()->setNextStation(*it);
				}
			}
		}
		std::for_each(m_activeLine.cbegin(), m_activeLine.cend() - 1, [this](Workstation* ws) {
			const std::string& stationName = ws->getItemName();
			auto findFirstStation = [stationName](const Workstation* ws2) {
				if (ws2->getNextStation()) {
					return stationName == ws2->getNextStation()->getItemName();
				}
				return false;

			};
			if (!std::any_of(m_activeLine.cbegin(), m_activeLine.cend(), findFirstStation)) {
				m_firstStation = ws;
			}
			});
		m_cntCustomerOrder = g_pending.size();
	}

	/*member function of the LineManager class that is used to reorder a vector of Workstation objects that have been stored in the m_activeLine member variable. 
	It creates a temporary vector of Workstation objects, tempStations, and pushes the first element from m_activeLine, which is stored in m_firstStation, into the vector. Then, 
	it iterates through m_activeLine and checks if the item name of the current Workstation object is the same as the item name of the next Workstation object of the Workstation object 
	in tempStations. If they are the same, the Workstation object is pushed into the tempStations vector. The loop continues until the size of tempStations is equal to the size of m_activeLine, 
	at which point tempStations is assigned to m_activeLine, effectively reordering the vector.*/
	void LineManager::reorderStations() {
		std::vector<Workstation*> tempStations;
		tempStations.push_back(m_firstStation);
		while (tempStations.size() < m_activeLine.size()) {
			for (auto& it : m_activeLine) {
				if (tempStations.back()->getNextStation()) {
					if (it->getItemName() == tempStations.back()->getNextStation()->getItemName()) {
						tempStations.push_back(it);
					}
				}
			}
		}
		m_activeLine = tempStations;
	}

	/*The function first checks to see if there are any pending orders, and if so, it adds the order to the first station in the active line.
	function then iterates through all the active lines, calling the fill() function on each station. This function adds any customer orders that 
	are waiting in the pending queue to the current station. function then iterates through all the active lines again, calling the attemptToMoveOrder() 
	function on each station. This function attempts to move an order from the current station to the next station in the line, if possible. function checks 
	to see if all the customer orders have been completed, or if any are still incomplete. If all the customer orders have been completed, the function
	returns true. Otherwise, it returns false.*/
	bool LineManager::run(std::ostream& os) {
		static size_t cnt = 1;
		os << "Line Manager Iteration: " << cnt << std::endl;
		cnt++;
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (auto& it : m_activeLine) {
			it->fill(os);
		}
		for (auto& it : m_activeLine) {
			it->attemptToMoveOrder();
		}
		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}

	//Displays the active line specified
	void LineManager::display(std::ostream& os) const {
		for (auto& it : m_activeLine) {
			it->display(os);
		}
	}
}