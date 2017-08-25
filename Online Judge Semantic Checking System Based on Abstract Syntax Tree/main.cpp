#include <bits/stdc++.h>
#include "Tree.h"
#include "mynode.h"
#include "TextToTree.h"

//#include  "/usr/include/x86_64-linux-gnu/sys/io.h"
//#include <windows.h>
using namespace std;
//#define FILE2 "../source code/switch_nobreak.c.001t.tu","switch_nobreakout.txt","switch_nobreak.c"
//////#define FILE1 "../source code/switch.c.001t.tu","switchout.txt","switch.c"
///#define FILE2 "../source code/invokefun.c.001t.tu","invokefunout.txt","invokefun.c"
///#define FILE2 "../source code/invokefun.c.001t.tu","invokefunout.txt","invokefun.c"
///#define FILE2 "../source code/ifelsetest.c.001t.tu","ifelsetestout.txt","ifelsetest.c"
///#define FILE2 "../source code/expr.c.001t.tu","exprout.txt","expr.c"
///#define FILE2 "../source code/cond_expr.c.001t.tu","cond_exprout.txt","cond_expr.c"
///#define FILE2 "../source code/if.c.001t.tu","ifout.txt","if.c"
///#define FILE2 "../source code/switch_case100.c.001t.tu","switch_case100out.txt","switch_case100.c"
///#define FILE2 "../source code/while.c.001t.tu","whileout.txt","while.c"
///#define FILE1 "../source code/while.c.001t.tu","whileout.txt","while.c"
///#define FILE1 "../source code/for.c.001t.tu","forout.txt","for.c"
///#define FILE1 "../source code/do_while.c.001t.tu","do_whileout.txt","do_while.c"
///#define FILE1 "../source code/binarysearch_while.c.001t.tu","binarysearch_whileout.txt","binarysearch_while.c"
///#define FILE2 "../source code/binarysearch_while.c.001t.tu","binarysearch_whileout.txt","binarysearch_while.c"
///#define FILE2 "../source code/binarysearch_for.c.001t.tu","binarysearch_forout.txt","binarysearch_for.c"
///#define FILE1 "../tmp/28694.c.001t.tu","28694.txt","28694.c"
///#define FILE2 "../tmp/31773.c.001t.tu","31773.txt","31773.c"
///#define FILE2 "../source code/37215.c.001t.tu","37215out.txt","37215.c"
///#define FILE1 "../source code/37215c99wrong.c.001t.tu","37215c99wrongout.txt","37215.c"
///需要修改 函数多次调用导致的出现环的问题
///          数组变量导致的环问题

int TD[MAXNODE][MAXNODE];

int ZhangShasha(Tree &tree1, Tree &tree2);
int treedist(vector <int> left1, vector <int> left2, int i, int j, Tree tree1, Tree tree2);
vector <Node> test2(int &root);
vector <Node> test1(int &root);
map<string ,int> costmap;
int Default;
void test();
void mmapini();
void getmodifycost(Tree tree1,Tree tree2);
double fun(char file1[],char file2[]);
void getPathAndSrcp(char tufile[],char path[],char outfile[],char srcp[]);


int main( int argc, char **argv)//char  basepath[],char  file1[],char  file2[])
{
    //  test(); return 0;
   char *file1= argv[1] ;//"/home/judge/data/1000/ac/1017.c.001t.tu"
  char  *file2=argv[2]; // //"28694.c.001t.tu"; "/home/judge/data/1000/ac/1018.c.001t.tu"
if (argc<2){
printf("lack  parameters  ,please check！！！   \n");
return -1;
}
 // cout<<"debug main(): "<<file1<<"    "<<file2<<endl;
    mmapini();
    //testfun();

    return fun(file1,file2);
}

