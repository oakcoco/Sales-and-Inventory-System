#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    // Get current time
    time_t now = time(0);
    tm* localTime = localtime(&now);

    // Create an array of strings to store date and time parts
    string dateTime[6];

    // Use stringstream to format values
    stringstream ss;

    ss << (1900 + localTime->tm_year);
    dateTime[0] = ss.str(); ss.str(""); ss.clear();

    ss << setw(2) << setfill('0') << (1 + localTime->tm_mon);
    dateTime[1] = ss.str(); ss.str(""); ss.clear();

    ss << setw(2) << setfill('0') << localTime->tm_mday;
    dateTime[2] = ss.str(); ss.str(""); ss.clear();

    ss << setw(2) << setfill('0') << localTime->tm_hour;
    dateTime[3] = ss.str(); ss.str(""); ss.clear();

    ss << setw(2) << setfill('0') << localTime->tm_min;
    dateTime[4] = ss.str(); ss.str(""); ss.clear();

    ss << setw(2) << setfill('0') << localTime->tm_sec;
    dateTime[5] = ss.str();

    // Display the array content
    cout << "Date and Time Array: ";
    for (int i = 0; i < 6; ++i)
    {
        cout << dateTime[i];
        if (i < 2) cout << "-";
        else if (i == 2) cout << " ";
        else if (i < 5) cout << ":";
    }
    cout << endl;

    return 0;
}

