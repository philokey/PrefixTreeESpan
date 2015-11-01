#include <iostream>
#include "prefixTreeESpan.h"
#include "util.h"
#include "test.h"
using namespace std;


time_t st1, st2;
int resultNum;
void getFreElement(list<int> subTree, const int &minSup, const vector<ProjectedDB> &projDB, const vector<Tree> &trees, const string &outputFile) {
    unordered_map<Element, unordered_set<int> > elemCnt;
    Element elem;
    for (auto db : projDB) {
        const vector<Scope> &dbScope = db.scope;
        auto m = dbScope.size();
        int tid = db.tid;
        const vector<Node> & node = trees[tid].node;
        for (int j = 0; j < m; ++j) {
            int l = dbScope[j].l;
            int r = dbScope[j].r;
            for (int k = l; k < r; ++k) {
                if (node[k].label == -1) continue;
                elem.build(node[k].label, j + 1);
                if (elemCnt.find(elem) == elemCnt.end()) {
                    elemCnt[elem] = unordered_set<int>{tid};
                } else {
                    elemCnt[elem].insert(tid);
                }
            }
        }
    }
    //cout<<elemCnt.size()<<endl;
    vector<Element> freElem;
    for (auto e : elemCnt) {
        if (e.second.size() >= minSup) {
            freElem.push_back(e.first);
        }
    }
//    for (auto e: freElem) {
//        e.output();
//    }
//    cout<<endl;
    list<int> newSubTree;
    vector<ProjectedDB> newProjDB;
    resultNum += freElem.size();
    for (auto e : freElem) {
        //auto t2 = clock();
        newProjDB.clear();
        newSubTree = subTree;
        auto treePos = newSubTree.end();
        int pos = e.pos;
        while (pos--) {
            --treePos;
        }
        newSubTree.insert(treePos, e.label);
        newSubTree.insert(treePos, -1);
        outputTree(newSubTree, outputFile);
        for (auto db : projDB) {
            auto dbScope = db.scope;
            auto m = dbScope.size();
            int tid = db.tid;
            auto node = trees[tid].node;
            for (int j = 0; j < m; ++j) {
                int l = dbScope[j].l;
                int r = dbScope[j].r;
                for (int k = l; k < r; ++k) {
                    if (node[k].label == e.label) {
                        ProjectedDB ndb(tid);
                        if (node[k + 1].label != -1) {
                            ndb.insert(node[k].l + 1, node[k].r);
                        }
                        for (pos = node[k].r + 1; pos < r && node[pos].label != -1; pos = node[pos].r + 1) {
                            ndb.insert(node[pos].l, node[pos].r);
                        }
                        newProjDB.push_back(ndb);
                    }
                }
            }
        }
        //cout<<newProjDB.size()<<endl;
        //st2 += clock() - t2;
        getFreElement(newSubTree, minSup, newProjDB, trees, outputFile);
        //cout<<(clock() - t1 ) * 1.0 / CLOCKS_PER_SEC<<endl;
    }
}

void prefixTreeESpan(const vector<Tree> &trees, const string &outputFile, const int &minSup) {
    //Step 1: Find length-1 frequent induced subtree patterns.
    auto beginT = clock();
    auto n = trees.size();
    Element elem;
    unordered_map<Element, int> elemCnt;
    unordered_set<Element> st;
    resultNum = 0;
    for (int i = 0; i < n; ++i) {
        const vector<Node> &node = trees[i].node;
        st.clear();
        for (auto nd: node) {
            elem.build(nd.label, 1);
            st.insert(elem);
        }
        for (auto s : st) {
            if (s.label == -1) continue;
            if (elemCnt.find(s) != elemCnt.end()) {
                elemCnt[s] += 1;
            } else {
                elemCnt[s] = 1;
            }
        }
    }

    //find length-1 frequent elements
    vector<Element> freElem;
    for (auto e : elemCnt) {
        if (e.second >= minSup) {
            freElem.push_back(e.first);
        }
    }
    //cout<<"length-1: "<<(clock() - beginT) * 1.0 / CLOCKS_PER_SEC<<endl;
    //generate length-1 projected database
    resultNum += freElem.size();
    vector<ProjectedDB> projDB;
    for (auto e : freElem) {
        projDB.clear();
        list<int> subTree{e.label, -1};
        //write result
        outputTree(subTree, outputFile);
        for (int i = 0; i < n; ++i) {
            const vector<Node> &node = trees[i].node;
            auto m = node.size();
            for (int j = 0; j < m; ++j) {
                if (node[j].label == e.label && node[j+1].label != -1) {
                    ProjectedDB db(i);
                    db.insert(node[j].l + 1, node[j].r);
                    projDB.push_back(db);
                }
            }

        }
        //cout<<projDB.size()<<" "<<projDB.capacity()<<endl;
        //st1 += clock() - t1;

//        cout<<char(e.label - 1 + 'A')<<endl;
//        cout<<char(e.label - 1 + 'A')<<" length-1 projected database\n";
//        for (auto db : projDB) {
//            db.output();
//        }

        getFreElement(subTree, minSup, projDB, trees, outputFile);
    }
    auto endT = clock();
    //cout<<"st1(s): "<< (st1)*1.0 / CLOCKS_PER_SEC<<endl;
    //cout<<"st2(s): "<< (st2)*1.0 / CLOCKS_PER_SEC<<endl;
    cout<<"total time(s):\t"<<(endT - beginT)*1.0 / CLOCKS_PER_SEC<<endl;
    cout<<"num:\t"<<resultNum<<endl;

}

int main(int argc, char **argv) {
    //test();
    //return 0;
    int opt;
    string inputFile;
    string outputFile;
    int minSup;
    //get parameter
    while ((opt = getopt(argc, argv, "i:o:s:"))  != -1) {
        //cout<<opt<<endl;
        switch (opt) {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 's':
                minSup = atoi(optarg);
                break;
        }
    }
    cout<<inputFile<<" "<<outputFile<<" "<<minSup<<endl;
    st1 = st2 = 0;
//    inputFile = "/Users/philokey/ClionProjects/PrefixTreeESpan/test.in";
//    outputFile = "/Users/philokey/ClionProjects/PrefixTreeESpan/test.out";
//    minSup = 2;
    vector<Tree> trees;
    read(inputFile, trees);
    cout<<trees.size()<<endl;
    const char* name = outputFile.c_str();
    remove(name);
    prefixTreeESpan(trees, outputFile, minSup);
    return 0;
}