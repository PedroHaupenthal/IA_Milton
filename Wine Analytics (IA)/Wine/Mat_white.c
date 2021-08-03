#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{

    float E1[5000];
    float E2[5000];
    float E3[5000];
    float E4[5000];
    float E5[5000];
    float E6[5000];
    float E7[5000];
    float E8[5000];
    float E9[5000];
    float E10[5000];
    float E11[5000];
    float E12[5000];

    float t[3][5000];

    float w1[13][13];
    float nw1[13][13];
    float vw1[13][13];

    float w2[13][13];
    float nw2[13][13];
    float vw2[13][13];

    float I[13][13];
    float O[13][13];
    float d1[13];
    float d2[13];
    float erro;
    int i = 0, j, l;
    int cs;
    int n;

    //------------------READ-----------------------------
    FILE *in;

    if ((in = fopen("white_normalizado.txt", "rt")) == NULL)
    {
        printf("Cannot open input file.\n");
        return 1;
    }

    while (!feof(in))
    {
        fscanf(in, "%f%f%f%f%f%f%f%f%f%f%f%f%f", &E1[i], &E2[i], &E3[i], &E4[i], &E5[i], &E6[i], &E7[i], &E8[i], &E9[i], &E10[i], &E11[i], &E12[i], &t[0][i]);

        i++;
    }

    for (j = 0; j < (i - 1); j++)
    {

        printf("%i %f %f %f %f %f %f %f %f %f %f %f %f %f\n ", j, E1[j], E2[j], E3[j], E4[j], E5[j], E6[j], E7[j], E8[j], E9[j], E10[j], E11[j], E12[j], t[0][j]);
    }

    fclose(in);
    getch();
    //-----------------------------------------------------

    for (j = 0; j < 13; j++)
    {
        for (i = 0; i < 13; i++)
        {
            vw1[i][j] = 0.0;
            w1[i][j] = (rand() / 32767.0) * 4.0 - 2.0;
        }
    }

    for (l = 0; l < 2; l++)
    {
        for (j = 0; j < 13; j++)
        {
            vw2[j][l] = 0.0;
            w2[j][l] = (rand() / 32767.0) * 4.0 - 2.0;
        }
    }

    do
    {

        erro = 0.0;
        for (n = 0; n < 4800; n++)
        {

            //-----propagation----------------------------
            cs = rand() % 4780;

            I[0][0] = E1[cs];
            I[0][1] = E2[cs];
            I[0][2] = E3[cs];
            I[0][3] = E4[cs];
            I[0][4] = E5[cs];
            I[0][5] = E6[cs];
            I[0][6] = E7[cs];
            I[0][7] = E8[cs];
            I[0][8] = E9[cs];
            I[0][9] = E10[cs];
            I[0][10] = E11[cs];
            I[0][11] = E12[cs];
            I[0][12] = 1.0;

            O[0][0] = I[0][0];
            O[0][1] = I[0][1];
            O[0][2] = I[0][2];
            O[0][3] = I[0][3];
            O[0][4] = I[0][4];
            O[0][5] = I[0][5];
            O[0][6] = I[0][6];
            O[0][7] = I[0][7];
            O[0][8] = I[0][8];
            O[0][9] = I[0][9];
            O[0][10] = I[0][10];
            O[0][11] = I[0][11];
            O[0][12] = I[0][12];

            for (j = 0; j < 13; j++)
            {
                I[1][j] = 0.0;
                for (i = 0; i < 13; i++)
                {
                    I[1][j] += w1[i][j] * O[0][i];
                }
                O[1][j] = 1.0 / (1.0 + exp(-I[1][j]));
            }

            I[1][3] = 1.0;
            O[1][3] = I[1][3];

            for (l = 0; l < 2; l++)
            {
                I[2][l] = 0.0;
                for (j = 0; j < 13; j++)
                {
                    I[2][l] += w2[j][l] * O[1][j];
                }
                O[2][l] = 1.0 / (1.0 + exp(-I[2][l]));
            }
            //-----backpropagation----------------------

            for (l = 0; l < 2; l++)
            {
                d2[l] = (t[l][cs] - O[2][l]) * O[2][l] * (1.0 - O[2][l]);
            }

            for (j = 0; j < 13; j++)
            {
                d1[j] = 0.0;
                for (l = 0; l < 2; l++)
                {
                    d1[j] += d2[l] * w2[j][l];
                }
                d1[j] = O[1][j] * (1.0 - O[1][j]) * d1[j];
            }

            //-------------------------------------------------
            for (l = 0; l < 2; l++)
            {
                for (j = 0; j < 13; j++)
                {
                    nw2[j][l] = w2[j][l] + 0.5 * d2[l] * O[1][j] + 0.5 * vw2[j][l];
                    vw2[j][l] = nw2[j][l] - w2[j][l];
                    w2[j][l] = nw2[j][l];
                }
            }

            //-------------------------------------------------
            for (j = 0; j < 13; j++)
            {
                for (i = 0; i < 13; i++)
                {
                    nw1[i][j] = w1[i][j] + 0.5 * d1[j] * O[0][i] + 0.5 * vw1[i][j];
                    vw1[i][j] = nw1[i][j] - w1[i][j];
                    w1[i][j] = nw1[i][j];
                }
            }

            //------------------------------------------
            for (l = 0; l < 2; l++)
            {
                erro += (t[l][cs] - O[2][l]) * (t[l][cs] - O[2][l]);
            }
        } //close for n

        erro = erro / 4780;
        printf("%f \n", erro);

    } while (erro > 0.000001);

    for (j = 0; j < 13; j++)
    {
        for (i = 0; i < 13; i++)
        {
            printf("w1[%d][%d]=%f; \n", i, j, w1[i][j]);
        }
    }
    for (l = 0; l < 2; l++)
    {
        for (j = 0; j < 13; j++)
        {
            printf("w2[%d][%d]=%f; \n", j, l, w2[j][l]);
        }
    }

    return 0;
}
