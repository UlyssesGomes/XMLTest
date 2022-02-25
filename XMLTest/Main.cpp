#include <iostream>
#include <ctime>

#include "IODataFile.h"
#include "XMLReader.h"
#include "Floor.h"

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

    XMLNode * node = reader.getRoot();

    for (auto u = node->children->begin(); u != node->children->end(); u++)
    {
        (*u)->fillObject(&floor);
        floor.print();
    }

    // TODO - botar a variável children privada e implementar uma classe que 
    // preencha a si mesma quando for um modelo container e não só element.
    // Em seguida ver uma forma que o XMLReader lê vários elements e não só
    // um container.

	return 0;
}