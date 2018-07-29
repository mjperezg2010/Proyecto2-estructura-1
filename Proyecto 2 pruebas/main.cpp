#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "treenode.h"
#include "treeelement.h"
#include "tablafrecuencia.h"
/*
Investigar
Delete del tree node





*/


using namespace std;

//Prototipos de la funcion
TablaFrecuencia Frecuencia(string);
string LeerArchivo(string);
vector<char> ListaCaracteres(vector<char>);
vector<int> ListaPosiciones(vector<int>);
vector<TreeElement> Ordenar(vector<TreeElement>);
void Algoritmo(TreeNode);

int main()
{

    /*string m = "M", g = "G", h = "H";
    size_t ms = 8, gs = 3, hs = 1;

    TreeElement elementoM;
    elementoM.element = m;
    elementoM.frequency = ms;
    TreeNode *arbolM = new TreeNode(elementoM);*/

    //Inciando programa
    cout << "Ingrese el nombre del archivo de texto: ";
    string nombreArchivo;
    cin >> nombreArchivo;
     //Tabla que contiene los tree elements
    vector<TreeElement> tablaDeFrecuencia;
    TablaFrecuencia tabla = Frecuencia(LeerArchivo(nombreArchivo));
    tabla.LlenarTablaFrecuencia();
    tablaDeFrecuencia = tabla.listaTablaFrecuencia;

    //Imprimir lista
    for (int i = 0; i < tablaDeFrecuencia.size(); i++)
    {
        cout << tablaDeFrecuencia[i].element << " - " << tablaDeFrecuencia[i].frequency << endl;
    }

    

    //Creacion del arbol
    vector<TreeNode *> nodosArboles;
    while (tablaDeFrecuencia.size() != 0)
    {
        //1 para la posicion final, 2 para la penultima
        string elemento1 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 1].element, elemento2 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 2].element;
        size_t frecuencia1 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 1].frequency, frecuencia2 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 2].frequency;
      

        //Creando el nuevo nodo
        TreeNode *arbolTemporal;
        stringstream concatenar;
       //Datos del nuevo nodo
        concatenar << elemento1 << elemento2; 
        string elementoArbol = concatenar.str();
        int frecuenciaArbol = frecuencia1 + frecuencia2; 
        TreeElement temporal;
        temporal.element = elementoArbol;
        temporal.frequency = frecuenciaArbol;
        arbolTemporal = new TreeNode(temporal);

         // guardara la posiciion de su nuevo hijo si lo encuentra
        int posHijo1 = -1;
        int posHijo2 = -1;
        for (int i = 0; i < nodosArboles.size(); i++)
        {
            if (nodosArboles[i]->GetData().element == elemento1) //temporal1->GetData().element)
            {
                posHijo1 = i;
                break;
            }
        }

        for (int i = 0; i < nodosArboles.size(); i++)
        {
            if (nodosArboles[i]->GetData().element == elemento2) //temporal1->GetData().element)
            {
                posHijo2 = i;
                break;
            }
        }

         //Mirar si econtro a su nuevo hijo izquierdo
        if (posHijo1 > -1)
        {
            nodosArboles[posHijo1]->SetParent(arbolTemporal);
            arbolTemporal->AddChild(nodosArboles[posHijo1]);
        }
        else
        {
            temporal.element = elemento1;
            temporal.frequency = frecuencia1;
            TreeNode *newChild = new TreeNode(temporal);
            arbolTemporal->AddChild(newChild);
        }

        //Mirar si enconttro a su nuevo hijo derecho
        if (posHijo2 > -1)
        {
            nodosArboles[posHijo2]->SetParent(arbolTemporal);
            arbolTemporal->AddChild(nodosArboles[posHijo2]);
        }
        else
        {
            temporal.element = elemento2;
            temporal.frequency = frecuencia2;
            TreeNode *newChild = new TreeNode(temporal);
            arbolTemporal->AddChild(newChild);
        }

       

        nodosArboles.push_back(arbolTemporal);

        //Eliminar las ultimas dos posiciones de la tabla de frecuencia
        tablaDeFrecuencia.erase(tablaDeFrecuencia.begin() + tablaDeFrecuencia.size() - 2, tablaDeFrecuencia.begin() + tablaDeFrecuencia.size());
        if (tablaDeFrecuencia.size() != 0)
        {
            TreeElement nuevo;
            nuevo.element = arbolTemporal->GetData().element;
            nuevo.frequency = arbolTemporal->GetData().frequency;
            tablaDeFrecuencia.push_back(nuevo);

            tablaDeFrecuencia = Ordenar(tablaDeFrecuencia);
           
        }

    } ///Fin del ciclo de crear arboles

    //cout<<nodosArboles[0]->GetChildren()[0]->GetChildren()[0]->GetData().element<<endl;
   

} //Fin del main 


