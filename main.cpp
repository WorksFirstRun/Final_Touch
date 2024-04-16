/*
    Authors : Mohamed Adel Kamal (20230343) Section : 1
              Anton Zakaria Ezzat (20231030) Section : 1
              Youssif Mohamed Youssif (20230513) Section : 1
    Purpose : Assignment3 P3 (20 Filter and gui) note : we did another 3 filters

    Explanation Video For the App : https://www.youtube.com/watch?v=I4X13Ypm-Dk
   Details of the code ? :
    Filters Done :
    Filters (1 -> 12)
    Bonus Filters (13 -> 18)
    5 Extra Choosen Filters by the team
   the following explains which one did which filter

    Filters Made by Mohamed Adel :
    Filter 1 (Gray Scale)
    Filter 4 (Merge Images)
    Filter 7 (Darken and Lighten)
    Filter 10 (Edge detecting)
    Filter 11 (Resize Image)
    Filter 13 (warm up filter)
    Filter 14 (oil painting)
    Filter 15 (Old Tv look Image)
    Filter 18 (Skew)
    Bonus Filter (Clardeon) (this filter is famous in Instgram, it makes a blue tint to the image)

    Filters Made by Anton Zakaria :
    Filter 3 (Invert Image)
    Filter 6 (Rotate Image)
    Filter 9 (Adding Frame to picture)
    Filter 12 (Blur Image)
    Filter 17 (Red Scale)
    Bonus Filter (Shuffle) (this filter split the image in 4 quarters and let the user choose how to order them)
    Bonus Filter (sepia tone)

    Filters Made by Youssif Mohamed :
    Filter 2 (Black and White)
    Filter 5 (Flip Image)
    Filter 8 (Crop Image)
    Filter 16 (Purple Effect)
    Bonus Filter (Blue Scale) (Similar to Filter 17)
    Bonus Filter (Green Scale) (Similar to Filter 17)



    ---Extra Functions that help the filters---
    magnitudearray
    fast_resize
    padding
    Color_padding
    RGB_TO_HSL
    HSL_To_RGB
    gaussian_noise


 */



#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
