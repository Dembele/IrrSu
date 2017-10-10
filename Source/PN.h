//PN.H BEGIN
#ifndef PN_H
#define PN_H
#include <vector>
class PN {
    // Вектор значений
    std::vector<int> p;
public:
    // Инициализируем значения вектора
    PN();
    // Генерирует новый вектор из зерна
    PN(unsigned int PSeed);
    // Получаем 2D шум, z может принимать лубое значение
    double PNoise(double x, double y, double z);
private:
    double FadeOut(double t);
    double LinearInterpolation(double t, double a, double b);
    double Gradient(int hash, double x, double y, double z);
};

#endif 
// PN.H END