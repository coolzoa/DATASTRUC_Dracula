#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief The Carta class
 * @autor David Díaz - Jose Murillo
 * Se encarga de crear las instancias de las diferentes cartas del deck
 */
class Carta{

private:
    string cara; //valor
    string palo; //simbolo
    string color;
    string direccion;

public:

    /**
     * @brief Carta
     * @param pCara Cara de la carta
     * @param pPalo Palo de la carta
     * Dependiendo del palo se le asigna el color a la carta
     * La direccion es usada para llamar a la imagen de la carta
     */
    Carta(string pCara, string pPalo){
        cara = pCara;
        palo = pPalo;
        if (pPalo == "Diamante" || pPalo == "Corazon"){
            color = "Rojo";
        } else if(pPalo == "Espada" || pPalo == "Trebol"){
            color = "Negro";
        } else if(pPalo == "Rojo"){
            color = "Rojo";
        } else if(pPalo == "Negro"){
            color = "Negro";
        }
        direccion = pCara + pPalo;
    }

    Carta(){}

    string getDireccion(){
        return direccion;
    }

    void setColor(string pcolor){
        color = pcolor;
    }

    string getColor(){
        return this->color;
    }

    string getPalo(){
        return this->palo;
    }

    string getCara(){
        return this->cara;
    }

    //print
    string print(){
        return (cara + " de " + palo + " Color: "+color);
    }

    /**
     * @brief getValue
     * @return Retorna el valor de la carta según las reglas del juego
     */
    int getValue(){
        if(cara=="Jack"){
            return 0;
        }else if(cara == ""){
            return 0;
        }else if(cara == "As"){
            return 1;
        }else if(cara == "Dos"){
            return 2;
        }else if (cara == "Tres"){
            return 3;
        }else if(cara == "Cuatro"){
            return 4;
        }else if(cara == "Cinco"){
            return 5;
        }else if(cara == "Seis"){
            return 6;
        }else if(cara == "Siete"){
            return 7;
        }else if(cara == "Ocho"){
            return 8;
        }else if(cara == "Nueve"){
            return 9;
        }else if(cara == "Diez"){
            return 10;
        }else if(cara == "Dama"){
            return 10;
        }else if(cara == "Rey"){
            return 10;
        }else {
            return -1;
        }
    }
};

#endif // CARTA_H