double fun(char file1[],char file2[]){
    vector<Node> nodeL1; ///树节点信息
    vector<Node> nodeL2; ///树节点信息
    int root1,root2;

    char path1[100],outfile1[100],srcp1[100];
    char path2[100],outfile2[100],srcp2[100];

    getPathAndSrcp(file1,path1,outfile1,srcp1);
    getPathAndSrcp(file2,path2,outfile2,srcp2);
 //  cout<<"debug fun(): "<<path1<<">>>>>>"<<outfile1<<">>>>>>"<<srcp1<<endl;
 // cout<<"debug fun(): "<<path2<<">>>>>>"<<outfile2<<">>>>>>"<<srcp2<<endl;

   // cout<<"debug : fun() : 文本将抽取树"<<endl;
    nodeL1 = TextToTree().convert(root1, path1,outfile1,srcp1);
    nodeL2 = TextToTree().convert(root2,path2,outfile2,srcp2);
  //  cout<<"ssssssssssssssssssssssss\n";
  //  freopen("CON","r",stdin);
 //   freopen("CON","w",stdout);
    freopen("/dev/tty", "w", stdout);
    freopen("/dev/tty", "r", stdin);

    if(nodeL1.size()==0||nodeL2.size()==0)
    {
        printf("There is no node,Please check the input path or srcp file name!!!\n");
        printf("nodeL1.size()=%d  nodeL2.size()=%d\n",nodeL1.size(),nodeL2.size()) ;
        return  -1;
    }

    Tree tree1(nodeL1,root1),tree2(nodeL2,root2);
  // cout<<"debug : tree build is finished!!!   "<<"tree1: nodelist.size="<<tree1.nodelist.size()<<" root:"<<tree1.root<<"      "<<"tree2: nodelist.size="<<tree2.nodelist.size()<<" root:"<<tree2.root<<endl;
    int distance = ZhangShasha(tree1,tree2);
   // cout<<"debug : Zhangshasha is finished!!!\n";
    double treesim = 1.0*((tree1.nodelist.size()+tree2.nodelist.size())*Default-distance)/((tree1.nodelist.size()+tree2.nodelist.size())*Default);
    printf("%s和%s的带权最小编辑树距离为：%d 相似度量化值为：%.3f%%\n",path1,path2,distance,treesim*100);
   return treesim*100;
}

void getPathAndSrcp(char tufile[],char path[],char outfile[],char srcp[]){
strcpy(path,tufile) ;        ///path
char tmp[100];
//cout<<path<<endl;
   int idx=-1;
   int len = strlen(path);
   for(int i=0;i<len;i++)
       if(path[i]=='/')
           idx = i ;
//    cout<<idx<<" "<<len<<endl;
    int j=0;
    for(int i=idx+1;i<len;i++){
   //     cout<<i<<"   ";
        tmp[j++] = path[i];
        }
     //   cout<<j<<endl;
    tmp[j]='\0';   ///获取文件名
 // cout<<endl<<tmp<<endl;
     len = strlen(tmp);
    int pos = 0,i;
    while( tmp[pos]!='.'&&pos<len )  pos++;
    for(i=0;i<pos;i++)
        srcp[i]=tmp[i];
    srcp[i] = '\0';   ///srcp;
    strcpy(outfile,srcp); ///outfile
    strcat(outfile,".txt");

   // cout<<path<<"---"<<outfile<<"---"<<srcp<<endl;

}

void printfinfo(Tree tree)
{
    cout<<"==========节点信息=============\n nodename index leftmost child_number\n";
    for(int i=0; i<tree.nodelist.size(); i++)
        //if(tree)
        cout<<tree.nodelist[i].nodename<<' '<<tree.nodelist[i].index<<' '<<tree.nodelist[i].leftmost<<' '<<tree.nodelist[i].edgelist.size()<<endl;

    cout<<"\n=============最左节点信息==============\n";
    for(int i=0; i<tree.left.size(); i++)
        cout<<tree.left[i]<<' ';

    cout<<"\n=============keyroots点信息==============\n";
    for(int i=0; i<tree.keyroots.size(); i++)
        cout<<tree.keyroots[i]<<' ';

    cout<<"\n============提取的节点名称信息==============\n";
    for(int i=0; i<tree.labels.size(); i++)
        cout<<tree.labels[i]<<' ';


    cout<<"\n\n\n";
    return ;
}
int ZhangShasha(Tree &tree1, Tree &tree2)
{

 //   cout<<"debug :come in Zhang-shasha \n";
    tree1.getindex();
    //cout<<"debug : tree1 getindex is over \n";
    //return 0;
  //  cout<<"debug :finish tree1 getindex \n";
    tree1.getleftarr();
//   cout<<"debug :finish tree1 getleftarr \n";
    tree1.getkeyroots();
    tree1.traverse();
  //  cout<<"debug :finish tree1 initial \n";

    tree2.getindex();
    tree2.getleftarr();
    tree2.getkeyroots();
    tree2.traverse();
  //  cout<<"debug :initial is over \n";
   // printfinfo(tree1);
  //  printfinfo(tree2);

    vector <int> left1 = tree1.left;
    vector <int> keyroots1 = tree1.keyroots;

    vector <int> left2 = tree2.left;
    vector <int> keyroots2 = tree2.keyroots;
    //cout<<keyroots1.size()<<" "<<keyroots2.size()<<endl;
    // space complexity of the algorithm


    getmodifycost(tree1,tree2);

  //  cout<<"getmodifycost is over!!!!\n";
    // solve subproblems
    for (int i1 = 1; i1 < keyroots1.size() + 1; i1++)           ///对Tree1的LR_keyroots集合遍历
    {
        for (int j1 = 1; j1 < keyroots2.size() + 1; j1++)       ///对Tree2的LR_keyroots集合遍历
        {
            int i = keyroots1[i1 - 1];
            int j = keyroots2[j1 - 1];
            TD[i][j] = treedist(left1, left2, i, j, tree1, tree2);
           // cout<<i<<" "<<j<<" "<<TD[i][j]<<endl;
        }
    }
    return TD[left1.size()][left2.size()];
}

