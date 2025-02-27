#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   
    if (argc != 6) {
        printf("Se requieren 5 argumentos.\n");
        return 1;
    }

    double largo = atof(argv[1]);
    double ancho = atof(argv[2]);
    int largoP = atoi(argv[3]);
    int anchoP = atoi(argv[4]);
    int alturaP =  atoi(argv[5]);
    int volumenP, areaP;

    double *ptrLargo = &largo;
    double *ptrAncho = &ancho;

    int *ptrLargoP = &largoP;
    int *ptrAnchoP = &anchoP;
    int *ptrAlturaP = &alturaP;

    double perimetro = 2 * (*ptrLargo + *ptrAncho);
    double area = *ptrLargo * *ptrAncho;

    printf("Cálculo del rectángulo:\n");
    printf("Área del rectángulo: %f\n", area);
    printf("Perímetro del rectángulo: %f\n\n", perimetro);

    volumenP = *ptrLargoP * *ptrAnchoP * *ptrAlturaP;
    areaP = 2 * (*ptrLargoP * *ptrAnchoP + *ptrLargoP * *ptrAlturaP + *ptrAnchoP * *ptrAlturaP);

    printf("Cálculo del paralelepípedo:\n");
    printf("Volumen del paralelepípedo: %d\n", volumenP);
    printf("Área del paralelepípedo: %d\n", areaP);

    return 0;
}