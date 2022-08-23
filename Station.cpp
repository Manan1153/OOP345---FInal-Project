#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

size_t sdds::Station::m_widthField = 0;
int sdds::Station::id_generator = 0;

sdds::Station::Station(const string& record) {
	Utilities ut;
	size_t next_pos = 0;
	bool more = true;

	m_id = ++id_generator;
	m_itemName = ut.extractToken(record, next_pos, more);
	m_Serial = stoi(ut.extractToken(record, next_pos, more));
	m_itemInStock = stoi(ut.extractToken(record, next_pos, more));
	m_widthField = m_widthField > ut.getFieldWidth() ? m_widthField : ut.getFieldWidth();
	m_desc = ut.extractToken(record, next_pos, more);
}

const string& sdds::Station::getItemName() const {
	return m_itemName;
}

size_t sdds::Station::getNextSerialNumber() {
	return m_Serial++;
}

size_t sdds::Station::getQuantity() const {
	return m_itemInStock;
}

void sdds::Station::updateQuantity() {
	if (m_itemInStock > 0)
	{
		m_itemInStock--;
	}
}

void sdds::Station::display(ostream& os, bool full) const {
	os << std::right;
	os << setw(3) << setfill('0') << m_id << " | ";
	os << left << setfill(' ') << setw(m_widthField + 1) << m_itemName << " | ";
	os << right << setw(6) << setfill('0') << m_Serial << " | ";

	if (full)
	{
		os << setfill(' ');
		os << right;
		os << setw(4) << m_itemInStock << " | " << m_desc;
	}
}