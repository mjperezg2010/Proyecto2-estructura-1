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
#include "treenode.h"
#include "treeelement.h"
#include "tablafrecuencia.h"

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



//Main Principal
/*
Aqui se llaman las funciones y se realiza el arbol usando la tabla de frecuencia.

Parametros: int argc, representa 
            char* argv[], represnta los elementos que se escriben en la linea de comando y los guarda en 
                          este arreglo de caracteres
Retorna:    

Errores: si el argc es menor a se enviara un mensaje que dira Parametros faltan
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Parametros faltan" << endl;
    }
    else
    {       
        //Tabla que contiene los tree elements
        vector<TreeElement> tablaDeFrecuencia;
        vector<TreeElement> listaFrecuencia;
        string nombreArchivo2= argv[1];
        TablaFrecuencia tabla = Frecuencia(LeerArchivo(argv[1]));

        for (int i = 0; i < tabla.listaElementos.size(); i++)
        {
            if (tabla.listaTablaFrecuencia[i].element[0] == 32)
            {
                tabla.listaTablaFrecuencia[i].frequency = tabla.listaTablaFrecuencia[i].frequency - 1;
            }
        }

        tablaDeFrecuencia = tabla.listaTablaFrecuencia;
        listaFrecuencia = tabla.listaTablaFrecuencia;
        

        //Creacion del arbol
        vector<TreeNode *> nodosArboles;
        while (tablaDeFrecuencia.size() != 0)
        {
            //1 para la posicion final, 2 para la penultima
            string elemento1 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 1].element;
            string elemento2 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 2].element;
            size_t frecuencia1 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 1].frequency;
            size_t frecuencia2 = tablaDeFrecuencia[tablaDeFrecuencia.size() - 2].frequency;

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

        Algoritmo(nodosArboles[nodosArboles.size() - 1], listaFrecuencia);
    }

    return 0;
} //Fin del main



//Guardar el contenido del archivo de texto
/*
Funcion que lee el archivo de texto que se envia como parametro en el main  

Parametros: string nombreArchivo, representa el nombre que tiene el archivo de texto que se abrira

Retorna: un string que almacena todo el archivo de texto


Errores: Si se envia un string que no sea un archivo de texto
*/
string LeerArchivo(string nombreArchivo)
{

    ifstream archivo;
    string texto;
    stringstream contenidoArchivo,archivo1;
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
/*
Funcion que lee todo el archivo de texto y separa los caracteres por frecuencia

Parametros: string archivo, representa el archivo de texto que esta guardado en ese string

Retorna: Retorna la tabla de frecuencia ya llena con los caracteres y ordenada por frecuencia

Errores:
*/
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
        if (t>0)
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


    for (int i = 0; i < lista.size(); i++)
    {
        TreeElement temporal;

        temporal.element = lista[i];
        temporal.frequency = posicionL[i];
        tabla.listaTablaFrecuencia.push_back(temporal);

        
    }

    tabla.listaTablaFrecuencia = Ordenar(tabla.listaTablaFrecuencia);
    tabla.listaElementos = lista;
    tabla.listaFrecuencia = posicionL;

    return tabla;

} //Fin de la funcion Calcular frecuencia


//Ordenar la tabla de frecuencia
/*
Funcion que ordena la tabla de frecuencia alfabeticamente y por frecuencia

Parametros: vector<TreeElement> tabla, representa un vector que tiene almacenados TreeElements para ordenarlos

Retorna: El vector de TreeElements ordenados 

Errores:
*/
vector<TreeElement> Ordenar(vector<TreeElement> tabla)
{
    //Ordenar posiciones
    sort(tabla.begin(), tabla.end(), compare);

    return tabla;
}

//Ordenar por frecuencia
/*
Funcion que ordena la tabla de frecuencia por frecuencia

Parametros: vector<TreeElement> tabla, representa un vector que tiene almacenados TreeElements para ordenarlos

Retorna: El vector de TreeElements ordenados 

Errores:
*/

vector<TreeElement> Ordenar2(vector<TreeElement> tabla)
{
    //Ordenar posiciones
    TreeElement aux;

    for (int i = 0; i < tabla.size(); i++)
    {
        for (int j = 0; j < tabla.size() - 1; j++)
        {
            if (tabla[j].frequency < tabla[j + 1].frequency)
            {
                aux = tabla[j];
                tabla[j] = tabla[j + 1];
                tabla[j + 1] = aux;
            }
        }
    }

    return tabla;
}


//Funcion para el sort
/*
Funcion que servira para enviarse como parametro al sort que ordenara los TreeElements

Parametros: vector<TreeElement> tabla, representa un vector que tiene almacenados TreeElements para ordenarlos

Retorna: true si la comparacion que se retorna es verdadero, false si la comparacion es false

Errores:
*/
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
/*
Funcion que servira para codificar los caracteres contenidos en la tabla de frecuencia

Parametros: vector<TreeElement> tabla, representa un vector que tiene almacenados TreeElements para ordenarlos

Retorna: true si la comparacion que se retorna es verdadero, false si la comparacion es false

Errores:
*/
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
        { //Revisar en hijo izquierdo
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

            //Desicion para concatenar el codigo
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

    delete raiz;

} //Fin