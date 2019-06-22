#include "vdireccion.h"
#include "ui_vdireccion.h"
#include "tablero.h"
#include "vmesa.h"


VDireccion::VDireccion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDireccion)
{
    ui->setupUi(this);

    Tablero* tJuego = Tablero::getInstance();
    tJuego->getJActual() == 1 ? ui->lPlayer->setText("Jugador 1") : ui->lPlayer->setText("Jugador 2");
}

VDireccion::~VDireccion()
{
    delete ui;
}

void VDireccion::on_bHorizontal_clicked()
{
    // Llamo la instancia del tablero de juego
    Tablero* tJuego = Tablero::getInstance();

    // Asigno las direcciones dependiendo de quien seleccionó la dirección
    if (tJuego->getJActual() == 1) {
        tJuego->setpDir1(0); //0 Horizontal
        tJuego->setpDir2(1); //1 Vertical
    }
    else {
        tJuego->setpDir1(1);
        tJuego->setpDir2(0);
    }

    tJuego->getJActual() == 1 ? tJuego->setJActual(2) : tJuego->setJActual(1);

    VMesa vcm;
    vcm.setModal(true);
    this->close();
    vcm.exec();
}

void VDireccion::on_bVertical_clicked()
{
    // Llamo la instancia del tablero de juego
    Tablero* tJuego = Tablero::getInstance();

    // Asigno las direcciones dependiendo de quien seleccionó la dirección
    if (tJuego->getJActual() == 1) {
        tJuego->setpDir1(1);
        tJuego->setpDir2(0);
    }
    else {
        tJuego->setpDir1(0);
        tJuego->setpDir2(1);
    }

    tJuego->getJActual() == 1 ? tJuego->setJActual(2) : tJuego->setJActual(1);

    VMesa vcm;
    vcm.setModal(true);
    this->close();
    vcm.exec();
}
