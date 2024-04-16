#include "colorsw.h"
#include <QString>
#include "ui_colorsw.h"

ColorsW::ColorsW(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColorsW)
{
    ui->setupUi(this);
    ui->colorsshow->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(0).arg(0).arg(0));
    ui->colorsshow->setStyleSheet("border: 2px solid white;");
}

ColorsW::~ColorsW()
{
    delete ui;
}

int GlobalR = 0;
int GlobalG = 0;
int GlobalB = 0;
int RGlobalR = 0;
int RGlobalG = 0;
int RGlobalB = 0;
int ColorIndex = 0;

void ColorsW::UpdateColorLabel(int R,int G,int B){
    ui->colorsshow->setStyleSheet(QString("background-color: rgb(%1, %2, %3) ; border: 2px solid white;").arg(R).arg(G).arg(B));
}

void ColorsW::on_RSlide_sliderMoved(int position)
{
    GlobalR = position;
    ColorIndex = 1;
    QString R = QString::number(position);
    ui->Rvalues->setFont(QFont("Arial", 12));
    ui->Rvalues->setStyleSheet(QString ("font-weight: bold; color: white; background-color: transparent;") );
    ui->Rvalues->setAlignment(Qt::AlignHCenter);
    ui->Rvalues->setText(R);
    UpdateColorLabel(GlobalR,GlobalG,GlobalB);
}


void ColorsW::on_GSlide_sliderMoved(int position)
{
    GlobalG = position;
    ColorIndex = 1;
    QString G = QString::number(position);
    ui->Gvalues->setFont(QFont("Arial", 12));
    ui->Gvalues->setStyleSheet(QString ("font-weight: bold; color: white; background-color: transparent;") );
    ui->Gvalues->setAlignment(Qt::AlignHCenter);
    ui->Gvalues->setText(G);
    UpdateColorLabel(GlobalR,GlobalG,GlobalB);
}


void ColorsW::on_BSlide_sliderMoved(int position)
{
   GlobalB = position;
   ColorIndex = 1;
   QString B = QString::number(position);
   ui->Bvalues->setFont(QFont("Arial", 12));
   ui->Bvalues->setStyleSheet(QString ("font-weight: bold; color: white; background-color: transparent;") );
   ui->Bvalues->setAlignment(Qt::AlignHCenter);
   ui->Bvalues->setText(B);
   UpdateColorLabel(GlobalR,GlobalG,GlobalB);
}


void ColorsW::on_colorsshow_linkActivated(const QString &link)
{

}


void ColorsW::on_Blue_clicked()
{
    ColorIndex = 2;
    RGlobalR = 0;
    RGlobalG = 0;
    RGlobalB = 255;
    UpdateColorLabel(0,0,255);
}


void ColorsW::on_Yellow_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 255;
    RGlobalB = 0;
    UpdateColorLabel(255,255,0);
}



void ColorsW::on_Purple_clicked()
{
    ColorIndex = 2;
    RGlobalR = 128;
    RGlobalG = 0;
    RGlobalB = 128;
    UpdateColorLabel(128,0,128);
}



void ColorsW::on_Brown_clicked()
{
    ColorIndex = 2;
    RGlobalR = 165;
    RGlobalG = 42;
    RGlobalB = 42;
    UpdateColorLabel(165,42,42);
}



void ColorsW::on_Orange_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 165;
    RGlobalB = 0;
    UpdateColorLabel(255,165,0);
}




void ColorsW::on_Magenta_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 0;
    RGlobalB = 255;
    UpdateColorLabel(255,0,255);
}


void ColorsW::on_Cyan_clicked()
{
    ColorIndex = 2;
    RGlobalR = 0;
    RGlobalG = 255;
    RGlobalB = 255;
    UpdateColorLabel(0,255,255);
}


void ColorsW::on_White_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 255;
    RGlobalB = 255;
    UpdateColorLabel(255,255,255);
}


void ColorsW::on_Black_clicked()
{
    ColorIndex = 2;
    RGlobalR = 0;
    RGlobalG = 0;
    RGlobalB = 0;
    UpdateColorLabel(0,0,0);
}



void ColorsW::on_Pink_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 192;
    RGlobalB = 203;
    UpdateColorLabel(255,192,203);
}




void ColorsW::on_Red_clicked()
{
    ColorIndex = 2;
    RGlobalR = 255;
    RGlobalG = 0;
    RGlobalB = 0;
    UpdateColorLabel(255,0,0);
}



void ColorsW::on_Green_clicked()
{
    ColorIndex = 2;
    RGlobalR = 0;
    RGlobalG = 255;
    RGlobalB = 0;
   UpdateColorLabel(0,255,0);
}


void ColorsW::on_SaveColor_clicked()
{
    if (ColorIndex == 1){
        emit RGBcolorsSent(GlobalR,GlobalG,GlobalB);
    }
    if (ColorIndex == 2){
        emit RGBcolorsSent(RGlobalR,RGlobalG,RGlobalB);
    }
    if (ColorIndex == 0){
        emit RGBcolorsSent(GlobalR,GlobalG,GlobalB);
    }
    close();
}

