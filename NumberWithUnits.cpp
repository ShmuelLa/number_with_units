#include "NumberWithUnits.hpp"
#include <cstdlib>
using namespace::std;

namespace ariel {

    NumberWithUnits::NumberWithUnits(long double amount, string unit_type) {
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
        long double amount;
        while (!file_name.fail() && !file_name.eof() ) {
            file_name >> unit1;
            if (unit1 == "1") {
                file_name >> unit1;
                file_name >> unit2;
                file_name >> amount;
                file_name >> unit2;
                units_map[unit1][unit2] = amount;
                units_map[unit2][unit1] = 1/amount;
                if (unit1 == "day") {
                    units_map[unit1]["min"] = 24*60;
                    units_map["min"][unit1] = 1 / (24*60);
                    units_map[unit1]["sec"] = 24*60*60;
                    units_map["sec"][unit1] = 1 / (24*60*60);
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
        if (_unit.second == other_num._unit.second) {
            long double sum = _unit.first - other_num._unit.first;
            return NumberWithUnits(sum, _unit.second);
        }
        if (units_map[_unit.second][other_num._unit.second] * units_map[other_num._unit.second][_unit.second] == 1) {
            long double sum = _unit.first - other_num._unit.first;
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
        if (_unit.second == other_num._unit.second) {
            long double sum = _unit.first + other_num._unit.first;
            return NumberWithUnits(sum, _unit.second);
        }
        if (units_map[_unit.second][other_num._unit.second] * units_map[other_num._unit.second][_unit.second] == 1) {
            long double sum = _unit.first + (other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
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
            long double sum = _unit.first + other_num._unit.first;
            return (_unit.first > other_num._unit.first);
        }
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
        if (_unit.second == other_num._unit.second) {
            long double sum = _unit.first + other_num._unit.first;
            return (_unit.first < other_num._unit.first);
        }
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
        if (_unit.second == other_num._unit.second) {
            return true;
        }
        if (units_map[_unit.second][other_num._unit.second] * units_map[other_num._unit.second][_unit.second] == 1
        &&  (abs(units_map[_unit.second][other_num._unit.second] * _unit.first - other_num._unit.first) <= epsilon
        || abs(units_map[_unit.second][other_num._unit.second] * _unit.first - other_num._unit.first) == 0)) {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        if (_unit.second == other_num._unit.second) {
            long double sum = _unit.first + other_num._unit.first;
            return (_unit.first <= other_num._unit.first);
        }
        else {
            throw("Units does not match");
        }
        return false;
    }

    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
        if (_unit.second == other_num._unit.second) {
            long double sum = _unit.first + other_num._unit.first;
            return (_unit.first >= other_num._unit.first);
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
        _unit.first = _unit.first + num._unit.first;
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
        _unit.first = _unit.first - num._unit.first;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator* (long double factor) {
        _unit.first = _unit.first * factor;
        return *this;
    }

    NumberWithUnits operator* (long double factor, const NumberWithUnits) {
        NumberWithUnits result(1, "km");
        return result;
    }

    ostream& operator<< (ostream& stream, const NumberWithUnits& num) {
        stream << num._unit.first << "[" << num._unit.second << "]";
        return stream;
    }

    istream& operator>> (istream& stream, const NumberWithUnits& num) {
        return stream;
    }
}