#include <iostream>
#include <ctime>

#include "IODataFile.h"
#include "XMLReader.h"
#include "Floor.h"
#include "FloorCollection.h"

using namespace std;


int main()
{
    Floor floor;
    clock_t start, end, total;
    XMLReader reader("xml/landscapeTiles_sheet.xml");
    start = clock();
    reader.readFile();
    end = clock();
    total = (end - start);
    cout << "Total: " << total << "ms" << endl;

    FloorCollection cFloor;
    XMLNode* node;
    for (int u = 0; u < reader.size(); u++)
    {
        node = reader[u];
        cFloor.autoFillElement(node);
        cFloor.print();
    }

    // TODO - verificar porque subiu o tempo de execução

	return 0;
}