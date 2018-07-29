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

/*
Pata imprimir la lista
for(int i=0;i<tablaDeFrecuencia.size();i++){
        cout<<tablaDeFrecuencia[i].element<< " - "<<tablaDeFrecuencia[i].frequency<<endl;
    }



*/

using namespace std;

TablaFrecuencia Frecuencia(string);
string LeerArchivo(string);
vector<char> ListaCaracteres(vector<char>);
vector<int> ListaPosiciones(vector<int>);

int main()
{
    
    
   
   
    /*string m = "M", g = "G", h = "H";
    size_t ms = 8, gs = 3, hs = 1;

    TreeElement elementoM;
    elementoM.element = m;
    elementoM.frequency = ms;
    TreeNode *arbolM = new TreeNode(elementoM);*/

    //Inciando programa
    cout<<"Ingrese el nombre del archivo de texto: ";
    string nombreArchivo;
    cin>>nombreArchivo;
    vector<TreeElement> tablaDeFrecuencia; //Tabla que contiene los tree elements
    TablaFrecuencia tabla=Frecuencia(LeerArchivo(nombreArchivo));
    tabla.LlenarTablaFrecuencia();
    tablaDeFrecuencia=tabla.listaTablaFrecuencia;
    
    //Imprimir lista
   /* for(int i=0;i<tablaDeFrecuencia.size();i++){
        cout<<tablaDeFrecuencia[i].element<< " - "<<tablaDeFrecuencia[i].frequency<<endl;
    }*/

    //Creacion del arbol
    vector<TreeNode*> nodosArboles;
   // while(tablaDeFrecuencia.size()==0){
        //1 para la posicion final, 2 para la penultima
       // string elemento1,elemento2;
        //size_t frecuencia1,frecuencia2;
        TreeNode* temporal1=new TreeNode(tablaDeFrecuencia[tablaDeFrecuencia.size()-1]);
        TreeNode* temporal2=new TreeNode(tablaDeFrecuencia[tablaDeFrecuencia.size()-2]);
        //cout<<temporal1->GetData().element<<endl;

        //Creando el nuevo nodo
       // if(tablaDeFrecuencia[tablaDeFrecuencia.size()-1].element[0]<tablaDeFrecuencia[tablaDeFrecuencia.size()-2].element[0]){
            
       // }




    //}//Fin de ciclo de crear arbol

    

    















} //Fin de la funcion







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
}

//Tabla de frecuencia

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
    
    tabla.listaElementos=lista;
    tabla.listaFrecuencia=posicionL;

    return tabla;

} //Fin de la funcion

