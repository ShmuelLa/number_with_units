#include "NumberWithUnits.hpp"

namespace ariel {
    NumberWithUnits::NumberWithUnits(double amount, string unit_type){}
    void NumberWithUnits::read_units(ifstream &file_name) {}
    NumberWithUnits operator+ (NumberWithUnits &other_num) {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits operator- (NumberWithUnits &other_num) {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits NumberWithUnits::operator- () const {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits & NumberWithUnits::operator-- () {
        return *this;
    }
    NumberWithUnits & NumberWithUnits::operator++ () {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-- (int) {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++ (int) {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator- (NumberWithUnits &other_num) {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits NumberWithUnits::operator+ () const {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits NumberWithUnits::operator+ (NumberWithUnits &other_num) {
        NumberWithUnits result(1, "km");
        return result;
    }
    bool NumberWithUnits::operator> (const NumberWithUnits &other_num) const {
        return true;
    }
    bool NumberWithUnits::operator< (const NumberWithUnits &other_num) const {
        return true;
    }
    bool NumberWithUnits::operator== (const NumberWithUnits &other_num) const {
        return true;
    }
    bool NumberWithUnits::operator<= (const NumberWithUnits &other_num) const {
        return true;
    }
    bool NumberWithUnits::operator>= (const NumberWithUnits &other_num) const {
        return true;
    }
    bool NumberWithUnits::operator!= (const NumberWithUnits &other_num) const {
        return true;
    }
    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits &num) {
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits &num) {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator* (double factor) {
        NumberWithUnits result(1, "km");
        return result;
    }
    NumberWithUnits operator* (double factor, const NumberWithUnits) {
        NumberWithUnits result(1, "km");
        return result;
    }
    ostream& operator<< (ostream& stream, const NumberWithUnits& num) {
        return stream;
    }
    istream& operator>> (istream& stream, const NumberWithUnits& num) {
        return stream;
    }
}