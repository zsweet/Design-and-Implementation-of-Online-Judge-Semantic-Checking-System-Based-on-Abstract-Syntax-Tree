#include "Tree.h"

Tree::Tree(){}

Tree::Tree(vector<Node> t , int b){
 nodelist=t;
 root=b;
 left.clear();
 keyroots.clear();
 labels.clear();
}
Tree::~Tree(){}

void Tree:: traverse()
{
    traverse(root); /// put together an ordered list of node labels of the tree
}

void Tree::traverse(int node)
{
    for (int i = 0; i < nodelist[node].edgelist.size(); i++)
    {
        traverse(nodelist[node].edgelist[i].childnodenum);
    }
    labels.push_back(nodelist[node].nodename);
    return ;
}

void Tree::getindex()
{
    //cout<<"调用getindex\n";
//   cout<<"debug: tree::getindex:"<<root<<endl;

    getindex(root, 0);    ///index each node in the tree according to traversal method


}
///int aaa=0;
///给树编号
int Tree::getindex(int node, int index)  ///节点 编号
{
// cout<<node<<"   ";
  //  cout<<"debug: tree::getindex: nodenum = "<<node<<endl;
  /// aaa++;  if(aaa>=10)return 0;
    for (int i = 0; i < nodelist[node].edgelist.size(); i++)
    {
       // cout<<node<<"?????????????????\n";
        index = getindex(nodelist[node].edgelist[i].childnodenum, index);
    }
    index++;
    nodelist[node].index = index;

    return index;
}

void Tree::getleftarr()
{
    /// put together a function which gives l()
    getnodeleft();
    getleftarr(root);
}

void Tree::getleftarr(int node)
{
    for (int i = 0; i < nodelist[node].edgelist.size(); i++)
    {
       getleftarr ( nodelist[node].edgelist[i].childnodenum );
    }
    left.push_back(nodelist[node].leftmost);

    return ;
}

void Tree::getnodeleft()
{
    getnodeleft(root);
}

void Tree::getnodeleft(int node) ///dfs深搜获得最左边编号
{
    if (node<0)  return;

    for (int i = 0; i < nodelist[node].edgelist.size(); i++)
        getnodeleft(nodelist[node].edgelist[i].childnodenum);

    if (nodelist[node].edgelist.size() == 0)
        nodelist[node].leftmost = nodelist[node].index;
    else
        nodelist[node].leftmost = nodelist[  nodelist[node].edgelist[0].childnodenum ].leftmost;
}

void Tree::getkeyroots() /// calculate the keyroots
{
    for (int i = 0; i < left.size(); i++)
    {
        int flag = 0;
        for (int j = i + 1; j < left.size(); j++)
        {
            if (left[j] == left[i])
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            keyroots.push_back(i + 1);
        }
    }
}


