#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

bool isCapital(char x)
{
       if (x >= 'A' && x <= 'Z') return true;
       else return false;
}

bool isBefore(string s1, string s2){

    // special case for $, it is the smallest char
    if (s1[0] == '$') return true;
    else if (s2[0] == '$') return false;
    else {
        //compare first chars of substring until diff found 
        int len1 = s1.length();
        int len2 = s2.length();
        int shortlen;
        bool isFirstShortest;
        if (len1 <= len2){
            shortlen = len1;
            isFirstShortest = true;
        }
        else {
            shortlen = len2;
            isFirstShortest = false;
        }

        // compare chars until one smaller than other
        for (int i = 0; i < shortlen; i++){
            char c1 = s1[i];
            char c2 = s2[i];
            if (isCapital(c1)) c1 += ('a' - 'A');
            if (isCapital(c2)) c2 += ('a' - 'A');
            // cout << c1 << " vs " << c2 << "\n";
            
            if (c1 < c2){ // if current char of s1 before s2's
                return true;
            }
            else if (c2 < c1){ // if current char of s2 before s1's
                return false;
            }
            // if same char check next char
        }

        // if whole strings are the same
        // return true if s1 shorter (or same length), false otherwise
        return isFirstShortest;
    }
}

vector<string> quickSort(vector<string> v){
    
    int s = v.size();

    // check if base case
    if (s == 1){
        return v;
    }

    // set pivot to middle element
    const int pivi = v.size() / 2;
    string pivot = v[pivi];

    // create vectors for earlier and later string
    vector<string> v1;
    vector<string> v2;

    // cout << "\n";

    // compare each element with pivot, if earlier: put in v1, if later: put in v1
    for (int i = 0; i < s; i++){
        if (i != pivi){ // if pivot ignore
            if (isBefore(v[i], pivot)){
                v1.push_back(v[i]);
            }
            else {
                v2.push_back(v[i]);
            }
        }
    }

    // cout << "out" << "\n";

    // cout << "v1: ";
    // for (int i = 0; i < v1.size(); i++){
    //     cout << v1[i] + " ";
    // }
    // cout << "\n" << "v2: ";
    // for (int i = 0; i < v2.size(); i++){
    //     cout << v2[i] + " ";
    // }
    // cout << "\n";

    // recursively sort both arrays then combine them + pivot
    if (!v1.empty()){
        v1 = quickSort(v1);
    }
    if (!v2.empty()){
        v2 = quickSort(v2);
    }

    v1.insert(v1.end(), pivot);
    v1.insert(v1.end(), v2.begin(), v2.end());

    return v1;
}

void testOrdering(){

    //print answers
    cout << 110010111010 << "\n";

    string a = "a";
    string b = "b";
    string ab = "ab";
    string ac = "ac";
    string ba = "ba";
    string d = "$";

    // answer T or 1
    bool isB1 = isBefore(a, b);
    cout << isB1;

    // answer T or 1
    bool isB2 = isBefore(ab, b);
    cout << isB2;

    // answer F or 0
    bool isB3 = isBefore(b, a);
    cout << isB3;

    // answer F or 0
    bool isB4 = isBefore(b, ab);
    cout << isB4;

    // answer T or 1
    bool isB5 = isBefore(ab, ac);
    cout << isB5;

    // answer F or 0
    bool isB6 = isBefore(ac, ab);
    cout << isB6;

    // answer T or 1
    bool isB8 = isBefore(a, a);
    cout << isB8;

    // answer T or 1
    bool isB9 = isBefore(ab, ab);
    cout << isB9;

    // answer T or 1
    bool isB10 = isBefore(ab, ba);
    cout << isB10;

    // answer F or 0
    bool isB11 = isBefore(ba, ab);
    cout << isB11;

    // answer T or 1
    bool isB12 = isBefore(d, a);
    cout << isB12;

    // answer F or 0
    bool isB13 = isBefore(a, d);
    cout << isB13;

}

void testSorting(){

    cout << "sorting 1: ";
    vector<string> s1 = {"c", "b", "a"};
    for (int i = 0; i < s1.size(); i++){
        cout << s1[i] + " ";
    }

    s1 = quickSort(s1);

    for (int i = 0; i < s1.size(); i++){
        cout << s1[i] + " ";
    }

    cout << "\n\n" << "sorting 2: ";

    vector<string> s2 = {"c", "a", "b"};
    for (int i = 0; i < s2.size(); i++){
        cout << s2[i] + " ";
    }

    s2 = quickSort(s2);

    for (int i = 0; i < s2.size(); i++){
        cout << s2[i] + " ";
    }
}

int main(){

    string word = "Hello";
    string s = word + "$";
    const int len = s.length();
    char first = s[0];

    vector<string> suffixes(len);
    vector<string> alphaed(len);
    vector<int> suffixArray(len);

    //create vector of suffixes
    for (int i = 0; i < len; i++){
        suffixes[i] = s.substr(i);
        cout << suffixes[i] + " ";
    }
    cout << "\n";
    //testOrdering();
    //testSorting();

    // sort suffixes alphabetically (spec. lexicographically) using quicksorting
    // TODO: use SA-IS (https://www.zork.net/~st/jottings/sais.html)
    alphaed = quickSort(suffixes);
    for (int i = 0; i < alphaed.size(); i++){
        cout << alphaed[i] << " ";
    }

    // TODO: create vector of starting positions of every suffix

    return 0;
}
