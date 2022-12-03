#include <iostream>
#include "BinTreeSearch.h"
#include <stdio.h> 
#include <time.h> 

using namespace std;

int main() {
    BinaryFile file;
    file.CreateBinFile("test.txt", "test.bin");
    BinTreeSearch bin("test.bin");

    //RegSmallBuisness r;
    //cout << "Create RegSmallBuisness object:\n";
    //cout << "Input number of license:\n";
    //cin >> r.num_lic;
    //cout << "Input name:\n";
    //cin >> r.name;
    //cout << "Input founder:\n";
    //cin >> r.founder;
    //cout << "Input active_lic:\n";
    //cin >> r.active_lic;

    //clock_t start = clock();

    //bin.search(bin.root, &r);

    //clock_t end = clock();
    //double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    //cout << "Time: " << seconds << '\n';
    //cout << "Time: " << "1.13 " << "seconds\n";

    //file.outBinFile("test.bin");
    

    
    bin.print(bin.root, bin.height(bin.root) * 5 + 5);
    
    //cout << '\n';
    //bin.printRotateCount();
    
    return 0;
    //BinTreeSearch* tree = new BinTreeSearch;
    //return tree->exec();
}