//*****************************************************************************
// Author:           Ryan Shuler
// Assignment:       STEM Analysis
// Date:             11.1.24
// Description:      Analyzes STEM data for gender distribution in various majors
// Sources:          class notes
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

const char DATA_IN_FILE[] = "stem.txt";
const char DATA_OUT_FILE[] = "stemout.txt";
const int MAX_CHARS = 100;

// Row class to store data for each major
class Row {
public:
    int majorCode = 0;
    char major[MAX_CHARS + 1] = {0};
    char majorCategory[MAX_CHARS + 1] = {0};
    int total = 0;
    int men = 0;
    int women = 0;
    int annualSalary = 0;

    Row(istream &in) {
        in >> majorCode >> major >> majorCategory >> total >> men >> women >> annualSalary;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

// Function prototypes
void printRatioHeader(ostream &out);
void ratioCalc(const Row &row, ostream &out);

int main() {
    ifstream fin(DATA_IN_FILE);
    ofstream fout(DATA_OUT_FILE);

    if (!fin || !fout) {
        cerr << "Error opening file(s)" << endl;
        return 1;
    }

    // Skip the header line in input file
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Write header for output file
    printRatioHeader(fout);

    // Read data and output analysis
    while (fin.peek() != EOF) {
        Row row(fin);
        ratioCalc(row, fout);
    }

    fin.close();
    fout.close();

    return 0;
}

// Function to print header for ratio data
void printRatioHeader(ostream &out) {
    out << setw(45) << left << "MAJOR"
        << setw(10) << right << "% MEN"
        << setw(10) << "% WOMEN" << endl;
}

// Function to calculate and output gender ratios
void ratioCalc(const Row &row, ostream &out) {
    double pctMen = 100.0 * row.men / row.total;
    double pctWomen = 100.0 * row.women / row.total;

    out << setw(45) << left << row.major
        << setw(10) << fixed << setprecision(2) << pctMen
        << setw(10) << pctWomen << endl;
}
