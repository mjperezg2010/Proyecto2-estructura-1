/*
Titulo: Clase TreeElement
Proposito: clase que servira para guardar el contenido de cada 
           TreeNode
Fecha: 31/Julio/2018
Elaborado por: Martín José Pérez Gálvez
*/
#include <string>

using namespace std;

#ifndef TREEELEMENT_H
#define TREEELEMENT_H

class TreeElement
{
   
  public:
    TreeElement();
    ~TreeElement();
    string element; // El contenido del TreeElement
    size_t frequency; //La frecuencia del elemento
    
  
    
};
#endif