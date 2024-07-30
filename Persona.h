#include <string>

class Persona {
public:
    std::string cedula;
    std::string id;

    Persona(const std::string& cedula, const std::string& id) : cedula(cedula), id(id) {}
};
