#ifndef DECK_H
#define DECK_H


#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "assert.h"
#include "Carta.h"
#include "linkedstack.h"

using namespace std;

/**
 * @brief The Deck class
 * @autor David Díaz - Jose Murillo
 * Descripción: Se encarga de instanciar un Deck mediante singleton, y
 * proveer métodos capaces de hacer uso y manejo de la pila de cartas.
 *
 * Entradas: Ninguna
 */
class Deck{

private:
    const int Cartas_por_deck = 52;
    LinkedStack<Carta> deck;

public:

    /**
     * @brief getInstance
     * @return Instancia del deck (Singleton)
     */
    static Deck* getInstance() {
        static Deck m_instance;
        return &m_instance;
    }

    /**
     * @brief Deck
     * Constructor del deck
     */
    Deck(){
        crear();
    }

    ~Deck(){
        deck.~LinkedStack();
    }

    /**
     * @brief crear
     * Limpia y crea un deck con los diferentes valores y palos, al final
     * agrega los Jokers
     */
    void crear(){
        deck.clear();

        string caras[] = {"As","Dos","Tres","Cuatro","Cinco","Seis","Siete","Ocho","Nueve","Diez",
                        "Jack","Dama","Rey"};
        string palos[] = {"Corazon","Diamante","Espada","Trebol"};
        for (int i = 0; i < Cartas_por_deck;i++){
            deck.push(Carta(caras[i % 13],palos[i / 13] ));
        }

        deck.push(Carta("Joker", "Negro"));
        deck.push(Carta("Joker", "Rojo"));
    }

    /**
     * @brief mezclar
     * Mezcla el mazo creado
     */
    void mezclar(){

        crear();

        Carta deckTemp[54];
        for(int i = 0; i < 54; i++){
            deckTemp[i] = deck.pop();
        }

        for (int primero = 0; primero < 54; primero++){
            int segundo = (rand() + time(0)) % 54;
            Carta temp = deckTemp[primero];
            deckTemp[primero] = deckTemp[segundo];
            deckTemp[segundo] = temp;
            deckTemp[segundo].print();
        }

        for(int i = 0; i < 54; i++){
            deck.push(deckTemp[i]);
        }
    }

    /**
     * @brief topCarta
     * @return
     * Retorna la carta que se encuentre en el tope del mazo
     */
    Carta topCarta(){
        return deck.pop();
    }
};

#endif // DECK_H
