#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>

namespace Ui {
class VentanaPrincipal;
}

/**
 * @brief The VentanaPrincipal class
 * @autor David Díaz - Jose Murillo - Maria Jose
 */
class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();

private:
    Ui::VentanaPrincipal *ui;

private slots:
    void on_bIniciar_clicked();
};

#endif // VENTANAPRINCIPAL_H
