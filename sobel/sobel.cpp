#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned char byte_t;

struct BITMAPFILEHEADER {
    byte_t bfType[2] = {};
    byte_t bfSize[4] = {};
    byte_t bfReserved1[2] = {};
    byte_t bfReserved2[2] = {};
    byte_t bfOffBits[4] = {};
};

struct BITMAPINFOHEADER {
    byte_t biSize[4];
    byte_t biWidth[4];
    byte_t biHeight[4];
    byte_t biPlanes[2];
    byte_t biBitCount[2];
    byte_t biCompression[4];
    byte_t biSizeImage[4];
    byte_t biXPelsPerMeter[2];
    byte_t biYPelsPerMeter[2];
    byte_t biClrImportant[4];
};

int dwa(byte_t* t)
{
    return t[0] + t[1] * 256;
}

int cztery(byte_t* t)
{
    return t[0] + t[1] * 256 + t[2] * 256 * 256 + t[3] * 256 * 256 * 256;
}

void readfile(ifstream& plik, BITMAPFILEHEADER& file)
{
    plik.read((char*)&(file.bfType), sizeof(file.bfType));
    plik.read((char*)&(file.bfSize), sizeof(file.bfSize));
    plik.read((char*)&(file.bfReserved1), sizeof(file.bfReserved1));
    plik.read((char*)&(file.bfReserved2), sizeof(file.bfReserved2));
    plik.read((char*)&(file.bfOffBits), sizeof(file.bfOffBits));
}

int readinfo(ifstream& plik, BITMAPINFOHEADER& info)
{
    plik.read((char*)&(info.biSize), sizeof(info.biSize));
    plik.read((char*)&(info.biWidth), sizeof(info.biWidth));
    plik.read((char*)&(info.biHeight), sizeof(info.biHeight));
    plik.read((char*)&(info.biPlanes), sizeof(info.biPlanes));
    plik.read((char*)&(info.biBitCount), sizeof(info.biBitCount));
    plik.read((char*)&(info.biCompression), sizeof(info.biCompression));
    plik.read((char*)&(info.biSizeImage), sizeof(info.biSizeImage));
    plik.read((char*)&(info.biXPelsPerMeter), sizeof(info.biXPelsPerMeter));
    plik.read((char*)&(info.biYPelsPerMeter), sizeof(info.biYPelsPerMeter));
    plik.read((char*)&(info.biClrImportant), sizeof(info.biClrImportant));

    return plik.tellg();
}

void writefile(ofstream& plik, BITMAPFILEHEADER& file)
{
    plik.write((char*)&(file.bfType), sizeof(file.bfType));
    plik.write((char*)&(file.bfSize), sizeof(file.bfSize));
    plik.write((char*)&(file.bfReserved1), sizeof(file.bfReserved1));
    plik.write((char*)&(file.bfReserved2), sizeof(file.bfReserved2));
    plik.write((char*)&(file.bfOffBits), sizeof(file.bfOffBits));
}

void writeinfo(ofstream& plik, BITMAPINFOHEADER& info)
{
    plik.write((char*)&(info.biSize), sizeof(info.biSize));
    plik.write((char*)&(info.biWidth), sizeof(info.biWidth));
    plik.write((char*)&(info.biHeight), sizeof(info.biHeight));
    plik.write((char*)&(info.biPlanes), sizeof(info.biPlanes));
    plik.write((char*)&(info.biBitCount), sizeof(info.biBitCount));
    plik.write((char*)&(info.biCompression), sizeof(info.biCompression));
    plik.write((char*)&(info.biSizeImage), sizeof(info.biSizeImage));
    plik.write((char*)&(info.biXPelsPerMeter), sizeof(info.biXPelsPerMeter));
    plik.write((char*)&(info.biYPelsPerMeter), sizeof(info.biYPelsPerMeter));
    plik.write((char*)&(info.biClrImportant), sizeof(info.biClrImportant));

}

