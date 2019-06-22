#ifndef VDIRECCION_H
#define VDIRECCION_H

#include <QDialog>

namespace Ui {
class VDireccion;
}

/**
 * @brief The VDireccion class
 * @autor David Díaz - Jose Murillo - Maria Jose
 */
class VDireccion : public QDialog
{
    Q_OBJECT

public:
    explicit VDireccion(QWidget *parent = 0);
    ~VDireccion();

private slots:
    void on_bHorizontal_clicked();
    void on_bVertical_clicked();

private:
    Ui::VDireccion *ui;
};

#endif // VDIRECCION_H
