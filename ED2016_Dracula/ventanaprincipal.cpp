#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "vcortarmazo.h"
#include "linkedstack.h"
#include "carta.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_bIniciar_clicked()
{
    VCortarMazo vcm;
    vcm.setModal(true);
    this->close();
    vcm.exec();
}