void wypisz(BITMAPFILEHEADER file, BITMAPINFOHEADER info)
{
    cout << "bfType: " << file.bfType[0] << file.bfType[1] << endl;
    cout << "bfSize: " << cztery(file.bfSize) << endl;
    cout << "bfReserved1: " << dwa(file.bfReserved1) << endl;
    cout << "bfReserved2: " << dwa(file.bfReserved2) << endl;
    cout << "bfOffBits: " << cztery(file.bfOffBits) << endl;
    cout << "biSize: " << cztery(info.biSize) << endl;
    cout << "biWidth: " << cztery(info.biWidth) << endl;
    cout << "biHeight: " << cztery(info.biHeight) << endl;
    cout << "biPlanes: " << dwa(info.biPlanes) << endl;
    cout << "biBitCount: " << dwa(info.biBitCount) << endl;
    cout << "biCompression: " << cztery(info.biCompression) << endl;
    cout << "biSizeImage: " << cztery(info.biSizeImage) << endl;
    cout << "biXPelsPerMeter: " << dwa(info.biXPelsPerMeter) << endl;
    cout << "biYPelsPerMeter: " << dwa(info.biYPelsPerMeter) << endl;
    cout << "biClrImportant: " << cztery(info.biClrImportant) << endl;
    cout << "wielkosc prawidlowa: " << cztery(file.bfSize) - cztery(file.bfOffBits) << endl;
}

int** wyczytaj(string zdjecie, int& ilosc, int& rozmiar)
{
    ifstream mas(zdjecie);



    mas >> ilosc;
    cout << "ilosc masek: ";
    cout << ilosc;

    mas >> rozmiar;
    cout << endl << "rozmiar masek: " << rozmiar * rozmiar;




    int** tablica;
    tablica = new int* [ilosc];

    for (int i = 0; i < ilosc; i++)
    {
        tablica[i] = new int[rozmiar * rozmiar];
    }
    cout << endl;
    for (int i = 0; i < ilosc; i++)
    {


        for (int j = 0; j < rozmiar * rozmiar; j++)
        {

            mas >> tablica[i][j];
            cout << tablica[i][j] << " ";
            if ((j + 1) % rozmiar == 0)
            {
                cout << endl;
            }
        }
        cout << endl << endl;

    }
    if (mas.good() == true)
    {
        mas.close();
    }
    return tablica;




}

void podzielenie(ofstream& out, ofstream& test, ifstream& in, unsigned long int wysokosc, unsigned long int szerokosc, unsigned int zeros, int ilosc, int rozmiar, int** tablica);

