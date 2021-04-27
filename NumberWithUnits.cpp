#include "NumberWithUnits.hpp"
#include <cstdlib>
#include <sstream>
using namespace::std;

namespace ariel {

    NumberWithUnits::NumberWithUnits(double amount, const string unit_type) {
        if (units_map.count(unit_type) == 0) {
            throw("This unit does not exist!");
        }
        else {
            _unit.first = amount;
            _unit.second = unit_type;
        }
    }

    void NumberWithUnits::read_units(ifstream &file_name) {
        string unit1, unit2;
        double amount;
        while (!file_name.fail() && !file_name.eof() ) {
            file_name >> unit1;
            if (unit1 == "1") {
                file_name >> unit1;
                file_name >> unit2;
                file_name >> amount;
                file_name >> unit2;
                units_map[unit1][unit2] = amount;
                units_map[unit2][unit1] = 1/amount;
                for (auto unit : units_map[unit1]) {
                    units_map[unit.first][unit2] = amount / unit.second;
                    units_map[unit2][unit.first] = unit.second / amount;
                }
                for (auto unit : units_map[unit2]) {
                    units_map[unit.first][unit1] = (1/amount) / unit.second;
                    units_map[unit1][unit.first] = unit.second / (1/amount);
                }
            }
        }
    }

    NumberWithUnits NumberWithUnits::operator- () const {
        NumberWithUnits result(_unit.first * (-1), _unit.second);
        return result;
    }

    NumberWithUnits & NumberWithUnits::operator-- () {
        _unit.first = _unit.first -1;
        return *this;
    }

    NumberWithUnits & NumberWithUnits::operator++ () {
        _unit.first = _unit.first +1;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-- (int) {
        NumberWithUnits result(_unit.first, _unit.second);
        _unit.first = _unit.first -1;
        return result;
    }

    NumberWithUnits NumberWithUnits::operator++ (int) {
        NumberWithUnits result(_unit.first, _unit.second);
        _unit.first = _unit.first +1;
        return result;
    }

    NumberWithUnits NumberWithUnits::operator- (NumberWithUnits &other_num) {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            double sum = _unit.first - (other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
            return NumberWithUnits(sum, _unit.second);   
        }
        else {
            throw("Units does not match");
        }
        NumberWithUnits result(_unit.first, _unit.second);
        return result;
    }

    NumberWithUnits NumberWithUnits::operator+ () const {
        NumberWithUnits result(_unit.first, _unit.second);
        return result;
    }

    NumberWithUnits NumberWithUnits::operator+ (NumberWithUnits &other_num) {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            double sum = _unit.first + (other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
            return NumberWithUnits(sum, _unit.second);   
        }
        else {
            throw("Units does not match");
        }
        NumberWithUnits result(_unit.first, _unit.second);
        return result;
    }

    bool NumberWithUnits::operator> (const NumberWithUnits &other_num) const {
        if (_unit.second == other_num._unit.second) {
            double sum = _unit.first + other_num._unit.first;
            return (_unit.first > other_num._unit.first);
        }
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (units_map[_unit.second][other_num._unit.second] * _unit.first > other_num._unit.first
                || (units_map[_unit.second][other_num._unit.second] * _unit.first - other_num._unit.first) > epsilon);
        }   
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (this->_unit.first < other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (abs(_unit.first - other_num._unit.first * units_map[other_num._unit.second][_unit.second]) <= epsilon);
        }
        return false;
    }

    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (this->_unit.first <= other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (this->_unit.first >= other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator!= (const NumberWithUnits &other_num) const {
        return !(*this == other_num);
    }

    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits &num) {
        if (_unit.second == num._unit.second) {
            _unit.first += num._unit.first;
            return *this;
        }
        if (units_map[_unit.second].count(num._unit.second) > 0 && units_map[num._unit.second].count(_unit.second) > 0) {
            if (units_map[_unit.second][num._unit.second] * units_map[num._unit.second][_unit.second] < epsilon
                || units_map[_unit.second][num._unit.second] * units_map[num._unit.second][_unit.second] == 1) {
                _unit.first += (num._unit.first * units_map[num._unit.second][_unit.second]);
                return *this; 
            }
        }
        else {
            throw("Units does not match");
        }
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
        if (_unit.second == num._unit.second) {
            _unit.first -= num._unit.first;
            return *this;
        }
        if (units_map[_unit.second].count(num._unit.second) > 0 && units_map[num._unit.second].count(_unit.second) > 0) {
            if (units_map[_unit.second][num._unit.second] * units_map[num._unit.second][_unit.second] < epsilon
                || units_map[_unit.second][num._unit.second] * units_map[num._unit.second][_unit.second] == 1) {
                _unit.first -= (num._unit.first * units_map[num._unit.second][_unit.second]);
                return *this; 
            }
        }
        else {
            throw("Units does not match");
        }
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator* (double factor) const {
        return NumberWithUnits(_unit.first * factor, this->_unit.second);
    }

    NumberWithUnits operator* (double factor, const NumberWithUnits &other_num) {
        return NumberWithUnits(other_num * factor);
    }

    ostream& operator<< (ostream& stream, const NumberWithUnits &num) {
        stream << num._unit.first << "[" << num._unit.second << "]";
        return stream;
    }

    istream& operator>> (istream& stream, NumberWithUnits &num) {
        double in_num = 0;
        string in_str, result_str;
        stream >> in_num >> in_str;
        for (string::size_type i=0; i < in_str.size(); i++) {
            if (in_str[i]  != '[' && in_str[i]  != ']' ) {
                result_str += in_str[i];
            }
        }
        num._unit.first = in_num;
        num._unit.second = result_str;
        return stream;
    }
}