#include "NumberWithUnits.hpp"
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
            if (unit1 == "day") {
                    units_map2[unit1]["min"] = 24*60;
                    units_map2["min"][unit1] = 1 / (24*60);
                    units_map2[unit1]["sec"] = 24*60*60;
                    units_map2["sec"][unit1] = 1 / (24*60*60);
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
    test1();
    ifstream in_file("units.txt");
    NumberWithUnits::read_units(in_file);
    NumberWithUnits sec1(1,"sec");
    NumberWithUnits min1(1,"min");
    NumberWithUnits hour1(1,"hour");
    NumberWithUnits day1(1,"day");
    cout << min1 << endl;
    cout << hour1 << endl;
    cout << sec1 << endl;
    cout << day1 << endl;
    cout << day1 + hour1 << endl;
    cout << day1 + min1 << endl;
    return 0;
}