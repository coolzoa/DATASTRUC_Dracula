#ifndef VGANADOR_H
#define VGANADOR_H

#include <QDialog>
#include "tablero.h"

namespace Ui {
class VGanador;
}

/**
 * @brief The VGanador class
 * @autor David Díaz - Jose Murillo - Maria Jose
 */
class VGanador : public QDialog
{
    Q_OBJECT

public:
    explicit VGanador(QWidget *parent = 0);
    ~VGanador();

private slots:
    void on_bVolver_clicked();
    void on_bSalir_clicked();

private:
    Ui::VGanador *ui;
    Tablero* tJuego = Tablero::getInstance();
};

#endif // VGANADOR_H
