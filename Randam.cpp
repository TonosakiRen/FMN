#include "Randam.h"
int Randam::RAND(int min, int max) {
    if (min == 0 && max == 0) {
        return 0;
    }
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
float Randam::RAND(float min, float max) {
    if (min == 0 && max == 0) {
        return 0;
    }
    int kmin = min * 1000;
    int kmax = max * 1000;

    float result = (kmin + (int)(rand() * (kmax - kmin + 1.0) / (1.0 + RAND_MAX))) / 1000.0f ;
    return result;
}
void Randam::SRAND() {
    srand((unsigned)time(NULL));
}