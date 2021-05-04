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
    myfile << "1 USD = 3.252 ILS" << endl;
    myfile << "1 GBP = 4.5109 ILS" << endl;
    myfile << "1 EURO = 3.9054 ILS" << endl;
    myfile << "1 ILS = 12904 RIAL" << endl;
    myfile << "1 CHUCK_NORRIS = 1 CHUCK_NORRIS" << endl;
    myfile << "1 SHEEP = 3 WOOL" << endl;
    myfile << "1 GOAT = 2 SHEEP";
    myfile.close(); 
}

void print_currency_coparisons(NumberWithUnits &a, NumberWithUnits &b, NumberWithUnits &c, NumberWithUnits &d, NumberWithUnits &e) {
    cout << "Comparing currencies from left to right while first left is the indicator" << endl
        << "We will compare by increasing and decresing the left currency from all the others" << endl
        << "Current: " << a << endl << "Incrementing..." << endl
        << b+a << " " << c+a << " " << d+a << " " << e+a << endl << "Decrementing...." << endl
        << b-a << " " << c-a << " " << d-a << " " << e-a << endl;
}

int main() {
    init_table_file();
    ifstream in_file("shmuel_units.txt");
    NumberWithUnits::read_units(in_file);
    istringstream iss{" 1 [ ILS ]  1 [USD ] 1 [ GBP] 1 [ EURO ] 1 [ RIAL] 1 [SHEEP] 1[GOAT]"};
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
    cout << "Now we can compare currencies.... starting with ILS" << endl << endl << endl;
    print_currency_coparisons(ILS, USD, GBP, EURO, RIAL);
    cout << "Now the GBP" << endl << endl;
    std::cin.ignore();
    print_currency_coparisons(GBP, USD, ILS, EURO, RIAL);
    cout << "Now the Iranian Rial.. It's amazing what some sanctions can do..." << endl << endl;
    std::cin.ignore();
    print_currency_coparisons(RIAL, USD, ILS, EURO, GBP);
    return 0;
}