#ifndef TABLERO_H
#define TABLERO_H

#include "assert.h"
#include "Deck.h"
#include <qstring.h>

using namespace std;

/**
 * @brief The Tablero class
 * @autor David Díaz - Jose Murillo - Maria Vargas
 * Esta clase se encarga de instanciar(singleton) un tablero para hacer uso
 * de el en toda la aplicación, en el se encuentran las cartas de los jugadores,
 * el manejo de la funcion de "undo", manejo de los turnos y puntaje de la partida.
 *
 * Entradas: Ninguna
 */
class Tablero{
    private:

        // Tablero de cartas lógico, en el se manejan las cartas
        Carta tablero[3][3];

        // Variables para hacer el manejo de la funcionalidad del "undo"
        LinkedStack<int> posMano;
        LinkedStack<int> posMesa;
        LinkedStack<int> jugadores;
        LinkedStack<Carta> cartas;

        // Se maneja las varibles de las rondas, puntajes y direcciones
        int JActual = 1;
        int pdir1 = 0;
        int pdir2 = 0;
        int ronda = 1;
        int puntajeJ1;
        int puntajeJ2;

        // Llevan las cartas de los jugadores y la carta seleccionada durante los turnos
        Carta player1[4];
        Carta player2[4];
        Carta cartaSeleccionada;

    public:


        Tablero(){
        }

        /**
         * @brief resetTablero
         * Borra los puntajes, vuelve a la ronda 1 y mezcla de nuevo el mazo
         */
        void resetTablero(){
            ronda = 1;
            puntajeJ1 = 0;
            puntajeJ2 = 0;
            Deck* mazo = Deck::getInstance();
            mazo->mezclar();
        }

        /**
         * @brief getCartaQString
         * @param pCarta Recibe una carta
         * @return Dirección de la carta en los recursos
         */
        QString getCartaQString(Carta pCarta){
            string str = ":/Cartas/Recursos/Cartas/"+pCarta.getDireccion()+".png";
            QString qStr = QString::fromLocal8Bit(str.c_str());

            return qStr;
        }

        /**
         * @brief getInstance
         * @return Retorna la instancia del tablero
         */
        static Tablero* getInstance() {
            static Tablero m_instance;
            return &m_instance;
        }

        /**
         * @brief repartir
         * Asigna 4 cartas a cada uno de los jugadores
         */
        void repartir(){
            Deck *mazo = Deck::getInstance();
            for(int i = 0; i < 4; i++){
                player1[i] = mazo->topCarta();
            }
            for(int i = 0; i < 4; i++){
                player2[i] = mazo->topCarta();
            }
        }

        /**
         * @brief reset
         * Limpia el tablero lógico
         */
        void reset(){
            for(int fila = 0;fila < 3; fila++){
                for (int columna = 0; columna < 3; columna++){
                    tablero[fila][columna] = Carta();
                }
            }
        }

        /**
         * @brief isFull
         * @return Indica si el tablero se encuentra lleno o no
         */
        bool isFull(){
            bool lleno = true;
            for (int i = 0; i < 3;i++){
                for (int j = 0; j < 3; j++){
                    if (tablero[i][j].getCara() == ""){
                        lleno = false;
                    }
                }
            }
            return lleno;
        }

