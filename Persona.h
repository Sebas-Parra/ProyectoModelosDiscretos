#include <string>

using namespace std;

class Persona {
public:
    string cedula;
    string id;
    int puntaje;

    Persona( string& cedula,  string& id) : cedula(cedula), id(id), puntaje(0) {}
    Persona( string& cedula,  string& id, int puntaje) : cedula(cedula), id(id), puntaje(puntaje) {}
    
    void setCedula(string cedul)  {
        this->cedula = cedul;
    }

    void setID(string i)  {
        this->id = i;
    }

    string getCedula()  { 
        return cedula; 
    }

    string getID() { 
        return id; 
    }

    void setPuntaje(int punto) {
        this->puntaje = punto;
    }

    int getPuntaje() {
        return puntaje;
    }


};
