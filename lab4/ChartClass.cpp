#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
  cfg= std::move(c);
  x_step=200;
}

void ChartClass::Set_Range() {
  double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
  double x,y,step;
  int i;

  xmin=cfg->Get_x_start();
  xmax=cfg->Get_x_stop();

  step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
  x=cfg->Get_x_start();

  for (i=0;i<=x_step;i++) {
    y=GetFunctionValue(x);
    if (y>ymax) ymax=y;
    if (y<ymin) ymin=y;
    x=x+step;
  }

  y_min=ymin;
  y_max=ymax;
  x_min=xmin;
  x_max=xmax;
}

double ChartClass::GetFunctionValue(double x) {
  if (cfg->Get_F_type()==1) return x*x;
  if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
  return x+sin(x*4.0);
}


double toRadians(double degrees) {
  return M_PI / 180 * degrees;
}

Matrix ChartClass::rotateRelativeTo(double angle, int x, int y) {
  double radians = toRadians(angle);
  Matrix rot_mat;
  rot_mat.data[0][0] = cos(radians);
  rot_mat.data[0][1] = -sin(radians);
  rot_mat.data[1][0] = sin(radians);
  rot_mat.data[1][1] = cos(radians);
  return translate(x, y) * rot_mat * translate(-x, -y);
}

Matrix ChartClass::translate(int dx, int dy) {
  Matrix trans_mat;
  trans_mat.data[0][0] = 1;
  trans_mat.data[0][2] = dx;
  trans_mat.data[1][1] = 1;
  trans_mat.data[1][2] = dy;
  return trans_mat;
}

Matrix ChartClass::scaleAndWindow(int w, int h) {

  double sx = (static_cast<double> (w) - 20) / (cfg->Get_x1() - cfg->Get_x0());
  double sy = (static_cast<double> (-h) ) / (cfg->Get_y1() - cfg->Get_y0()); // negative value to reflect

  Matrix scale_mat;
  scale_mat.data[0][0] = sx;
  scale_mat.data[1][1] = sy;
  scale_mat.data[0][2] = 10 - sx * cfg->Get_x0();
  scale_mat.data[1][2] = static_cast<double> (h - 10) - sy * cfg->Get_y0();
  return scale_mat;
}


void ChartClass::Draw(wxDC *dc, int w, int h) {
  Set_Range();

  reset(dc, w, h);

  Matrix t = calculateTransformation(w, h);

  drawAxises(dc, t, w, h);

  drawFunction(dc, t);
}

void ChartClass::transformLine2d(Matrix t, Vector& start, Vector& end) {
  start = t * start;
  end = t * end;
}

void ChartClass::reset(wxDC* dc, int w, int h) {
  dc->SetBackground(wxBrush(RGB(255, 255, 255)));
  dc->Clear();
  dc->SetPen(wxPen(RGB(255, 0, 0)));
  dc->DrawRectangle(10, 10, w - 20, h - 20);
  dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));
}

Matrix ChartClass::calculateTransformation(int w, int h) {


  Matrix t = translate(cfg->Get_dX(), cfg->Get_dY()) * scaleAndWindow(w, h);

  if (cfg->RotateScreenCenter()) {
    return rotateRelativeTo(-cfg->Get_Alpha(), w / 2, h / 2) * t;
  }
  else {
    Vector center;
    center.Set(0, 0);
    center = t * center;
    return rotateRelativeTo(-cfg->Get_Alpha(), center.GetX(), center.GetY()) * t;
  }
}

void ChartClass::drawFunction(wxDC* dc, Matrix t) {
  dc->SetPen(*wxGREEN_PEN);

  double dx = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
  double stop = cfg->Get_x_stop();
  Vector start, end;

  if (dx <= 0) return;

  for (double x = cfg->Get_x_start(); x < stop; x += dx) {
    start.Set(x, GetFunctionValue(x));
    end.Set(x + dx, GetFunctionValue(x + dx));
    transformLine2d(t, start, end);
    dc->DrawLine(static_cast<int> (start.GetX()), static_cast<int> (start.GetY()), static_cast<int> (end.GetX()), static_cast<int> (end.GetY()));
  }
}

