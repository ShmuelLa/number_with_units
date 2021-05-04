#include "NumberWithUnits.hpp"
#include <sstream>
using namespace::std;

namespace ariel {
    
    /**
     * @brief Construct a new Number With Units:: Number With Units object
     * 
     * @param amount the amount of the created unit
     * @param unit_type the unit type, must be from the current unit table
     */
    NumberWithUnits::NumberWithUnits(double amount, const string &unit_type) {
        if (units_map.count(unit_type) > 0) {
            _unit.first = amount;
            _unit.second = unit_type;
        }
        else {
            throw("This unit does not exist!");
        }
    }

    /**
     * @brief Reads the units and arranges them in the current units table
     * For each and every unit we crate a dedicated map that contains all 
     * of its convertable units and their conversion value
     * 
     * @param file_name file stream of the txt file to be readed from
     */
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

    /**
     * @brief check the compability of conversion between two different units
     * by checking if each and every one of them is present in each other value map
     * 
     * @param unit1 first unit to check
     * @param unit2 second unit to check
     * @return true if they math
     * @return false otherwise
     */
    bool NumberWithUnits::check_units_compability(const string unit1, const string unit2) const {
        if (units_map[unit1].count(unit2) > 0 && units_map[unit2].count(unit1) > 0) {
            return true;
        }
        return false;
    }

    /**
     * @brief unary - operator, multiplies the current amount with a negative value
     * 
     * @return NumberWithUnits a new object with it's value multiplied by (-1)
     */
    NumberWithUnits NumberWithUnits::operator- () const {
        NumberWithUnits result(_unit.first * (-1), _unit.second);
        return result;
    }

    /**
     * @brief postfix decrease by 1
     * 
     * @return NumberWithUnits& reference to the current object after the chagne
     */
    NumberWithUnits & NumberWithUnits::operator-- () {
        _unit.first = _unit.first -1;
        return *this;
    }

    /**
     * @brief postfix increase by 1
     * 
     * @return NumberWithUnits& reference to the current object after the chagne
     */
    NumberWithUnits & NumberWithUnits::operator++ () {
        _unit.first = _unit.first +1;
        return *this;
    }

    /**
     * @brief prefix decrease by one
     * 
     * @return NumberWithUnits a new object representing the current object before the change
     */
    NumberWithUnits NumberWithUnits::operator-- (int) {
        NumberWithUnits result(_unit.first, _unit.second);
        _unit.first = _unit.first -1;
        return result;
    }

    /**
     * @brief prefix increase by one
     * 
     * @return NumberWithUnits a new object representing the current object before the change
     */
    NumberWithUnits NumberWithUnits::operator++ (int) {
        NumberWithUnits result(_unit.first, _unit.second);
        _unit.first = _unit.first +1;
        return result;
    }

