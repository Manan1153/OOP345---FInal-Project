
// Name:    Manan Harshadbhai Solanki
// Seneca Student ID: 156824203
// Seneca email:    mhsolanki@myseneca.ca
// Date of completion:  08-09-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

char sdds::Utilities::m_delimiter = '|';

void sdds::Utilities::setFieldWidth(size_t newWidth)
{
    m_widthField = newWidth;
}

size_t sdds::Utilities::getFieldWidth() const
{
    return m_widthField;
}

string sdds::Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{

    if (str[next_pos] == m_delimiter || next_pos >= str.length())
    {
        more = false;
        throw invalid_argument("Invalid next_pos arguement");
    }

    string token = "";
    string WHITESPACE = "";

    while (next_pos < (size_t)str.length())
    {
        if (str[next_pos] != ' ')
        {
            if (str[next_pos] == '\n' || str[next_pos] == '\r')
            {
                break;
            }

            else if (str[next_pos] == m_delimiter)
            {
                if (m_widthField < token.length())
                {
                    m_widthField = token.length();
                }

                more = true;
                next_pos++;
                return token;
            }

            else
            {
                if (token.length() > 0)
                {
                    token += WHITESPACE + str[next_pos];
                    WHITESPACE = "";
                }

                else
                {
                    token += str[next_pos];
                    WHITESPACE = "";
                }

                if (next_pos == (size_t)str.length() - 1)
                {
                    if (m_widthField < token.length()) {
                        m_widthField = token.length();
                    }

                    more = false;
                    next_pos++;
                    return token;
                }
            }
        }

        else
        {
            WHITESPACE += ' ';
        }

        next_pos++;
    }

    more = false;
    return token;
}
