#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QDebug>
#include "Image_Class.h"
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <QValidator>
#include "colorsw.h"
using namespace std;

vector <vector <int>> magnitudearray(Image Userimage);
vector<vector<int>> Padding(Image UserImage,int pv);
vector < vector < vector <int> >> Color_Padding(Image UserImage, int pv);
vector <float> RGB_TO_HSL(int R, int G, int B); // Converting from RGB to HSl system
vector<int> HSL_To_RGB(float H, float S, float L); // Converting from HSL to RGB system
Image Fast_Resize(Image UserImage1, int width, int height); // Resize Filter
Image Filter1(Image UserImage); // GrayScale
Image Filter2(Image UserImage); // Black and white
Image Filter3(Image UserImage); // Inver Images
Image Filter4(Image UserImage1, Image UserImage2); // Merge Images
Image Filter5(Image UserImage, int Choice); // Flip
Image Filter6(Image UserImage, int Choice); // Rotate
Image Filter7(Image UserImage,int percent); // light and darkness
Image Filter8(Image UserImage,int x, int y, int width, int height); // crop
Image Filter9_simple(Image image, int red, int green, int blue, vector<vector<vector<int>>> padding, int pv); // border simple
Image Filter9_Fancy(Image UserImage, vector<vector<vector<int>>> padding, int pv); // add a fancy border
Image Filter10(Image UsserImage, vector<vector <int>> magnitude); // Edge Detecting
Image Filter12(Image UserImage, int blurRadius); // Blur
Image Filter13(Image  UserImage); // Warm up
Image Filter14(Image UserImage, vector<vector<int>> paddingmatrix, int pv); // oil painting
Image Filter15(Image UserImage); // TV Look
Image Filter16(Image UserImage); // Purple Effect
Image Filter17(Image UserImage); // Red Scale
Image Filter18(Image OriginalImage, int degree); // Skew
Image SopiaTone (Image UserImage); // Bonus Filter
Image Shuffle_Filter( Image& UserImage,int order[4]); // Bonus Filter
Image clardeon_Filter(Image UserImage); // Bonus Filter
Image Green_Scale(Image UserImage); // Bonus Filter
Image Blue_Scale(Image UserImage); // Bonus Filter
QString Filename;
int GlobalSliderValue = 0;
int SliderIndex = 0;
bool loaded = false;
QString AnotherVersionFilename;
Image UserImage;
Image AnotherVersionUserImage;
int GlobalHight = 0;
int GlobalWidth = 0;
int GR = 0,GG = 0,GB = 0;
bool colorloaded = false;
bool CheckFancyBox = false;
int GlobalBorderScale = 0;
int GlobalFlipoption = 0;
int GStartWidth = -1;
int GStartHeight = -1;
int GEndWidth = -1;
int GEndHeight = -1;

bool S1 = false,S2 = false,S3 = false,S4 = false; // Shuffles buttons
int ShuffleOrder[4] = {-1,-1,-1,-1};
int ShuffleOrderCounter = 1;
vector <int> LastOpenedB;
int lastitem = 3;

struct BinGroups{
    int R = 0;
    int G = 0;
    int B = 0;
    int PixelNums = 0;
};

void Dialog::HWidgets(){
    ui->ApplyingFilter->hide();
    ui->SliderBD->hide();
    ui->SliderDD->hide();
    ui->SliderSkew->hide();
    ui->SliderOIL->hide();
    ui->SliderBlur->hide();
    ui->SliderRotate->hide();
    ui->SizeGroup->hide();
    ui->ColorGroup->hide();
    ui->FlipGroup->hide();
    ui->CropGroup->hide();
    ui->ShuffleGroup->hide();
    ui->DegreeSlider->setValue(0);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider_2->setValue(0);
    ui->OilSlider->setValue(0);
    ui->BlurSlide->setValue(0);
    ui->RotateSlide->setValue(1);
    ui->StartHeightL->setReadOnly(true);
    ui->StartWidthL->setReadOnly(true);
    ui->EndHeightL->setReadOnly(true);
    ui->EndWidthL->setReadOnly(true);
    GlobalHight = 0;
    GlobalWidth = 0;
    GlobalSliderValue = 0;
    GR = 0;
    GG = 0;
    GB = 0;
    colorloaded = false;
    ui->Color->setStyleSheet(QString("border: 2px solid black; background: none;"));
    ShuffleOrder[0] = ShuffleOrder[1] = ShuffleOrder[2] = ShuffleOrder[3] = -1;
    ui->Shuffle1->setText("");
    ui->Shuffle2->setText("");
    ui->Shuffle3->setText("");
    ui->Shuffle4->setText("");
    ShuffleOrderCounter = 1;
    LastOpenedB = {};
    lastitem = 3;
    S1 = S2 = S3 = S4 = false;
    ui->Shuffle1->setEnabled(true);
    ui->Shuffle2->setEnabled(true);
    ui->Shuffle3->setEnabled(true);
    ui->Shuffle4->setEnabled(true);
}


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label_2->setStyleSheet("font-weight: bold; background-color: rgba(25, 25, 25, 255); border: 2px solid white; color: white;");
    ui->label_3->setStyleSheet("font-weight: bold; background-color: rgba(25, 25, 25, 255); border: 2px solid white; color: white;");
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->TakeSize->setValidator(new QIntValidator(0,4000,this));
    ui->TakeHight->setValidator(new QIntValidator(0,4000,this));

    HWidgets();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

    HWidgets();
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Image files (*.png *.tga *.jpg *.jpeg *.bmp)");
    Filename = dialog.getOpenFileName();
    if (Filename.isEmpty() and loaded){
        Filename = AnotherVersionFilename;
        UserImage = AnotherVersionUserImage;
    }
    else if (Filename.isEmpty()){
        ui->label_2->setText("Choose Your Image");
        ui->label_2->setFont(QFont("Arial", 14));
        ui->label_2->setStyleSheet("font-weight: bold; background-color: rgba(25, 25, 25, 255); color: white;");
        ui->label_2->setAlignment(Qt::AlignCenter);
    }
    else{
        loaded = UserImage.loadNewImage(Filename.toStdString());
        AnotherVersionUserImage = UserImage;
        AnotherVersionFilename = Filename;
        ui->label_2->setPixmap(Filename);
        ui->label_2->setScaledContents(true);
    }

}


void Dialog::on_GrayScaleFilter_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter1(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}


void Dialog::on_ResetImage_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage.loadNewImage(Filename.toStdString());
        ui->label_3->setText("apply a filter to see the changes");
        ui->label_3->setFont(QFont("Arial", 14));
        ui->label_3->setStyleSheet("font-weight: bold; background-color: rgba(25, 25, 25, 255); color: white;");
        ui->label_3->setAlignment(Qt::AlignCenter);
    }
}


void Dialog::on_SaveImage_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        QString SavedFile = QFileDialog::getSaveFileName();
        string SavedFile_string = SavedFile.toStdString();
        UserImage.saveImage((SavedFile_string+".jpg"));
    }

}

