#ifndef VCORTARMAZO_H
#define VCORTARMAZO_H

#include <QDialog>

namespace Ui {
class VCortarMazo;
}

/**
 * @brief The VCortarMazo class
 * @autor David Díaz - Jose Murillo - Maria Jose
 */
class VCortarMazo : public QDialog
{
    Q_OBJECT

public:
    explicit VCortarMazo(QDialog *parent = 0);
    ~VCortarMazo();

private:
    Ui::VCortarMazo *ui;
private slots:
    void on_bSeguir_clicked();
    void on_bCortarMazo_clicked();
};

#endif // VCORTARMAZO_H
