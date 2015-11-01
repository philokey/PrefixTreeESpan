#include "test.h"

void test() {
    string inputFile;
    string outputFile;
    int minSup;
    //treedata/CSlog.data
    inputFile = "treedata/CSlog.data";
    outputFile = "test2.out";
    vector<Tree> trees;
    cout<<inputFile<<endl;
    read(inputFile, trees);
    //cout<<"end\n";
    int lines = trees.size();
    for (double p = 1; p < 4; p += 0.5) {
        cout<<p<<" ";
        minSup = lines * p / 100;
        //cout<<minSup<<endl;
        prefixTreeESpan(trees, outputFile, minSup);
    }

    inputFile = "treedata/T1M.data";
    cout<<inputFile<<endl;
    trees.clear();
    read(inputFile, trees);
    lines = trees.size();
    for (double p = 0.1; p < 1.1; p += 0.1) {
        cout<<p<<endl;
        minSup = lines * p / 100;
        prefixTreeESpan(trees, outputFile, minSup);
    }

    inputFile = "treedata/D10.data";
    cout<<inputFile<<endl;
    trees.clear();
    read(inputFile, trees);
    lines = trees.size();
    for (double p = 0.5; p < 4; p += 0.5) {
        cout<<p<<endl;
        minSup = lines * p / 100;
        prefixTreeESpan(trees, outputFile, minSup);
    }

    inputFile = "treedata/F5.data";
    cout<<inputFile<<endl;
    trees.clear();
    read(inputFile, trees);
    lines = trees.size();
    for (double p = 0.5; p < 4; p += 0.5) {
        cout<<p<<endl;
        minSup = lines * p / 100;
        prefixTreeESpan(trees, outputFile, minSup);
    }
}
