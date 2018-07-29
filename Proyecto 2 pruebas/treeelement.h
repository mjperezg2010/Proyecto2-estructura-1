#include <string>


using namespace std;

#ifndef TREEELEMENT_H
#define TREEELEMENT_H

class TreeElement
{
   
        
    
    // vector<Integer> hijos;
  public:
    TreeElement();
    ~TreeElement();
    string element; // El contenido del TreeElement
    size_t frequency; //La frecuencia del elemento
    
    /*void SetElement(string);
    string GetElement();
    void SetFrequency(size_t);
    size_t GetFrequency();*/
    
};
#endif