void ChartClass::drawAxises(wxDC* dc, Matrix t, int w, int h) {

  int number_of_graduations = 6;
  int penWidth = 1;

  dc->SetPen(wxPen(RGB(0, 0, 255), penWidth));

  Vector arrowUp;
  Vector arrowDown;

  arrowUp.Set(x_max - 0.2, 0.1);
  arrowDown.Set(x_max - 0.2, -0.1);

  // X axis

  Vector x_axis_start;
  Vector x_axis_end;

  x_axis_start.Set(x_min, 0);
  x_axis_end.Set(x_max, 0);

  transformLine2d(t, x_axis_start, x_axis_end);
  arrowUp = t * arrowUp;
  arrowDown = t * arrowDown;
  dc->DrawLine(static_cast<int> (x_axis_start.GetX()), static_cast<int> (x_axis_start.GetY()), static_cast<int> (x_axis_end.GetX()), static_cast<int> (x_axis_end.GetY()));
  dc->DrawLine(static_cast<int> (arrowUp.GetX()), static_cast<int> (arrowUp.GetY()), static_cast<int> (x_axis_end.GetX()), static_cast<int> (x_axis_end.GetY()));
  dc->DrawLine(static_cast<int> (arrowDown.GetX()), static_cast<int> (arrowDown.GetY()), static_cast<int> (x_axis_end.GetX()), static_cast<int> (x_axis_end.GetY()));

  double x_length = x_max - x_min;
  double graduation_x_step = x_length / number_of_graduations;

  Vector grad_start;
  Vector grad_end;
  Vector text_pos;
  for (double x = x_min; x < x_max; x += graduation_x_step) {
    if (abs(x - 0.0) < 0.005 || abs(x - x_max) < 0.005) continue;

    grad_start.Set(x, -0.08);
    grad_end.Set(x, 0.08);
    text_pos.Set(x - 0.05, -0.12);

    text_pos = t * text_pos;
    transformLine2d(t, grad_start, grad_end);

    dc->DrawLine(grad_start.GetX(), grad_start.GetY(), grad_end.GetX(), grad_end.GetY());
    dc->DrawRotatedText(wxString::Format(wxT("%.2f"), x), wxPoint(text_pos.GetX(), text_pos.GetY()), cfg->Get_Alpha());
  }

  // Y axis

  Vector y_axis_start;
  Vector y_axis_end;
  y_axis_start.Set(0, y_min);
  y_axis_end.Set(0, y_max);

  arrowUp.Set(-0.08, y_max - 0.12);
  arrowDown.Set(0.08, y_max - 0.12);

  transformLine2d(t, y_axis_start, y_axis_end);
  arrowUp = t * arrowUp;
  arrowDown = t * arrowDown;

  dc->DrawLine(static_cast<int> (y_axis_start.GetX()), static_cast<int> (y_axis_start.GetY()), static_cast<int> (y_axis_end.GetX()), static_cast<int> (y_axis_end.GetY()));
  dc->DrawLine(static_cast<int> (arrowUp.GetX()), static_cast<int> (arrowUp.GetY()), static_cast<int> (y_axis_end.GetX()), static_cast<int> (y_axis_end.GetY()));
  dc->DrawLine(static_cast<int> (arrowDown.GetX()), static_cast<int> (arrowDown.GetY()), static_cast<int> (y_axis_end.GetX()), static_cast<int> (y_axis_end.GetY()));

  double y_length = y_max - y_min;
  double graduation_y_step = y_length / number_of_graduations;

  for (double y = y_min; y < y_max; y += graduation_y_step) {
    if (abs(y - 0.0) < 0.005 || abs(y - y_max) < 0.005) continue;

    grad_start.Set(-0.05, y);
    grad_end.Set(0.05, y);
    text_pos.Set(0.08, y + 0.08);

    text_pos = t * text_pos;
    transformLine2d(t, grad_start, grad_end);

    dc->DrawLine(grad_start.GetX(), grad_start.GetY(), grad_end.GetX(), grad_end.GetY());
    dc->DrawRotatedText(wxString::Format(wxT("%.2f"), y), wxPoint(text_pos.GetX(), text_pos.GetY()), cfg->Get_Alpha());
  }
}


double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}

