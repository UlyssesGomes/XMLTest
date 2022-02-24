#include <iostream>
#include <ctime>

#include "IODataFile.h"
#include "XMLReader.h"

using namespace std;


int main()
{

    clock_t start, end, total;
    XMLReader reader("xml/landscapeTiles_sheet.xml");
    start = clock();
    reader.readFile();
    end = clock();
    total = (end - start);
    cout << "Total: " << total << "ms" << endl;

	return 0;
}