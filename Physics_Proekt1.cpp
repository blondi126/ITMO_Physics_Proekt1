#include <iostream>
#include <cmath>
#define PI 3.14159265
#define AEM (1.6605*pow(10,(-27)))

using namespace std;

int main()
{
    double q = (1.6) * pow(10, (-19));
    double B = 1 * pow(10, (-2));
    double v = 1000;
    double alpha = 45;
    double m[5] = { (20 * AEM), (21 * AEM), (22 * AEM), (23 * AEM), (24 * AEM) };
    double t[1000], Vx[5][1000], Vy[5][1000], X[5][1000], Y[5][1000];
    double ax[5], ay[5];
    for (int j = 0; j < 5; j++) {
        ax[j] = (q / m[j]) * B* v * (sin(alpha * PI / 180) + cos(alpha * PI / 180));
        ay[j] = (q / m[j]) * B * v * (sin(alpha * PI / 180) - cos(alpha * PI / 180));
        double t0 = 0.000000025;
        for (int i = 0; i < 1000; i++) {
            t[i] = t0;
            t0 += 0.000000025;
            Vx[j][i] = v * cos(alpha * PI / 180) + ax[j] * t[i];
            Vy[j][i] = v * sin(alpha * PI / 180) - ax[j] * t[i];
        }
        X[j][0] = t0 * Vx[j][0];
        Y[j][0] = t0 * Vy[j][0];
        for (int i = 1; i < 1000; i++) {
            X[j][i] = X[j][i - 1] + t0 * Vx[j][i - 1];
            Y[j][i] = Y[j][i - 1] + t0 * Vy[j][i - 1];
        }
    }
    

    FILE* fp;
    char fname[] = "PROJECT.txt";
    fopen_s(&fp, fname, "w+");
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 1000; i++) {
            fprintf(fp, "%E %E \n", X[j][i], Y[j][i]);
        }
        fprintf(fp, "\n ----------------------------------------------------------- \n\n");
    }
    fclose(fp);
    return 0;
}