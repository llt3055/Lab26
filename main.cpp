// COMSC-210 | Lab  26| Tianyi Cao 
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    
    const int NUM_RUNS = 15;
    long long stats[2][4][3] = {0}; 
    string nm;

    for (int run = 0; run < NUM_RUNS; run++) {

    vector<string> v;
    list<string> l;
    set<string> s;

    // read codes.txt into vector
    auto start = high_resolution_clock::now();
    ifstream fin1("codes.txt");
    while (getline(fin1, nm)) v.push_back(nm);
    fin1.close();
    stats[0][0][0] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    
    // read codes.txt into list
    start = high_resolution_clock::now();
    ifstream fin2("codes.txt");
    while (getline(fin2, nm)) l.push_back(nm);
    fin2.close();
    stats[0][0][1] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

    // Set Read
    start = high_resolution_clock::now();
    ifstream fin3("codes.txt");
    while (getline(fin3, nm)) s.insert(nm);
    fin3.close();
    stats[0][0][2] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    
    start = high_resolution_clock::now();
    l.sort();
    stats[0][1][1] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    stats[0][1][2] = -1; // Set is inherently sorted

    // List Sort
    start = high_resolution_clock::now();
    v.insert(v.begin() + v.size(), "TESTCODE");
    stats[0][2][0] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    auto itL = l.begin();
    advance(itL, l.size());
    l.insert(itL, "TESTCODE");
    stats[0][2][1] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    s.insert("TESTCODE");
    stats[0][2][2] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    v.erase(v.begin() + v.size() / 2);
    stats[0][3][0] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count(); 

    start = high_resolution_clock::now();
    itL = l.begin();
    advance(itL, l.size() / 2);
    l.erase(itL);
    stats[0][3][1] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count(); 

    start = high_resolution_clock::now();
    auto itS = s.begin();
    advance(itS, s.size() / 2);
    s.erase(itS);
    stats[0][3][2] = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count(); 
    cout << "\nMilestone 2 complete: 3D array populated and adapted to 15-run loop." << endl;

    // Summing results from slice 0 into the accumulator slice 1
        for (int op = 0; op < 4; op++) {
            for (int cont = 0; cont < 3; cont++) {
                if (stats[0][op][cont] != -1) {
                    stats[1][op][cont] += stats[0][op][cont];
                } else {
                    stats[1][op][cont] = -1; 
                }
            }
        }
        cout << "Iteration " << run + 1 << " complete." << endl;
    }

    // Calculating averages and matching the sample table output
    cout << "\n" << left << setw(10) << "Operation" << setw(12) << "Vector" << setw(12) << "List" << setw(12) << "Set" << endl;
    string opNames[] = {"Read", "Sort", "Insert", "Delete"};
    for (int op = 0; op < 4; op++) {
        cout << left << setw(10) << opNames[op];
        for (int cont = 0; cont < 3; cont++) {
            if (stats[1][op][cont] == -1) {
                cout << setw(12) << "-1";
            } else {
                // Average = Total Sum / 15
                cout << setw(12) << stats[1][op][cont] / NUM_RUNS;
            }
        }
        cout << endl;
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/