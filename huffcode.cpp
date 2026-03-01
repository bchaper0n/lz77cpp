#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// Hoffman node
struct HoffmanNode {
        char ch;
        float weight;
        HoffmanNode* leftChild;
        HoffmanNode* rightChild;

        HoffmanNode (char c, float w) {
            ch = c;
            weight = w;
            leftChild = nullptr;
            rightChild = nullptr;
        }

        HoffmanNode (float w, HoffmanNode l, HoffmanNode r) {
            weight = w;
            leftChild = &l;
            rightChild = &r;
        }
};

// Hoffman code based on string
class HoffmanTree {
    private:
        string str;
        vector<HoffmanNode> weights;
        HoffmanNode* root;

        vector<HoffmanNode> orderByWeight(vector<HoffmanNode> ws){ // using quick sort
            int s = ws.size();

            // check if base case
            if (s == 1){
                return ws;
            }

            // set pivot to middle element
            const int pivi = s / 2;
            HoffmanNode pivot = ws[pivi];

            // create vectors for earlier and later elements
            vector<HoffmanNode> v1;
            vector<HoffmanNode> v2;

            // compare each element with pivot, if earlier: put in v1, if later: put in v1
            for (int i = 0; i < s; i++){
                if (i != pivi){ // if pivot ignore
                    if (ws[i].weight >= pivot.weight){
                        v1.push_back(ws[i]);
                    }
                    else {
                        v2.push_back(ws[i]);
                    }
                }
            }

            // recursively sort both arrays then combine them + pivot
            if (!v1.empty()){
                v1 = orderByWeight(v1);
            }
            if (!v2.empty()){
                v2 = orderByWeight(v2);
            }

            v1.insert(v1.end(), pivot);
            v1.insert(v1.end(), v2.begin(), v2.end());

            return v1;
        }

        void calcWeights(){

            unordered_map<char, int> freqs;
            vector<HoffmanNode> ws;

            for (char c: str){
                if (freqs[c] == 0){
                    freqs[c] = 1;
                } 
                else { 
                    freqs[c]++;
                }
            }

            int len = str.length();

            for (auto c : freqs){
                cout << c.first << ": " << c.second << "\n";
                HoffmanNode ht (c.first, (float) c.second / (float) len);
                ws.push_back(ht);
            }

            weights = orderByWeight(ws);
        }

        void buildTree(){
            vector<HoffmanNode> ws = weights;

            // check if size 1, single element is root of tree
            while (ws.size() != 1){

                // pop last 2 (with smallest weights)
                HoffmanNode left = ws.back();
                ws.pop_back();
                HoffmanNode right = ws.back();
                ws.pop_back();

                // create new node with both as children
                float combWeight = left.weight + right.weight;
                HoffmanNode hn (combWeight, left, right);
                
                // push node in vector with right order by weight
                ws.push_back(hn);
                weights = orderByWeight(ws);
                
                // for (int i = ws.size() - 1; i >= 0; i--){
                //     if (combWeight <= ws[i].weight){
                //         //ws.insert(i, hn);
                //         ws.push_back(hn);
                //         break;
                //     }
                // }

            }

            root = &ws.front();
        }

    public:
        HoffmanTree (string s) {
            str = s;
            root = nullptr;
            calcWeights();
            buildTree();
        }

        vector<HoffmanNode> getWeights(){
            return weights;
        }

        HoffmanNode* getRoot(){
            return root;
        }
};



int main(){
    // get freqs of each character, calc weights
    // build hoffman tree
    // get codes for each char

    HoffmanTree ht("abcaaabvcabcb");

    vector<HoffmanNode> ws = ht.getWeights();
    HoffmanNode* root = ht.getRoot();

    cout << "root: " << &root << ".";

    // for (auto c : ws){
    //     cout << c.ch << ": " << c.weight << "\n";
    // }

    return 0;
}
