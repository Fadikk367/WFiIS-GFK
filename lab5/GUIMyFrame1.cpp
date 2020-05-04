#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


double toRadians(double degrees) {
  return M_PI / 180 * degrees;
}


Matrix4 scale(double sx = 1., double sy = 1., double sz = 1.) {
  Matrix4 mat;
  mat.data[0][0] = sx;
  mat.data[1][1] = sy;
  mat.data[2][2] = sz;
  return mat;
}

Matrix4 translate(double tx = 0., double ty = 0., double tz = 0.) {
  Matrix4 mat;
  mat.data[0][3] = tx;
  mat.data[1][3] = ty;
  mat.data[2][3] = tz;
  mat.data[0][0] = 1.;
  mat.data[1][1] = 1.;
  mat.data[2][2] = 1.;
  mat.data[3][3] = 1.;
  return mat;
}

Matrix4 rotateX(double theta) {
  double thetaRad = toRadians(theta);
  Matrix4 mat;
  mat.data[0][0] = 1.;
  mat.data[1][1] = cos(thetaRad);
  mat.data[1][2] = -sin(thetaRad);
  mat.data[2][1] = sin(thetaRad);
  mat.data[2][2] = cos(thetaRad);
  mat.data[3][3] = 1.;
  return mat;
}

Matrix4 rotateY(double theta) {
  double thetaRad = toRadians(theta);
  Matrix4 mat;
  mat.data[0][0] = cos(thetaRad);
  mat.data[0][2] = sin(thetaRad);
  mat.data[1][1] = 1.;
  mat.data[2][0] = -sin(thetaRad);
  mat.data[2][2] = cos(thetaRad);
  mat.data[3][3] = 1.;
  return mat;
}

Matrix4 rotateZ(double theta) {
  double thetaRad = toRadians(theta);
  Matrix4 mat;
  mat.data[0][0] = cos(thetaRad);
  mat.data[0][1] = -sin(thetaRad);
  mat.data[1][0] = sin(thetaRad);
  mat.data[1][1] = cos(thetaRad);
  mat.data[2][2] = 1.;
  mat.data[3][3] = 1.;
  return mat;
}

Matrix4 get_transformation_matrix(GUIMyFrame1* that) {

  double thetaY = that->WxSB_RotateY->GetValue();
  double thetaX = that->WxSB_RotateX->GetValue();
  double thetaZ = that->WxSB_RotateZ->GetValue();

  double dX = static_cast<double> (that->WxSB_TranslationX->GetValue() - 100) / 50.0;
  double dY = static_cast<double> (that->WxSB_TranslationY->GetValue() - 100) / 50.0;
  double dZ = static_cast<double> (that->WxSB_TranslationZ->GetValue() - 100) / 50.0;

  double sX = static_cast<double> (that->WxSB_ScaleX->GetValue()) / 100;
  double sY = static_cast<double> (that->WxSB_ScaleY->GetValue()) / 100;
  double sZ = static_cast<double> (that->WxSB_ScaleZ->GetValue()) / 100;

  Matrix4 scaling = scale(sX, sY, sZ);

  Matrix4 rotatingX = rotateX(-thetaX);
  Matrix4 rotatingY = rotateY(-thetaY);
  Matrix4 rotatingZ = rotateZ(-thetaZ);
  Matrix4 rotating = rotatingX * rotatingY * rotatingZ;

  Matrix4 translating = translate(dX, dY, dZ);

  return translating * scaling * rotating;
}


void drawLines(wxDC* dc, Matrix4& t, int w, int h) {
  Vector4 begin, end;
  wxPen pen;
  for (const auto& segment : data) {

    begin.Set(segment.begin.x, segment.begin.y, segment.begin.z);
    end.Set(segment.end.x, segment.end.y, segment.end.z);
    pen.SetColour(wxColour(RGB(segment.color.R, segment.color.G, segment.color.B)));

    double d = 2.; /// przyjêta odleg³oœæ kamery/obserwatora od rzutni

    begin = t * begin;
    end = t * end;

    /// Generalny zarys obcinania linii:
    ///  > obliczamy wektor kierunkowy prostej begin->end
    ///  > znajdujemy parametr t taki aby wspó³rzêdna "z" znalaz³a siê na rzutni
    ///  > odpowiednio "przesuwamy" begin/end (w zale¿noœci od przyapdku) w miejsce przeciêcia 
    ///    rzutni z odcinkiem ³¹cz¹cym dwa punkty => t * <odpowiednia sk³adowa wektora kierunkowego>
    ///  > jeœli obydwa punkty le¿¹ przed rzutni¹ => pomijamy iteracjê
    ///    w przeciwnym wypadku ca³y odcinek znajduje siê za ekranem (za ekranem czyli w bryle widzenia z perspektywy wspó³rzêdnej z)
    ///    koniec lini przed rzutni¹, pocz¹tek za
    if (begin.GetZ() > -d && end.GetZ() < -d) {
      Vector4 k;
      k.Set(end.GetX() - begin.GetX(), end.GetY() - begin.GetY(), end.GetZ() - begin.GetZ());
      double t = (-d - end.GetZ()) / (end.GetZ() - begin.GetZ());
      end.Set(end.GetX() - t * k.GetX(), end.GetY() - t * k.GetY(), -d + 0.00001);
    }
    /// pocz¹tek linii przed rzutni¹, koneic za
    else if (begin.GetZ() < -d && end.GetZ() > -d) {
      Vector4 k;
      k.Set(end.GetX() - begin.GetX(), end.GetY() - begin.GetY(), end.GetZ() - begin.GetZ());
      double t = (-d - begin.GetZ()) / (end.GetZ() - begin.GetZ());
      begin.Set(begin.GetX() + t * k.GetX(), begin.GetY() + t * k.GetY(), -d + 0.00001);
    }
    /// ca³a linia przed rzutni¹
    else if (begin.GetZ() < -d && end.GetZ() < -d) {
      continue;
    }

    dc->SetPen(pen);

    /// "h - ..." ¿eby odwróciæ obraz
    dc->DrawLine(
      (w / 2) + (w / 2) * begin.GetX() / (1.0 + begin.GetZ() / d),
      h - ((h / 2) + (h / 2) * begin.GetY() / (1.0 + begin.GetZ() / d)),  
      (w / 2) + (w / 2) * end.GetX() / (1.0 + end.GetZ() / d),
      h - ((h / 2) + (h / 2) * end.GetY() / (1.0 + end.GetZ() / d))); 
  }
}


void GUIMyFrame1::Repaint() {

  wxClientDC dc1(WxPanel);
  wxBufferedDC dc(&dc1);

  int w, h;
  WxPanel->GetSize(&w, &h);

  dc.SetBackground(wxBrush(RGB(255, 255, 255)));
  dc.Clear();
  dc.SetPen(wxPen(RGB(255, 0, 0)));
  dc.SetClippingRegion(wxRect(0, 0, w, h));

  Matrix4 t = get_transformation_matrix(this); /// to przekazanie "this" raczej ma³o eleganckie ale zrobione w imiê troszeczkê lepszej czytelnoœci

  drawLines(&dc, t, w, h);
}