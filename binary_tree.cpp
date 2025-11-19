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

string classify(Node* node, bool x, bool y){
    if(!node) return ":(";
    if(!node->feature.empty()){
       if (node->feature == "x") {
            return classify(x ? node->right : node->left, x, y);
       }
       if (node->feature == "y"){
            return classify(y ? node->right : node->left, x, y);
       }
    }
    return node->label;
}

Node* build_tree(){
    Node* root = new Node("x");
    root->left = new Node("","No");
    root->right = new Node("y");
    root->right->left = new Node("","No");
    root->right->right = new Node("","Yes");
    return root;
}

string predict(bool x, bool y) {
    Node* root = build_tree();
    string result = classify(root,x,y);
    return result;
}

PYBIND11_MODULE(binary_tree,m){
    m.def("predict",&predict,"Predict");
};






