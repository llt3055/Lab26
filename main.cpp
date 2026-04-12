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

    // Vector Sort
    start = high_resolution_clock::now();
    sort(v.begin(), v.end());
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    vSort = duration.count();

    // List Sort
    start = high_resolution_clock::now();
    l.sort();
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    lSort = duration.count();

    // Set (Already sorted by design)
    sSort = -1;

    // Vector Insert
    start = high_resolution_clock::now();
    v.insert(v.begin() + v.size() / 2, "TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    vIns = duration.count();
    

    // List Insert
    start = high_resolution_clock::now();
    auto itL = l.begin();
    advance(itL, l.size() / 2);
    l.insert(itL, "TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    lIns = duration.count();

    // Set Insert
    start = high_resolution_clock::now();
    s.insert("TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    sIns = duration.count();

    // Vector Delete
    start = high_resolution_clock::now();
    v.erase(v.begin() + v.size() / 2);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    vDel = duration.count();

    // List Delete
    start = high_resolution_clock::now();
    itL = l.begin();
    advance(itL, l.size() / 2);
    l.erase(itL);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    lDel = duration.count();

    // Set Delete
    start = high_resolution_clock::now();
    auto itS = s.begin();
    advance(itS, s.size() / 2);
    s.erase(itS);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    sDel = duration.count();

    // FINAL OUTPUT 
    cout << left << setw(10) << "Operation" << setw(12) << "Vector" << setw(12) << "List" << setw(12) << "Set" << endl;
    cout << left << setw(10) << "Read"   << setw(12) << vRead << setw(12) << lRead << setw(12) << sRead << endl;
    cout << left << setw(10) << "Sort"   << setw(12) << vSort << setw(12) << lSort << setw(12) << sSort << endl;
    cout << left << setw(10) << "Insert" << setw(12) << vIns  << setw(12) << lIns  << setw(12) << sIns  << endl;
    cout << left << setw(10) << "Delete" << setw(12) << vDel  << setw(12) << lDel  << setw(12) << sDel << endl;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/