        /**
         * @brief comprobarRonda
         * @return Comprueba si el tablero está lleno, de ser así, se realizan los calculos
         * necesarios y se suman las puntuaciones a los jugadores, y retorna "true" para seguir con la
         * siguiente ronda.
         */
        bool comprobarRonda(){
            if(!isFull()){
                return false;
            }else{
                int medioFila = puntajeFila(0);
                int medioColumna = puntajeColumna(0);
                int menorFila = puntajeFila(1);
                int menorColumna = puntajeColumna(1);
                int mayorFila = puntajeFila(2);
                int mayorColumna = puntajeColumna(2);

                int puntajesFila[3] = {medioFila,menorFila,mayorFila};
                int puntajesColumna[3] = {medioColumna,menorColumna,mayorColumna};

                // Ordeno de menor a mayor los puntajes de las filas
                int j, temp;
                for (int i = 0; i < 3; i++){
                    j = i;
                    while (j > 0 && puntajesFila[j] < puntajesFila[j-1]){
                        temp = puntajesFila[j];
                        puntajesFila[j] = puntajesFila[j-1];
                        puntajesFila[j-1] = temp;
                        j--;
                        }
                }

                // Ordeno de menor a mayor los puntajes de las columnas
                for (int i = 0; i < 3; i++){
                    j = i;
                    while (j > 0 && puntajesColumna[j] < puntajesColumna[j-1]){
                        temp = puntajesColumna[j];
                        puntajesColumna[j] = puntajesColumna[j-1];
                        puntajesColumna[j-1] = temp;
                        j--;
                        }
                }

                // Puntajes de los jugadores
                int puntajes1[3];
                int puntajes2[3];

                // Asigno los puntajes dependiendo de la dirección seleccionada al inicio del juego
                if(pdir1 == 0){
                    for(int i = 0; i < 3; i++){
                        puntajes1[i] = puntajesFila[i];
                    }

                    for(int i = 0; i < 3; i++){
                        puntajes2[i] = puntajesColumna[i];
                    }
                } else {
                    for(int i = 0; i < 3; i++){
                        puntajes2[i] = puntajesFila[i];
                    }

                    for(int i = 0; i < 3; i++){
                        puntajes1[i] = puntajesColumna[i];
                    }
                }

                // Se realizan las comparaciones y dependiendo del ganador se suma el bono
                if (puntajes1[2] > puntajes2[2]){
                    puntajeJ1 += puntajes1[2]+ (puntajes1[2] - puntajes2[2]);
                    puntajeJ2 += puntajes2[2];
                }else if(puntajes1[2] < puntajes2[2]){
                    puntajeJ1 += puntajes1[2];
                    puntajeJ2 += puntajes2[2]+ (puntajes2[2] - puntajes1[2]);
                }else if (puntajes1[1] > puntajes2[1]){
                    puntajeJ1 += puntajes1[1]+ (puntajes1[1] - puntajes2[1]);
                    puntajeJ2 += puntajes2[1];
                }else if (puntajes1[1] < puntajes2[1]){
                    puntajeJ1 += puntajes1[1];
                    puntajeJ2 += puntajes2[1]+ (puntajes2[1] - puntajes1[1]);
                }else if (puntajes1[0] > puntajes2[0]){
                    puntajeJ1 += puntajes1[0]+ (puntajes1[0] - puntajes2[0]);
                    puntajeJ2 += puntajes2[0];
                }else if (puntajes1[0] < puntajes2[0]){
                    puntajeJ1 += puntajes1[0];
                    puntajeJ2 += puntajes2[0]+ (puntajes2[0] - puntajes1[0]);
                }else{
                    puntajeJ1 += puntajes1[2];
                    puntajeJ2 += puntajes2[2];
                }

                // Limpio el tablero de cartas
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        tablero[i][j] = Carta("", "");
                    }
                }

                //Limpio el historial de movimientos
                posMano.clear();
                posMesa.clear();
                cartas.clear();
                jugadores.clear();

