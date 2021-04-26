#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <exception>
namespace ariel
{

    class NumberWithUnits
    {
    private:
        double size;
        std::string unit;
        double convertion(const std::string &convert) const;
        int compare(const NumberWithUnits &other) const;

    public:
        NumberWithUnits(const double size, const std::string &units);

        NumberWithUnits();

        static void read_units(std::istream &units_file);

        //---------------------------------UNARI----------------------------

        NumberWithUnits operator-() const;

        NumberWithUnits operator+() const;

        //---------------------------------------BINARY------------------------
        NumberWithUnits operator+(const NumberWithUnits &other);

        NumberWithUnits operator-(const NumberWithUnits &other);

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        NumberWithUnits &operator-=(const NumberWithUnits &other);

        friend NumberWithUnits operator*(const NumberWithUnits &other, const double n);

        friend NumberWithUnits operator*(const double n, const NumberWithUnits &other);

        NumberWithUnits &operator*=(double num);

        //----------------------------increment and discrement---------- :
        NumberWithUnits &operator++();
        NumberWithUnits &operator--();
        NumberWithUnits operator++(int flag);
        NumberWithUnits operator--(int flag);

        // ------------bool operators------------------

        friend bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        //----------IO operators-------------

        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &num);

    };

}