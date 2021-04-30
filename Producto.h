#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <string>
using namespace std;

class Producto {
    private:
        int codigo;
        string nombre;
        float precioC, precioV, peso, alto, ancho, largo;
    public:
        Producto(int, string, float, float ,float, float, float, float);
        Producto();
        // setters
        void setCodigo(int codigo)      {this->codigo   = codigo;}
        void setNombre(string nombre)   {this->nombre   = nombre;}
        void setPrecioC(float precioC)  {this->precioC  = precioC;}
        void setPrecioV(float precioV)  {this->precioV  = precioV;}
        void setPeso(float peso)        {this->peso     = peso;}
        void setAlto(float alto)        {this->alto     = alto;}
        void setAncho(float ancho)      {this->ancho    = ancho;}
        void setLargo(float largo)      {this->largo    = largo;}
        // getters
        int getCodigo()     {return codigo;}
        string getNombre()  {return nombre;}
        float getPrecioC()  {return precioC;}
        float getPrecioV()  {return precioV;}
        float getPeso()     {return peso;}
        float getAlto()     {return alto;}
        float getAncho()    {return ancho;}
        float getLargo()    {return largo;}
};
#endif