#include "util.h"
Tree buildTree(const vector<int> &data) {
    stack<int> sta;
    Tree tree;
    Node node;
    int n = data.size();
    int d;
    for (int i = 0; i < n; ++i) {
        d = data[i];
        node.build(d, i);
        tree.node.push_back(node);
        if (d != -1) {
            sta.push(i);
        } else {
            tree.node[sta.top()].r = i;
            sta.pop();
        }
    }
    return tree;
}
void read(string inputFile, vector<Tree> &trees) {
    ifstream fin(inputFile);
    int label;
    string instr;
    stack<Node*> sta;
    vector<int> data;
    Tree tree;
    int pos = 0;
    if (fin.is_open()) {
        while (getline(fin, instr)) {
            istringstream sin(instr);
            data.clear();
            while (sin >> label) {
                data.push_back(label);
            }
            tree = buildTree(data);
            //tree.output();
            trees.push_back(tree);
        }
    } else {
        cerr<<"open input file error"<<endl;
        exit(1);
    }
}
void outputTree(list<int> fre, string outputFile) {
    //cout<<"hehe\n";
    ofstream fout(outputFile, ios::app);
    for (auto e : fre) {
        fout<<e<<" ";
    }
    fout<<"\n";
    fout.close();
}
