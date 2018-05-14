/* 
 * File:   main.cpp
 * Author: JEREMY
 * https://www.reddit.com/r/dailyprogrammer/comments/8gjc3k/20180502_challenge_359_intermediate_unwrap_some/
 * Created on May 14, 2018, 3:24 PM
 * Finished: 5:12 PM
 */

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    ifstream infileMax("unwraptext.txt");
    ifstream infileParse("unwraptext.txt");
    ifstream infileParseHelper("unwraptext.txt");
    int maxChar = 0;
    int lineSize;
    string temp;
    string help;
    
    // get max number of characters in a line
    while(getline(infileMax, temp)) {
        lineSize = temp.length() - 1; 
        if(lineSize > maxChar) {
            maxChar = lineSize;
        }
    }

    cout << "   ";
    
    
    getline(infileParseHelper, help);
    
    // finding lines that end with periods, and if line size + first word of next line < max width, its a new paragraph
    // this condition is unfortunately the best it gets for 'reverse engineering'
    while(getline(infileParse, temp)) {
        // if there is a next line, get the first word of next line.
        if(getline(infileParseHelper, help)) {
        stringstream tempStream(help);
        tempStream >> help;
            //getting rid of \n
            temp.erase(temp.end() - 1);
            // finding lines that end with a period
            char end = *(temp.end() - 1);
            if( (end == '.') || (end == '!') || (end == '?') ) {
                if((temp.size() + help.size()) <= maxChar ) {
                    cout << temp << endl << endl << "   ";
                }   
                else {
                    cout << temp << " ";
                }
            }
            else {
                cout << temp << " ";
            }
        }
        else {
            cout << temp;
        }
    }
    
    return 0;
}