int forestdist[MAXNODE][MAXNODE];  ///???????????????????
int delcost1[MAXNODE],relcost[MAXNODE][MAXNODE];
int inscost2[MAXNODE];

void getmodifycost(Tree tree1,Tree tree2)
{
    int Delete = 1;
    int Insert = 1;
    int Relabel = 1;
    int len1=tree1.labels.size(),len2=tree2.labels.size();
    map<string ,int> ::iterator ite;
    int cost,cost1,cost2;
    for(int i=0; i<len1; i++)
    {
        ite=costmap.find(tree1.labels[i]);
        cost = (ite == costmap.end() ?  Default : costmap[tree1.labels[i]]);
        delcost1[i]=Delete*cost;
    }
    for(int i=0; i<len2; i++)
    {
        ite=costmap.find(tree2.labels[i]);
        cost = (ite == costmap.end() ?       : costmap[tree2.labels[i]]);
        inscost2[i]=Insert*cost;
    }
    for(int i=0; i<len1; i++)
    {
        ite=costmap.find(tree1.labels[i]);
        cost1 = (ite == costmap.end() ?  Default : costmap[tree1.labels[i]]);
        for(int j=0; j<len2; j++)
        {
           ite=costmap.find(tree2.labels[j]);
           cost2 = (ite == costmap.end() ?  Default : costmap[tree2.labels[j]]);
           relcost[i][j] = max(cost1,cost2)*Relabel;
        }
    }
}

int treedist(vector <int> left1, vector <int> left2, int i, int j, Tree tree1, Tree tree2)
{
//   int **forestdist = new int*[i + 1];
//   for(int k=0;k<i+1;k++)
    //      forestdist[k]=new int[j + 1];


    // costs of the three atomic operations

    forestdist[0][0] = 0;
    for (int i1 = left1[i-1]; i1 <= i; i1++)
    {
        forestdist[i1][0] = forestdist[i1 - 1][0] + delcost1[i1];
    }
    for (int j1 = left2[j - 1]; j1 <= j; j1++)
    {
        forestdist[0][j1] = forestdist[0][j1 - 1] + inscost2[j1];
    }
    for (int i1 =  left1[i-1]; i1 <= i; i1++)
    {
        for (int j1 = left2[j - 1]; j1 <= j; j1++)
        {
            int i_temp = (left1[i - 1] > i1 - 1) ? 0 : i1 - 1;
            int j_temp = (left2[j - 1] > j1 - 1) ? 0 : j1 - 1;
            if ((left1[i1 - 1] == left1[i - 1]) && (left2[j1 - 1] == left2[j - 1]))  ///i在i1的左子树上
            {
                int Cost = (tree1.labels[i1 - 1]==tree2.labels[j1 - 1]) ? 0 : relcost[i1][j1];
                forestdist[i1][j1] = min(min(forestdist[i_temp][j1] + delcost1[i1], forestdist[i1][j_temp] + inscost2[j1]),
                                         forestdist[i_temp][j_temp] + Cost);
                TD[i1][j1] = forestdist[i1][j1];
               // if(TD[i1][j1]!=0)
               //     printf("debug: TD[%d][%d]=%d\n",i1,j1,TD[i1][j1]);
                // println(i1 + " " + j1);
            }
            else   ///i在i1的右子树上 ，因此需要分割成两部分计算
            {
                int i1_temp = left1[i1 - 1] - 1;
                int j1_temp = left2[j1 - 1] - 1;

                int i_temp2 = (left1[i - 1] > i1_temp) ? 0 : i1_temp;
                int j_temp2 = (left2[j - 1] > j1_temp) ? 0 : j1_temp;

                forestdist[i1][j1] = min(min(forestdist[i_temp][j1] + delcost1[i1], forestdist[i1][j_temp] + inscost2[j1]),
                                         forestdist[i_temp2][j_temp2] + TD[i1][j1]);
            }
        }
    }
    /* for(int k=0;k<i+1;k++)
      delete[] forestdist[k];
    delete[] forestdist;*/
   // System.out.println("########################");
    return forestdist[i][j];
}

void mmapini()
{
    costmap.clear();
    string strfun = "function_decl";
    string strbrc = "branch";
    string strslc = "selection";
    string strgtx = "goto_expr";
    Default = 2;
    costmap[strfun]=5;
    costmap[strbrc]=5;
    costmap[strslc]=5;
    costmap[strgtx]=5;
}

