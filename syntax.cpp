#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{

    ifstream infile("analyzer.txt"); /*assigning infile to to the input text otherwise 
						     the program will spit out all zeroes as the result.*/

    //Variables
    string Storeline;      //Variable to store the line
    string token = "";     //variable to store the token
    string Name = "";      //variable to store the table name
    bool Finished = false; //boolean to determine end of line read
    string chump;          //the string we use to input our text file

    //Structure for symbol table
    struct SymbolTable
    {
        string tokenType;
        string tokenName;
    } table[1000]; //this will be a constructor of sorts

    //position in line read
    int position = 0;
    int a = 0;

    cout << "Enter the file name, don't forget to enter the txt extension as well.\n";
    cin >> chump;

    getline(infile, chump); /*gets the data from the txt file and converts it to a string.*/

    if (!infile.is_open()) //input.txt cannot be open then we get this error message.
    {
        cout << "cant open file!";
        return 0;
    }

    //Read til end of file
    do
    {
        Finished = false;

        //get line from input file
        getline(infile, Storeline);

        if (!infile.eof())
        {
            //do... while until line is read
            do
            {
                char character = Storeline[position++];
                if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
                {
                    token = token + character; //here we tokenize each alphabetical character
                }
                else if (character == '(' || character == ')' || character == '{' || character == '}' || character == ';' || character == '=' || character == '+' || character >= 0 || character <= 0)
                //We tokenize the symbols that are not letters
                {
                    if (token == "int" || token == "double" || token == "char")
                    //here we specifiying what the symbol table should look for
                    {
                        table[a].tokenType = token; //We search our symbol table for the Token types
                        while (character != ';')    //I need this semicolon so the variable names will show up.
                        {
                            character = Storeline[position++];
                            Name = Name + character;
                        }
                        table[a].tokenName = Name; //We search our symbol table or the Token Names
                        a++;
                    }
                    cout << token << endl;
                    if (Name != "")
                    {
                        cout << Name << endl;
                    }
                    token = ""; //displays variable type
                    Name = "";  //displays variable itself
                    cout << character << endl;
                }
                if (position >= Storeline.length())
                {
                    Finished = true;
                    position = 0;
                }
            } while (!Finished);
        }
    } while (!infile.eof());

    //close input file
    infile.close();

    //table format
    cout << "Type      Variable Name\n";

    //loop to display each of the symbol tables data
    for (int f = 0; f < a; f++)
    {
        cout << table[f].tokenType << "        " << table[f].tokenName << endl;
    }

    system("pause");

    return 0;
}