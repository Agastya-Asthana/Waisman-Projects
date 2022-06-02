#include <stdio.h>
#include <stdlib.h>
#include <matplot/matplot.h>
#include <vector>

using namespace std;

int Num_Of_Commas(char* string);
int Num_Of_Lines(char filename[100]);
vector<int> Generate_Integer_Array_From_String(char*** cube, int col, int num_lines);


int main() {
    printf("Hello World!\n");
    char filename[100] = "/Users/agastyaasthana/Documents/Waisman Projects/Data Handler/RPM.csv";
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == nullptr) printf("The file could not be found!");

    // Find the number of heading and the number of lines I gotta read have to read
    int num_of_lines = Num_Of_Lines(filename);
    char comma_header[255];
    fscanf(file_ptr, "%s", comma_header);
    int num_of_headings = Num_Of_Commas(comma_header) + 1;
    printf("%s has %d headings and %d line\n", comma_header, num_of_headings, num_of_lines);

    //Moves the pointer past the newline character
    fgetc(file_ptr);

    // Allocating a 3D cube on the heap to make space all the data
    /*
     * The data structure is in the form of a cube because
     * the x-dimension filters by heading
     * the y-dimension filters by line
     * and the z-dimension takes you to the data in a string format
     * */
    char ***cube = (char***)(malloc(sizeof(char**) * num_of_headings));
    for (int i = 0; i < num_of_headings; ++i) {
        cube[i] = (char**)(malloc(sizeof(char *) * num_of_lines));
        for (int j = 0; j < num_of_lines; ++j) {
            cube[i][j] = (char*)(malloc(sizeof(char) * 50));
        }
    }
    printf("Cube formation complete\n\n");

    // The indices into each of the accessible places of the cube
    short heading_index = 0, line_index = 0, char_index = 0;
    // iterate over every single character until an end of file character is reached
    for (char c = fgetc(file_ptr); c != EOF ; c = fgetc(file_ptr)) {
        if (c == ','){
            cube[heading_index][line_index][char_index++] = '\0';
            heading_index++;
            char_index = 0;
        } else if (c == '\n' || c == '\r'){
            cube[heading_index][line_index][char_index++] = '\0';
            heading_index = 0;
            line_index++;
            char_index = 0;
        } else {
            cube[heading_index][line_index][char_index++] = c;
        }
    }
    printf("The data has been filled into the cube\n");
    printf("Going to make some accesses to the cube to check validity....\n");
    printf("1st heading 10th line string: %s\n", cube[1][10]);

    //Get an integer vector version of the numbers from the cube
    vector<int> time = Generate_Integer_Array_From_String(cube, 0, num_of_lines);
    vector<int> RPM = Generate_Integer_Array_From_String(cube, 1, num_of_lines);
    for (int i = 0; i < num_of_lines; ++i) {
        printf("%d\t", RPM.at(i));
    }
    matplot::hist(time);
    matplot::show();



    fclose(file_ptr);
    return 0;
}

int Num_Of_Commas(char* string){
    int commas = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] == ',') ++commas;
    }
    return commas;
}

/**
 * Open the file specified by the filename and search for newline characters
 * @param filename
 * @return number of lines a file contains
 */
int Num_Of_Lines(char filename[100]){
    FILE *file_ptr = fopen(filename, "r");
    int lines = 0;
    for (char c = fgetc(file_ptr); c != EOF ; c = fgetc(file_ptr)) {
        if (c == '\n' || c == '\r') lines++;
    }
    fclose(file_ptr);
    return lines;
}

vector<int> Generate_Integer_Array_From_String(char*** cube, int col, int num_lines){
    vector<int> t(num_lines);
    for (int i = 0; i < num_lines; ++i) {
        t.at(i) = atoi(cube[col][i]);
    }
    return t;
}