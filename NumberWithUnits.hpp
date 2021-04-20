#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace ariel {
    class NumberWithUnits {
        private:
        public:
            NumberWithUnits(double amount, string unit_type);
		    static void read_units(ifstream &file_name);
            NumberWithUnits operator- () const;
            NumberWithUnits operator+ () const;
            NumberWithUnits & operator-- ();
            NumberWithUnits & operator++ ();
            NumberWithUnits operator-- (int);
            NumberWithUnits operator++ (int);
            NumberWithUnits operator+ (NumberWithUnits &other_num);
            NumberWithUnits operator- (NumberWithUnits &other_num);
            bool operator> (const NumberWithUnits &other_num) const;
            bool operator< (const NumberWithUnits &other_num) const;
            bool operator== (const NumberWithUnits &other_num) const;
            bool operator<= (const NumberWithUnits &other_num) const;
            bool operator>= (const NumberWithUnits &other_num) const;
            bool operator!= (const  NumberWithUnits &other_num) const;
            NumberWithUnits& operator+= (const NumberWithUnits &num);
            NumberWithUnits& operator-= (const NumberWithUnits &num);
            NumberWithUnits operator* (double factor);
            friend NumberWithUnits operator* (double factor, const NumberWithUnits);
            friend ostream& operator<< (ostream& stream, const NumberWithUnits& num);
            friend istream& operator>> (istream& stream, const NumberWithUnits& num);
	};
}