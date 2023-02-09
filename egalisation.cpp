#include <stdio.h>
#include "image_ppm.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgLueHisto[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ImageOut.dat\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgLueHisto) ;
    sscanf (argv[3],"%s",cNomImgEcrite) ;

    OCTET *ImgIn, *ImgInHisto, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgInHisto, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    lire_image_pgm(cNomImgLueHisto, ImgInHisto, nH * nW);

    float histo[256];

    for (int elt=0; elt < 256; elt++)
    {
        histo[elt] = 0;
    }

    //Dans ce tableau, on va compter l'occurence des niveaux de gris de l'image
    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            histo[ImgInHisto[i*nW+j]] += 1;
        }
    }

    float tabRepartition[256], transformation[256];

    tabRepartition[0] = (float)histo[0]/nTaille;

    for (int x = 1; x < 256; x++) {
        tabRepartition[x] = tabRepartition[x - 1] + (float)histo[x]/nTaille;
    }

    for (int x = 0; x < 256; x++) {
        transformation[x] = round(tabRepartition[x]*255);
    }

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i*nW+j] = transformation[ImgIn[i*nW+j]];
        }
    }


  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
}