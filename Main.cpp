#include "NumberWithUnits.hpp"
#include <sstream>
using namespace::std;
using namespace::ariel;

int test1() {
    map <string, map <string, double> > units_map2;
    string unit1, unit2;
    double amount;
    ifstream in_file("units.txt");

    if (!in_file) {
        perror("Error opening file");
    }
    while (!in_file.fail() && !in_file.eof() ) {
        in_file >> unit1;
        if (unit1 == "1") {
            in_file >> unit1;
            in_file >> unit2;
            in_file >> amount;
            in_file >> unit2;
            units_map2[unit1][unit2] = amount;
            units_map2[unit2][unit1] = 1/amount;
            for (auto unit : units_map2[unit1]) {
                units_map2[unit.first][unit2] = amount / unit.second;
                units_map2[unit2][unit.first] = unit.second / amount;
            }
            for (auto unit : units_map2[unit2]) {
                units_map2[unit.first][unit1] = (1/amount) / unit.second;
                units_map2[unit1][unit.first] = unit.second / (1/amount);
            }
        }
    }
    cout << "==========================" << endl;
    for (map <string, map<string, double>>::iterator it = units_map2.begin(); it != units_map2.end(); ++it) {
        cout << it->first;
        map <string,double> internal_map = it->second;
        for (map<string, double>::iterator it2 = internal_map.begin(); it2 != internal_map.end(); ++it2) {
            cout << " <" << it2->first << " , " << it2->second << " >" << endl;
        }
    }
    cout << "==========================" << endl;
    /**
    for (map <string, map<string, double>>::iterator it = units_map2.begin(); it != units_map2.end(); ++it) {
        map <string,double> internal_map = it->second;
        for (map<string, double>::iterator it2 = internal_map.begin(); it2 != internal_map.end(); ++it2) {
            for (map <string, map<string, double>>::iterator it3 = units_map2.begin(); it3 != units_map2.end(); ++it3) {
                if (it3->first == it2->first) {
                    cout << it3->first << "  " << it2->second << "| " << it2->first << " " << endl;
                }
            }
        }
    }
    */
    return 0;
}

int main() {
    /**
    test1();
    ifstream in_file("units.txt");
    NumberWithUnits::read_units(in_file);
    istringstream input = istringstream("20 [ g ]");
    istringstream input2 = istringstream(" 900 [ton] ");
    istringstream iss3{" 8 [   sec     ]   -1 [ton ] 29.7 [min ]"};
    NumberWithUnits a(7, "ILS");
    NumberWithUnits b(7, "ILS");
    NumberWithUnits c(7, "ILS");
    iss3 >> a >> b >> c;
    NumberWithUnits temp_input(7, "ILS");
    cout << temp_input << endl;
    input >> temp_input;
    cout << temp_input << endl;
    input2 >> temp_input;
    cout << temp_input << endl;
    return 0;
    */
}