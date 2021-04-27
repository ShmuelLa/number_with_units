#include "NumberWithUnits.hpp"
#include <sstream>
using namespace::std;

namespace ariel {

    NumberWithUnits::NumberWithUnits(double amount, const string &unit_type) {
        if (units_map.count(unit_type) > 0) {
            _unit.first = amount;
            _unit.second = unit_type;
        }
        else {
            throw("This unit does not exist!");
        }
    }

    void NumberWithUnits::read_units(ifstream &file_name) {
        string unit1, unit2;
        double amount = 0;
        while (!file_name.fail() && !file_name.eof() ) {
            file_name >> unit1;
            if (unit1 == "1") {
                file_name >> unit1;
                file_name >> unit2;
                file_name >> amount;
                file_name >> unit2;
                units_map[unit1][unit2] = amount;
                units_map[unit2][unit1] = 1/amount;
                for (auto const &unit : units_map[unit1]) {
                    units_map[unit.first][unit2] = amount / unit.second;
                    units_map[unit2][unit.first] = unit.second / amount;
                }
                for (auto const &unit : units_map[unit2]) {
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

    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            double sum = _unit.first - (other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
            return NumberWithUnits(sum, _unit.second);   
        }
        throw("Units does not match");
    }

    NumberWithUnits NumberWithUnits::operator+ () const {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            double sum = _unit.first + (other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
            return NumberWithUnits(sum, _unit.second);   
        }
        throw("Units does not match");
    }

    bool NumberWithUnits::operator> (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (units_map[_unit.second][other_num._unit.second] * _unit.first > other_num._unit.first
                || (units_map[_unit.second][other_num._unit.second] * _unit.first - other_num._unit.first) > epsilon);
        }   
        throw("Units does not match");
    }

    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (this->_unit.first < other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        throw("Units does not match");
    }

    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (abs(_unit.first - other_num._unit.first * units_map[other_num._unit.second][_unit.second]) <= epsilon);
        }
        throw("Wrong Unit");
    }

    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        return (*this < other_num || *this == other_num);
    }

    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
        if (units_map[_unit.second].count(other_num._unit.second) > 0 && units_map[other_num._unit.second].count(_unit.second) > 0) {
            return (this->_unit.first >= other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        throw("Units does not match");
    }

    bool NumberWithUnits::operator!= (const NumberWithUnits &other_num) const {
        return !(*this == other_num);
    }

    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits &num) {
        if (units_map[_unit.second].count(num._unit.second) > 0 && units_map[num._unit.second].count(_unit.second) > 0) {
            _unit.first += (num._unit.first * units_map[num._unit.second][_unit.second]);
            return *this; 
        }
        throw("Units does not match");
    }

    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
        if (units_map[_unit.second].count(num._unit.second) > 0 && units_map[num._unit.second].count(_unit.second) > 0) {
            _unit.first -= (num._unit.first * units_map[num._unit.second][_unit.second]);
            return *this; 
        }
        throw("Units does not match");
    }

    NumberWithUnits NumberWithUnits::operator* (double factor) const {
        return NumberWithUnits(_unit.first * factor, this->_unit.second);
    }

    NumberWithUnits operator* (double factor, const NumberWithUnits &other_num) {
        return other_num * factor;
    }

    ostream& operator<< (ostream& stream, const NumberWithUnits &num) {
        stream << num._unit.first << "[" << num._unit.second << "]";
        return stream;
    }

    istream& operator>> (istream& stream, NumberWithUnits &num) {
        double in_num = 0;
        string result;
        char tmp_char = ' ';
        stream >> in_num;
        stream >> tmp_char ;
        while (tmp_char != ']') {
            if (tmp_char != '[') {
                result.push_back(tmp_char);
            }
            stream >> tmp_char;
        }
        if (units_map.count(result) > 0) {
            num._unit.first = in_num;
            num._unit.second = result;
            return stream;
        }
        throw("Wrong Unit");
    }
}