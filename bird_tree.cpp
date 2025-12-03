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

string classify(Node* node, bool wings, bool feathers,bool beak,bool eggs,bool can_fly){
    if(!node) return ":(";
    if(!node->feature.empty()){
       if (node->feature == "wings") {
            return classify(wings ? node->right : node->left, wings, feathers,beak,eggs,can_fly);
       }
       if (node->feature == "feathers"){
            return classify(feathers ? node->right : node->left, wings, feathers,beak,eggs,can_fly);
       }
       if (node->feature == "beak"){
            return classify(beak ? node->right : node->left, wings, feathers,beak,eggs,can_fly);
       }

       if (node->feature == "eggs"){
            return classify(eggs ? node->right : node->left, wings, feathers,beak,eggs,can_fly);
       }

       if (node->feature == "can_fly"){
            return classify(can_fly ? node->right : node->left, wings, feathers,beak,eggs,can_fly);
       }

    }
    return node->label;
}

Node* build_tree(){
    Node* root = new Node("wings");
    root->left = new Node("","Not a bird");
    root->right = new Node("feathers");
    root->right->left = new Node("","Not a bird");
    root->right->right = new Node("beak");
    root->right->right->left = new Node("","Not a bird");
    root->right->right->right = new Node("eggs");
    root->right->right->right->left = new Node("","Not a bird");
    root->right->right->right->right = new Node("can_fly");
    root->right->right->right->right->left = new Node("","Not a bird");
    root->right->right->right->right->right = new Node("","Bird");
    return root;
}

string predict(bool wings, bool feathers,bool beak,bool eggs, bool can_fly) {
    Node* root = build_tree();
    string result = classify(root,wings,feathers,beak,eggs,can_fly);
    return result;
}

PYBIND11_MODULE(bird_tree,m){
    m.def("predict",&predict,"Predict");
};






