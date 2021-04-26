#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "NumberWithUnits.hpp"

using namespace std;

const double EPS = 0.001;

namespace ariel
{

    map<string, map<string, double>> units;

    NumberWithUnits::NumberWithUnits(const double size, const string &unit)
    {
        if (units.count(unit) == 0)
        {
            throw runtime_error("Unknown unit");
        }
        this->size = size;
        this->unit = unit;
    }

    // NumberWithUnits::NumberWithUnits() {}

    void NumberWithUnits::read_units(std::istream &units_file)
    {
        string from;
        string to;
        string buffer;
        int t = 0;
        double size = 0;
        while (units_file >> t >> from >> buffer >> size >> to)
        {
            units[from][to] = size;
            units[to][from] = 1.0 / size;
            for (auto &u : units[to])
            {
                double weight = units[from][to] * u.second;
                units[from][u.first] = weight;
                units[u.first][from] = 1.0 / weight;
            }
            for (auto &u : units[from])
            {
                double weight = units[to][from] * u.second;
                units[to][u.first] = weight;
                units[u.first][to] = 1.0 / weight;
            }
        }
    }

    double NumberWithUnits::convertion(const string &convert) const
    {
        if (convert == this->unit)
        {
            return this->size;
        }
        if (units.count(this->unit) == 1 && units.at(this->unit).count(convert) == 1)
        {
            return units.at(this->unit).at(convert) * this->size;
        }
        throw invalid_argument("kaki");
    }

    NumberWithUnits NumberWithUnits::operator-() const
    {
        NumberWithUnits ans(this->size, this->unit);
        ans.size *= -1;
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+() const
    {
        NumberWithUnits ans(this->size, this->unit);
        ans.size *= 1;
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other)
    {
       return NumberWithUnits(size + other.convertion(unit), unit);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other)
    {
        return NumberWithUnits(size - other.convertion(unit), unit);
    }

    NumberWithUnits operator*(const NumberWithUnits &other, const double n)
    {
        NumberWithUnits ans(other.size, other.unit);
        ans.size = ans.size * n;
        return ans;
    }

    NumberWithUnits operator*(const double n, const NumberWithUnits &other)
    {
        NumberWithUnits ans(other.size, other.unit);
        ans.size = ans.size * n;
        return ans;
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        this->size += other.convertion(unit);
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        this->size -= other.convertion(unit);
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator*=(double num)
    {
        this->size *= num;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++this->size;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        --this->size;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int flag)
    {
        NumberWithUnits ans(this->size++, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator--(int flag)
    {
        NumberWithUnits ans(this->size--, this->unit);
        return ans;
    }

    //--------------------bool-----------------

    int NumberWithUnits::compare(const NumberWithUnits &other) const
    {
        int ans = 0;
        double sub = size - other.convertion(unit);
        if (sub > EPS)
        {
            ans = 1;
        }
        if (-sub > EPS)
        {
            ans = -1;
        }
        return ans;
    }

    bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) == 1;
    }
    bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) >= 0;
    }
    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) == -1;
    }
    bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) <= 0;
    }
    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) == 0;
    }
    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return n1.compare(n2) != 0;
    }
    ostream &operator<<(std::ostream &os, const NumberWithUnits &num)
    {
        os << num.size << "[" << num.unit << "]";
        return os;
    }


    istream &operator>>(std::istream &is, NumberWithUnits &num)
    {
        double size=0;
        string type;
        char begin_sign=' ';
        char end_sign=' ';

        is >> skipws >> size >> begin_sign >> type;
        if (type.at(type.length()-1) == ']')
        {
            type = type.substr(0, type.length() - 1);
        }else{
            is >> skipws >> end_sign;
        }


        if (units.count(type)!=1)
        {
            throw invalid_argument("invalid unit");
        }

        num.size = size;
        num.unit = type;
        return is;
    }

}