#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdlib.h>
#include <matplot/matplot.h>
#include <vector>

using namespace std;

class DataHandler{
public:
    void LoadFile(char *filename);
    char*** GenerateCube();

protected:
    int Num_Of_Commas(char* string);
    int Num_Of_Lines(char filename[100]);
    vector<int> Generate_Integer_Array_From_String(char*** cube, int col, int num_lines);
};



#endif //DATA_HANDLER_H
