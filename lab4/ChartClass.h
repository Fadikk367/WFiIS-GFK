#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;
class Vector;

class ChartClass {
  private:

    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    double x_min,x_max; // zakres zmiennej x
    double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje
    double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji

    Matrix scaleAndWindow(int w , int h);
    Matrix rotateRelativeTo(double angle, int x, int y);
    Matrix translate(int dx, int dy);

    Matrix calculateTransformation(int w, int h);

    void reset(wxDC* dc, int w, int h);
    void transformLine2d(Matrix t, Vector& start, Vector& end);
    void drawAxises(wxDC* dc, Matrix t, int w, int h);
    void drawFunction(wxDC* dc, Matrix t);

  public:

    ChartClass(std::shared_ptr<ConfigClass> c);
    void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
    double Get_Y_min(); // zwraca y_min
    double Get_Y_max(); // zwraca y_max  
    void Draw(wxDC *dc, int w, int h);  // rysuje wykres
};

#endif

