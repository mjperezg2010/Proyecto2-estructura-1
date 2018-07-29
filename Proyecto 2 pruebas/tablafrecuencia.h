#include <fstream>
#include <vector>
#include "treeelement.h"

using namespace std;

#ifndef TABLAFRECUENCIA_H
#define TABLAFRECUENCIA_H

class TablaFrecuencia{
    private:
       

    public:
        TablaFrecuencia();
       // vector<char> GetListaElementos();
     //vector<int> GetListaFrecuencia();
        vector<char> listaElementos;
        vector<int> listaFrecuencia;
        string LeerArchivo();
        void CrearTabla(string);
        vector<TreeElement> listaTablaFrecuencia;//Tablafecuencia
        void LlenarTablaFrecuencia();
       




};
#endif