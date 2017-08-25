#ifndef TEXTTOTREE_H
#define TEXTTOTREE_H
#include "mynode.h"
#define MAXNODE 500
#define MAXN 20000

class TextToTree
{
    public:
        TextToTree();
        virtual ~TextToTree();

        vector <Node> convert(int &root,const char InputFileName[],const char OutputFileName[],const char filename[]);
    protected:
    private:

};

#endif // TEXTTOTREE_H