int main()
{

    int wybor;
    string zdjecie;
    int d;
    int ilosc = 0;
    int rozmiar = 0;

    cout << "podaj nazwe zdjecia: ";
    cin >> zdjecie;
    cout << endl;

    do
    {
        cout << "1 - calosc do jednej tablicy \ 2 - podziel na czesci";
        cin >> wybor;
        cout << endl;
    } while (wybor != 1 && wybor != 2);


    ifstream in(zdjecie, ios::binary); //tworzy plik nazwa zdjecia




    if (in.good() == true)
    {

        ofstream out("output.bmp", ios::binary);        //tworzy drugi plik
        ofstream test("test.bmp", ios::binary);
        BITMAPFILEHEADER file;
        BITMAPINFOHEADER info;


        int maska;
        do {

            cout << "jaka maske wybrac?  {1}-sobel {2}-wlasna {3}-uklad pliku" << endl;
            cin >> maska;
            if (maska == 1)
            {
                zdjecie = "sobel.txt";
            }
            if (maska == 2)
            {
                zdjecie = "nowy.txt";
            }
            if (maska == 3)
            {
                cout << "pierwsze dwie liczby mowiace o ilosci masek oraz dlugosci boku jednej maski" << endl;
                cout << "nastepne cyfry sa kolejnymi liczbami masek" << endl << endl;
            }
        } while (maska != 1 && maska != 2);
        system("cls");



        int** tablica = wyczytaj(zdjecie, ilosc, rozmiar);//maski



        readfile(in, file);     //wyczytuje
        d = readinfo(in, info);


        writefile(out, file);
        writeinfo(out, info);

        writefile(test, file);
        writeinfo(test, info);

        wypisz(file, info);


        unsigned char c;
        unsigned long int wysokosc = cztery(info.biHeight), szerokosc = cztery(info.biWidth);
        char buffer;


        unsigned int zeros = 0;

        if (szerokosc % 4 != 0)
        {
            int bytes = szerokosc * 3;
            zeros = ((bytes / 4) + 1) * 4 - bytes;
        }

        cout << "ilosc zer: " << zeros;



        for (long int i = d; i < cztery(file.bfOffBits); i++)
        {
            in.read(&buffer, 1);
            out.write(&buffer, 1);
            test.write(&buffer, 1);
        }


        if (wybor == 1)
        {



            //tworze tablice pikseli
            unsigned char** piksel[3];
            for (int i = 0; i < 3; i++)
            {
                piksel[i] = new unsigned char* [wysokosc];
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < wysokosc; j++)
                {
                    piksel[i][j] = new unsigned char[szerokosc];
                }
            }
            //piksek[rgb][wysokosc][szerokosc]!!!

            unsigned char** piksel2[3];
            for (int i = 0; i < 3; i++)
            {
                piksel2[i] = new unsigned char* [wysokosc];
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < wysokosc; j++)
                {
                    piksel2[i][j] = new unsigned char[szerokosc];
                }
            }

            for (int i = 0; i < wysokosc; i++)
            {
                for (int j = 0; j < szerokosc; j++)
                {
                    piksel2[0][i][j] = 0;
                    piksel2[1][i][j] = 0;
                    piksel2[2][i][j] = 0;
                }
            }



            for (unsigned long int i = 0; i < wysokosc; i++)
            {
                for (unsigned long int j = 0; j < szerokosc; j++)
                {



                    in.read((char*)&c, sizeof(char));
                    piksel[0][i][j] = c;
                    test.write((char*)&c, sizeof(char));

                    in.read((char*)&c, sizeof(char));
                    piksel[1][i][j] = c;
                    test.write((char*)&c, sizeof(char));

                    in.read((char*)&c, sizeof(char));
                    piksel[2][i][j] = c;
                    test.write((char*)&c, sizeof(char));

                }


                for (int j = 0; j < zeros; j++)
                {
                    in.read((char*)&c, sizeof(char));
                    test.write((char*)&c, sizeof(char));
                }

            }

            long int wynik = 0;
            long int wynikpart = 0;

            int pomocS = -(rozmiar / 2), pomocW = -(rozmiar / 2);   // -(3/2)= -1


            for (unsigned long int i = (rozmiar / 2); i < wysokosc - (rozmiar / 2); i++)
            {
                for (unsigned long int j = (rozmiar / 2); j < szerokosc - (rozmiar / 2); j++)
                {
                    for (int RGB = 0; RGB < 3; RGB++)
                    {

                        for (int ile = 0; ile < ilosc; ile++)
                        {

                            for (int roz = 0; roz < rozmiar * rozmiar; roz++)
                            {


                                wynikpart += (piksel[RGB][i + pomocW][j + pomocS]) * tablica[ile][roz];

                                pomocS++;
                                if (pomocS == rozmiar - 1)
                                {
                                    pomocS = -(rozmiar / 2);
                                    pomocW++;
                                }

                            }
                            pomocW = -(rozmiar / 2);

                            if (wynikpart < 0)wynikpart = 0;

                            wynik += wynikpart;
                            wynikpart = 0;
                        }




                        if (wynik > 255)wynik = 255;
                        if (wynik < 0)wynik = 0;

                        piksel2[RGB][i][j] = wynik;

                        wynik = 0;

                    }
                }
            }

            for (unsigned long int i = 0; i < wysokosc; i++)
            {
                for (unsigned long int j = 0; j < szerokosc; j++)
                {




                    c = piksel2[0][i][j];

                    out.write((char*)&c, sizeof(char));


                    c = piksel2[1][i][j];

                    out.write((char*)&c, sizeof(char));

                    c = piksel2[2][i][j];

                    out.write((char*)&c, sizeof(char));



                }

                for (int j = 0; j < zeros; j++)
                {

                    out.write((char*)&c, sizeof(char));
                }

            }


            for (int i = 0; i < ilosc; i++)
            {
                delete[] tablica[i];
            }

            delete[] tablica;




            for (int j = 0; j < 3; j++)//zamyka tablice
            {

                for (int i = 0; i < wysokosc; i++)
                {
                    delete[] piksel[j][i];
                }
            }

            for (int i = 0; i < 3; i++)
            {
                delete[] piksel[i];
            }


            for (int j = 0; j < 3; j++)//zamyka tablice
            {

                for (int i = 0; i < wysokosc; i++)
                {
                    delete[] piksel2[j][i];
                }
            }

            for (int i = 0; i < 3; i++)
            {
                delete[] piksel2[i];
            }

        }
        else if (wybor == 2)
        {
            podzielenie(out, test, in, wysokosc, szerokosc, zeros, ilosc, rozmiar, tablica);
        }

        if (in.good() == true)//zamyka pliki
        {
            in.close();

            if (out.good() == true)
            {
                out.close();
                test.close();

            }

        }



        cout << endl << "ready";


    }




    return 0;
}

