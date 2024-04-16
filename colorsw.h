#ifndef COLORSW_H
#define COLORSW_H

#include <QDialog>

namespace Ui {
class ColorsW;
}

class ColorsW : public QDialog
{
    Q_OBJECT

public:
    explicit ColorsW(QWidget *parent = nullptr);
    ~ColorsW();
    void UpdateColorLabel(int,int,int);

signals:
    void RGBcolorsSent(int &R, int &G, int &B);

private slots:
    void on_colorsshow_linkActivated(const QString &link);

    void on_RSlide_sliderMoved(int position);

    void on_GSlide_sliderMoved(int position);

    void on_BSlide_sliderMoved(int position);

    void on_Blue_clicked();

    void on_Yellow_clicked();

    void on_Purple_clicked();

    void on_Brown_clicked();

    void on_Orange_clicked();

    void on_Magenta_clicked();

    void on_Cyan_clicked();

    void on_White_clicked();

    void on_Black_clicked();

    void on_Pink_clicked();

    void on_Red_clicked();

    void on_Green_clicked();

    void on_SaveColor_clicked();

private:
    Ui::ColorsW *ui;
};

#endif // COLORSW_H
