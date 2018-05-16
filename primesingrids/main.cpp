/* 
 * File:   main.cpp
 * Author: JEREMY
 *
 * Created on May 15, 2018, 8:15 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

//three problems:
//1) checking if it is prime - must use brute force for guaranteed 
//2) checking all possible combinations - must check all combos!
//3) grids of 10+ will exceed int max

// these two functions are checking if a number is prime
// by checking if an integer is 
// divisible by any number below it's square root

bool bruteforce (int const original, int index) {
    if(index > sqrt(original)) {
        return true;
    }
    if( (original%index) == 0) {
        return false;
    }
    return bruteforce(original, index + 1);
}

bool isPrime(int const num) {
    return bruteforce(num, 2);    
}

int reverse(int num) {
    int reversed = 0;
    while(num > 0) {
        reversed = reversed*10 + num % 10;
        num /= 10;
    }
    return reversed;
}
int main(int argc, char** argv) {

    int answer = 0;
    int size;
    string row;
    vector<int> distinct;
    
    distinct.push_back(1); 
    
    
    ifstream infile("primesingrids3.txt");
    infile >> size;
    
    // loading into 2d array
    int** grid = new int*[size];
    for(int i = 0 ; i < size; i++) {
        infile >> row;
        grid[i] = new int[size];
        for (int j = 0 ; j < size; j++) {
            grid[i][j] = (row[j] - '0');
        }
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    // every horizontal combo, 
    // for example for a line of three digits
    // 1 2 3
    // => 123, 12, 1, 23, 2, 3
    // 1 
    //   2 3
    //   2 
    //     3
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int digits = size - j; digits > 0; digits--) {
                int sum = 0;
                // getting sum
                for (int k = digits; k > 0; k--) {
                    sum = sum + (pow(10, k - 1) * grid[i][j + digits - k]);
                }
                if(isPrime(sum)) {
                    if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                        cout << "found prime horizontally: " << sum << endl;
                        distinct.push_back(sum); 
                        answer++;
                    }
                }              
                int reverseSum = reverse(sum);
                if(isPrime(reverseSum)) {
                    if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                        cout << "found prime horizontally: " << reverseSum << endl;
                        distinct.push_back(reverseSum); 
                        answer++;
                    }
                }
            }
        }
    }
    
    // every vertical combo
    // for example for a line of three digits
    // 1 
    // 2 
    // 3
    //=> 123, 12, 1, 23, 2, 3
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int digits = size - j; digits > 0; digits--) {
                int sum = 0;
                // getting sum
                for (int k = digits; k > 0; k--) {
                    sum = sum + (pow(10, k - 1) * grid[j + digits - k][i]);
                }
                if(isPrime(sum)) {
                    if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                        cout << "found prime horizontally: " << sum << endl;
                        distinct.push_back(sum); 
                        answer++;
                    }
                }              
                int reverseSum = reverse(sum);
                if(isPrime(reverseSum)) {
                    if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                        cout << "found prime horizontally: " << reverseSum << endl;
                        distinct.push_back(reverseSum); 
                        answer++;
                    }
                }
            }
        }
    }
    
    // now for diagonal
    // number of diagonals = 2x-1
    // for an southeast 3x3, 5 diagonals
    // 0th: (0,2)
    // 1st: (0,1),(1,2) => (0,1) => (1,2)
    // 2nd: (0,0),(1,1),(2,2) => (0,0), (1,1) = > (0,0) => (1,1), (2,2) -> (1,1) => (2,2)
    // 3rd: (1,0),(2,1) => (1,0) => (2,1)
    // 4th: (2,0)
    int x1 = 0;
    int y1 = size - 1;
    for(int diagonal = 0; diagonal < (size * 2) - 1; diagonal++) {
        if(diagonal < size) {
            for(int startpoint = 0; startpoint <= diagonal; startpoint++) {
                for(int digits = diagonal - startpoint + 1; digits > 0; digits--) {
                    int sum = 0;
                    for (int k = digits; k > 0; k--) {
                        
                        sum = sum + (pow(10, k - 1)) * grid[y1 + startpoint + digits - k][x1 + startpoint + digits - k];
                    }
                    if(isPrime(sum)) {
                        if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                            distinct.push_back(sum); 
                            answer++;
                        }
                    }              
                    int reverseSum = reverse(sum);
                    if(isPrime(reverseSum)) {
                        if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                            distinct.push_back(reverseSum); 
                            answer++;
                        }
                    }
                }
            }
            if(y1 != 0) {
                y1--;
            } 
            else {
                x1++;
            }
        }
        else {
            for(int startpoint = 0; startpoint < ((size * 2) - 1 - diagonal); startpoint++) {
                for(int digits = (size * 2) - 1 - diagonal - startpoint; digits > 0; digits--) {
                    int sum = 0;
                    for (int k = digits; k > 0; k--) {
                        sum = sum + (pow(10, k - 1)) * grid[y1 + startpoint + digits - k][x1 + startpoint + digits - k];
                    }
                    if(isPrime(sum)) {
                        if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                            distinct.push_back(sum); 
                            answer++;
                        }
                    }              
                    int reverseSum = reverse(sum);
                    if(isPrime(reverseSum)) {
                        if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                            distinct.push_back(reverseSum); 
                            answer++;
                        }
                    }
                }
            }
            x1++;
        }
    }
    
    // now diagonal SW
    // for an 3x3, 5 diagonals
    // 0th: (0,0)
    // 1st: (1,0),(0,1) => (1,0) => (0,1)
    // 2nd: (2,0),(1,1),(0,2) => (2,0), (1,1) = > (2,0) => (1,1), (0,2) -> (1,1) => (0,2)
    // 3rd: (2,1),(1,2) => (2,1) => (1,2)
    // 4th: (2,2)
    int x2 = 0;
    int y2 = 0;
    for(int diagonal = 0; diagonal < (size * 2) - 1; diagonal++) {
        if(diagonal < size) {
            for(int startpoint = 0; startpoint <= diagonal; startpoint++) {
                for(int digits = diagonal - startpoint + 1; digits > 0; digits--) {
                    int sum = 0;
                    for (int k = digits; k > 0; k--) {
                        //cout << "x: " << x2 - startpoint - (digits - k) << " y: " << y2 + startpoint + digits - k << " ";
                        sum = sum + (pow(10, k - 1)) * grid[y2 + startpoint + digits - k][x2 - startpoint - (digits - k)];
                    }
                    //cout << "sum is " << sum << endl;;
                    if(isPrime(sum)) {
                        if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                            distinct.push_back(sum); 
                            answer++;
                        }
                    }              
                    int reverseSum = reverse(sum);
                    if(isPrime(reverseSum)) {
                        if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                            distinct.push_back(reverseSum); 
                            answer++;
                        }
                    }
                }
            }
            if(x2 != size - 1) {
                x2++;
            } 
            else {
                y2++;
            }
        }
        else {
            for(int startpoint = 0; startpoint < ((size * 2) - 1 - diagonal); startpoint++) {
                for(int digits = (size * 2) - 1 - diagonal - startpoint; digits > 0; digits--) {
                    int sum = 0;
                    for (int k = digits; k > 0; k--) {
                        //cout << "x: " << x2 - startpoint - (digits - k) << " y: " << y2 + startpoint + digits - k << " ";
                        sum = sum + (pow(10, k - 1)) * grid[y2 + startpoint + digits - k][x2 - startpoint - (digits - k)];
                    }
                    //cout << "sum is " << sum << endl;;
                    if(isPrime(sum)) {
                        if(find(begin(distinct), end(distinct), sum) == end(distinct)) {
                            distinct.push_back(sum); 
                            answer++;
                        }
                    }              
                    int reverseSum = reverse(sum);
                    if(isPrime(reverseSum)) {
                        if(find(begin(distinct), end(distinct), reverseSum) == end(distinct)) {
                            distinct.push_back(reverseSum); 
                            answer++;
                        }
                    }
                }
            }
            y2++;
        }
    }
    cout << "list of distinct prime numbers: ";
    for (int i = 0; i < distinct.size(); i++) {
        cout << distinct[i] << " ";
    }
    cout << endl;
    cout << "answer: " << answer << endl;
    
    return 0;
}

