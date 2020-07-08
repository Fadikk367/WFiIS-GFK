#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.ConvertToGreyscale();
  Repaint();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Blur(5);
  Repaint();
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Mirror(true);
  Repaint();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Copy();
  Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
  Repaint();
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
  wxClientDC dc(m_scrolledWindow);
  dc.Clear();
  Img_Cpy = Img_Org.Copy();
  Img_Cpy.Rescale(320, 240);
  Repaint();
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
  wxClientDC dc(m_scrolledWindow);
  dc.Clear();
  Img_Cpy = Img_Org.Rotate(30 * M_PI / 180, wxPoint(0, 0));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Copy();
  Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
  wxClientDC dc(m_scrolledWindow);
  dc.Clear();
  Img_Cpy = Img_Org.Copy();
  Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Copy();
  unsigned char* data = Img_Cpy.GetData();
  unsigned char* org_data = Img_Org.GetData();

  int w = Img_Org.GetWidth();
  int h = Img_Org.GetHeight();
  int length = w * h * 3;

  int sum;
  for (int i = 1; i < h - 1; i++) {
    for (int j = 1; j < w - 1; j++) {
      for (int k = 0; k < 3; k++) {
        sum = 0;

        sum += org_data[3 * w * (i - 1) + 3 * (j + 1) + k];
        sum += org_data[3 * w * i + 3 * (j + 1) + k];
        sum += org_data[3 * w * (i + 1) + 3 * (j + 1) + k];

        sum += -org_data[3 * w * (i - 1) + 3 * (j - 1) + k];
        sum += -org_data[3 * w * i + 3 * (j - 1) + k];
        sum += -org_data[3 * w * (i + 1) + 3 * (j - 1) + k];

        data[3 * w * i + 3 * j + k] = std::abs(sum) / 3;
      }
    }
  }
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
  Img_Cpy = Img_Org.Copy();
  unsigned char* data = Img_Cpy.GetData();

  int w = Img_Org.GetWidth();
  int h = Img_Org.GetHeight();
  int length = w * h * 3;

  for (int i = 0; i < length; ++i) {
    data[i] = data[i] <= 128 ? 0 : 255;
  }
}

int truncate(int value) {
  if (value < 0) return 0;
  if (value > 255) return 255;
  return value;
}


void GUIMyFrame1::Contrast(int value)
{
  Img_Cpy = Img_Org.Copy();
  unsigned char* data = Img_Cpy.GetData();

  int w = Img_Org.GetWidth();
  int h = Img_Org.GetHeight();
  int length = w * h * 3;

  float contrast = value * 2.55;
  float factor = (259 * (contrast + 255)) / (255 * (259 - contrast));

  for (int i = 0; i < length; ++i) {
    data[i] = truncate((data[i] - 128) * factor + 128);
  }
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
  Img_Cpy = Img_Org.Copy();
  unsigned char* data = Img_Cpy.GetData();

  int w = Img_Org.GetWidth();
  int h = Img_Org.GetHeight();
  int length = w * h * 3;

  for (int i = 0; i < length; ++i) {
    data[i] = truncate(data[i] + value);
  }
}