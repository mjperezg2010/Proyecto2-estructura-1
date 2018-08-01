#include <string>
#include <vector>
#include "treenode.h"


using namespace std;

//Constructor 1
/*
Constructor donde se inicializa TreeNode y _data

Parametros: const TreeElement &data, representa el data que se le asignara
            al _data de la clase
Retorna:    

Errores: Error si se envia de parametro otro elemento diferente
*/
TreeNode::TreeNode(const TreeElement &data) : _data(data)
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
{/*
    TreeNode *nodoTemporal = ;
     //For principal
    for (int i = 0; i < GetData().element.size(); i++)
    {
       // stringstream codigo;
        char letraTemporal = GetData().element[i];

        while (!nodoTemporal->IsLeaf())
        { //Reivisar en hijo izquierdo
            for (int i = 0; i < nodoTemporal->GetChildren()[0]->GetData().element.size(); i++)
            {
                if (letraTemporal == nodoTemporal->GetChildren()[0]->GetData().element[i])
                {
                    hijo = true;
                    break;
                }
            }

            //Revisar en hijo derecho
            for (int i = 0; i < nodoTemporal->GetChildren()[1]->GetData().element.size(); i++)
            {
                if (letraTemporal == nodoTemporal->GetChildren()[1]->GetData().element[i])
                {
                    hijo = false;
                    break;
                }
            }

            if (hijo)
            {
                nodoTemporal = nodoTemporal->GetChildren()[0];
                codigo << "1";
            }
            else
            {
                nodoTemporal = nodoTemporal->GetChildren()[1];
                codigo << "0";
            }

        } //FIn del while

        nodoTemporal = raiz;
        listaCodigos.push_back(codigo.str());
        listaNombres.push_back(letraTemporal);
       
        // codigo<<"-";
    }
    */
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
Funcion que añade un hijo con TreeElement al TreeNode actual

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
Funcion que añade un hijo con un TreeNode al TreeNode actual

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
/*
Funcion que devuelve el data del TreeNode actual

Parametros: 

Retorna: El valor de _data

Errores: 

*/
TreeElement TreeNode::GetData()
{
    return _data;
}



//SetData
/*
Funcion que asigna un nuevo data al TreeNode actual

Parametros: const TreeElement & data, representa el data que le asignara al
            TreeNode actual

Retorna: 

Errores: Si se envia otro parametro diferente a const TreeElement

*/
void TreeNode::SetData(const TreeElement &data)
{
    _data = data;
    //_data->element = data.element;
    //_data->frequency = data.frequency;
}



//IsRoot
/*
Funcion que dice si el TreeNode es raiz o no 

Parametros:

Retorna: true si el Tree nodo es raiz y false si el TreeNode no es raiz

Errores: 

*/
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
/*
Funcion que dice si el TreeNode es hoja

Parametros:

Retorna: true si el Tree nodo es hoja y false si el TreeNode no es hoja

Errores: 

*/
bool TreeNode::IsLeaf()
{
    if (_children.size() == 0)
    {
        return true;
    }
    else
        return false;
}
