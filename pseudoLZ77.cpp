#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


string encodeStr(string inputText){

    int inputLen = inputText.length();
    int maxWindowSize = 5;
    map<string, int> dict;

    int currWindowBegin = 0;
    int currWindowLen = 1;

    // set first char to have non-empty dictionary
    string first = inputText.substr(currWindowBegin, currWindowLen);
    dict[first] = 1;

    // add first char to output
    string outputText = first;
    currWindowBegin++;

    // traverse string and convert repeatable sequences to pos of first instance
    while (currWindowBegin + currWindowLen < inputLen + 1){
        string curr = inputText.substr(currWindowBegin, currWindowLen);
        int currPos = dict[curr];

        // if sequence not in dictionary, add its position in input
        if (currPos == 0){
            if (currWindowLen == 1){ // if single char not in dict, add it
                dict[curr] = currWindowBegin + 1; // add pos offset because 0 = not in dict
                outputText += curr;
            }
            else{
                string sub = curr.substr(0, currWindowLen - 1);
                outputText += to_string(dict[sub]) + curr.back();
                dict[curr] = currWindowBegin + 1;
            }
            currWindowBegin = currWindowBegin + currWindowLen;
            currWindowLen = 1;
        }
        else { // if sequence in dict, check if its also in dict when combined with next char
            currWindowLen++;
        }
    }

    return outputText;
}

string decodeStr(string encodedText){
    
    int inputLen = encodedText.length();
    map<int, string> dict;

    // set first char to have non-empty dictionary
    string first = encodedText.substr(0, 1);
    dict[1] = first;

    // add first char to output
    string decodedText = first;
    
    for (int i = 1; i < inputLen; i++){
        char c = encodedText[i];
        if (isdigit(c)){
            int d = c - '0';
            string val = dict[d];
            string l = to_string(c) + encodedText[i+1];
            string newStr = val + encodedText[i+1];
            // cout << "new str = " << l << " or " << newStr << ": " << i + 1 << "\n";
            decodedText += newStr;
            dict[i + 1] = newStr;
            i++;
        }
        else {
            decodedText += c;
        }
    }

    return decodedText;
}

int main(){

    string inputText = "AABABBABBAABA";
    string encodedText = encodeStr(inputText);

    cout << "in str:  " << inputText << "\n";
    cout << "enc str: " << encodedText << "\n";

    string decodedText = decodeStr(encodedText);

    cout << "dec str: " << decodedText << "\n";
    cout << (inputText == decodedText);
    
    return 0;
}
