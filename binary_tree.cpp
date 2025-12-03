#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
using namespace std;


struct Node {
    string feature;
    string label;
    Node* left;
    Node* right;

    Node(string f = "",string l = "") {
        feature = f;
        label = l;
        left = right = nullptr;
    }
};

string classify(Node* node, bool x, bool y,bool z){
    if(!node) return ":(";
    if(!node->feature.empty()){
       if (node->feature == "x") {
            return classify(x ? node->right : node->left, x,y,z);
       }
       if (node->feature == "y") {
            return classify(y ? node->right : node->left, x,y,z);
       }
       if (node->feature == "z") {
            return classify(z ? node->right : node->left, x,y,z);
       }

    }
    return node->label;
}

Node* build_tree(){
    Node* root = new Node("x");
    root->left = new Node("z");
    root->right = new Node("y");
    root->left->left = new Node("","Dog");
    root->right->right = new Node("","Bird");

    return root;
}

string predict(bool x, bool y,bool z) {
    Node* root = build_tree();
    string result = classify(root,x,y,z);
    return result;
}

PYBIND11_MODULE(binary_tree,m){
    m.def("predict",&predict,"Predict");
};