//Guardar el contenido del archivo de texto
string LeerArchivo(string nombreArchivo)
{

    ifstream archivo;
    string texto;
    stringstream contenidoArchivo;
    //nombreArchivo="test01.txt";
    archivo.open(nombreArchivo.c_str(), ios::in);

    while (!archivo.eof())
    {
        getline(archivo, texto);
        contenidoArchivo << texto << "\n";
    }

    archivo.close();

    return contenidoArchivo.str();
}//Fin del a funcion leer archivo



//Calculo de frecuencia
TablaFrecuencia Frecuencia(string archivo)
{
    string archivo1 = archivo;
    TablaFrecuencia tabla;
    //Ordenar alfabeticamente y repetidas
    stable_sort(archivo1.begin(), archivo1.end());

    vector<int> posicionL;
    int contador;
    vector<char> lista;
    char t;
    for (int i = 0; i < archivo1.length(); i++)
    {
        t = archivo1[i];

        if (archivo1.length() == (i + 1) && (archivo1[i] != archivo1[i - 1]))
        {
            lista.push_back(archivo1[i]);
            posicionL.push_back(contador);
            break;
        }

        if (archivo1[i] == archivo1[i + 1])
        {
            contador++;
        }
        else
        {
            lista.push_back(archivo1[i]);
            posicionL.push_back(contador);
            contador = 1;
        }
    }

    //Ordenar posiciones
    int aux;
    char aux2;
    for (int i = 0; i < posicionL.size(); i++)
    {
        for (int j = 0; j < posicionL.size() - 1; j++)
        {
            if (posicionL[j] < posicionL[j + 1])
            {
                aux = posicionL[j];
                aux2 = lista[j];
                posicionL[j] = posicionL[j + 1];
                lista[j] = lista[j + 1];
                posicionL[j + 1] = aux;
                lista[j + 1] = aux2;
            }
        }
    }

    tabla.listaElementos = lista;
    tabla.listaFrecuencia = posicionL;

    return tabla;

} //Fin de la funcion Calcular frecuencia



//Ordenar la tabla de frecuencia
vector<TreeElement> Ordenar(vector<TreeElement> tabla)
{
    //Ordenar posiciones
    TreeElement aux;
    char aux2;
    for (int i = 0; i < tabla.size(); i++)
    {
        for (int j = 0; j < tabla.size() - 1; j++)
        {
            if (tabla[j].frequency < tabla[j + 1].frequency)
            {
                aux = tabla[j];
                //aux2 = tabla.listaElementos[j];
                tabla[j] = tabla[j + 1];
               // tabla.listaElementos[j] = tabla.listaElementos[j + 1];
                tabla[j + 1] = aux;
                //tabla.listaElementos[j + 1] = aux2;
            }
        }
    }

    return tabla;
}


//Codificacion para mostrar el algoritmo de huffman
void Algoritmo(TreeNode* raiz){
    TreeNode* nodoTemporal;
    //stringstream codigo;

    nodoTemporal=raiz->GetChildren()[0];

    while(nodoTemporal!=raiz){
        if(nodoTemporal->IsLeaf()){
           // if(nodoTemporal)
        }
        

    }//FIn del while

}//Fin