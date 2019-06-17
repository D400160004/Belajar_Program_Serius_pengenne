
#include <iostream.h>
#include<iomanip.h>
#include <stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

float x;
float n_panas, n_normal, n_sedang, n_dingin, n_sgtdgn ;

float panas()
{
    n_panas=0;

    if( x >= 40)
    n_panas=0;
   else if ( x > 30 && x < 40)
    n_panas=(40-x)/(40-30);

    else if ( x >= 10 && x <=30)
    n_panas=1;

    return n_panas;
}

float normal()
{
    n_normal=0;

    if( x < 30 || x > 50)
    n_normal=0;

    else if (x >= 30 && x <= 40)
   n_normal=(x-30)/(40-30);

    else if (x > 40 && x <= 50)
    n_normal=(50-x)/(50-40);

    return n_normal;
}

float sedang()
{
    n_sedang=0;

    if(x < 40 || x > 100)
    n_sedang=0;

    else if (x >= 40 && x <=50)
    n_sedang=(x-40)/(50-40);

   else if (x > 50 && x <=100)
   n_sedang=(100-x)/(100-50);

    return n_sedang;
}

float dingin()
{
    n_dingin=0;

    if(x < 50 || x > 110)
    n_dingin=0;

    else if (x >= 50 && x <= 100)
    n_dingin=(x-50)/(100-50);

   else if (x > 100 && x <= 110)
   n_dingin=(110-x)/(110-100);

    return n_dingin;
}

float sgtdgn()
{
    n_sgtdgn=0;

    if( x < 110)
    n_sgtdgn=0;

    else if (x >= 110)
    n_sgtdgn=1;

   else if ( x >= 100 && x <= 110 )
   n_sgtdgn=(x-100)/(110-100);

    return n_sgtdgn;
}

main() {
float total;
clrscr();

cout<<"               Logika Fuzzy Menentukan Suhu "<<endl<<endl;
cout<<"               Siti Mulia Sari J1F115017   "<<endl<<endl<<endl;

cout<< "Suhu (Celcius) = ";
cin>> x;

cout<<endl<<endl;
cout<<"======================="<<endl;
//cout<<"Hasil : "<<endl;

cout << "M. Panas ["<< x <<"] = "<<panas()<<endl;
cout << "M. Normal ["<< x <<"] = "<<normal()<<endl;
cout << "M. Sedang ["<< x <<"] = "<<sedang()<<endl;
cout << "M. Dingin ["<< x <<"] = "<<dingin()<<endl;
cout << "M. Sangat Dingin ["<< x <<"] = "<<sgtdgn()<<endl;

cout <<"------------------------------------------------+"<<endl;
total =
panas()+normal()+sedang()+dingin()+ sgtdgn();

cout<<" Hasil :                                                  "<<total;
getch();
}