                return true;
            }
        }

        /**
         * @brief setJugada
         * @param carta Carta a insertar en la matriz "tablero"
         * @param numcasilla Casilla en la que se insertará la carta
         * @return Si la jugada es valida se retorna verdadero, de lo contrario se retorna falso
         */
        bool setJugada (Carta carta, int numcasilla){
            bool  valido = false;
            switch (numcasilla)
            {
            case 1:
                valido = validar(0,0);
                if (valido == true){
                    tablero[0][0] = carta;
                }
                return valido;

            case 2:
                valido = validar(0,1);
                if (valido == true){
                    tablero[0][1] = carta;
                }
                return valido;

            case 3:
                valido = validar(0,2);
                if (valido == true){
                    tablero[0][2] = carta;
                }
                return valido;

            case 4:
                valido = validar(1,0);
                if (valido == true){
                    tablero[1][0] = carta;
                }
                return valido;

            case 5:
                valido = (tablero[1][1].getCara()=="");
                if (valido){
                    tablero[1][1] = carta;
                }
                break;

            case 6:
                valido = validar(1,2);
                if (valido == true){
                    tablero[1][2] = carta;
                }
                return valido;

            case 7:
                valido = validar(2,0);
                if (valido == true){
                    tablero[2][0] = carta;
                }
                return valido;

            case 8:
                valido = validar(2,1);
                if (valido == true){
                    tablero[2][1] = carta;
                }
                return valido;

            case 9:
                valido = validar(2,2);
                if (valido == true){
                    tablero[2][2] = carta;
                }
                return valido;
            }
        }

        /**
         * @brief validar
         * @param fila Fila en la matriz "tablero"
         * @param columna Columna en la matriz "tablero"
         * @return Si el espacio en la fila/columna está vacío y se cumplen las reglas del juego,
         * la carta se podrá colocar y se retorna true
         */
        bool validar(int fila, int columna){
            switch (fila)
            {
                case 0:
                    if (columna == 0){
                        return ( (tablero[0][0].getCara() == "") && (tablero[0][1].getCara() != "" || tablero[1][0].getCara()!="") );
                        break;

                    }else if(columna == 1){
                        return (tablero[0][1].getCara() == "");
                        break;

                    }else if (columna == 2){
                        return ((tablero[0][2].getCara() == "") && (tablero[0][1].getCara()!="" || tablero[1][2].getCara()!=""));
                    }

                case 1:
                    if (columna == 0){
                        return (tablero[1][0].getCara()=="");

                    }else if (columna == 2){
                        return (tablero[1][2].getCara()=="");
                    }

                case 2:
                    if (columna == 0){
                        return ((tablero[2][0].getCara()=="")&& (tablero[1][0].getCara()!="" || tablero[2][1].getCara()!=""));

                    }else if(columna == 1){
                        return (tablero[2][1].getCara() == "");

                    }else if (columna == 2){
                        return ((tablero[2][2].getCara() == "")&& (tablero[1][2].getCara()!="" || tablero[2][1].getCara()!=""));
                    }
                default:
                    return false;
            }
            return false;
        }

        /**
         * @brief puntajeFila
         * @param fila Fila en la que se calculará su resultado
         * @return El puntaje de la fila
         */
        int puntajeFila(int fila){
            //veo si alguno de la fila es vampiro
            if ((tablero[fila][0].getValue() == -1) || (tablero[fila][1].getValue() == -1) || (tablero[fila][2].getValue() == -1)){
                return 0;
            }else{
                int suma = 0;
                int multiplicar = 1;

                //agarro las cartas de la fila
                Carta c1 = tablero[fila][0];
                Carta c2 = tablero[fila][1];
                Carta c3 = tablero[fila][2];

                //veo si hay 2 del mismo palo

                if (((c1.getPalo() == c2.getPalo()) && (c1.getPalo() != ""))|| ((c2.getPalo() == c3.getPalo()) && (c2.getPalo() != "") )|| ((c1.getPalo() == c3.getPalo()) && (c3.getPalo() != "") )){
                    multiplicar = multiplicar * 2;
                }

                //si tiene 3 cartas del mismo color
                if (c1.getColor() == c2.getColor() && c2.getColor() == c3.getColor()){
                    multiplicar = multiplicar * 3;
                }

                //veo si son de mismo palo
                if (c1.getPalo() == c2.getPalo() && c2.getPalo() == c3.getPalo()){
                    multiplicar = multiplicar * 5;
                }

                // Dependiendo de la fila se suman los valores de las cartas
                // y se aplican los multiplicadores respectivos
                switch(fila){
                case 0:
                    for (int i = 0; i < 3; i++){
                            if (tablero[0][i].getCara()!="Rey"){
                                suma = suma + tablero[0][i].getValue();
                            }
                    }

                    suma = suma * multiplicar;
                    return suma;

                case 1:
                    for (int i = 0; i < 3; i++){
                            if (tablero[1][i].getCara()!="Rey"){
                                suma = suma + tablero[1][i].getValue();
                            }
                    }
                    suma = suma * multiplicar;
                    return suma;

                case 2:
                    for(int i = 0; i < 3; i++){
                            if (tablero[2][i].getCara()!="Rey"){
                                suma = suma + tablero[2][i].getValue();
                            }
                    }
                    suma = suma * multiplicar;
                    return suma;

                }
            }
        }

        /**
         * @brief puntajeColumna
         * @param columna Columna en la que se tomará el resultado
         * @return El puntaje de la columna
         */
        int puntajeColumna(int columna){
            if ((tablero[0][columna].getValue() == -1) || (tablero[1][columna].getValue() == -1)|| (tablero[2][columna].getValue() == -1)){
                return 0;
            }else{
                int suma = 0;
                int multiplicar = 1;


                //agarro las cartas de la columna
                Carta c1 = tablero[0][columna];
                Carta c2 = tablero[1][columna];
                Carta c3 = tablero[2][columna];

                //veo si hay 2 del mismo palo
                if (((c1.getPalo() == c2.getPalo()) && (c1.getPalo() != ""))|| ((c2.getPalo() == c3.getPalo()) && (c2.getPalo() != ""))|| ((c1.getPalo() == c3.getPalo()) && (c3.getPalo() != ""))){
                    multiplicar = multiplicar * 2;
                }

                //si tiene 3 cartas del mismo color
                if (c1.getColor() == c2.getColor() && c2.getColor() == c3.getColor()){
                    multiplicar = multiplicar * 3;
                }

                //veo si son de mismo palo
                if (c1.getPalo() == c2.getPalo()&& c2.getPalo() == c3.getPalo()){
                    multiplicar = multiplicar * 5;
                }

                // Dependiendo de la columna se suma y se aplica el multiplicador
                switch(columna){
                case 0:
                    for (int i = 0; i < 3; i++){
                            if (tablero[i][0].getCara() != "Dama"){
                                suma = suma + tablero[i][0].getValue();
                            }
                    }
                    suma = suma * multiplicar;
                    return suma;

                case 1:
                    for (int i = 0; i < 3; i++){
                            if (tablero[i][1].getCara() != "Dama"){
                                suma = suma + tablero[i][1].getValue();
                            }
                    }
                    suma = suma * multiplicar;
                    return suma;

                case 2:
                    for (int i = 0; i < 3; i++){
                            if(tablero[i][2].getCara() != "Dama"){
                                suma = suma + tablero[i][2].getValue();
                            }
                    }
                    suma = suma * multiplicar;
                    return suma;

                }
            }
        }

        //Getters & Setters

        void setTablero(int pFila, int pCol, Carta pCarta){
            tablero[pFila][pCol] = pCarta;
        }

        Carta* getCartasJ1(){
            return player1;
        }

        Carta* getCartasJ2(){
            return player2;
        }

        void setJActual(int pA){
            JActual = pA;
        }

        int getJActual() {
            return JActual;
        }

        int getpDir1(){
            return pdir1;
        }

        void setpDir1(int value){
            pdir1 = value;
        }

        int getpDir2(){
            return pdir2;
        }

        void setpDir2(int value){
            pdir2 = value;
        }

        Carta getCartaSeleccionada(){
            return cartaSeleccionada;
        }

        void setCartaSeleccionada(Carta pCarta){
            cartaSeleccionada = pCarta;
        }

        int getRonda(){
            return ronda;
        }

        void incRonda(){
            ronda++;
        }

        string getGanador(){
            if(puntajeJ1 > puntajeJ2){
                return "Jugador 1";
            } else {
                return "Jugador 2";
            }
        }

        int getPuntajeJ1(){
            return puntajeJ1;
        }

        int getPuntajeJ2(){
            return puntajeJ2;
        }

        //Codigo de Undo

        /**
         * @brief getSizeUndo
         * @return Cantidad de movimientos posibles de devolver
         */
        int getSizeUndo(){
            return jugadores.getSize();
        }

        /**
         * @brief pushJugada
         * @param pPosCarta
         * @param pJugador
         * @param pCarta
         *
         * Se inserta una jugada en el stack
         */
        void pushJugada(int pPosCarta, int pJugador, Carta pCarta){
            posMano.push(pPosCarta);
            jugadores.push(pJugador);
            cartas.push(pCarta);
        }

        /**
         * @brief pushPosMesa
         * @param pPosMesa
         * Se inserta la posicion en la que se inserto la carta
         */
        void pushPosMesa(int pPosMesa){
            posMesa.push(pPosMesa);
        }

        // Retorno las variables del stack

        int popPosicionMano(){
            return posMano.pop();
        }

        int popPosicionMesa(){
            return posMesa.pop();
        }

        int popJugador(){
            return jugadores.pop();
        }

        Carta popCarta(){
            return cartas.pop();
        }
};

#endif // TABLERO_H