void test()
{
    vector<Node> nodeL1; ///树节点信息
    vector<Node> nodeL2; ///树节点信息
    int root1,root2;

    nodeL1 = test1(root1),nodeL2=test2(root2);

    Tree tree1(nodeL1,root1),tree2(nodeL2,root2);
    int distance = ZhangShasha(tree1,tree2);
    printf("tree1和tree2的最小编辑树距离为：%d",distance);
}

vector <Node> test1(int & root)
{
    root=0;
    vector<Edge> edge;
    vector <Node> node;
    ///0
    edge.clear();
    edge.push_back(Edge(1));
    edge.push_back(Edge(2));
    node.push_back(Node(edge,"f"));

    ///1
    edge.clear();
    edge.push_back(Edge(3));
    edge.push_back(Edge(4));
    node.push_back(Node(edge,"d"));

    ///2
    edge.clear();
    node.push_back(Node(edge,"e"));

    ///3
    edge.clear();
    node.push_back(Node(edge,"a"));

    ///4
    edge.clear();
    edge.push_back(Edge(5));
    node.push_back(Node(edge,"c"));

    ///5
    edge.clear();
    node.push_back(Node(edge,"b"));
    return node;
}


vector <Node> test2(int &root)
{
    root=0;
    vector<Edge> edge;
    vector <Node> node;
    ///0
    edge.clear();
    edge.push_back(Edge(1));
    edge.push_back(Edge(2));
    node.push_back(Node(edge,"f"));

    ///1
    edge.clear();
    edge.push_back(Edge(3));
    node.push_back(Node(edge,"c"));

    ///2
    edge.clear();
    node.push_back(Node(edge,"e"));

    ///3
    edge.clear();
    edge.push_back(Edge(4));
    edge.push_back(Edge(5));
    node.push_back(Node(edge,"d"));

    ///4
    edge.clear();
    node.push_back(Node(edge,"a"));

    ///5
    edge.clear();
    node.push_back(Node(edge,"b"));
    return node;

}


/*
void testfun(){
    vector<Node> nodeL1; ///树节点信息
    vector<Node> nodeL2; ///树节点信息
    int root1,root2;

    string basepath="../tu/";
    string tufile[100];// = {"switch.c.001t.tu","ifelsetest.c.001t.tu","cond_expr.c.001t.tu"};
    int cnt =0 ;
    DfsFolder(basepath,0,tufile,cnt);
    for(int i=0;i<cnt;i++)
        cout<<tufile[i]<<endl;

    char path1[100],outfile1[100],srcp1[100];
    char path2[100],outfile2[100],srcp2[100];

    for(int i=0; i<cnt; i++)
    {
        getPathAndSrcp(basepath,tufile[i],path1,outfile1,srcp1);

        ///build tree1
        nodeL1.clear();
        nodeL1 = TextToTree().convert(root1,path1,outfile1,srcp1);
        freopen("CON","r",stdin);
        freopen("CON","w",stdout);
        if(nodeL1.size()==0)
        {
            printf("There is no node,Please check the input path or srcp file name!!!\n");
            cout<<"nodeL1.size()="<<nodeL1.size()<<endl;
            return  ;
        }

        Tree tree1(nodeL1,root1);

        for( int j=i+1;j<cnt;j++ )
        {
            getPathAndSrcp(basepath,tufile[j],path2,outfile2,srcp2);
            ///build tree2
            nodeL2.clear();
            nodeL2 = TextToTree().convert(root2,path2,outfile2,srcp2);
            freopen("CON","r",stdin);
            freopen("CON","w",stdout);
            if(nodeL2.size()==0)
            {
                printf("There is no node,Please check the input path or srcp file name!!!\n");
                cout<<"  nodeL2.size()="<<nodeL2.size();
                return  ;
            }
            cout<<"正在比对"<<srcp1<<"和"<<srcp2<<"   ";
            Tree tree2(nodeL2,root2);

            cout<<"建树之前"<<nodeL1.size()<<" "<<nodeL2.size()<<endl;
            int distance = ZhangShasha(tree1,tree2);
            double treesim = 1.0*((tree1.nodelist.size()+tree2.nodelist.size())*Default-distance)/((tree1.nodelist.size()+tree2.nodelist.size())*Default);
            //cout<<path1<<" "<<outfile1<<" "<<srcp1<<"   "<<path2<<" "<<outfile2<<" "<<srcp2<<endl;
            printf("%s和%s的最小编辑树距离为：%d 相似度量化值为：%.3f%%\n\n\n\n\n",srcp1,srcp2,distance,treesim*100);
        }

    }
    return ;
}
*/
