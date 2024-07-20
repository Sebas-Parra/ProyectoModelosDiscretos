#ifndef PREGUNTAS_H
#define PREGUNTAS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Preguntas {
private:
    vector<string> preguntas;
    vector<string> respuestas;
    void cargarPreguntasRespuestas(const string& archivo) {
        ifstream file(archivo);
        string line;
        string pregunta;
        string respuesta;

        while (getline(file, line)) {
            if (line.find("PREGUNTA:") != string::npos) {
                pregunta = line.substr(10);
            }
            else if (line.find("RESPUESTA:") != string::npos) {
                respuesta = line.substr(10);
                preguntas.push_back(pregunta);
                respuestas.push_back(respuesta);
            }
        }
    }

public:
    Preguntas(const string& archivo) {
        cargarPreguntasRespuestas(archivo);
    }

    const vector<string>& obtenerPreguntas() const {
        return preguntas;
    }

    const vector<string>& obtenerRespuestas() const {
        return respuestas;
    }

    
};

#endif // PREGUNTAS_H
