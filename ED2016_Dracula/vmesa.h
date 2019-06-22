#ifndef VMESA_H
#define VMESA_H

#include <QDialog>
#include "tablero.h"

namespace Ui {
class VMesa;
}

/**
 * @brief The VMesa class
 * @autor David Díaz - Jose Murillo - Maria Jose
 */
class VMesa : public QDialog
{
    Q_OBJECT

public:
    explicit VMesa(QWidget *parent = 0);
    ~VMesa();

    QTimer *timer;
    int seconds;
    int minutes;
    int hours;

private slots:
    void turno();
    void ronda();

    void botonesMano(bool entrada);
    void botonesMesa(bool entrada);
    void limpiarMesa();
    void definirGanador();
    void marcadores();
    void recargarBoton(QPushButton* pButton);

    void count();
    void start();

    void on_mano1_clicked();
    void on_campo2_clicked();
    void on_mano2_clicked();
    void on_mano3_clicked();
    void on_mano4_clicked();
    void on_campo1_clicked();
    void on_campo3_clicked();
    void on_campo4_clicked();
    void on_campo6_clicked();
    void on_campo7_clicked();
    void on_campo8_clicked();
    void on_campo9_clicked();
    void on_bUndo_clicked();

private:
    Ui::VMesa *ui;
    Tablero* tJuego = Tablero::getInstance();
    Deck* mazo = Deck::getInstance();

};

#endif // VMESA_H
