#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// Huffman node
//template <typename T> TODO: make chunk generic between char or string
struct HuffmanNode {
        
        char chunk;
        float weight;
        bool isComplex;
        HuffmanNode* leftChild;
        HuffmanNode* rightChild;

        HuffmanNode (const HuffmanNode &hn) {
            chunk = hn.chunk;
            weight = hn.weight;
            isComplex = hn.isComplex;
            leftChild = hn.leftChild;
            rightChild = hn.rightChild;
        }

        HuffmanNode (char c, float w) {
            chunk = c;
            weight = w;
            isComplex = false;
            leftChild = rightChild = nullptr;
        }

        HuffmanNode (float w, HuffmanNode* l, HuffmanNode* r) {
            weight = w;
            isComplex = true;
            leftChild = l;
            rightChild = r;
        }

        void printNode(){

            std::string nodeInfo = "chunk = c: ";
            std::string childrenInfo = "";

            // check if parent node or leaf char node
            if (isComplex){
                nodeInfo += "NULL";
            }
            else {
                nodeInfo.append(1, chunk);
            }
            nodeInfo += ", w: " + to_string(weight) + "\n";
            
            // check if leaf
            if (leftChild == nullptr && rightChild == nullptr){
                childrenInfo += "leaf (no children)\n";
            }
            else {
                if (leftChild != nullptr){
                    childrenInfo += " - left child = c: ";
                    if (leftChild->isComplex){
                        childrenInfo += "NULL";
                    }
                    else {
                        childrenInfo.append(1, leftChild->chunk);
                    }
                    childrenInfo += ", w: " + to_string(leftChild->weight) + "\n";
                }
                
                if (rightChild != nullptr){
                    childrenInfo += " - right child = c: ";
                    if (rightChild->isComplex){
                        childrenInfo += "NULL";
                    }
                    else {
                        childrenInfo.append(1, rightChild->chunk);
                    }
                    childrenInfo += ", w: " + to_string(rightChild->weight) + "\n";
                }
            }
            
            cout << nodeInfo << childrenInfo << "\n";
        }
};

// Huffman code based on string
//template <typename T>
class HuffmanTree {
    private:
        string str;
        vector<HuffmanNode> weights;
        HuffmanNode* root;

        vector<HuffmanNode> orderByWeight(vector<HuffmanNode> ws){ // using quick sort
            int s = ws.size();

            // check if base case
            if (s == 1){
                return ws;
            }

            // set pivot to middle element
            const int pivi = s / 2;
            HuffmanNode pivot = ws[pivi];

            // create vectors for earlier and later elements
            vector<HuffmanNode> v1;
            vector<HuffmanNode> v2;

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

        vector<HuffmanNode> calcWeights(string s){

            unordered_map<char, int> freqs;
            vector<HuffmanNode> ws;

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
                // cout << c.first << ": " << c.second << ", " << weight << "\n";
                HuffmanNode ht (c.first, weight);
                ws.push_back(ht);
            }

            return orderByWeight(ws); //
        }

    public:
        HuffmanTree (string s) {
            str = s;
            root = nullptr;
            weights = calcWeights(s); // calculate weight for every chunk
        }

        vector<HuffmanNode> getWeights(){
            return weights;
        }
};



int main(){
    // get freqs of each character, calc weights
    // build huffman tree
    // get codes for each char

    HuffmanTree* ht = new HuffmanTree ("ab");
    vector<HuffmanNode> ws = ht->getWeights();

    return 0;
}
