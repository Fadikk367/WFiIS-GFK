#include <wx/wx.h>
#include <cmath>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

int scaleToScreen(float value)
{
  return static_cast<int> (100 * value + 250);
}

float maxValue(float d[100][3], int n)
{
  float result = d[0][2];
	 for (int i = 0; i < n; ++i)
     if (result < d[i][2]) result = d[i][2];

  return result;
}

float minValue(float d[100][3], int n)
{
  float result = d[0][2];
  for (int i = 0; i < n; ++i)
    if (result > d[i][2]) result = d[i][2];
	
  return result;
}

float aproxShepard(float d[100][3], int N, float x, float y)
{
  float denominator = 0;
  float numerator = 0;
	for (int i = 0; i < N; ++i)
	{
    //const float weightDenominator = std::pow(x - d[i][0], 2) + std::pow(y - d[i][1], 2);
    const float weightDenominator = (x - d[i][0]) * (x - d[i][0]) + (y - d[i][1])* (y - d[i][1]);
    const float weight = 1.f / weightDenominator;

    denominator += weight;
    numerator += weight * d[i][2];
	}

  return numerator / denominator;
}

void drawPoints(wxMemoryDC& dc, int N, float points[100][3])
{
  wxPoint center;
  const int markerRadius = 3;
  for (int i = 0; i < N; i++) {
    center.x = points[i][0] * 100 + 250;
    center.y = points[i][1] * 100 + 250;
    dc.DrawLine(center.x - markerRadius, 500 - center.y, center.x + markerRadius + 1,500 - center.y);
    dc.DrawLine(center.x, 500 - (center.y - markerRadius), center.x, 500 - (center.y + markerRadius + 1));
  }
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.Clear();
    
 // demo.....
 memDC.SetPen(*wxBLACK_PEN);
 memDC.SetBrush(*wxWHITE_BRUSH);

 unsigned char* pixels = image.GetData();

 auto** valueGrid = new float*[500];
 for (int i = 0; i < 500; ++i)
   valueGrid[i] = new float[500];

 for (int i = 0; i < 500; ++i)
	{
		for (int j = 0; j < 500; ++j)
		{
      const float value = aproxShepard(d, N,j/100.f - 2.5, -i/100.f + 2.5);
      valueGrid[i][j] = value;
		}
	}

  const float f_max = maxValue(d, N);
  const float f_min = minValue(d, N);

	
  if (MappingType)
  {
    for (int i = 0; i < 500; i++)
    {
      for (int j = 0; j < 500; j++)
      {
        const float normalized_z = (valueGrid[i][j] - f_min) / (f_max - f_min);
        switch (MappingType)
        {
        case 1:
          pixels[500 * 3 * i + 3 * j] =  static_cast<unsigned char> ((1 - normalized_z) * 255);
          pixels[500 * 3 * i + 3 * j + 1] = 0;
          pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char> (normalized_z * 255);
          break;
        case 2:
          pixels[500 * 3 * i + 3 * j] =  static_cast<unsigned char> (255 * (normalized_z < 0.5 ? (1.f - 2 * normalized_z) : 0.f));
          pixels[500 * 3 * i + 3 * j + 1] = static_cast<unsigned char> (255 * (normalized_z < 0.5 ? (2 * normalized_z) : (2 * (1.f - normalized_z))));
          pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char> (255 * (normalized_z < 0.5 ? 0 : (0.5 * normalized_z)));
          break;
        case 3:
          pixels[500 * 3 * i + 3 * j] = static_cast<unsigned char> (normalized_z * 255);
          pixels[500 * 3 * i + 3 * j + 1] = static_cast<unsigned char> (normalized_z * 255);
          pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char> (normalized_z * 255);
          break;
        default:
          break;
        }
      }
    }
  	
    const wxBitmap colorMap(image, 24);
    memDC.DrawBitmap(colorMap, 0, 0);
  }


  if (Contour)
  {
    int code = 0;
  	for (int n = 0; n < NoLevels; ++n)
  	{
      const float treshold = (n + 1.f) * (f_max - f_min) / (NoLevels + 1.f) + f_min;
      for (int y = 0; y < 500 - 1; ++y)
      {
        for (int x = 0; x < 500 - 1; ++x)
        {
          code = 0;
          if (valueGrid[y + 1][x] < treshold) code += 1;
          if (valueGrid[y + 1][x + 1] < treshold) code += 2;
          if (valueGrid[y][x + 1] < treshold) code += 4;
          if (valueGrid[y][x] < treshold) code += 8;

        	switch(code)
        	{
	          case 1:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x + 1, y + 1);
              memDC.DrawPoint(x + 1, y);
              break;
	          case 2:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x + 1, y);
              memDC.DrawPoint(x, y + 1);
              break;
	          case 3:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x + 1, y);
              break;
	          case 4:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x + 1, y + 1);
              memDC.DrawPoint(x, y + 1);
              break;
	          case 5:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x + 1, y + 1);
              break;
	          case 6:
              memDC.DrawPoint(x, y);
              memDC.DrawPoint(x, y + 1);
              break;
	          case 7:
              memDC.DrawPoint(x, y);
              break;
	          case 8:
              memDC.DrawPoint(x + 1, y);
              memDC.DrawPoint(x + 1, y + 1);
              memDC.DrawPoint(x, y + 1);
              break;
	          case 9:
              memDC.DrawPoint(x + 1, y);
              memDC.DrawPoint(x + 1, y + 1);
              break;
	          case 10:
              memDC.DrawPoint(x + 1, y);
              memDC.DrawPoint(x, y + 1);
              break;
	          case 11:
              memDC.DrawPoint(x + 1, y);
              break;
	          case 12:
              memDC.DrawPoint(x, y + 1);
              memDC.DrawPoint(x + 1, y + 1);
              break;
	          case 13:
              memDC.DrawPoint(x + 1, y + 1);
              break;
	          case 14:
              memDC.DrawPoint(x, y + 1);
              break;
            default:
              break;
        	}
        }
      }
  	}
  }

 if (ShowPoints) drawPoints(memDC, N, d);

 for (int i = 0; i < 500; ++i)
   delete[] valueGrid[i];
 delete[] valueGrid;
}
