#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    ofstream file("canINTbeinserter.csv", ios::app);
    if (!file)
    {
        cerr << "Error opening file.\n";
        return 1;
    }

    int value = 123;
    file << value << ",";

    file.close();
    return 0;
}

