#ifndef CLIENTE_H
#define CLIENTE_H
#include "Persona.h"

class Cliente : public Persona {
    private:
        string rfc;
    public:
        Cliente(string, string, string, string ,string, string);
        Cliente();
        // getters
        string getRfc() {return rfc;}
        // setters
        void setRfc(string rfc)             {this->rfc = rfc;}
};
#endif