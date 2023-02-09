#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <fstream>
#include <cfloat>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.dat\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite) ;

    OCTET *ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    float a0 = FLT_MAX;
    float a1 = FLT_MIN;

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            if (ImgIn[i*nW+j] < a0) {
                a0 = ImgIn[i*nW+j];
            }
            else if (ImgIn[i*nW+j] > a1) {
                a1 = ImgIn[i*nW+j];
            }
        }
    }

    std::cout << "a0 : " << a0 << std::endl;
    std::cout << "a1 : " << a1 << std::endl;
    std::cout << "alpha : " << -(255*a0)/(a1-a0) << std::endl;
    std::cout << "beta : " << 255/(a1-a0) << std::endl;


    for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++) {
            ImgOut[i*nW+j] = -(255/(a1-a0))*(a0-ImgIn[i*nW+j]);
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
}