


#ifndef SDDS_CUSTOMERORDER__
#define SDDS_CUSTOMERORDER__
#include "Station.h"


namespace sdds {
	//struct containing data about an Item that a Customer may add to their order
	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string src) : m_itemName(src) {};
	};
	//Class containing data on a customs order
	class CustomerOrder {

		std::string m_name{ "" };
		std::string m_product{ "" };
		size_t m_cntItem{ 0 };
		Item** m_lstItem;
		static size_t m_widthField;
	public:
		// function declarations relating to Customer order
		CustomerOrder();
		CustomerOrder(std::string& str);
		CustomerOrder(const CustomerOrder& newCustomerOrder);
		CustomerOrder& operator=(const CustomerOrder& newCustomerOrder) = delete;
		CustomerOrder(CustomerOrder&& newCustomerOrder) noexcept;
		CustomerOrder& operator=(CustomerOrder&& newCustomerOrder)noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		std::string removeSpaces(const std::string& oldstr);
	};
}
#endif
