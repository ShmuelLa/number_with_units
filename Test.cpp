#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("Input") {
    ifstream units_file{"units.txt"};

}

TEST_CASE("Output") {

}

TEST_CASE("Right Calculation") {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits distance(5,"km");
    NumberWithUnits weight(5,"kg");
    CHECK((distance*2) == ("10[km]"));
    CHECK((weight*2) == ("10[kg]"));
}