void podzielenie(ofstream& out, ofstream& test, ifstream& in, unsigned long int wysokosc, unsigned long int szerokosc, unsigned int zeros, int ilosc, int rozmiar, int** tablica)
{


    unsigned char c;


    unsigned char** pomoc[3];
    for (int i = 0; i < 3; i++)
    {
        pomoc[i] = new unsigned char* [rozmiar];
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < rozmiar; j++)
        {
            pomoc[i][j] = new unsigned char[szerokosc];
        }
    }

    for (int dlugosc = rozmiar; dlugosc < wysokosc; dlugosc += rozmiar / 2)
    {



        unsigned char** piksel[3];
        for (int i = 0; i < 3; i++)
        {
            piksel[i] = new unsigned char* [rozmiar];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < rozmiar; j++)
            {
                piksel[i][j] = new unsigned char[szerokosc];
            }
        }
        //piksek[rgb][wysokosc][szerokosc]!!!




        unsigned char** piksel2[3];
        for (int i = 0; i < 3; i++)
        {
            piksel2[i] = new unsigned char* [rozmiar];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < rozmiar; j++)
            {
                piksel2[i][j] = new unsigned char[szerokosc];
            }
        }




        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < szerokosc; j++)
            {
                piksel2[0][i][j] = 0;
                piksel2[1][i][j] = 0;
                piksel2[2][i][j] = 0;
            }
        }



        for (unsigned long int i = 0; i < rozmiar; i++)
        {
            for (unsigned long int j = 0; j < szerokosc; j++)
            {



                in.read((char*)&c, sizeof(char));
                piksel[0][i][j] = c;
                test.write((char*)&c, sizeof(char));

                in.read((char*)&c, sizeof(char));
                piksel[1][i][j] = c;
                test.write((char*)&c, sizeof(char));

                in.read((char*)&c, sizeof(char));
                piksel[2][i][j] = c;
                test.write((char*)&c, sizeof(char));

                if (i >= rozmiar / 2)
                {
                    pomoc[0][i][j] = piksel[0][i][j];
                    pomoc[1][i][j] = piksel[1][i][j];
                    pomoc[1][i][j] = piksel[1][i][j];
                }



            }


            for (int j = 0; j < zeros; j++)
            {
                in.read((char*)&c, sizeof(char));
                test.write((char*)&c, sizeof(char));
            }

        }

        long int wynik = 0;
        long int wynikpart = 0;



        int pomocS = -(rozmiar / 2), pomocW = -(rozmiar / 2);   // -(3/2)= -1


        for (unsigned long int i = (rozmiar / 2); i < (rozmiar / 2) - ((rozmiar / 2) - 1); i++)
        {
            for (unsigned long int j = (rozmiar / 2); j < szerokosc - (rozmiar / 2); j++)
            {
                for (int RGB = 0; RGB < 3; RGB++)
                {

                    for (int ile = 0; ile < ilosc; ile++)
                    {

                        for (int roz = 0; roz < rozmiar * rozmiar; roz++)
                        {


                            wynikpart += (piksel[RGB][i + pomocW][j + pomocS]) * tablica[ile][roz];

                            pomocS++;
                            if (pomocS == rozmiar - 1)
                            {
                                pomocS = -(rozmiar / 2);
                                pomocW++;
                            }

                        }
                        pomocW = -(rozmiar / 2);

                        if (wynikpart < 0)wynikpart = 0;

                        wynik += wynikpart;
                        wynikpart = 0;
                    }




                    if (wynik > 255)wynik = 255;
                    if (wynik < 0)wynik = 0;

                    piksel2[RGB][i][j] = wynik;

                    wynik = 0;

                }
            }
        }




        for (unsigned long int i = 0; i < rozmiar; i++)
        {
            for (unsigned long int j = 0; j < szerokosc; j++)
            {




                c = piksel2[0][i][j];

                out.write((char*)&c, sizeof(char));


                c = piksel2[1][i][j];

                out.write((char*)&c, sizeof(char));

                c = piksel2[2][i][j];

                out.write((char*)&c, sizeof(char));



            }

            for (int j = 0; j < zeros; j++)
            {

                out.write((char*)&c, sizeof(char));
            }

        }





        for (int j = 0; j < 3; j++)//zamyka tablice
        {

            for (int i = 0; i < rozmiar; i++)
            {
                delete[] piksel[j][i];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            delete[] piksel[i];
        }


        for (int j = 0; j < 3; j++)//zamyka tablice
        {

            for (int i = 0; i < rozmiar; i++)
            {
                delete[] piksel2[j][i];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            delete[] piksel2[i];
        }


    }

    for (int i = 0; i < ilosc; i++)
    {
        delete[] tablica[i];
    }

    delete[] tablica;



    for (int j = 0; j < 3; j++)//zamyka tablice
    {

        for (int i = 0; i < rozmiar; i++)
        {
            delete[] pomoc[j][i];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        delete[] pomoc[i];
    }


};