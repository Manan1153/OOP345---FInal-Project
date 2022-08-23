#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
using namespace std;
namespace sdds
{
	class Station
	{
		int m_id;
		string m_itemName;
		string m_desc;
		unsigned int m_Serial;
		unsigned int m_itemInStock;

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const string& record);
		const string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H
