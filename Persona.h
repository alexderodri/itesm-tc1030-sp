#ifndef PERSONA_H
#define PERSONA_H
#include <string>
using namespace std;

class Persona {
    protected:
        string nombre, direccion, tel, fechaN, sexo;
    public:
        Persona(string, string, string, string ,string);
        Persona();
        // getters
        string getNombre()      {return nombre;}
        string getDireccion()   {return direccion;}
        string getTel()         {return tel;}
        string getFechaN()      {return fechaN;}
        string getSexo()        {return sexo;}
        // setters
        void setNombre(string nombre)       {this->nombre = nombre;}
        void setDireccion(string direccion) {this->direccion = direccion;}
        void setTel(string tel)             {this->tel = tel;}
        void setFechaN(string fechaN)       {this->fechaN = fechaN;}
        void setSexo(string sexo)           {this->sexo = sexo;}
};
#endif