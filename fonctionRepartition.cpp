#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

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

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

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
            histo[ImgIn[i*nW+j]] += 1;
        }
    }


    float tabRepartition[256];

    tabRepartition[0] = (double)histo[0]/nTaille;

    for (int x = 1; x < 256; x++) {
        tabRepartition[x] = tabRepartition[x - 1] + (double)histo[x]/nTaille;
    }


    //On va ensuite mettre toutes les valeurs dans le fichier "histo.dat"
    std::ofstream fichier(cNomImgEcrite);

    for (int k = 0; k < 256; k++) 
    {
        fichier << k << " " << tabRepartition[k] << "\n";
    }

    fichier.close();
}