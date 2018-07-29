#include "tablafrecuencia.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

TablaFrecuencia::TablaFrecuencia(){

}

void TablaFrecuencia::LlenarTablaFrecuencia(){
    for(int i=0;i<listaElementos.size();i++){
        TreeElement temporal;

        if(listaElementos[i]==32){
            temporal.element="SP";
        }else if(listaElementos[i]==10){
            temporal.element="LF";
        }else if(listaElementos[i]==13){
            temporal.element="CR";
        }else{
            temporal.element=listaElementos[i];
        }
        
        temporal.frequency=listaFrecuencia[i];
        listaTablaFrecuencia.push_back(temporal);
    }
}


/*
void TablaFrecuencia::CrearTabla(string archivo){
     string archivo1 = archivo;
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

    for (int i = 0; i < lista.size(); i++)
    {
        cout << lista[i] << " - " << posicionL[i] << endl;
    }

    listaElementos=lista;
}


string TablaFrecuencia::LeerArchivo(){
    ifstream archivo;
    string texto;
    stringstream contenidoArchivo;
    archivo.open("test01.txt", ios::in);

    while (!archivo.eof())
    {
        getline(archivo, texto);
        contenidoArchivo << texto << "\n";
    }

    archivo.close();

    return contenidoArchivo.str();
}
*/