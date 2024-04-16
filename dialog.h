#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void HWidgets();
    void Colorsetter(int &R, int &G, int &B);

private slots:


    void on_pushButton_clicked();
    void on_GrayScaleFilter_clicked();
    void on_ResetImage_clicked();
    void on_SaveImage_clicked();
    void on_BlackWhite_clicked();
    void on_InvertImage_clicked();
    void on_DetectEdges_clicked();
    void on_Warmup_clicked();
    void on_TvLook_clicked();
    void on_PurpleEffect_clicked();
    void on_RedScale_clicked();
    void on_ApplyingFilter_clicked();
    void on_Brightness_clicked();
    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_MergetwoImages_clicked();

    void on_DegreeSlider_sliderMoved(int position);

    void on_Skew_clicked();

    void on_OilSlider_sliderMoved(int position);

    void on_OilPainting_clicked();

    void on_BlurSlide_sliderMoved(int position);

    void on_Blur_clicked();

    void on_RotateSlide_sliderMoved(int position);

    void on_Rotate_clicked();

    void on_TakeSize_textChanged(const QString &arg1);

    void on_TakeHight_textChanged(const QString &arg1);

    void on_Resize_clicked();

    void on_ChoosingColor_clicked();

    void on_Frame_clicked();

    void on_FancyCheckBox_toggled(bool checked);

    void on_BorderSlide_sliderMoved(int position);

    void on_HFlip_toggled(bool checked);

    void on_VFlip_toggled(bool checked);

    void on_Flip_clicked();

    void on_StartHeightL_textChanged(const QString &arg1);

    void on_EndHeightL_textChanged(const QString &arg1);

    void on_StartWidthL_textChanged(const QString &arg1);

    void on_EndWidthL_textChanged(const QString &arg1);

    void on_Crop_clicked();

    void on_SopiaTone_clicked();

    void on_Shuffle_clicked();

    void on_Shuffle1_clicked();

    void on_Shuffle2_clicked();

    void on_Shuffle3_clicked();

    void on_Shuffle4_clicked();

    void on_clardeon_clicked();

    void on_GreenScale_clicked();

    void on_BlueScale_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
