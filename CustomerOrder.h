#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
using namespace std;
namespace sdds
{
    struct Item
    {
        string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const string& src) : m_itemName(src) {};
    };

    struct CustomerOrder
    {
        string m_name;
        string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const string& str);
        CustomerOrder(const CustomerOrder& src);
        CustomerOrder& operator=(const CustomerOrder& src) = delete;
        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const string& itemName) const;
        void fillItem(Station& station, ostream& os);
        void display(ostream& os) const;
    };
}
#endif // !SDDS_CUSTOMERORDER_H
