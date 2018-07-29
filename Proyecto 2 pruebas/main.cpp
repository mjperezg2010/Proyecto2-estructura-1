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
for (int i = 0; i < tabla.listaElementos.size(); i++)
    {
        cout << tabla.listaElementos[i] << " - " << tabla.listaFrecuencia[i]<<endl;
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
    cout<<"Ingrese el nombre del archivo de texto: ";
    string nombreArchivo;
    cin>>nombreArchivo;
    TablaFrecuencia tabla=Frecuencia(LeerArchivo(nombreArchivo));

   for (int i = 0; i < tabla.listaElementos.size(); i++)
    {
        cout << tabla.listaElementos[i] << " - " << tabla.listaFrecuencia[i]<<endl;
    }

    //Creacion del arbol
    while()















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
    cout << endl;

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

