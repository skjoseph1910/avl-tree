#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include <queue>
using namespace std;

struct node
{
    int val;
    int height;
    node *left;
    node *right;
};

class AVL
{
private:
    node *root;
    node* Lrotate(node * &);
    node* Rrotate(node * &);
    node* LRrotate(node * &);
    node* RLrotate(node * &);
    node* insert(int, node*);
    int getheight(node *);
    void inorder(node *);
    void postorder(node *);
    void preorder(node *);
public:
    string name;
    AVL();
    ofstream outputfile;
    void insert(int);
    void display(string);
    void printlev(int, node*);
    void levle(int);
};



int main(int argc, char * argv[])
{
    
    if (argc < 2) {
        cout << "Usage: sort \"value=<file>;command=<file>;output=<file>\"" << endl;
        return -1;
    }
    ArgumentManager am(argc, argv);
    string infilename = am.get("value");
    string commandfilename = am.get("command");
    string output= am.get("output");
    
    AVL tree;
    ifstream input, input2;
    input.open(infilename);
    input2.open(commandfilename);
    tree.name=output;
    tree.outputfile.open(tree.name);
    string line;
    ofstream writingfile;
    while (getline(input, line))
    {
        if (line=="")
            continue;
        istringstream ss(line);
        do {
            string word;
            ss >> word;
            stringstream geek(word);
            int x=0;
            if (word!="")
            {
                geek>>x;
                tree.insert(x);
            }
        } while (ss);
    }
    while (getline(input2, line))
    {
        if (line=="")
            continue;
        if (line.at(1)=='n')
            tree.display("inorder");
        else if (line.at(1)=='r')
            tree.display("preorder");
        else if (line.at(1)=='o')
            tree.display("postorder");
        else if (line.at(1)=='e')
        {
            line.erase(0,6);
            stringstream geek(line);
            int x=0;
            geek>>x;
            tree.levle(x);
        }
    }
    input.close(); input2.close(); tree.outputfile.close();
    return 0;
}

void AVL :: printlev(int a, node *b)
{
    if (b==nullptr)
        return;
    else if (a==1)
    {
        outputfile<<b->val<<" ";
    }
    else if (a>1)
    {
        printlev(a-1, b->left);
        printlev(a-1, b->right);
    }
}

void AVL :: levle(int a)
{
    if (a>getheight(root)+1)
    {
        outputfile<<"empty"<<endl;
        return;
    }
    printlev(a, root);
    outputfile<<endl;
}

void AVL :: preorder(node *a)
{
    if (a==nullptr)
        return;
    outputfile<<a->val<<" ";
    preorder(a->left);
    preorder(a->right);
}

void AVL :: postorder(node *a)
{
    if (a==nullptr)
        return;
    postorder(a->left);
    postorder(a->right);
    outputfile<<a->val<<" ";
}

void AVL :: display(string a)
{
    if (a=="inorder")
        inorder(root);
    if (a=="postorder")
        postorder(root);
    if (a=="preorder")
        preorder(root);
    outputfile<<endl;
}

void AVL :: inorder(node *a)
{
    if (a==nullptr)
        return;
    inorder(a->left);
    outputfile << a->val << " ";
    inorder(a->right);

}

void AVL :: insert(int a)
{
    root=insert(a, root);
}

node* AVL :: insert(int num, node *a)
{
    if (a==nullptr)
    {
        a=new node;
        a->val=num;
        a->height=0;
        a->left =  nullptr;
        a->right = nullptr;
    }
    else if (num==a->val)
        return a;
    else if(num < a->val)
    {
        a->left = insert(num, a->left);
        if(getheight(a->left) - getheight(a->right) == 2)
        {
            if(num < a->left->val)
                a = Rrotate(a);
            else
                a = LRrotate(a);
        }
    }
    else if(num > a->val)
    {
        a->right = insert(num, a->right);
        if(getheight(a->right) - getheight(a->left) == 2)
        {
            if(num > a->right->val)
                a = Lrotate(a);
            else
                a = RLrotate(a);
        }
    }
    
    a->height = max(getheight(a->left), getheight(a->right))+1;
    return a;
}

int AVL :: getheight(node *a)
{
    if (a==nullptr)
        return -1;
    return a->height;
}

node* AVL :: RLrotate(node* &a)
{
    a->right=Rrotate(a->right);
    return Lrotate(a);
    
}

node* AVL :: LRrotate(node* &a)
{
    a->left=Lrotate(a->left);
    return Rrotate(a);
}

AVL :: AVL()
{
    root=nullptr;
}

node* AVL :: Lrotate(node* &a)
{
    node *newroot=a->right;
    a->right=newroot->left;
    newroot->left=a;
    a->height = max(getheight(a->right), getheight(a->left))+1;
    newroot->height=max(getheight(a->right), a->height)+1;
    return newroot;
}

node* AVL :: Rrotate(node* &a)
{
    node *newroot=a->left;
    a->left=newroot->right;
    newroot->right=a;
    a->height = max(getheight(a->right), getheight(a->left))+1;
    newroot->height=max(getheight(a->left), a->height)+1;
    return newroot;
}