void Dialog::on_BlackWhite_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter2(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_InvertImage_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter3(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_DetectEdges_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        vector<vector<int>> magnitud = magnitudearray(UserImage);
        UserImage = Filter10(UserImage,magnitud);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_Warmup_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter13(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_TvLook_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter15(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_PurpleEffect_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter16(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_RedScale_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Filter17(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_ApplyingFilter_clicked()
{

    if (SliderIndex == 1)
    {
        if (!Filename.isEmpty()){
            UserImage = Filter7(UserImage, GlobalSliderValue);
            GlobalSliderValue = 0;
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 2)
    {
        if (!Filename.isEmpty()){
            UserImage = Filter18(UserImage, GlobalSliderValue);
            GlobalSliderValue = 0;
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 3)
    {
        if (!Filename.isEmpty()){
            vector<vector<int>> padding = Padding(UserImage,GlobalSliderValue);
            UserImage = Filter14(UserImage,padding,GlobalSliderValue);
            GlobalSliderValue = 0;
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 4){
        if (!Filename.isEmpty()){
        UserImage = Filter12(UserImage, GlobalSliderValue);
        GlobalSliderValue = 0;
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 5){
        if (!Filename.isEmpty()){
        UserImage = Filter6(UserImage,GlobalSliderValue);
        GlobalSliderValue = 1;
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 6){
        if (!Filename.isEmpty())
        {
        UserImage.loadNewImage(Filename.toStdString());
        UserImage = Fast_Resize(UserImage,GlobalWidth, GlobalHight);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
       }
    }

    if (SliderIndex == 7 and colorloaded){
        if (!Filename.isEmpty() and !CheckFancyBox){
        UserImage.loadNewImage(Filename.toStdString());
        vector<vector<vector<int>>> padding = Color_Padding(UserImage,GlobalBorderScale);
        UserImage = Filter9_simple(UserImage,GR,GG,GB,padding,GlobalBorderScale);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
        }

        if (!Filename.isEmpty() and CheckFancyBox){
            UserImage.loadNewImage(Filename.toStdString());
            vector<vector<vector<int>>> padding = Color_Padding(UserImage,GlobalBorderScale);
            UserImage = Filter9_simple(UserImage,GR,GG,GB, padding, GlobalBorderScale);
            UserImage = Filter9_Fancy(UserImage, padding, GlobalBorderScale);
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 8){
        if (!Filename.isEmpty() and (ui->HFlip->isChecked() or ui->VFlip->isChecked()) ){
            UserImage = Filter5(UserImage,GlobalFlipoption);
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 9){
        if (!Filename.isEmpty() and GStartWidth!=-1 and GStartHeight!=-1 and GEndWidth!=-1 and GEndHeight!=-1){
            UserImage.loadNewImage(Filename.toStdString());
            UserImage = Filter8(UserImage,GStartWidth,GStartHeight,GEndWidth,GEndHeight);
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

    if (SliderIndex == 10 and ShuffleOrder[0] != -1 and ShuffleOrder[1] != -1 and ShuffleOrder[2] != -1 and ShuffleOrder[3] != -1){
        if (!Filename.isEmpty()){
            UserImage = Shuffle_Filter(UserImage,ShuffleOrder);
            UserImage.saveImage("NewImage.jpg");
            QString newfilename = "NewImage.jpg";
            ui->label_3->setPixmap(newfilename);
            ui->label_3->setScaledContents(true);
        }
    }

}

void Dialog::on_Brightness_clicked()
{
    HWidgets();
    ui->SliderBD->show();
    ui->SliderDD->show();
    ui->ApplyingFilter->show();
    SliderIndex = 1;
}

void Dialog::on_OilPainting_clicked()
{
    HWidgets();
    ui->SliderOIL->show();
    ui->ApplyingFilter->show();
    SliderIndex = 3;
}


void Dialog::on_MergetwoImages_clicked()
{
    HWidgets();
    QString SecondFileName;
    if (!Filename.isEmpty()){
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setNameFilter("Image files (*.png *.tga *.jpg *.jpeg *.bmp)");
        SecondFileName = dialog.getOpenFileName();
    }
    if (!Filename.isEmpty() and !SecondFileName.isEmpty()){
    Image SecondImage(SecondFileName.toStdString());
    UserImage = Filter4(UserImage,SecondImage);
    UserImage.saveImage("NewImage.jpg");
    QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_Skew_clicked()
{
    HWidgets();
    ui->SliderSkew->show();
    ui->ApplyingFilter->show();
    SliderIndex = 2;
}

void Dialog::on_Blur_clicked()
{
    HWidgets();
    ui->SliderBlur->show();
    ui->ApplyingFilter->show();
    SliderIndex = 4;
}

void Dialog::on_Rotate_clicked()
{
    HWidgets();
    ui->SliderRotate->show();
    ui->ApplyingFilter->show();
    GlobalSliderValue = 1;
    SliderIndex = 5;
}

void Dialog::on_Resize_clicked()
{
    HWidgets();

    ui->SizeGroup->show();
    ui->ApplyingFilter->show();
    SliderIndex = 6;
}

void Dialog::on_Frame_clicked()
{
    HWidgets();
    ui->ColorGroup->show();
    ui->ApplyingFilter->show();
    SliderIndex = 7;
}

void Dialog::on_Flip_clicked()
{
    HWidgets();
    ui->FlipGroup->show();
    ui->ApplyingFilter->show();
    SliderIndex = 8;
}

void Dialog::on_Crop_clicked()
{
    HWidgets();
    ui->CropGroup->show();
    ui->ApplyingFilter->show();
    if(loaded){
        ui->StartHeightL->setReadOnly(false);
        ui->StartWidthL->setReadOnly(false);
        ui->EndWidthL->setReadOnly(false);
        ui->EndHeightL->setReadOnly(false);
        ui->StartHeightL->setValidator(new QIntValidator(0,UserImage.height - 1,this));
        ui->StartWidthL->setValidator(new QIntValidator(0,UserImage.width - 1,this));
        ui->EndWidthL->setValidator(new QIntValidator(0,UserImage.width,this));
        ui->EndHeightL->setValidator(new QIntValidator(0,UserImage.height,this));
        ui->label_13->setText(QString::number(UserImage.width));
        ui->label_15->setText(QString::number(UserImage.height));
        SliderIndex = 9;
    }
}

void Dialog::on_SopiaTone_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = SopiaTone(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_clardeon_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = clardeon_Filter(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}


void Dialog::on_Shuffle_clicked()
{
    HWidgets();
    ui->ShuffleGroup->show();
    ui->ApplyingFilter->show();
    SliderIndex = 10;
    if (!Filename.isEmpty()){
        ui->label_3->setPixmap(Filename);
        ui->label_3->setScaledContents(true);
    }
}

void Dialog::on_GreenScale_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Green_Scale(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}


void Dialog::on_BlueScale_clicked()
{
    HWidgets();
    if (!Filename.isEmpty()){
        UserImage = Blue_Scale(UserImage);
        UserImage.saveImage("NewImage.jpg");
        QString newfilename = "NewImage.jpg";
        ui->label_3->setPixmap(newfilename);
        ui->label_3->setScaledContents(true);
    }
}


// => LineInput <=
void Dialog::on_TakeSize_textChanged(const QString &arg1)
{   
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= 4000 and !arg1.isEmpty()){
            string temp;
            temp = arg1.toStdString();
            GlobalWidth = stoi(temp);
        }

        else if (!arg1.isEmpty())
        {
            GlobalWidth = 4000;
        }
    }
}

void Dialog::on_TakeHight_textChanged(const QString &arg1)
{
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= 4000 and !arg1.isEmpty())
        {
            string temp;
            temp = arg1.toStdString();
            GlobalHight = stoi(temp);
        }
        else if (!arg1.isEmpty())
        {
            GlobalHight = 4000;
        }
    }
}

void Dialog::on_StartHeightL_textChanged(const QString &arg1)
{
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= (UserImage.height - 1) and !arg1.isEmpty())
        {
            string temp;
            temp = arg1.toStdString();
            GStartHeight = stoi(temp);
        }
        else if (!arg1.isEmpty()){
            GStartHeight = (UserImage.height - 1);
            ui->StartHeightL->setText(QString::number(UserImage.height-1));
        }
    }
}


void Dialog::on_EndHeightL_textChanged(const QString &arg1)
{
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= UserImage.height  and !arg1.isEmpty())
        {
            string temp;
            temp = arg1.toStdString();
            GEndHeight = stoi(temp);
        }
        else if (!arg1.isEmpty()){
            GEndHeight = UserImage.height;
            ui->EndHeightL->setText(QString::number(UserImage.height));
        }
    }
}


void Dialog::on_StartWidthL_textChanged(const QString &arg1)
{
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= (UserImage.width - 1) and !arg1.isEmpty())
        {
            string temp;
            temp = arg1.toStdString();
            GStartWidth = stoi(temp);
        }
        else if (!arg1.isEmpty()){
            GStartWidth = (UserImage.width - 1);
            ui->StartWidthL->setText(QString::number(UserImage.width-1));
        }
    }
}


void Dialog::on_EndWidthL_textChanged(const QString &arg1)
{
    if (!Filename.isEmpty())
    {
        if (0 <= arg1.toInt() and arg1.toInt() <= UserImage.width and !arg1.isEmpty())
        {
            string temp;
            temp = arg1.toStdString();
            GEndWidth = stoi(temp);
        }
        else if (!arg1.isEmpty()){
            GEndWidth = UserImage.width;
            ui->EndWidthL->setText(QString::number(UserImage.width));
        }
    }
}


// => Sliders <=

void Dialog::on_horizontalSlider_sliderMoved(int position)
{
    GlobalSliderValue = position;
}

void Dialog::on_horizontalSlider_2_sliderMoved(int position)
{
    GlobalSliderValue = -position;
}


void Dialog::on_DegreeSlider_sliderMoved(int position)
{
    GlobalSliderValue = position;
}

void Dialog::on_OilSlider_sliderMoved(int position)
{
    GlobalSliderValue = position;
}

void Dialog::on_BlurSlide_sliderMoved(int position)
{
    GlobalSliderValue = position;
}

void Dialog::on_RotateSlide_sliderMoved(int position)
{
    GlobalSliderValue = position;
}

void Dialog::on_BorderSlide_sliderMoved(int position)
{
    GlobalBorderScale = position;
}

// => color label setter <=
void Dialog::Colorsetter(int &R, int &G, int &B){
    ui->Color->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(R).arg(G).arg(B));
    GR = R;
    GG = G;
    GB = B;
    colorloaded = true;
}

void Dialog::on_ChoosingColor_clicked()
{
    ColorsW cw;
    connect(&cw,&ColorsW::RGBcolorsSent,this, &Dialog::Colorsetter);
    cw.setModal(true);
    cw.exec();
}


// => Check Box <=

void Dialog::on_FancyCheckBox_toggled(bool checked)
{
    CheckFancyBox = checked;
}


void Dialog::on_HFlip_toggled(bool checked)
{
    if(ui->HFlip->isChecked()){
        ui->VFlip->setChecked(false);
    }
    GlobalFlipoption = 1;
}


void Dialog::on_VFlip_toggled(bool checked)
{
    if(ui->VFlip->isChecked()){
        ui->HFlip->setChecked(false);
    }
    GlobalFlipoption = 2;
}

// ==> Shuffle Buttons <==


void Dialog::on_Shuffle1_clicked()
{
    if (S1){
        ShuffleOrderCounter--;
        ui->Shuffle1->setText("");
        ShuffleOrder[0] = -1;
        if (LastOpenedB[lastitem-1] == 4){
            ui->Shuffle4->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 3){
            ui->Shuffle3->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 2){
            ui->Shuffle2->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else{
            LastOpenedB.pop_back();
        }
        S1 = false;
    }
    else{
        ui->Shuffle1->setText(QString::number(ShuffleOrderCounter));
        ui->Shuffle1->setFont(QFont("Arial", 14));
        ShuffleOrder[0] = ShuffleOrderCounter;
        ShuffleOrderCounter++;
        if (S4){
            ui->Shuffle4->setEnabled(false);
        }
        if (S3){
            ui->Shuffle3->setEnabled(false);
        }
        if (S2){
            ui->Shuffle2->setEnabled(false);
        }
        S1 = true;
        for (int i = 0 ; i < 4 ; i++){
            if (ShuffleOrder[i] == ShuffleOrderCounter - 1){
                if (i == 0){
                    LastOpenedB.push_back(1);
                    break;
                }
                LastOpenedB.push_back(i+1);
                if (lastitem < 3){
                    lastitem++;
                }
            }
        }
    }
}


void Dialog::on_Shuffle2_clicked()
{
    if (S2){
        ShuffleOrderCounter--;
        ui->Shuffle2->setText("");
        ShuffleOrder[1] = -1;
        if (LastOpenedB[lastitem-1] == 4){
            ui->Shuffle4->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 3){
            ui->Shuffle3->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 1){
            ui->Shuffle1->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else{
            LastOpenedB.pop_back();
        }

        S2 = false;
    }
    else{
        ui->Shuffle2->setText(QString::number(ShuffleOrderCounter));
        ui->Shuffle2->setFont(QFont("Arial", 14));
        ShuffleOrder[1] = ShuffleOrderCounter;
        ShuffleOrderCounter++;
        if (S4){
            ui->Shuffle4->setEnabled(false);
        }
        if (S3){
            ui->Shuffle3->setEnabled(false);
        }
        if (S1){
            ui->Shuffle1->setEnabled(false);
        }
        S2 = true;
        for (int i = 0 ; i < 4 ; i++){
            if (ShuffleOrder[i] == ShuffleOrderCounter - 1){
                if (i == 0){
                    LastOpenedB.push_back(2);
                    break;
                }
                LastOpenedB.push_back(i+1);
                if (lastitem < 3){
                    lastitem++;
                }
            }
        }
    }
}


void Dialog::on_Shuffle3_clicked()
{
    if (S3){
        ShuffleOrderCounter--;
        ui->Shuffle3->setText("");
        ShuffleOrder[2] = -1;
        if (LastOpenedB[lastitem-1] == 4){
            ui->Shuffle4->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 2){
            ui->Shuffle2->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 1){
            ui->Shuffle1->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else{
            LastOpenedB.pop_back();
        }
        S3 = false;
    }
    else{
        ui->Shuffle3->setText(QString::number(ShuffleOrderCounter));
        ui->Shuffle3->setFont(QFont("Arial", 14));
        ShuffleOrder[2] = ShuffleOrderCounter;
        ShuffleOrderCounter++;
        if (S4){
            ui->Shuffle4->setEnabled(false);
        }
        if (S2){
            ui->Shuffle2->setEnabled(false);
        }
        if (S1){
            ui->Shuffle1->setEnabled(false);
        }
        S3 = true;
        for (int i = 0 ; i < 4 ; i++){
            if (ShuffleOrder[i] == ShuffleOrderCounter - 1){
                if (i == 0){
                    LastOpenedB.push_back(3);
                    break;
                }
                LastOpenedB.push_back(i+1);
                if (lastitem < 3){
                    lastitem++;
                }
            }
        }
    }
}


void Dialog::on_Shuffle4_clicked()
{
    if (S4){
        ShuffleOrderCounter--;
        ui->Shuffle4->setText("");
        ShuffleOrder[3] = -1;
        if (LastOpenedB[lastitem-1] == 3){
            ui->Shuffle3->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 2){
            ui->Shuffle2->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else if (LastOpenedB[lastitem-1] == 1){
            ui->Shuffle1->setEnabled(true);
            LastOpenedB.pop_back();
            lastitem--;
        }
        else{
            LastOpenedB.pop_back();
        }
        S4 = false;
    }
    else{
        ui->Shuffle4->setText(QString::number(ShuffleOrderCounter));
        ui->Shuffle4->setFont(QFont("Arial", 14));
        ShuffleOrder[3] = ShuffleOrderCounter;
        ShuffleOrderCounter++;
        if (S3){
            ui->Shuffle3->setEnabled(false);
        }
        if (S2){
            ui->Shuffle2->setEnabled(false);
        }
        if (S1){
            ui->Shuffle1->setEnabled(false);
        }
        S4 = true;
        for (int i = 0 ; i < 4 ; i++){
            if (ShuffleOrder[i] == ShuffleOrderCounter - 1){
                if (i == 0){
                    LastOpenedB.push_back(4);
                    break;
                }
                LastOpenedB.push_back(i+1);
                if (lastitem < 3){
                    lastitem++;
                }
            }
        }
    }
}





// ======================================================================
// =================================Filters==============================
// ======================================================================

// The following function is using convolution method for edge detecting
// the summary of the method is that i have 2 matrix which are vertical kernel and horizontalkernel
// for each pixel in the image i take the values of it and each pixel around it and multiply it by the kernels
// i do a pythagoras to the result and assign it to the mad variable
// if the mag is bigger than the threshold (which is a factor that i decide)
// that means this pixel is a edge pixel
// i make the value 0 for black borders , if its not bigger than the threshold i assign it to 255
// then i add the value to the 2d vector
vector <vector <int>> magnitudearray(Image Userimage) {
    vector<vector<int>> magnitude(Userimage.width, vector<int>(Userimage.height));
    int vecticalkernel [3][3] = {{1,2,1},
                         {0,0,0},
                         {-1,-2,-1}};
    int horizontalkernel [3][3]={{-1,0,1},
                         {-2,0,2},
                         {-1,0, 1}};
    for (int i = 0; i < Userimage.width; i++) {
        for (int j = 0; j < Userimage.height; j++) {
            int Vkernelvalue = 0;
            int Hkernelvalue = 0;
            int mag = 0;

            if (i == 0 && j == 0) {
                // Handle top-left corner
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i + 1, j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i, j + 1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * vecticalkernel[2][2]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i + 1, j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i, j + 1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * horizontalkernel[2][2]);

            } else if (i == 0 && j == Userimage.height - 1) {
                // Handle top-right corner
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i + 1, j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i, j - 1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * vecticalkernel[2][0]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i + 1, j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i, j - 1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * horizontalkernel[2][0]);
            } else if (i == Userimage.width - 1 && j == 0) {
                // Handle bottom-left corner
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i, j + 1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * vecticalkernel[0][2]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i, j + 1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * horizontalkernel[0][2]);
            } else if (i == Userimage.width - 1 && j == Userimage.height - 1) {
                // Handle bottom-right corner
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i, j - 1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * vecticalkernel[0][0]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i, j - 1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * horizontalkernel[0][0]);
            } else if (i == 0) {
                // Handle top row
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i, j - 1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i, j + 1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * vecticalkernel[2][0] +
                                 Userimage.getPixel(i + 1, j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * vecticalkernel[2][2]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i, j - 1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i, j + 1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * horizontalkernel[2][0] +
                                 Userimage.getPixel(i + 1, j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * horizontalkernel[2][2]);
            } else if (j == 0) {
                // Handle left column
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i + 1, j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * vecticalkernel[0][2] +
                                 Userimage.getPixel(i, j + 1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * vecticalkernel[2][2]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i + 1, j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * horizontalkernel[0][2] +
                                 Userimage.getPixel(i, j + 1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i + 1, j + 1, 0) * horizontalkernel[2][2]);
            } else if (i == Userimage.width - 1) {
                // Handle bottom row
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i, j - 1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i, j + 1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * vecticalkernel[0][0] +
                                 Userimage.getPixel(i - 1, j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * vecticalkernel[0][2]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i, j - 1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i, j + 1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * horizontalkernel[0][0] +
                                 Userimage.getPixel(i - 1, j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i - 1, j + 1, 0) * horizontalkernel[0][2]);
            } else if (j == Userimage.height - 1) {
                // Handle right column
                Vkernelvalue += (Userimage.getPixel(i, j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i + 1, j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * vecticalkernel[0][0] +
                                 Userimage.getPixel(i, j - 1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * vecticalkernel[2][0]);
                Hkernelvalue += (Userimage.getPixel(i, j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i - 1, j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i + 1, j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i - 1, j - 1, 0) * horizontalkernel[0][0] +
                                 Userimage.getPixel(i, j - 1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i + 1, j - 1, 0) * horizontalkernel[2][0]);
            }
            else{
                Vkernelvalue += (Userimage.getPixel(i,j, 0) * vecticalkernel[1][1] +
                                 Userimage.getPixel(i-1,j-1, 0) * vecticalkernel[0][0] +
                                 Userimage.getPixel(i-1,j, 0) * vecticalkernel[0][1] +
                                 Userimage.getPixel(i-1,j+1, 0) * vecticalkernel[0][2] +
                                 Userimage.getPixel(i,j-1, 0) * vecticalkernel[1][0] +
                                 Userimage.getPixel(i,j+1, 0) * vecticalkernel[1][2] +
                                 Userimage.getPixel(i+1,j-1, 0) * vecticalkernel[2][0] +
                                 Userimage.getPixel(i+1,j, 0) * vecticalkernel[2][1] +
                                 Userimage.getPixel(i+1,j+1, 0) * vecticalkernel[2][2]);
                Hkernelvalue += (Userimage.getPixel(i,j, 0) * horizontalkernel[1][1] +
                                 Userimage.getPixel(i-1,j-1, 0) * horizontalkernel[0][0] +
                                 Userimage.getPixel(i-1,j, 0) * horizontalkernel[0][1] +
                                 Userimage.getPixel(i-1,j+1, 0) * horizontalkernel[0][2] +
                                 Userimage.getPixel(i,j-1, 0) * horizontalkernel[1][0] +
                                 Userimage.getPixel(i,j+1, 0) * horizontalkernel[1][2] +
                                 Userimage.getPixel(i+1,j-1, 0) * horizontalkernel[2][0] +
                                 Userimage.getPixel(i+1,j, 0) * horizontalkernel[2][1] +
                                 Userimage.getPixel(i+1,j+1, 0) * horizontalkernel[2][2]);
            }

            mag = sqrt(pow(Vkernelvalue,2)+pow(Hkernelvalue, 2));
            if (mag > 120){
                mag = 0;
            }
            else{
                mag = 255;
            }
            magnitude[i][j] = mag;
        }
    }
    return magnitude;
}

vector <float> RGB_TO_HSL(int R, int G, int B){
    float S,H,L;
    float delta = 0;
    float Rratio = (float) R/255;
    float Gratio = (float) G/255;
    float Bratio = (float) B/255;


    float min = std::min( std::min(Rratio,Gratio),Bratio );
    float max = std::max(std::max(Rratio,Gratio), Bratio);

    L = (max+min)/2;

    if (max == min){
        H = 0;
        S = 0;
    }
    else{
        delta = max - min;
        if (L > 0.5){
            S = delta / (2-max-min);
        }
        else{
            S = delta / (max+min);
        }

        if (max == Rratio){
            H = (Gratio - Bratio) / delta;
        }
        if (max == Gratio){
            H = 2 + (Bratio - Rratio) / delta;
        }
        if (max == Bratio){
            H = 4 + (Rratio - Gratio) / delta;
        }
        H *=60;
        if (0>H){
            H +=360;
        }
    }

    return {H,S,L};


}

vector<int> HSL_To_RGB(float H, float S, float L){
    float C = (1.0f - std::abs(2.0f * L - 1.0f)) * S;
    float X = C * (1.0f - std::abs(std::fmod(H / 60.0f, 2.0f) - 1.0f));
    float m = L - C / 2.0f;

    float R, G, B;

    if (H >= 0 && H < 60) {
        R = C; G = X; B = 0;
    } else if (H >= 60 && H < 120) {
        R = X; G = C; B = 0;
    } else if (H >= 120 && H < 180) {
        R = 0; G = C; B = X;
    } else if (H >= 180 && H < 240) {
        R = 0; G = X; B = C;
    } else if (H >= 240 && H < 300) {
        R = X; G = 0; B = C;
    } else { // H >= 300 && H < 360
        R = C; G = 0; B = X;
    }

    int RF = static_cast<int>((R + m) * 255);
    int GF = static_cast<int>((G + m) * 255);
    int BF = static_cast<int>((B + m) * 255);

    return {RF, GF, BF};
}

float gaussian_noise(float mean, float stddev) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<float> distribution(mean, stddev);
    return distribution(gen);
}


vector < vector < int >> Padding(Image UserImage, int pv) { // 0 padding
    unsigned RedValue;
    unsigned GreenValue;
    unsigned BlueValue;
    int GrayScale;
    // final padding matrix for the image
    vector < vector < int >> paddingmatrix(UserImage.width + pv, vector < int > (UserImage.height + pv,0));
    Image smallerimage = Fast_Resize(UserImage,UserImage.width-pv,UserImage.height-pv);
    for (int i = pv; i < UserImage.width ; i++) {
        for (int j = pv; j < UserImage.height ; j++) {


            RedValue = smallerimage.getPixel(i-pv, j-pv, 0);
            GreenValue = smallerimage.getPixel(i-pv, j-pv, 1);
            BlueValue = smallerimage.getPixel(i-pv, j-pv, 2);
            // applying an equation to get the grayscale value
            GrayScale = (0.299 * RedValue) + (0.587 * GreenValue) + (0.114 * BlueValue);
            paddingmatrix[i][j] = GrayScale;
        }
    }
    return paddingmatrix;
}

vector < vector < vector <int> >> Color_Padding(Image UserImage, int pv) { // 0 padding
    // final padding matrix for the image
    double borderratio = 0.02;
    int BorderScaleRatio = max(UserImage.width,UserImage.height) * borderratio;
    BorderScaleRatio +=pv;
    vector < vector < vector <int> >> paddingmatrix(UserImage.width + BorderScaleRatio, vector < vector<int> > (UserImage.height + BorderScaleRatio, vector<int>(3,0)));
    Image smallerimage = Fast_Resize(UserImage,UserImage.width-BorderScaleRatio,UserImage.height-BorderScaleRatio);
    for (int i = BorderScaleRatio; i < UserImage.width ; i++) {
        for (int j = BorderScaleRatio; j < UserImage.height ; j++) {

            // applying 0 padding to the corners
            for(int k = 0 ; k < 3 ; k++){
                paddingmatrix[i][j][k] = smallerimage.getPixel(i-BorderScaleRatio,j-BorderScaleRatio,k);
            }

        }
    }
    return paddingmatrix;
}


Image Fast_Resize(Image UserImage1, int width, int height){
    Image Newimage(width, height);
    unsigned P1,P2,P3,P4;
    float px,py;
    int x1_f,y1_f,x2_c,y2_c;
    float dx,dy;
    unsigned BL;
    float SFX = (float) UserImage1.width/Newimage.width; // scaling factor X
    float SFY = (float) UserImage1.height/Newimage.height; // scaling factor Y

    for (int i = 0; i < width ; i++){
        for (int j = 0 ; j < height ; j++){
            for(int k = 0 ; k < 3 ; k++){
                px = SFX * float(i);
                py = SFY * float(j);

                x1_f = (int) px;
                y1_f = (int) py;
                x2_c = px + 1;
                y2_c = py + 1;

                x1_f = min(max(x1_f , 0) , UserImage1.width - 1);
                y1_f = min(max(y1_f, 0) , UserImage1.height - 1);
                x2_c = min(max(x2_c , 0) , UserImage1.width - 1);
                y2_c = min(max(y2_c , 0) , UserImage1.height - 1);

                dx = px - float(x1_f);
                dy = py - float(y1_f);

                P1 = UserImage1.getPixel(x1_f, y1_f,k);
                P2 = UserImage1.getPixel(x1_f,y2_c,k);
                P3 = UserImage1.getPixel(x2_c,y1_f,k);
                P4 = UserImage1.getPixel(x2_c,y2_c,k);

                BL = (1-dx)*(1-dy)*P1 + dx*(1-dy)*P3 + dy*(1-dx)*P2 + dx*dy*P4;

                Newimage(i,j,k) = BL;
            }
        }
    }
    return Newimage;
}


Image Filter1(Image UserImage){ // GrayScale Filter
    unsigned RedValue;
    unsigned GreenValue;
    unsigned BlueValue;
    unsigned GrayScale;
    for (int i = 0; i < UserImage.width ; i++){
        for (int j = 0 ; j < UserImage.height ; j++){
            RedValue = UserImage.getPixel(i,j,0);
            GreenValue = UserImage.getPixel(i,j,1);
            BlueValue = UserImage.getPixel(i, j, 2);
            // applying an equation for getting the grayscale value
            GrayScale = (0.299 * RedValue) + (0.587 * GreenValue) + (0.114 * BlueValue);
            UserImage.setPixel(i,j,0,GrayScale);
            UserImage.setPixel(i,j,1,GrayScale);
            UserImage.setPixel(i,j,2,GrayScale);
        }
    }
    return UserImage;
}

Image Filter2(Image UserImage){ // Black and White
    unsigned int grayThreshold = 128;

    for (int i = 0; i < UserImage.width; ++i) {
        for (int j = 0; j < UserImage.height; ++j) {

            unsigned avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += UserImage(i, j, k);

            }
            avg /= 3;
            if (avg < grayThreshold) {
                for (int k = 0; k < 3; ++k) {
                    UserImage(i, j, k) = 0;
                }
            } else {
                for (int k = 0; k < 3; ++k) {
                    UserImage(i, j, k) = 255;
                }
            }
        }
    }
    return UserImage;
}



Image Filter3(Image UserImage) { // Invert Images
    for (int i = 0; i < UserImage.width; i++) {
        for (int j = 0; j < UserImage.height; j++) {
            unsigned RedValue = UserImage.getPixel(i, j, 0);
            unsigned GreenValue = UserImage.getPixel(i, j, 1);
            unsigned BlueValue = UserImage.getPixel(i, j, 2);

            unsigned InvertedRed = 255 - RedValue;
            unsigned InvertedGreen = 255 - GreenValue;
            unsigned InvertedBlue = 255 - BlueValue;

            UserImage.setPixel(i, j, 0, InvertedRed);
            UserImage.setPixel(i, j, 1, InvertedGreen);
            UserImage.setPixel(i, j, 2, InvertedBlue);
        }
    }

    return UserImage;
}

Image Filter4(Image UserImage1, Image UserImage2){ // Merge filter
    unsigned R1,G1,B1;
    unsigned R2,G2,B2;
    unsigned CR,CG,CB;
    // Resizing the Images to Make them both same size
    if (UserImage1.width < UserImage2.width or UserImage1.height < UserImage2.height){
        UserImage1 = Fast_Resize(UserImage1, UserImage2.width, UserImage2.height);
    }
    if (UserImage1.width > UserImage2.width or UserImage1.height > UserImage2.height){
        UserImage2 = Fast_Resize(UserImage2, UserImage1.width, UserImage1.height);
    }

    for (int i = 0 ; i < UserImage1.width ; i++){
        for (int j = 0 ; j < UserImage1.height ; j++) {
            R1 = UserImage1.getPixel(i, j, 0);
            R2 = UserImage2.getPixel(i, j, 0);
            G1 = UserImage1.getPixel(i, j, 1);
            G2 = UserImage2.getPixel(i, j, 1);
            B1 = UserImage1.getPixel(i, j, 2);
            B2 = UserImage2.getPixel(i, j, 2);

            // Getting the average of each color
            CR = (R1+R2)/2;
            CG = (G1+G2)/2;
            CB = (B1+B2)/2;

            // ensuring it's not more than 255
            if (CR > 255){
                CR = 255;
            }
            if (CG > 255){
                CG = 255;
            }
            if (CB > 255){
                CB = 255;
            }

            UserImage1.setPixel(i, j, 0, CR);
            UserImage1.setPixel(i, j, 1, CG);
            UserImage1.setPixel(i, j, 2, CB);
        }
    }
    return UserImage1;
}

Image Filter5(Image UserImage, int Choice) {
    if (Choice == 1) {

        auto HorizontalFlip = [ & UserImage]() {
            int width = UserImage.width;
            int height = UserImage.height;
            for (int j = 0; j < height; ++j) {
                for (int i = 0; i < width / 2; ++i) {
                    for (int k = 0; k < 3; ++k) {

                        unsigned int tempPixel = UserImage(i, j, k);
                        UserImage(i, j, k) = UserImage(width - i - 1, j, k);
                        UserImage(width - i - 1, j, k) = tempPixel;
                    }
                }

            }

        };
        HorizontalFlip();
    }

    if (Choice == 2) {
        auto verticalFlip = [ & UserImage]() {
            int width = UserImage.width;
            int height = UserImage.height;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height / 2; ++j) {
                    for (int k = 0; k < 3; ++k) {

                        unsigned int tempPixel = UserImage(i, j, k);
                        UserImage(i, j, k) = UserImage(i, height - j - 1, k);
                        UserImage(i, height - j - 1, k) = tempPixel;
                    }
                }
            }
        };
        verticalFlip();
    }
    return UserImage;
}

Image Filter6(Image UserImage, int Choice) {
    Image rotatedImage(UserImage.height, UserImage.width);
    if (Choice == 1) {
        for (int i = 0; i < UserImage.width; ++i) {
            for (int j = 0; j < UserImage.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotatedImage(j, i, k) = UserImage(i, j, k);
                }
            }
        }
    }
    if (Choice == 2) {
        rotatedImage.width = UserImage.width;
        rotatedImage.height = UserImage.height;
        for (int i = 0; i < UserImage.width; ++i) {
            for (int j = 0; j < UserImage.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Swap the width and height indices and reverse the row index
                    rotatedImage(UserImage.width - i - 1, UserImage.height - j - 1, k) = UserImage(i, j, k);
                }
            }
        }
    }
    if (Choice == 3) {
        for (int i = 0; i < UserImage.width; ++i) {
            for (int j = 0; j < UserImage.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Swap the width and height indices and reverse the column index
                    rotatedImage(UserImage.height - j - 1, i, k) = UserImage(i, j, k);
                }
            }
        }
    }
    return rotatedImage;
}

Image Filter7(Image UserImage, int percent){ // Darken or Lighter Filter
    // ======================================================
    // applying the filter
    float factor = (float) percent / 100;
    unsigned R,G,B;
    for(int i = 0 ; i < UserImage.width ; i ++){
        for (int j = 0 ; j < UserImage.height ; j++){
            R = UserImage.getPixel(i, j, 0);
            G = UserImage.getPixel(i, j, 1);
            B = UserImage.getPixel(i, j, 2);

            // applying changes to the colors values
            R += (R * factor);
            G += (G * factor);
            B += (B * factor);

            // Ensure the values stays in the range
            if (R>255){
                R = 255;
            }
            if (G>255){
                G = 255;
            }
            if (B>255){
                B = 255;
            }

            UserImage.setPixel(i, j , 0, R);
            UserImage.setPixel(i, j, 1, G);
            UserImage.setPixel(i, j, 2, B);

        }
    }
    return UserImage;
}


Image Filter8(Image UserImage,int x, int y, int width, int height) {

    if (x + width > UserImage.width){

    }

    Image croppedImage(width-x, height-x);




    for (int i = x; i < width; ++i) {
        for (int j = y; j < height; ++j) {

            unsigned int redValue = UserImage.getPixel( i,  j, 0);
            unsigned int greenValue = UserImage.getPixel( i,  j, 1);
            unsigned int blueValue = UserImage.getPixel( i,  j, 2);

            croppedImage.setPixel(i-x, j-y, 0, redValue);
            croppedImage.setPixel(i-x, j-y, 1, greenValue);
            croppedImage.setPixel(i-x, j-y, 2, blueValue);
        }
    }

    return croppedImage;
}


Image Filter9_simple(Image image, int red, int green, int blue, vector<vector<vector<int>>> padding,int pv){
    double borderratio =  0.02;
    int BorderScaleRatio = max(image.width,image.height) * borderratio;
    BorderScaleRatio +=pv;
    Image NewImage(image.width+BorderScaleRatio,image.height+BorderScaleRatio);
    for(int i = 0 ; i < NewImage.width ; i++){
        for (int j = 0 ; j < NewImage.height ; j++){
            for(int k = 0 ; k < 3 ; k++){
                NewImage.setPixel(i,j,k,padding[i][j][k]);
            }
        }
    }
    // Top Frame
    for (int i = 0; i < NewImage.width; ++i) {
        for (int j = 0; j < BorderScaleRatio ; ++j) {
            NewImage.setPixel(i, j, 0, red);
            NewImage.setPixel(i, j, 1, green);
            NewImage.setPixel(i, j, 2, blue);
        }
    }
    // Left Frame
    for (int i = 0; i < BorderScaleRatio ; ++i) {
        for (int j = 0; j < NewImage.height; ++j) {
            NewImage.setPixel(i, j, 0, red);
            NewImage.setPixel(i, j, 1, green);
            NewImage.setPixel(i, j, 2, blue);
        }
    }
    // Right Frame
    for (int i = NewImage.width - BorderScaleRatio ; i < NewImage.width; ++i) {
        for (int j = 0; j < NewImage.height; ++j) {
            NewImage.setPixel(i, j, 0, red);
            NewImage.setPixel(i, j, 1, green);
            NewImage.setPixel(i, j, 2, blue);
        }
    }
    // Bottom Frame
    for (int i = 0; i < NewImage.width; ++i) {
        for (int j = NewImage.height - BorderScaleRatio ; j < NewImage.height; ++j) {
            NewImage.setPixel(i, j, 0, red);
            NewImage.setPixel(i, j, 1, green);
            NewImage.setPixel(i, j, 2, blue);
        }
    }

    return NewImage;
}

Image Filter9_Fancy(Image image, vector<vector<vector<int>>> padding,int pv) {
    unsigned red, green, blue;
    red = 230;
    green = 230;
    blue = 230;
    double borderratio =  0.02;
    int BorderScaleRatio = max(image.width,image.height) * borderratio;
    BorderScaleRatio +=pv;
    int FancyRatio = pv;

    // Top Frame
    for (int i = BorderScaleRatio; i < image.width - BorderScaleRatio; ++i) {
        for (int j = BorderScaleRatio; j < BorderScaleRatio + FancyRatio + 6; ++j) {
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
            for (int x = BorderScaleRatio + FancyRatio + 16; x < image.width - (BorderScaleRatio + FancyRatio + 16); ++x) {
                for (int y = BorderScaleRatio + FancyRatio + 16; y < (BorderScaleRatio + FancyRatio + 22); ++y) {
                    image.setPixel(x, y, 0, red);
                    image.setPixel(x, y, 1, green);
                    image.setPixel(x, y, 2, blue);
                }
            }
        }
    }
    // Left Frame
    for (int i = BorderScaleRatio; i < (BorderScaleRatio + FancyRatio +6); ++i) {
        for (int j = BorderScaleRatio; j < image.height - BorderScaleRatio; ++j) {
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
            for (int x = BorderScaleRatio + FancyRatio + 16; x < BorderScaleRatio + FancyRatio + 22; ++x) {
                for (int y = BorderScaleRatio + FancyRatio + 22; y < image.height - (BorderScaleRatio + FancyRatio + 22); ++y) {
                    image.setPixel(x, y, 0, red);
                    image.setPixel(x, y, 1, green);
                    image.setPixel(x, y, 2, blue);
                }
            }
        }
    }
    // Right Frame
    for (int i = image.width - (BorderScaleRatio + FancyRatio +6); i < image.width - BorderScaleRatio; ++i) {
        for (int j = BorderScaleRatio; j < image.height - BorderScaleRatio; ++j) {
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
            for (int x = image.width - (BorderScaleRatio + FancyRatio + 22); x < image.width - (BorderScaleRatio + FancyRatio + 16); ++x) {
                for (int y = BorderScaleRatio + FancyRatio + 22; y < image.height - (BorderScaleRatio + FancyRatio + 22); ++y) {
                    image.setPixel(x, y, 0, red);
                    image.setPixel(x, y, 1, green);
                    image.setPixel(x, y, 2, blue);
                }
            }
        }
    }
    // Bottom Frame
    for (int i = BorderScaleRatio; i < image.width - BorderScaleRatio; ++i) {
        for (int j = image.height - (BorderScaleRatio + FancyRatio +6); j < image.height - BorderScaleRatio; ++j) {
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
            for (int x = BorderScaleRatio +FancyRatio+ 16; x < image.width - (BorderScaleRatio +FancyRatio+ 16); ++x) {
                for (int y = image.height - (BorderScaleRatio +FancyRatio+ 22); y < image.height - (BorderScaleRatio +FancyRatio+ 16); ++y) {
                    image.setPixel(x, y, 0, red);
                    image.setPixel(x, y, 1, green);
                    image.setPixel(x, y, 2, blue);
                }
            }
        }
    }

    return image;
}


Image Filter10(Image UsserImage, vector<vector <int>> magnitude){ // Edge Detecting Filter
    for(int i = 0 ; i < UsserImage.width ; i++){
        for(int j = 0 ; j < UsserImage.height ; j++){
            for(int k = 0 ; k < 3 ; k++){
                UsserImage.setPixel(i, j, k, magnitude[i][j]);
            }
        }
    }
    return UsserImage;
}

Image Filter12(Image UserImage, int blurRadius){
    Image blurredImage(UserImage.width, UserImage.height); // Create a new image to store the blurred result

    for (int i = 0; i < UserImage.width; ++i) {
        for (int j = 0; j < UserImage.height; ++j) {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            int validPixels = 0;

            for (int di = -blurRadius; di <= blurRadius; ++di) {
                for (int dj = -blurRadius; dj <= blurRadius; ++dj) {
                    int bluri = i + di;
                    int blurj = j + dj;

                    if (bluri >= 0 && bluri < UserImage.width && blurj >= 0 && blurj < UserImage.height) {
                        totalRed += UserImage.getPixel(bluri, blurj, 0);
                        totalGreen += UserImage.getPixel(bluri, blurj, 1);
                        totalBlue += UserImage.getPixel(bluri, blurj, 2);
                        validPixels++;
                    }
                }
            }

            unsigned char averageRed = static_cast<unsigned char>(totalRed / validPixels);
            unsigned char averageGreen = static_cast<unsigned char>(totalGreen / validPixels);
            unsigned char averageBlue = static_cast<unsigned char>(totalBlue / validPixels);

            blurredImage.setPixel(i, j, 0, averageRed);
            blurredImage.setPixel(i, j, 1, averageGreen);
            blurredImage.setPixel(i, j, 2, averageBlue);
        }
    }
    return blurredImage;
}

Image Filter13(Image  UserImage){
    float H,S,L;
    unsigned R,G,B;
    for(int i = 0 ; i < UserImage.width ; i++){
        for (int j = 0 ; j < UserImage.height ; j++){
            R = UserImage.getPixel(i, j, 0);
            G = UserImage.getPixel(i, j, 1);
            B = UserImage.getPixel(i, j, 2);

            // changing from RGB system to HSL system
            H = RGB_TO_HSL(R, G, B)[0];
            S = RGB_TO_HSL(R, G, B)[1];
            L = RGB_TO_HSL(R, G, B)[2];

            // editing the saturation to get the warmup effect
            S = max(0.0f,min(1.0f, S + 0.16f));

            // converting back to RGB system after applying changes
            R = HSL_To_RGB(H,S,L)[0];
            G = HSL_To_RGB(H,S,L)[1];
            B = HSL_To_RGB(H,S,L)[2];

            UserImage.setPixel(i, j, 0, R);
            UserImage.setPixel(i, j, 1, G);
            UserImage.setPixel(i, j, 2, B);

        }
    }

    for (int i = 0 ; i < UserImage.width ; i ++){
        for (int j = 0 ; j <UserImage.height ; j ++){
            R = UserImage.getPixel(i,j,0);
            G = UserImage.getPixel(i,j,1);
            B = UserImage.getPixel(i,j,2);
            B *=0.812; // decreasing the blue effect in the image
            UserImage.setPixel(i,j,0,R);
            UserImage.setPixel(i,j,1,G);
            UserImage.setPixel(i,j,2,B);
        }
    }

    return UserImage;
}

Image Filter14(Image UserImage, vector<vector<int>> paddingmatrix, int pv){
    // creating 20 class to classify each pixel
    BinGroups Bin1,Bin2,Bin3,Bin4,Bin5, Bin6, Bin7, Bin8, Bin9, Bin10;
    BinGroups Bin11,Bin12,Bin13,Bin14,Bin15, Bin16, Bin17, Bin18, Bin19, Bin20;
    BinGroups Bins[20] = {Bin1,Bin2,Bin3,Bin4,Bin5,
                          Bin6, Bin7, Bin8, Bin9, Bin10,
                          Bin11,Bin12,Bin13,Bin14,Bin15,
                          Bin16, Bin17, Bin18, Bin19, Bin20};

    float lowerbound = 0;
    float upperbound = 12.75;
    int maxbins,maxbinsindex,finalpixelR,finalpixelG,finalpixelB;
    int GrayScale;

    Image NewImage(UserImage.width,UserImage.height);
    for(int i = pv ; i < UserImage.width ; i ++) {
        for (int j = pv; j < UserImage.height; j++) {
            // adding each pixel in the kernel matrix to its group
            for (int k = i-pv; k <= i + pv; k++) {
                for (int l = j-pv; l <= j + pv; l++) {
                    GrayScale = paddingmatrix[k][l];
                    for (int m = 0; m < 20; m++) { // adding pixels values to its proper group
                        if ((int) lowerbound < GrayScale and GrayScale <= (int) upperbound) {
                            Bins[m].R += UserImage.getPixel(k, l, 0);
                            Bins[m].G += UserImage.getPixel(k, l, 1);
                            Bins[m].B += UserImage.getPixel(k, l, 2);
                            Bins[m].PixelNums += 1;
                            break;
                        }
                        lowerbound += 12.75;
                        upperbound += 12.75;
                    }
                    lowerbound = 0;
                    upperbound = 12.75;
                }
            }
            // getting the highest members group
            maxbins = Bins[0].PixelNums;
            maxbinsindex = 0;
            for (int n = 1; n < size(Bins); n++) {
                if (Bins[n].PixelNums > maxbins) {
                    maxbins = Bins[n].PixelNums;
                    maxbinsindex = n;
                }
            }
            // ensuring not diving by zero
            if (maxbins == 0){
                maxbins = 1;
            }
            // getting the final value for the pixel
            finalpixelR = Bins[maxbinsindex].R / maxbins;
            finalpixelG = Bins[maxbinsindex].G / maxbins;
            finalpixelB = Bins[maxbinsindex].B / maxbins;

            NewImage.setPixel(i, j, 0, finalpixelR);
            NewImage.setPixel(i, j, 1, finalpixelG);
            NewImage.setPixel(i, j, 2, finalpixelB);
            // resting the groups
            for (int m = 0; m < 20; m++) {
                Bins[m].R = 0;
                Bins[m].G = 0;
                Bins[m].B = 0;
                Bins[m].PixelNums = 0;
            }
        }
    }
    return NewImage;
}

Image Filter15(Image UserImage){
    unsigned int R,G,B;
    for (int i = 0 ; i < UserImage.width ; i++){
        for (int j = 0 ; j < UserImage.height ; j++){

            if (j%3 == 0){ // applying the changes each 3 pixels in the height
                // getting a random variable between -25 and 25
                int randvar = gaussian_noise(0,25);
                R = UserImage.getPixel(i,j,0);
                G = UserImage.getPixel(i,j,1);
                B = UserImage.getPixel(i,j,2);

                R += abs(randvar);
                G += abs(randvar);
                B += abs(randvar);
                if (R > 255){
                    R = 255;
                }
                if (G > 255){
                    G = 255;
                }
                if (B > 255){
                    B = 255;
                }
                if (j == UserImage.height - 1){
                    UserImage.setPixel(i,j,0,R);
                    UserImage.setPixel(i,j,1,G);
                    UserImage.setPixel(i,j,2,B);
                    continue;
                }
                UserImage.setPixel(i,j,0,R);
                UserImage.setPixel(i,j+1,0,R);
                UserImage.setPixel(i,j,1,G);
                UserImage.setPixel(i,j,2,B);
            }
        }
    }
    return UserImage;
}


Image Filter16(Image UserImage){
    unsigned int Red,Green,Blue;
    for (int i = 0 ; i < UserImage.width ; i ++){
        for (int j = 0 ; j <UserImage.height ; j ++){
            Red = UserImage.getPixel(i,j,0);
            Green = UserImage.getPixel(i,j,1);
            Blue = UserImage.getPixel(i,j,2);
            Green *=0.722;
            UserImage.setPixel(i,j,0,Red);
            UserImage.setPixel(i,j,1,Green);
            UserImage.setPixel(i,j,2,Blue);
        }
    }
    return UserImage;
}

Image Filter17(Image UserImage){
    unsigned RedValue;
    unsigned GreenValue;
    unsigned BlueValue;
    int GrayScale;
    unsigned gbscale;
    for (int i = 0; i < UserImage.width ; i++){
        for (int j = 0 ; j < UserImage.height ; j++){
            RedValue = UserImage.getPixel(i,j,0);
            GreenValue = UserImage.getPixel(i,j,1);
            BlueValue = UserImage.getPixel(i, j, 2);
            // applying an equation for getting the grayscale value
            GrayScale = (0.299 * RedValue) + (0.587 * GreenValue) + (0.114 * BlueValue);
            gbscale = 255 - GrayScale;
            // 240+grayscale*(15/127) ==> ensure the red values between 240 and 255
            // 240+(GrayScale - 128)*(15/128)) ==> ensure the red values between 240 and 255
            if (GrayScale < 128){
                UserImage.setPixel(i,j,0,round(240+GrayScale*(15/127)));
                UserImage.setPixel(i,j,1,gbscale);
                UserImage.setPixel(i,j,2,gbscale);
                continue;
            }
            UserImage.setPixel(i,j,0,round(240+(GrayScale - 128)*(15/128)));
            UserImage.setPixel(i,j,1,gbscale);
            UserImage.setPixel(i,j,2,gbscale);
        }
    }
    return  UserImage;
}

Image Filter18(Image OriginalImage, int degree){
    int Nwidth = OriginalImage.width + OriginalImage.width * (tan((M_PI/180.0f)*degree));
    int Nhight = OriginalImage.height;
    int Nx,Ny;
    unsigned colorvalue;

    // resizing the image
    Image NewImage = Fast_Resize(OriginalImage, Nwidth, Nhight);
    for (int i = 0 ; i < NewImage.width ; i++){
        for (int j = 0 ; j < NewImage.height ; j++){
            for (int k = 0 ; k < 3 ; k++){
                NewImage.setPixel(i, j, k, 255);
            }
        }
    }


    for (int i = 0 ; i < NewImage.width ; i++){
        for (int j = 0 ; j < NewImage.height ; j++){
            Nx = i + (tan((M_PI/180.0f)*degree)) * (j - OriginalImage.width);
            Ny = j;
            if (Ny >= 0 && Ny < OriginalImage.height && Nx >= 0 && Nx < OriginalImage.width) {
                for (int k = 0; k < 3; k++) {
                    colorvalue = OriginalImage.getPixel(Nx, Ny, k);
                    NewImage.setPixel(i, j, k, colorvalue);
                }
            }
        }
    }


    return NewImage;

}

Image SopiaTone (Image UserImage)  {

    for (int i = 0; i < UserImage.width; ++i) {
        for (int j = 0; j < UserImage.height; ++j) {

            int originalRed = UserImage.getPixel(i, j, 0);
            int originalGreen = UserImage.getPixel(i, j, 1);
            int originalBlue = UserImage.getPixel(i, j, 2);


            int newRed = (int)((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
            int newGreen = (int)((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
            int newBlue = (int)((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));


            newRed = std::min(std::max(newRed, 0), 255);
            newGreen = std::min(std::max(newGreen, 0), 255);
            newBlue = std::min(std::max(newBlue, 0), 255);


            UserImage.setPixel(i, j, 0, newRed);
            UserImage.setPixel(i, j, 1, newGreen);
            UserImage.setPixel(i, j, 2, newBlue);
        }
    }
    return UserImage;
}



Image Shuffle_Filter( Image& UserImage,int order[4]) {
    Image FirstQuarter(UserImage.width / 2, UserImage.height / 2);
    Image SecondQuarter(UserImage.width / 2, UserImage.height / 2);
    Image ThirdQuarter(UserImage.width / 2, UserImage.height / 2);
    Image FourthQuarter(UserImage.width / 2, UserImage.height / 2);

    if (UserImage.height % 2 == 1){
        UserImage.height = UserImage.height - 1;
    }

    // Split the image into quarters as before...
    for (int i = 0; i < UserImage.width / 2; ++i) {
        for (int j = 0; j < UserImage.height / 2; ++j) {
            for (int k = 0; k < UserImage.channels; ++k) {
                FirstQuarter.setPixel(i, j, k, UserImage.getPixel(i, j, k));
            }
        }
    }

    for (int i = UserImage.width / 2; i < UserImage.width; ++i) {
        for (int j = 0; j < UserImage.height / 2; ++j) {
            for (int k = 0; k < UserImage.channels; ++k) {
                SecondQuarter.setPixel(i - UserImage.width / 2, j, k, UserImage.getPixel(i, j, k));
            }
        }
    }

    for (int i = 0; i < UserImage.width / 2; ++i) {
        for (int j = UserImage.height / 2; j < UserImage.height; ++j) {
            for (int k = 0; k < UserImage.channels; ++k) {
                ThirdQuarter.setPixel(i, j - UserImage.height / 2, k, UserImage.getPixel(i, j, k));
            }
        }
    }

    for (int i = UserImage.width / 2; i < UserImage.width; ++i) {
        for (int j = UserImage.height / 2; j < UserImage.height; ++j) {
            for (int k = 0; k < UserImage.channels; ++k) {
                FourthQuarter.setPixel(i - UserImage.width / 2, j - UserImage.height / 2, k,
                                       UserImage.getPixel(i, j, k));
            }
        }
    }

    Image ShuffledImage(UserImage.width, UserImage.height);

    Image *orderedQuarters[4];
    orderedQuarters[order[0] - 1] = &FirstQuarter;
    orderedQuarters[order[1] - 1] = &SecondQuarter;
    orderedQuarters[order[2] - 1] = &ThirdQuarter;
    orderedQuarters[order[3] - 1] = &FourthQuarter;

    Image *quarters[] = {orderedQuarters[0], orderedQuarters[1], orderedQuarters[2], orderedQuarters[3]};

    // Copy each quarter to the shuffled image at the appropriate position
    for (int q = 0; q < 4; ++q) {
        int startX = (q % 2) * (UserImage.width / 2);
        int startY = (q / 2) * (UserImage.height / 2);
        for (int i = 0; i < UserImage.width / 2; ++i) {
            for (int j = 0; j < UserImage.height / 2; ++j) {
                for (int k = 0; k < UserImage.channels; ++k) {
                    ShuffledImage.setPixel(startX + i, startY + j, k, quarters[q]->getPixel(i, j, k));
                }
            }
        }
    }


    return ShuffledImage;
}


Image clardeon_Filter(Image UserImage){


    float H,S,L;
    unsigned R,G,B;

    for(int i = 0 ; i < UserImage.width ; i++){
        for (int j = 0 ; j < UserImage.height ; j++){
            R = UserImage.getPixel(i, j, 0);
            G = UserImage.getPixel(i, j, 1);
            B = UserImage.getPixel(i, j, 2);

            H = RGB_TO_HSL(R, G, B)[0];
            S = RGB_TO_HSL(R, G, B)[1];
            L = RGB_TO_HSL(R, G, B)[2];

            L = max(0.0f, min(1.0f, L *1.2f));
            S = max(0.0f,min(1.0f,S*1.2f));

            H += 10; // Example adjustment, tweak as needed

            // Adjust contrast
            L = pow(L, 1.1); // Example contrast adjustment, tweak as needed

            R = HSL_To_RGB(H,S,L)[0];
            G = HSL_To_RGB(H,S,L)[1];
            B = HSL_To_RGB(H,S,L)[2];

            R *= 0.9;

            UserImage.setPixel(i, j, 0, R);
            UserImage.setPixel(i, j, 1, G);
            UserImage.setPixel(i, j, 2, B);

        }
    }

    return UserImage;
}

Image Green_Scale(Image UserImage){
    unsigned RedValue;
    unsigned GreenValue;
    unsigned BlueValue;
    int GrayScale;
    unsigned gbscale;
    for (int i = 0; i < UserImage.width; i++) {
        for (int j = 0; j < UserImage.height; j++) {
            RedValue = UserImage.getPixel(i, j, 0);
            GreenValue = UserImage.getPixel(i, j, 1);
            BlueValue = UserImage.getPixel(i, j, 2);
            // applying an equation for getting the grayscale value
            GrayScale = (0.299 * RedValue) + (0.587 * GreenValue) + (0.114 * BlueValue);
            gbscale = 255 - GrayScale;
            // 240+grayscale*(15/127) ==> ensure the red values between 240 and 255
            // 240+(GrayScale - 128)*(15/128)) ==> ensure the red values between 240 and 255
            if (GrayScale < 128) {
                UserImage.setPixel(i, j, 0, gbscale);
                UserImage.setPixel(i, j, 1, round(240 + GrayScale * (15 / 127)));
                UserImage.setPixel(i, j, 2, gbscale);
                continue;
            }
            UserImage.setPixel(i, j, 0, gbscale);
            UserImage.setPixel(i, j, 1, round(240 + (GrayScale - 128) * (15 / 128)));
            UserImage.setPixel(i, j, 2, gbscale);
        }
    }
    return UserImage;
}

Image Blue_Scale(Image UserImage){
    unsigned RedValue;
    unsigned GreenValue;
    unsigned BlueValue;
    int GrayScale;
    unsigned gbscale;
    for (int i = 0; i < UserImage.width; i++) {
        for (int j = 0; j < UserImage.height; j++) {
            RedValue = UserImage.getPixel(i, j, 0);
            GreenValue = UserImage.getPixel(i, j, 1);
            BlueValue = UserImage.getPixel(i, j, 2);
            // applying an equation for getting the grayscale value
            GrayScale = (0.299 * RedValue) + (0.587 * GreenValue) + (0.114 * BlueValue);
            gbscale = 255 - GrayScale;
            // 240+grayscale*(15/127) ==> ensure the red values between 240 and 255
            // 240+(GrayScale - 128)*(15/128)) ==> ensure the red values between 240 and 255
            if (GrayScale < 128) {
                UserImage.setPixel(i, j, 0, gbscale);
                UserImage.setPixel(i, j, 1, gbscale);
                UserImage.setPixel(i, j, 2, round(240 + GrayScale * (15 / 127)));
                continue;
            }
            UserImage.setPixel(i, j, 0, gbscale);
            UserImage.setPixel(i, j, 1, gbscale);
            UserImage.setPixel(i, j, 2, round(240 + GrayScale * (15 / 127)));
        }
    }
    return UserImage;
}


