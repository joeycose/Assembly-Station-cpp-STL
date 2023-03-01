

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	size_t CustomerOrder::m_widthField = 0;

	// set list Item to null when fuction is called
	CustomerOrder::CustomerOrder() {
		m_lstItem = nullptr;
	}

	//Customer Order function overloaded 
	// constructor for the CustomerOrder class. It takes in a string argument and uses the Utilities 
	// class to extract information from the string. It then sets the values of the CustomerOrder object accordingly. 
	// It also checks if the field width set by the Utilities object is greater than the current field width and updates it if so. 
	// Finally, it allocates memory 
	//for the array of Item pointers and creates a new Item object for each item name in the string.
	CustomerOrder::CustomerOrder(std::string& str) {

		Utilities tempUtilities{};
		bool more = true;
		size_t index = 0;

		this->m_name = tempUtilities.extractToken(str, index, more);
		m_name = removeSpaces(m_name);
		this->m_product = tempUtilities.extractToken(str, index, more);
		m_product = removeSpaces(m_product);

		for (size_t i = index; i < str.length(); i++) {
			this->m_cntItem += (str[i] == tempUtilities.getDelimiter());
		}

		this->m_lstItem = new Item * [++m_cntItem];

		for (int i = 0; i < (int)this->m_cntItem; i++) {
			const std::string& itemName = tempUtilities.extractToken(str, index, more);
			this->m_lstItem[i] = new Item(itemName);
			this->m_lstItem[i]->m_itemName = removeSpaces(this->m_lstItem[i]->m_itemName);
		}

		if (CustomerOrder::m_widthField < tempUtilities.getFieldWidth()) {
			CustomerOrder::m_widthField = tempUtilities.getFieldWidth();
		}

	}

	//Overload Customer order function to recieve new customer order
	// and throws an exception based on the copy operators
	CustomerOrder::CustomerOrder(const CustomerOrder& newCustomerOrder) {
		throw "Error: copy operators not allowed";
	}

	//move constructor of the CustomerOrder class. It is a constructor used to create a CustomerOrder object from 
	// another CustomerOrder object through a move operation. It sets the m_lstItem pointer 
	//to nullptr and then performs a move assignment on the newCustomerOrder parameter passed to it.
	CustomerOrder::CustomerOrder(CustomerOrder&& newCustomerOrder) noexcept {
		m_lstItem = nullptr;
		*this = std::move(newCustomerOrder);
	}

	//overload of the assignment operator for the CustomerOrder class. It takes in an r-value reference to another 
	// CustomerOrder object, and performs a move assignment. It first checks for self-assignment and then deletes any 
	// existing memory in the current object. 
	//It then assigns the data members of the new CustomerOrder to the current object, and sets the data members of 
	//the new object to default values. It then returns the current object.
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& newCustomerOrder)noexcept {
		if (this != &newCustomerOrder) {
			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; ++i) {
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
			}
			m_lstItem = newCustomerOrder.m_lstItem;
			m_name = newCustomerOrder.m_name;
			m_product = newCustomerOrder.m_product;
			m_cntItem = newCustomerOrder.m_cntItem;
			newCustomerOrder.m_lstItem = nullptr;
			newCustomerOrder.m_name = "";
			newCustomerOrder.m_cntItem = 0;
			newCustomerOrder.m_product = "";
		}
		return *this;
	}

	//Destuctor for Custom Order, for-loop loops through Item and deletes
	//if the item is lass than 0; else delete list item
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete this->m_lstItem[i];
		}
		delete[] this->m_lstItem;
	};

	//Checks if the item is filled or unfilled and returns the value false
	//if listed and true if not;
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {

		for (int i = 0; i < (int)this->m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false) {
				return false;
			}
		}
		return true;

	}

	//Checks if the customer order is filled
	bool CustomerOrder::isOrderFilled() const {

		for (int i = 0; i < (int)m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				return false;
			}
		}
		return true;

	}

	//takes in a Station object and an ostream object as its parameters. The function loops through the list 
	// of items (m_lstItem) that belong to the CustomerOrder object and checks if the item name of the station 
	// object matches one of the items in the list. If it does it checks the quantity of the station object 
	// and if it is greater 
	// than 0, the quantity is updated and the item in the list is marked as
	//filled and the next serial number is assigned to it. If the quantity is 0, a message is 
	//displayed indicating that the item is unable to be filled.
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false) {

				if (station.getQuantity() > 0) {

					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
					return;
				}
				else if (station.getQuantity() == 0 && !m_lstItem[i]->m_isFilled) {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
				}

			}
		}
		
	}

	//Displays the customers order and displays if the customer order is filled
	//or unfilled
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++) {

			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] "
				<< std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "TO BE FILLED" << std::endl;
			}
		}

	}

	//Removes the whitespaces are unprecedented spaces throughout the program
	//so that it satisfies matrix compilation standards. return newstr.
	std::string CustomerOrder::removeSpaces(const std::string& oldStr) {
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
