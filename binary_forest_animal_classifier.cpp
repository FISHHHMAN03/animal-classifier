#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

// ------------------------ Node CLASS ------------------------

class Node {
public:

    function<bool(const vector<string>&)> predicate;
    shared_ptr<Node> yes;
    shared_ptr<Node> no;
    string label;

    bool isLeaf;

    // Internal node (question node)
    Node(function<bool(const vector<string>&)> pred,
         shared_ptr<Node> y,
         shared_ptr<Node> n)
        : predicate(pred), yes(y), no(n), isLeaf(false) {}

    // Leaf node
    Node(const string& lbl)
        : label(lbl), isLeaf(true){}
};

//Clusters
enum class Cluster {
    Vertebrates,
    Invertebrates,
    Count
};

enum class Category {
    Bird,
    Mammal,
    Reptile,
    Fish,
    Amphibian,
    Arthropod,
    Count
    };


// Forest Array
static shared_ptr<Node> Forest[(int)Cluster::Count][(int)Category::Count];

// ------------------------ HELPERS ------------------------

bool hasTrait(const string& t, const vector<string>& traits) {
    return find(traits.begin(), traits.end(), t) != traits.end();
}

string evaluate(const shared_ptr<Node>& root, const vector<string>& traits) {
    auto node = root;

    while (node && !node->isLeaf){
        if (node->predicate(traits)) {
            node = node->yes;
        } else {
            node = node->no;
        }
    }
    return node ? node->label : "<null>";
}

// ------------------------ CLUSTERS ------------------------

void initForest()   {

    auto BirdTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("has_feathers", t); },

        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("can_fly", t); },

            make_shared<Node>("Eagle"),

            make_shared<Node>(
                [](const vector<string>& t){ return hasTrait("can_swim", t); },
                make_shared<Node>("Penguin"),
                make_shared<Node>("Ostrich")
            )
        ),

        make_shared<Node>("Not Bird")
    );

    Forest[(int)Cluster::Vertebrates][(int)Category::Bird] = BirdTree;



    auto MammalTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("viviparity", t); },

        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("four_legs", t); },

            make_shared<Node>(
                [](const vector<string>& t){ return hasTrait("is_predator", t); },

                    make_shared<Node>("Lion"),
                    make_shared<Node>("Horse")
            ),

            make_shared<Node>(
                [](const vector<string>& t){ return hasTrait("two_legs", t); },
                    make_shared<Node>("Ape"),
                    make_shared<Node>("Dolphin")
            )
        ),

        make_shared<Node>("Not Mammal")
    );

    Forest[(int)Cluster::Vertebrates][(int)Category::Mammal] = MammalTree;

    auto ReptileTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("lay_eggs", t); },

        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("shell", t); },

            make_shared<Node>("Turtle"),

            make_shared<Node>(
                [](const vector<string>& t){ return hasTrait("four_legs", t); },
                    make_shared<Node>("Lizard"),
                    make_shared<Node>("Snake")
            )
        ),

        make_shared<Node>("Not Reptile")
    );


    Forest[(int)Cluster::Vertebrates][(int)Category::Reptile] = ReptileTree;


    auto FishTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("has_fins", t); },

        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("is_predator", t); },

            make_shared<Node>("Shark"),
            make_shared<Node>("Fish")
        ),

        make_shared<Node>("Not Fish")
    );

    Forest[(int)Cluster::Vertebrates][(int)Category::Fish] = FishTree;

    auto AmphibianTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("moist_skin", t); },

        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("can_jump", t); },

            make_shared<Node>("Frog"),
            make_shared<Node>("Newt")
        ),

        make_shared<Node>("Not Amphibian")
    );


    Forest[(int)Cluster::Vertebrates][(int)Category::Amphibian] = AmphibianTree;

    auto ArthropodTree =
    make_shared<Node>(
        [](const vector<string>& t){ return hasTrait("two_parts", t); },
        make_shared<Node>(
            [](const vector<string>& t){ return hasTrait("eight_legs", t); },
            make_shared<Node>("Spider"),
            make_shared<Node>("Insect")
        ),

        make_shared<Node>("Not Arthropod")
    );

    Forest[(int)Cluster::Invertebrates][(int)Category::Arthropod] = ArthropodTree;
}

Cluster detectCluster(const vector<string>& traits){
    if (hasTrait("has_spine",traits)){
        return Cluster::Vertebrates;
    }
    return Cluster::Invertebrates;
}


vector<string> classifyByCluster(const vector<string>& traits) {

    static bool initialized = false;
    if (!initialized) {
        initForest();
        initialized = true;
    }

    vector<string> matches;
    auto cluster = detectCluster(traits);

    for (int i = 0; i < (int)Category::Count; ++i) {
        auto& tree = Forest[(int)cluster][i];
        if (!tree) continue;

        string result = evaluate(tree, traits);
        if (result.rfind("Not ", 0) != 0) {
            matches.push_back(result);
        }
    }

    return matches;
}

// ------------------------ PYBIND11 MODULE ------------------------

namespace py = pybind11;

PYBIND11_MODULE(binary_forest_animal_classifier, m) {
    m.doc() = "Animal classifier using a C++ binary forest";

    m.def("classify", [](const vector<string>& traits) {
        return classifyByCluster(traits);
    });
}
