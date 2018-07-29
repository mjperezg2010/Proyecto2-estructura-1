#include <string>
#include <vector>
#include "treenode.h"
//#include "treeelement.h"
//#include <typeinfo>

using namespace std;

//Constructor 1
TreeNode::TreeNode(const TreeElement &data): _data(data)
{
   // _data->element = data.element;
    //_data->frequency = data.frequency;
    _parent = nullptr;
    

}

//Constructor 2
TreeNode::TreeNode(const TreeElement &data, TreeNode *parent)
{
    //_data->element = data.element;
   // _data->frequency = data.frequency;
    _parent = parent;
}

//Funcion destructor de Tree
TreeNode::~TreeNode()
{
    for (int i = 0; i < _children.size(); i++)
    {
        //_children[i]->_parent=nullptr;      ///Dudas magistrales
        // delete TreeElement;                 duddas crear delete ahi
    }
}

//Lista de hijos
vector<TreeNode *> &TreeNode::GetChildren()
{ //Dudas Pilas el pop y aqui la clase tree node

    return _children;
}

//SetParent
void TreeNode::SetParent(TreeNode *parent)
{
    _parent = parent;
}

//Addchild 1
void TreeNode::AddChild(const TreeElement &data)
{
    TreeNode *newChild = new TreeNode(data);
    
    _children.push_back(newChild);
}

//Addchild 2
void TreeNode::AddChild(TreeNode *child)
{
    _children.push_back(child);
}

//GetData
TreeElement TreeNode::GetData()
{
   return _data;
}

//SetData
void TreeNode::SetData(const TreeElement &data)
{
    _data=data;
    //_data->element = data.element;
    //_data->frequency = data.frequency;
}

//IsRoot
bool TreeNode::IsRoot()
{
    if (_parent == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//IsLeaf
bool TreeNode::IsLeaf()
{
    if (_children.size() == 0)
    {
        return true;
    }
    else
        return false;
}
