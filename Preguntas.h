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
    vector<vector<string>> opciones;
    vector<string> respuestas;

    void cargarPreguntasRespuestas(const string& archivo) {
        ifstream file(archivo);
        string line;
        string pregunta;
        vector<string> opcionesPregunta;
        string respuesta;

        while (getline(file, line)) {
            if (line.find("PREGUNTA:") != string::npos) {
                if (!pregunta.empty()) {
                    preguntas.push_back(pregunta);
                    opciones.push_back(opcionesPregunta);
                    respuestas.push_back(respuesta);
                }
                pregunta = line.substr(10);
                opcionesPregunta.clear();
            }
            else if (line.find("A)") != string::npos ||
                line.find("B)") != string::npos ||
                line.find("C)") != string::npos ||
                line.find("D)") != string::npos) {
                opcionesPregunta.push_back(line);
            }
            else if (line.find("RESPUESTA:") != string::npos) {
                respuesta = line.substr(10);
            }
        }

        if (!pregunta.empty()) {
            preguntas.push_back(pregunta);
            opciones.push_back(opcionesPregunta);
            respuestas.push_back(respuesta);
        }
    }

public:
    Preguntas(const string& archivo) {
        cargarPreguntasRespuestas(archivo);
    }

    const vector<string>& obtenerPreguntas() const {
        return preguntas;
    }

    const vector<vector<string>>& obtenerOpciones() const {
        return opciones;
    }

    const vector<string>& obtenerRespuestas() const {
        return respuestas;
    }
};

#endif // PREGUNTAS_H
