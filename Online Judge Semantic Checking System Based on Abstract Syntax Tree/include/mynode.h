#ifndef MYNODE_H_INCLUDED
#define MYNODE_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

///定义树节点
struct Edge
{
    string attribute; ///属性节点名 (可能含有属性值)
    int childnodenum;   ///属性节点号
    Edge(int b)
    {
        attribute="",childnodenum=b;
    }
    Edge(string a="",int b=0)
    {
        attribute=a,childnodenum=b;
    }
};
struct Node{
  vector<Edge>edgelist;
  vector<string>attribute;

  int index;
  int leftmost;
  string nodename;
  Node(){
    edgelist.clear();
  }
  Node(vector<Edge>e,string name){
     edgelist = e,nodename=name;
  }
};


#endif // MYNODE_H_INCLUDED
