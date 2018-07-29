#include <fstream>
#include <vector>

using namespace std;

class TablaFrecuencia{
    private:
       

    public:
        TablaFrecuencia();
        vector<char> GetListaElementos();
        vector<int> GetListaFrecuencia();
        vector<char> listaElementos;
        vector<int> listaFrecuencia;
        string LeerArchivo();
        void CrearTabla(string);
       // vector<char> listaElementos;




};