


#include <string>
#include <iostream>
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

	//Variables used in other modules external
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	//Workstation constructor that takes string param and Station::string param
	Workstation::Workstation(const std::string& str) : Station::Station(str) {

	}

	//Fills the item order using output stream operator
	void Workstation::fill(std::ostream& os) {
		if (this->m_orders.size() > 0) {
			this->m_orders.front().fillItem(*this, os);
		}
	}

	/*It is attempting to move an order from the front of the orders list. It checks to see if the
	first order in the list has been filled with the item name associated with this workstation, or 
	if the quantity in the workstation is 0. If either is true, it will move the order to either the
	next workstation in the line, or to a completed or incomplete list, depending on if the order is filled. 
	It then returns true, to indicate that the order has been moved.*/
	bool Workstation::attemptToMoveOrder() {

		if (this->m_orders.size() > 0) {

			if (this->m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0) {
				if (this->m_pNextStation) {
					*m_pNextStation += std::move(this->m_orders.front());
					m_orders.pop_front();
					return true;
				}
				else {
					if (this->m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(this->m_orders.front()));
						m_orders.pop_front();
						return true;
					}
					else {
						g_incomplete.push_back(std::move(this->m_orders.front()));
						m_orders.pop_front();
						return true;
					}
				}
			}
		}
		return false;
	}

	// sets the next workstation to a different state using station as a param
	void Workstation::setNextStation(Workstation* station) {
		this->m_pNextStation = station;
	}

	// returns the next station
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	//Displays the workstation, sets getitemname and uses
	//iterations to display the correct amount and format of
	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (this->getNextStation() != nullptr) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";
		}
		os << std::endl;
	}

	//Operator overload sets m.orders and moves the order, returns 
	//the pointer related mo.order being pushed back
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		this->m_orders.push_back(std::move(newOrder));
		return *this;
	}

}
