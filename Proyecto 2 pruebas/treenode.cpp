#include <string>
#include <vector>
#include "treenode.h"
//#include "treeelement.h"
//#include <typeinfo>

using namespace std;

//Constructor 1
/*
Constructor donde se inicializa TreeNode y _data

Parametros: const TreeElement &data, representa el data que se le asignara
            al _data de la clase
Retorna:    

Errores: Error si se envia de parametro otro elemento diferente
*/
TreeNode::TreeNode(const TreeElement &data): _data(data)
{
   // _data->element = data.element;
    //_data->frequency = data.frequency;
    _parent = nullptr;
    

}

//Constructor 2
/*
Constructor donde se inicializa TreeNode, _data y _parent

Parametros: const TreeElement &data, representa el data que se le asignara
            al _data de la clase
            TreeNode* parent, representa el TreeNode que sera el padre del TreeNode
Retorna:    

Errores: Error si se envia de parametro otro elemento diferente
*/
TreeNode::TreeNode(const TreeElement &data, TreeNode *parent)
{
    //_data->element = data.element;
   // _data->frequency = data.frequency;
    _parent = parent;
}


//Funcion destructor de TreeNOde
/*
Destructor de TreeNode

Parametros: 

Retorna:    

Errores: 
*/
TreeNode::~TreeNode()
{
    for (int i = 0; i < _children.size(); i++)
    {
        //_children[i]->_parent=nullptr;      ///Dudas magistrales
        // delete TreeElement;                 duddas crear delete ahi
    }
}


//Lista de hijos
/*
Funcion que lista de hijos

Parametros: 

Retorna: Un vector de TreeNode* que contiene los hijos del TreNode actual

Errores: 
*/
vector<TreeNode *> &TreeNode::GetChildren()
{ //Dudas Pilas el pop y aqui la clase tree node

    return _children;
}


//SetParent
/*
Funcion que asigna el padre a un TreeNode

Parametros: TreeNode* parent, representa el TreeNode que sera
            _parent del TreeNode actual

Retorna: 

Errores: Enviar otro parametro que no sea el TreeNode
*/
void TreeNode::SetParent(TreeNode *parent)
{
    _parent = parent;
}


//Addchild 1
/*
Funcion que añade un hijo al TreeNode actual

Parametros: const TreeElement, representa el TreeNode 

Retorna: 

Errores: Enviar otro parametro que no sea el TreeNode
*/
void TreeNode::AddChild(const TreeElement &data)
{
    TreeNode *newChild = new TreeNode(data);
    
    _children.push_back(newChild);
}

//Addchild 2
/*
Funcion que asigna el padre a un TreeNode

Parametros: TreeNode* parent, representa el TreeNode que sera
            _parent del TreeNode actual

Retorna: 

Errores: Enviar otro parametro que no sea el TreeNode

*/
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
