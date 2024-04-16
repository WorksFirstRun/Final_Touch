#ifndef CROPW_H
#define CROPW_H

#include <QDialog>

namespace Ui {
class CropW;
}

class CropW : public QDialog
{
    Q_OBJECT

public:
    explicit CropW(QWidget *parent = nullptr);
    ~CropW();

private:
    Ui::CropW *ui;
};

#endif // CROPW_H
