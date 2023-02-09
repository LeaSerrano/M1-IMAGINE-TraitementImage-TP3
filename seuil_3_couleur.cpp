#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S_Rmin, S_Rmax, S_Gmin, S_Gmax, S_Bmin, S_Bmax;
  
  if (argc != 9) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SeuilRouge SeuilVert SeuilBleu \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S_Rmin);
   sscanf (argv[4],"%d",&S_Rmax);
   sscanf (argv[5],"%d",&S_Gmin);
   sscanf (argv[6],"%d",&S_Gmax);
   sscanf (argv[7],"%d",&S_Bmin);
   sscanf (argv[8],"%d",&S_Bmax);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille*3);
   
   for (int elt=0; elt < nTaille*3; elt++){ 
        if (ImgIn[elt] <= S_Rmin) {
            ImgOut[elt] = S_Rmin;
        } 
        else if (ImgIn[elt] >= S_Rmax) {
            ImgOut[elt] = S_Rmax;
        }
        else if (ImgIn[elt] < S_Rmax & ImgIn[elt] > S_Rmin) {
             ImgOut[elt] = ImgIn[elt];
        }

        if (ImgIn[elt+1] <= S_Gmin) {
            ImgOut[elt+1] = S_Gmin;
        } 
        else if (ImgIn[elt+1] >= S_Gmax) {
            ImgOut[elt+1] = S_Gmax;
        }
        else if (ImgIn[elt+1] < S_Gmax & ImgIn[elt+1] > S_Gmin) {
             ImgOut[elt+1] = ImgIn[elt+1];
        }

        if (ImgIn[elt+2] <= S_Bmin) {
            ImgOut[elt+2] = S_Bmin;
        } 
        else if (ImgIn[elt+2] >= S_Bmax) {
            ImgOut[elt+2] = S_Bmax;
        }
        else if (ImgIn[elt+2] < S_Bmax & ImgIn[elt+2] > S_Bmin) {
             ImgOut[elt+2] = ImgIn[elt+2];
        }
   } 

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
