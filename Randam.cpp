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
    return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
void Randam::SRAND() {
    srand((unsigned)time(NULL));
}