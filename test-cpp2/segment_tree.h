#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_


namespace segment_tree {

namespace internal {

struct Node {
    int a;
    int b;
    Node* left;
    Node* right;
};

}

using namespace internal;

class SegmentTree {
public:
    Node* root;
    void add(int a, int b) {
        Node* n = new Node{a, b};
//        if() {
//
//        }
    }


    void balance() {

    }

};

//inline void test() {
//}

inline void test() {

}
}


#endif /* SEGMENT_TREE_H_ */
