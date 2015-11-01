#ifndef PREFIXTREEESPAN_PREFIXTREEESPAN_H
#define PREFIXTREEESPAN_PREFIXTREEESPAN_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;
struct Node {
    int label;
    int l, r;
    Node() {
        label = l = r = -1;
    }
    void build(int a, int b) {
        label = a;
        l = r = b;
    }
};
struct Tree {
    vector<Node> node;
    void output() {
        int n = node.size();
        for (auto &nd : node) {
            if (nd.label != -1) {
                cout << "(" << char(nd.label - 1 + 'A') << "," << nd.l << " " << nd.r << ") ";
            } else {
                cout << "(" << -1 << "," << nd.l << " " << nd.r << ") ";
            }
        }
        cout<<endl;
    }
};
struct Scope {
    int l, r;
    Scope(int a, int b) {
        l = a;
        r = b;
    }
};
struct ProjectedDB { //projected datebase for one frequent node
    int tid; //tree's id
    vector<Scope> scope;
    ProjectedDB(int id) {
        tid = id;
    }
    ProjectedDB() {};
    void insert(int l, int r) {
        scope.push_back(Scope(l, r));
    }
    void output() {
        cout<<"tid: "<<tid<<"\n";
        for (auto s : scope) {
            cout<<s.l<<" "<<s.r<<endl;
        }
    }
};
struct  Element {
    int label;
    int pos;
    Element() {
        label = 0;
        pos = 0;
    }
    void build(int _label,int _pos) {
        label = _label;
        pos = _pos;
    }
    bool operator < (const Element &e) const {
        if (label != e.label) {
            return label < e.label;
        }else {
            return pos < e.pos;
        }
    }
    bool operator ==(const Element &e) const {
        return e.label == label && e.pos == pos;
    }
    void output() {
        cout<<char(label - 1 + 'A')<<"\n";
    }
};
namespace std{
    template <>
    class hash<Element> {
    public:
        size_t operator()(const Element &e) const {
            return hash<int>()(e.label * 100000000 + e.pos);
        }
    };
}
void prefixTreeESpan(const vector<Tree> &trees, const string &outputFile, const int &minSup);
#endif //PREFIXTREEESPAN_PREFIXTREEESPAN_H