    /**
     * @brief binary decrease operator
     * 
     * @param other_num the rval of the equation
     * @return NumberWithUnits the result if the units match
     */
    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return NumberWithUnits(_unit.first - (other_num._unit.first * units_map[other_num._unit.second][_unit.second]), _unit.second);   
        }
        throw("Units does not match");
    }

    /**
     * @brief unary - operator, multiplies the current amount with a positive 1 value
     * 
     * @return NumberWithUnits reference to the same object with no change
     */
    NumberWithUnits NumberWithUnits::operator+ () const {
        return *this;
    }

    /**
     * @brief binary increase operator
     * 
     * @param other_num the rval of the equation
     * @return NumberWithUnits the result if the units match
     */
    NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return NumberWithUnits(_unit.first + (other_num._unit.first * units_map[other_num._unit.second][_unit.second]), _unit.second);   
        }
        throw("Units does not match");
    }

    /**
     * @brief comperator operator checks if the left object is bigger then the right object
     * will throw an exception if the units does not match
     * 
     * @param other_num the right object to compare
     * @return true if the left is bigger
     * @return false otherwise
     */
    bool NumberWithUnits::operator> (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return (units_map[_unit.second][other_num._unit.second] * _unit.first > other_num._unit.first
                || (units_map[_unit.second][other_num._unit.second] * _unit.first - other_num._unit.first) > epsilon);
        }   
        throw("Units does not match");
    }

    /**
     * @brief comperator operator checks if the left object is smaller then the right object
     * will throw an exception if the units does not match
     * 
     * @param other_num the right object to compare
     * @return true if the right is bigger
     * @return false otherwise
     */
    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return (this->_unit.first < other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        throw("Units does not match");
    }

    /**
     * @brief comperator operator checks if the left object is smaller or equal to the right object
     * will throw an exception if the units does not match
     * 
     * @param other_num the right object to compare
     * @return true if the right is bigger or equal
     * @return false otherwise
     */
    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        return (*this < other_num || *this == other_num);
    }

    /**
     * @brief comperator operator checks if the left object is bigger or equal to the right object
     * will throw an exception if the units does not match
     * 
     * @param other_num the right object to compare
     * @return true if the right is smaller or equal
     * @return false otherwise
     */
    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return (this->_unit.first >= other_num._unit.first * units_map[other_num._unit.second][_unit.second]);
        }   
        throw("Units does not match");
    }

    /**
     * @brief inequality comperator will throw an exception if the units does not match
     * 
     * @param other_num the right object to compare
     * @return true if both objects are not equal
     * @return false otherwise
     */
    bool NumberWithUnits::operator!= (const NumberWithUnits &other_num) const {
        return !(*this == other_num);
    }

    /**
     * @brief the equality operator, checks if two objects are equal by amount and value
     * for precision purposes compare them by using a small epsilon
     * 
     * @param other_num the other number to check
     * @return true if they are equal
     * @return false otherwise (throws an exception if they don't match)
     */
    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
        if (check_units_compability(_unit.second, other_num._unit.second)) {
            return (abs(_unit.first - other_num._unit.first * units_map[other_num._unit.second][_unit.second]) <= epsilon);
        }
        throw("Wrong Unit");
    }

    /**
     * @brief binary increase operator
     * 
     * @param num the number to increase by
     * @return NumberWithUnits& reference to the number after the change
     */
    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits &num) {
        if (check_units_compability(_unit.second, num._unit.second)) {
            _unit.first += (num._unit.first * units_map[num._unit.second][_unit.second]);
            return *this; 
        }
        throw("Units does not match");
    }

    /**
     * @brief binary decrease operator
     * 
     * @param num the number to decrease by
     * @return NumberWithUnits& reference to the number after the change
     */
    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
        if (check_units_compability(_unit.second, num._unit.second)) {
            _unit.first -= (num._unit.first * units_map[num._unit.second][_unit.second]);
            return *this; 
        }
        throw("Units does not match");
    }

    /**
     * @brief multiplication operator for multiplying an object with a number
     * 
     * @param factor the real number factor to multiply by
     * @return NumberWithUnits the result
     */
    NumberWithUnits NumberWithUnits::operator* (double factor) const {
        return NumberWithUnits(_unit.first * factor, this->_unit.second);
    }

    /**
     * @brief multiplication operator for multiplying a number with an object
     * 
     * @param factor the real number factor to multiply by
     * @param other_num the number object to multiply
     * @return NumberWithUnits 
     */
    NumberWithUnits operator* (double factor, const NumberWithUnits &other_num) {
        return other_num * factor;
    }
    
    /**
     * @brief output stream operator that defines the outputstream form of the objects
     * print "amount[unit name]"
     * 
     * @param stream outpust stream
     * @param num number to print
     * @return ostream& outpust stream with the result
     */
    ostream& operator<< (ostream& stream, const NumberWithUnits &num) {
        stream << num._unit.first << "[" << num._unit.second << "]";
        return stream;
    }

    /**
     * @brief input stream the can generate an object (or several objects)
     * from a string stream converts the "amount[unit name]" form back to an object form
     * 
     * @param stream input stream
     * @param num number to manipulate with the new unit
     * @return istream& input stream with result only if the unit is in the table
     */
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