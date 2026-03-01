#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// Hoffman node
//template <typename T> TODO: make chunk generic between char or string
struct HoffmanNode {
        
        char chunk; // possibility for chunk to be char or string 
        float weight;
        HoffmanNode* leftChild;
        HoffmanNode* rightChild;

        HoffmanNode (char c, float w) {
            chunk = c;
            weight = w;
            leftChild = rightChild = nullptr;
        }

        HoffmanNode (float w, HoffmanNode l, HoffmanNode r) {
            weight = w;
            leftChild = &l;
            rightChild = &r;
        }
};

// Hoffman code based on string
//template <typename T>
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

        vector<HoffmanNode> calcWeights(string s){

            unordered_map<char, int> freqs;
            vector<HoffmanNode> ws;

            for (char c: s){
                if (freqs[c] == 0){
                    freqs[c] = 1;
                } 
                else { 
                    freqs[c]++;
                }
            }

            int len = s.length();

            for (auto c : freqs){
                float weight = (float) c.second / (float) len;
                cout << c.first << ": " << c.second << ", " << weight << "\n";
                HoffmanNode ht (c.first, weight);
                ws.push_back(ht);
            }

            return orderByWeight(ws); //
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
                ws = orderByWeight(ws);
                
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

        // traverse tree
        unordered_map<char, string> traverseTree(HoffmanNode node, string currSequence){
            
            unordered_map<char, string> left;
            unordered_map<char, string> right;

            // check if leaf
            if (node.leftChild != nullptr && node.rightChild != nullptr){
                return {{node.chunk, currSequence}};
            }

            // check left
            if (node.leftChild != nullptr){
                left = traverseTree(*node.leftChild, currSequence + "0");
            }
            // check right
            if (node.rightChild != nullptr){
                right = traverseTree(*node.rightChild, currSequence + "1");
            }

            // combine
            left.insert(right.begin(), right.end());
            return left;
        }

    public:
        HoffmanTree (string s) {
            str = s;
            root = nullptr;
            weights = calcWeights(s); // calculate weight for every chunk
            //buildTree(); // build hoffman tree based on these weights
        }

        vector<HoffmanNode> getWeights(){
            return weights;
        }

        HoffmanNode* getRoot(){
            return root;
        }

        unordered_map<char, string> getCoding(){
            unordered_map<char, string> codes;

            codes = traverseTree(*root, "");

            return codes;
        }
};



int main(){
    // get freqs of each character, calc weights
    // build hoffman tree
    // get codes for each char

    HoffmanTree ht("aabc");

    vector<HoffmanNode> ws = ht.getWeights();

    cout << "\nreceived weights\n";

    for (HoffmanNode w : ws){
        cout << w.chunk << ": " << w.weight << "\n"; 
    }

    return 0;
}
