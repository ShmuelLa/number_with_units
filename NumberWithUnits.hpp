#pragma once
#include <iostream>
#include <fstream>
#include <map>
using std::string;
using std::map;
using std::pair;
using std::ifstream;
using std::ostream;
using std::istream;

namespace ariel {
    static map <string, map <string, double>> units_map;
    const static double epsilon = 0.00001;

    class NumberWithUnits {
        private:
            pair <double, string> _unit;

        public:
            NumberWithUnits(double amount, const string &unit_type);
            bool check_units_compability(const string unit1, const string unit2) const;
		    static void read_units(ifstream &file_name);
            NumberWithUnits operator- () const;
            NumberWithUnits operator+ (const NumberWithUnits &other_num) const;
            NumberWithUnits operator+ () const;
            NumberWithUnits & operator-- ();
            NumberWithUnits operator-- (int);
            NumberWithUnits & operator++ ();
            NumberWithUnits operator++ (int);
            NumberWithUnits operator- (const NumberWithUnits &other_num) const;
            bool operator> (const NumberWithUnits &other_num) const;
            bool operator< (const NumberWithUnits &other_num) const;
            bool operator== (const NumberWithUnits &other_num) const;
            bool operator<= (const NumberWithUnits &other_num) const;
            bool operator>= (const NumberWithUnits &other_num) const;
            bool operator!= (const  NumberWithUnits &other_num) const;
            NumberWithUnits& operator+= (const NumberWithUnits &num);
            NumberWithUnits& operator-= (const NumberWithUnits &num);
            NumberWithUnits operator* (double factor) const;
            friend NumberWithUnits operator* (double factor, const NumberWithUnits &other_num);
            friend ostream& operator<< (ostream& stream, const NumberWithUnits &num);
            friend istream& operator>> (istream& stream, NumberWithUnits &num);
	};
}