/*
Titulo: Proyecto#2 Codificacion usando arbol de huffman
Proposito: Codificar archivos de texto con el algoritmo de huffman
Fecha: 31/Julio/2018
Elaborado por: Martín José Pérez Gálvez
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
vector<TreeElement> Ordenar2(vector<TreeElement>);
void Algoritmo(TreeNode *, vector<TreeElement>);
bool compare(TreeElement, TreeElement);

//
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Parametros faltan" << endl;
    }
    else
    {
        //Inciando programa
       /* cout << "Ingrese el nombre del archivo de texto: ";
        string nombreArchivo;
        cin >> nombreArchivo;*/
        //Tabla que contiene los tree elements
        vector<TreeElement> tablaDeFrecuencia;
        vector<TreeElement> listaFrecuencia;
        string nombreArchivo2= argv[1];
        //cout<<nombreArchivo2<<endl;
        TablaFrecuencia tabla = Frecuencia(LeerArchivo(argv[1]/*nombreArchivo*/));

        for (int i = 0; i < tabla.listaElementos.size(); i++)
        {
            if (tabla.listaTablaFrecuencia[i].element[0] == 32)
            {
                tabla.listaTablaFrecuencia[i].frequency = tabla.listaTablaFrecuencia[i].frequency - 1;
            }
        }

        tablaDeFrecuencia = tabla.listaTablaFrecuencia;
        listaFrecuencia = tabla.listaTablaFrecuencia;
        //listaFrecuencia=tabla.listaTablaFrecuencia
        //Imprimir lista

        /* for (int i = 0; i < tablaDeFrecuencia.size(); i++)
    {
        // int valor = tablaDeFrecuencia[i].element[0];
        cout << tablaDeFrecuencia[i].element << " - " << tablaDeFrecuencia[i].frequency << endl;
    }*/

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

                tablaDeFrecuencia = Ordenar2(tablaDeFrecuencia);
            }

        } ///Fin del ciclo de crear arboles

        //cout << nodosArboles[nodosArboles.size() - 1] /*->GetChildren()[0]*/->GetData().element << endl;
        Algoritmo(nodosArboles[nodosArboles.size() - 1], listaFrecuencia);
    }

    return 0;
} //Fin del main

//Guardar el contenido del archivo de texto
string LeerArchivo(string nombreArchivo)
{

    ifstream archivo;
    string texto;
    stringstream contenidoArchivo,archivo1;

   // archivo1<<nombreArchivo<<".txt";
    
    //nombreArchivo="test01.txt";
    archivo.open(nombreArchivo.c_str(), ios::in);

    while (!archivo.eof())
    {
        getline(archivo, texto);
        contenidoArchivo << texto << "\n";
    }

    archivo.close();

    return contenidoArchivo.str();
} //Fin del a funcion leer archivo

//Calculo de frecuencia
TablaFrecuencia Frecuencia(string archivo)
{
    string archivo1 = archivo;
    TablaFrecuencia tabla;
    //Ordenar alfabeticamente y repetidas
    stable_sort(archivo1.begin(), archivo1.end());
    //cout<<archivo1<<endl;
    vector<int> posicionL;
    int contador;
    vector<char> lista;
    char t;
    for (int i = 0; i < archivo1.length(); i++)
    {
        t = archivo1[i];
        if (t != -108 && t != -109 && t != -103 && t != -128 && t != -30)
        {

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
    }

    // tabla.LlenarTablaFrecuencia();
    for (int i = 0; i < lista.size(); i++)
    {
        TreeElement temporal;

        temporal.element = lista[i];
        temporal.frequency = posicionL[i];
        tabla.listaTablaFrecuencia.push_back(temporal);

        // listaTablaFrecuencia.push_back(temporal);
    }
    // sort(tabla.listaTablaFrecuencia.begin(),tabla.listaFrecuencia.end(),compare);
    tabla.listaTablaFrecuencia = Ordenar(tabla.listaTablaFrecuencia);
    /* char aux2;
    int aux;

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
    }*/

    /* for (int i = 0; i < lista.size(); i++)
    {
        cout << lista[i] << " ";
    }


   
    cout << endl;*/
    tabla.listaElementos = lista;
    tabla.listaFrecuencia = posicionL;

    return tabla;

} //Fin de la funcion Calcular frecuencia

//Ordenar la tabla de frecuencia
vector<TreeElement> Ordenar(vector<TreeElement> tabla)
{
    //Ordenar posiciones
    //  TreeElement aux;
    //char aux2;

    /*for (int i = 0; i < tabla.size(); i++)
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
    }*/
    sort(tabla.begin(), tabla.end(), compare);

    return tabla;
}

vector<TreeElement> Ordenar2(vector<TreeElement> tabla)
{
    //Ordenar posiciones
    TreeElement aux;
    //char aux2;

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
    //sort(tabla.begin(),tabla.end(),compare);

    return tabla;
}

//Funcion para el sort
bool compare(TreeElement a, TreeElement b)
{
    if (a.frequency == b.frequency)
    {
        return a.element > b.element;
    }
    else
    {
        return a.frequency > b.frequency;
    }
}

//Codificacion para mostrar el algoritmo de huffman
void Algoritmo(TreeNode *raiz, vector<TreeElement> listaFrecuencia)
{

    TreeNode *nodoTemporal = raiz;
    stringstream codigo;
    vector<string> listaCodigos;
    vector<char> listaNombres;
    char letraTemporal;
    bool hijo; //True izquierdo y false derecho

    //For principal
    for (int i = 0; i < nodoTemporal->GetData().element.size(); i++)
    {
        stringstream codigo;
        letraTemporal = nodoTemporal->GetData().element[i];

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

    vector<string> listaHuffman2;

    for (int i = 0; i < listaFrecuencia.size(); i++)
    {
        for (int j = 0; j < listaNombres.size(); j++)
        {
            if (listaFrecuencia[i].element[0] == listaNombres[j])
            {
                listaHuffman2.push_back(listaCodigos[j]);
            }
        }
    }

    for (int i = 0; i < listaCodigos.size(); i++)
    {
        if (listaFrecuencia[i].element[0] == 32)
        {
            cout << "{key: SP, code: " << listaHuffman2[i] << "}" << endl;
        }
        else if (listaFrecuencia[i].element[0] == 10)
        {
            cout << "{key: LF, code: " << listaHuffman2[i] << "}" << endl;
        }
        else
        {
            cout << "{key: " << listaFrecuencia[i].element << ", code: " << listaHuffman2[i] << "}" << endl;
        }
    }

} //Fin