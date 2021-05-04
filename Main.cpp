#include "NumberWithUnits.hpp"
#include <sstream>
using namespace::std;
using namespace::ariel;

/**
 * @brief initializes some currency values
 * source: https://www.boi.org.il/he/markets/ExchangeRates/Pages/Default.aspx
 * sheep/lamb: https://ec.europa.eu/info/sites/default/files/food-farming-fisheries/farming/documents/sheep-meat-dashboard_en.pdf
 * 
 */
void init_table_file(){
    ofstream myfile;
    myfile.open ("shmuel_units.txt");
    myfile << "1 ILS = 3.252 USD" << endl;
    myfile << "1 ILS = 4.5109 GBP" << endl;
    myfile << "1 ILS = 3.9054 EURO" << endl;
    myfile << "1 ILS = 12904 RIAL" << endl;
    myfile << "1 CHUCK_NORRIS = 1 CHUCK_NORRIS" << endl;
    myfile << "1 SHEEP = 3 WOOL" << endl;
    myfile << "1 GOAT = 2 SHEEP";
    myfile.close(); 
}

void print_currency_coparisons(NumberWithUnits &a, NumberWithUnits &b, NumberWithUnits &c, NumberWithUnits &d, NumberWithUnits &e) {
    cout << "Comparing currencies from left to right while first left is the indicator" << endl
        << "We will compare by adding and increasing one from the left currency to all the others" << endl
        << "Current: " << a << endl;
    a+=b;
    cout a;

}

int main() {
    init_table_file();
    ifstream in_file("shmuel_units.txt");
    NumberWithUnits::read_units(in_file);
    istringstream iss{" 100 [ ILS ]  100 [USD ] 100 [ GBP] 100 [ EURO ] 100 [ RIAL] 1 [SHEEP] 1[GOAT]"};
    cout << "We initialize everything with chuck CHUCK_NORRIS because everything starts with chuck norris" << endl;
    std::cin.ignore();
    NumberWithUnits ILS(1, "CHUCK_NORRIS");
    NumberWithUnits USD(1, "CHUCK_NORRIS");
    NumberWithUnits GBP(1, "CHUCK_NORRIS");
    NumberWithUnits EURO(1, "CHUCK_NORRIS");
    NumberWithUnits RIAL(1, "CHUCK_NORRIS");
    NumberWithUnits SHEEP(1, "CHUCK_NORRIS");
    NumberWithUnits GOAT(1, "CHUCK_NORRIS");
    cout << " " << ILS << " " << USD << " " << GBP << " " << EURO << " " << RIAL << " " << SHEEP << " " << GOAT << endl;
    iss >> ILS >> USD >> GBP >> EURO >> RIAL >> SHEEP >> GOAT;
    cout << "Now we will overwrite accordingly" << endl;
    std::cin.ignore();
    cout << " " << ILS << " " << USD << " " << GBP << " " << EURO << " " << RIAL << " " << SHEEP << " " << GOAT << endl;
    std::cin.ignore();
    cout << "Now we can compare currencies...." << endl << endl << endl;
    print_currency_coparisons(ILS, USD, GBP, EURO, RIAL);
    return 0;
}