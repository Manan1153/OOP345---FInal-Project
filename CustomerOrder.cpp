#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

size_t CustomerOrder::m_widthField = 0;

//default contructor
CustomerOrder::CustomerOrder() :
	m_name{},
	m_product{},
	m_cntItem{},
	m_lstItem{ nullptr }{}

//1-argu constructor
CustomerOrder::CustomerOrder(const string& str) {
	Utilities util;
	size_t pos = 0;
	bool more = true;

	m_name = util.extractToken(str, pos, more);
	m_product = util.extractToken(str, pos, more);

	string itemList = "";
	size_t count = 0;

	do
	{
		string tmp = util.extractToken(str, pos, more);

		if (itemList.length() > 0)
		{
			itemList += Utilities::getDelimiter();
		}

		itemList += tmp;
		count++;

	} while (more);

	m_lstItem = new Item * [count];
	m_cntItem = count;

	pos = 0;
	count = 0;
	more = true;

	do
	{
		string tmp = util.extractToken(itemList, pos, more);
		m_lstItem[count++] = new Item(tmp);
	} while (more);

	if (m_widthField < util.getFieldWidth())
	{
		m_widthField = util.getFieldWidth();
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& order) {
	throw string("Copy constructor cannot be called");
}
//move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept : CustomerOrder() {
	*this = std::move(src);
}

//move assignment operator
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (this != &src)
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}

		delete[] m_lstItem;

		m_lstItem = src.m_lstItem;
		m_cntItem = src.m_cntItem;
		m_product = src.m_product;
		m_name = src.m_name;
		
		src.m_cntItem = 0;
		src.m_name = "";
		src.m_lstItem = nullptr;
		src.m_product = "";
	}
	return *this;
}

//destructor
CustomerOrder::~CustomerOrder() {
	for (size_t i = 0; i < m_cntItem; i++)
	{
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const
{
	return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [](const Item* item)
		{
			return item->m_isFilled;
		});
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](Item* it)
		{
			if (it->m_itemName == itemName)
			{
				return (it->m_isFilled);
			}
			return true;
		});
}

void CustomerOrder::fillItem(Station& station, ostream& os) {
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == station.getItemName()) {

			if (station.getQuantity() > 0)
			{
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				station.updateQuantity();
				os << setw(11) << right;
				os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "] " << endl;

				break;
			}
			else
			{
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}
}

void CustomerOrder::display(ostream& os) const {
	os << m_name << " - " << m_product << endl;

	for (size_t i = 0; i < m_cntItem; i++) {
		os << std::right;
		os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
		os << setfill(' ') << left;
		os << setw(m_widthField + 2) << m_lstItem[i]->m_itemName << " - ";
		os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
		os << endl;
	}
}

