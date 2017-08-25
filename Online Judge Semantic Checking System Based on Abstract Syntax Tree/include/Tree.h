#ifndef TREE_H
#define TREE_H
#include "mynode.h"
#include <bits/stdc++.h>
using namespace std;

class Tree
{
public:
    Tree();
    Tree(vector<Node>t, int b);
     ~Tree();
    vector <Node> nodelist;
    int root;
    vector <int> left;      /// function l() which gives the leftmost child
    vector <int> keyroots; /// list of keyroots, i.e., nodes with a left child and the tree root
    vector <string>labels;  /// list of the labels of the nodes used for node comparison
    void traverse();
    void traverse(int node);
    void getindex();
    int getindex(int node, int index);
    void getleftarr();
    void getleftarr(int node);
    void getnodeleft();
    void getnodeleft(int node);
    void getkeyroots();
protected:

private:

};

#endif // TREE_H
