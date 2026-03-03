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
        HuffmanNode* leftChild;
        HuffmanNode* rightChild;

        // cto for character/weights (leafs)
        HuffmanNode (char c, float w) {
            chunk = c;
            weight = w;
            leftChild = rightChild = nullptr;
        }

        // cto for intermediate/complex nodes
        HuffmanNode (float w, HuffmanNode* left, HuffmanNode* right) {
            chunk = char(0);
            weight = w;
            leftChild = left;
            rightChild = right;
        }

        // print node and its children
        void printNode(){

            std::string nodeInfo = "chunk = c: ";
            std::string childrenInfo = "";

            // check if parent node or leaf char node
            if (chunk == char(0)){
                nodeInfo += "NULL";
            }
            else {
                nodeInfo.append(1, chunk);
            }
            nodeInfo += ", w: " + std::to_string(weight) + "\n";
            
            // check if leaf
            if (leftChild == nullptr && rightChild == nullptr){
                childrenInfo += "leaf (no children)\n";
            }
            else {
                if (leftChild != nullptr){
                    childrenInfo += " - left child = c: ";
                    if (leftChild->chunk == char(0)){
                        childrenInfo += "NULL";
                    }
                    else {
                        childrenInfo.append(1, leftChild->chunk);
                    }
                    childrenInfo += ", w: " + std::to_string(leftChild->weight) + "\n";
                }
                
                if (rightChild != nullptr){
                    childrenInfo += " - right child = c: ";
                    if (rightChild->chunk == char(0)){
                        childrenInfo += "NULL";
                    }
                    else {
                        childrenInfo.append(1, rightChild->chunk);
                    }
                    childrenInfo += ", w: " + std::to_string(rightChild->weight) + "\n";
                }
            }
            
            cout << nodeInfo << childrenInfo << "\n";
        }
};

// Huffman code based on string
//template <typename T>
class HuffmanTree {
    private:
        std::string str;
        vector<HuffmanNode*> weights;
        HuffmanNode* root;
        unordered_map<char, std::string> codes;

        // order char frequency by weight (desc)
        vector<HuffmanNode*> orderByWeight(vector<HuffmanNode*> ws){ // using quick sort
            int wsSize = ws.size();

            // check if base case
            if (ws.size() == 1){
                return ws;
            }

            // set pivot to middle element
            const int pivi = ws.size() / 2;
            HuffmanNode* pivot = ws[pivi];

            // create vectors for lower and higher freq elements, respectively
            vector<HuffmanNode*> v1;
            vector<HuffmanNode*> v2;

            // compare each element with pivot, if lower freq: put in v1, if higher: put in v1
            for (int i = 0; i < ws.size(); i++){
                if (i != pivi){ // if pivot ignore
                    if (ws[i]->weight >= pivot->weight){
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

        // calculate weights for freq of each char
        vector<HuffmanNode*> calcWeights(std::string s){

            unordered_map<char, int> freqs;
            vector<HuffmanNode*> ws;

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
                HuffmanNode* ht = new HuffmanNode (c.first, weight);
                ws.push_back(ht);
            }

            return orderByWeight(ws); //
        }

        // build huffman tree using weights of each char
        void buildTree(){
            std::vector<HuffmanNode*> ws = weights;

            // check if size 1, single element is root of tree
            while (ws.size() != 1){

                // pop last 2 (with smallest weights)
                HuffmanNode* left = ws.back();
                ws.pop_back();
                HuffmanNode* right =ws.back();
                ws.pop_back();

                // create new node with both as children
                float combWeight = left->weight + right->weight;
                HuffmanNode* hn = new HuffmanNode(combWeight, left, right);
                
                // push node in vector with right order by weight
                ws.push_back(hn);
                ws = orderByWeight(ws); // TODO: inefficient, just insert at right spot
            }

            root = ws[0];
        }

        // traverse tree by building string for each char leaf
        unordered_map<char, std::string> traverseTree(HuffmanNode* node, std::string currSequence){
            
            unordered_map<char, std::string> left;
            unordered_map<char, std::string> right;

            // check if leaf
            if (node->leftChild == nullptr && node->rightChild == nullptr){
                return {{node->chunk, currSequence}};
            }

            // check left
            if (node->leftChild != nullptr){
                left = traverseTree(node->leftChild, currSequence + "0");
            }
            // check right
            if (node->rightChild != nullptr){
                right = traverseTree(node->rightChild, currSequence + "1");
            }

            // combine
            left.insert(right.begin(), right.end());
            return left;
        }

        // build huffman codes for each leaf
        void buildCode(){
            codes = traverseTree(root, "");
        }

    public:
        // cto
        HuffmanTree (std::string s) {
            str = s;
            root = nullptr;
            weights = calcWeights(s); // calculate weight for every chunk
            buildTree(); // build huffman tree using calculated weight
            buildCode(); // build code map for each character
        }

        // get weights for each char in string
        vector<HuffmanNode*> getWeights(){
            return weights;
        }

        // get code for each char in string
        unordered_map<char, std::string> getCodes(){
            return codes;
        }
};



int main(){
    // get freqs of each character, calc weights
    // build huffman tree
    // get codes for each char

    HuffmanTree* ht = new HuffmanTree ("this is an example of a huffman tree");
    vector<HuffmanNode*> ws = ht->getWeights();

    for (auto w: ws){
        cout << w->chunk << ": " << w->weight << "\n";
    }
    cout << "\n";

    unordered_map<char, std::string> cs = ht->getCodes();

    for (auto c: cs){
        cout << c.first << ": " << c.second << "\n";
    }    

    return 0;
}
