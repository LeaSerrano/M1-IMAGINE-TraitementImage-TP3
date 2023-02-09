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

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille*3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    float a0R = FLT_MAX;
    float a1R = FLT_MIN;

    float a0G = FLT_MAX;
    float a1G = FLT_MIN;

    float a0B = FLT_MAX;
    float a1B = FLT_MIN;

    for (int elt=0; elt < nTaille3; elt++)
    {
        if (ImgIn[elt] < a0R) {
            a0R = ImgIn[elt];
        }
        else if (ImgIn[elt] > a1R) {
            a1R = ImgIn[elt];
        }

        if (ImgIn[elt+1] < a0G) {
            a0G = ImgIn[elt+1];
        }
        else if (ImgIn[elt+1] > a1G) {
            a1G = ImgIn[elt+1];
        }

        if (ImgIn[elt+2] < a0B) {
            a0B = ImgIn[elt+2];
        }
        else if (ImgIn[elt+2] > a1B) {
            a1B = ImgIn[elt+2];
        }
    }

    std::cout << "a0R : " << a0R << std::endl;
    std::cout << "a1R : " << a1R << std::endl;
    std::cout << "alphaR : " << -(255*a0R)/(a1R-a0R) << std::endl;
    std::cout << "betaR : " << 255/(a1R-a0R) << std::endl;

    std::cout << "a0G : " << a0G << std::endl;
    std::cout << "a1G : " << a1G << std::endl;
    std::cout << "alphaG : " << -(255*a0G)/(a1G-a0G) << std::endl;
    std::cout << "betaG : " << 255/(a1G-a0G) << std::endl;

    std::cout << "a0B : " << a0B << std::endl;
    std::cout << "a1B : " << a1B << std::endl;
    std::cout << "alphaB : " << -(255*a0B)/(a1B-a0B) << std::endl;
    std::cout << "betaB : " << 255/(a1B-a0B) << std::endl;


    for (int elt=0; elt < nTaille3; elt++) {
        ImgOut[elt] = -(255/(a1R-a0R))*(a0R-ImgIn[elt]);
        ImgOut[elt+1] = -(255/(a1G-a0G))*(a0G-ImgIn[elt+1]);
        ImgOut[elt+2] = -(255/(a1B-a0B))*(a0B-ImgIn[elt+2]);
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
}