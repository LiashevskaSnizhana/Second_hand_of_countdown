#include <stdlib.h>
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define M 20
#define N 20


void rucicka(char** pole1, int x0, int y0, int x1, int y1) {
    int y = 0;
    int x = 0;
    int xx = 0;
	int xy = 0; 
	int yx = 0; 
	int yy = 0;
    int dx = x1 - x0;
    int dy = y1 - y0;

    int xSign = dx > 0 ? 1 : -1;
    int ySign = dy > 0 ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    if (dx > dy) {
        xx = xSign;
        xy = 0;
        yx = 0;
        yy = ySign;
    }
    else {
            int tmp = dx;
            dx = dy;
            dy = tmp;
            xx = 0;
            xy = ySign;
            yx = xSign;
            yy = 0;
    }

    int d = 2 * dy - dx;
    

    for (x = 0; x <= dx; x++) {
        int indexX = x0 + x * xx + y * yx;
        int indexY = y0 + x * xy + y * yy;

        pole1[indexY][indexX] = '#';

        if (d >= 0) {
            y++;
            d -= 2 * dx;
        }
        d += 2 * dy;
    }
}

void print_Sec(char** pole1) {
    int i = 0;
    for (i = M - 1; i >= 0; i--) {
        char str[N + 1];
        strncpy(str, pole1[i], sizeof(char) * M);
        str[M] = '\0';
        puts(str);
    }
}

int roundEdge(int a, int length) {
    return a < 0 ? 0 : a >= length ? length - 1 : a;
}

float calcModifier(unsigned int a, float step) {
    return ((float)a * 0.5f) / fabsf(step);
}

void malPole(char** pole1) {
    int x = 0;
    int y = 0;
    for (x = 0; x < M; x++) {
        for (y = 0; y < N; ++y) {
            if ((y == 0) || (y == M - 1)) {
                pole1[y][x] = '-';
            }
            else if ((x == 0) || (x == N - 1)) {
                pole1[y][x] = '|';
            }
            else
                pole1[y][x] = ' ';
        }
    }
}

int main() {
    char** pole1 = malloc(sizeof(char*) * M);
    int x = 0;
    int y = 0;
    int i = 0;


    for (i = 0; i < M; i++) {
        pole1[i] = malloc(sizeof(char) * M);
    }

    int baseX = M * 0.5;
    int baseY = N* 0.5;

    for (i = 59; i >= 0; i--) {
        float d = ((float)i / 60.0f) * 2 * (float)M_PI;
        float dx = sinf(d);
        float dy = cosf(d);

        float modifier;
        if (fabsf(dx) > fabsf(dy)) {
            modifier = calcModifier(M, dx);
        }
        else {
            modifier = calcModifier(N, dy);
        }

        int x = roundEdge(baseX + (int)(dx * modifier), M);
        int y = roundEdge(baseY + (int)(dy * modifier), N);

        printf("Second: %d\n", i);

        malPole(pole1);
        rucicka(pole1, baseX, baseY, x, y);
        print_Sec(pole1);
    }
    
    for (i = 59; i >= 0; i--) {
    	free(pole1[i]);
    }
    return 0;
}
