#include "GUIMyFrame.h"

wxString GetMetadata(FIBITMAP*);


GUIMyFrame::GUIMyFrame( wxWindow* parent ) : MyFrame( parent ) {
	m_image = new wxImage();
	m_original_image = new wxImage();
	wxInitAllImageHandlers();
}

void GUIMyFrame::onUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dc(m_panel1);
	refresh(dc);
}

void GUIMyFrame::loadImageHandler( wxCommandEvent& event ) {
	wxClientDC dc(m_panel1);
	wxString metaData = "";
	auto* dialog = new wxFileDialog(this, "choose photo", "./", "", wxT("Obraz JPEG (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dialog->ShowModal() == wxID_CANCEL) return;
	if (!m_image->LoadFile(dialog->GetPath(), wxBITMAP_TYPE_JPEG)) return;
	*m_original_image = m_image->Copy();

	FIBITMAP* bitmapFI = FreeImage_Load(FIF_JPEG, dialog->GetPath(), JPEG_DEFAULT);
	metaData = GetMetadata(bitmapFI);
	m_textCtrl1->Clear();
	m_textCtrl1->WriteText(metaData);
	
	refresh(dc);
}

void GUIMyFrame::putCenzureHandler( wxCommandEvent& event ) {
	wxClientDC dc(m_panel1);
	if (!m_original_image->Ok())
		return;

	*m_image = m_original_image->Copy();
	
	const int width = m_original_image->GetWidth();
	const int height = m_original_image->GetHeight();

	/// Wydzielenie obszaru do nalozenia cenzury
	const int cenzureHeight = 0.15 * height;
	const int cenzureWidth = 0.2 * width;
	const int offsetY = 0.03 * height;
	const int offsetX = 0.55 * width;

	/// Stworzenie i wypelnienie obiektu CImg na podstawie wybranego fragmentu zdjecia
	cimg_library::CImg<unsigned char> cImage(cenzureWidth, cenzureHeight, 1, 3);
	unsigned char* imgData = m_image->GetData();
	
	for (int y = 0; y < cenzureHeight; ++y) {
		for (int x = 0; x < cenzureWidth; ++x) {
			cImage(x, y, 0) = imgData[3 * ((y + offsetY) * width + x + offsetX) + 0];
			cImage(x, y, 1) = imgData[3 * ((y + offsetY) * width + x + offsetX) + 1];
			cImage(x, y, 2) = imgData[3 * ((y + offsetY) * width + x + offsetX) + 2];
		}
	}
		
	cImage.blur(3);

	/// "wklejenie" ocenzurowanego fragmentu do zdjecia
	for (int y = 0; y < cenzureHeight; ++y) {
		for (int x = 0; x < cenzureWidth; ++x) {
			imgData[3 * ((y + offsetY) * width + x + offsetX) + 0] = cImage(x, y, 0);
			imgData[3 * ((y + offsetY) * width + x + offsetX) + 1] = cImage(x, y, 1);
			imgData[3 * ((y + offsetY) * width + x + offsetX) + 2] = cImage(x, y, 2);
		}
	}

	refresh(dc);
}

void GUIMyFrame::erodeHandler( wxCommandEvent& event ) {
	wxClientDC dc(m_panel1);
	if (!m_original_image->Ok())
		return;

	*m_image = m_original_image->Copy();
		
	const int height = m_image->GetHeight();
	const int width = m_image->GetWidth();

	/// stworzenie kopii zdjecia jako obiektu CImg
	cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
	unsigned char* imgData = m_image->GetData();
		
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			cImage(x, y, 0) = imgData[3 * (y * width + x) + 0];
			cImage(x, y, 1) = imgData[3 * (y * width + x) + 1];
			cImage(x, y, 2) = imgData[3 * (y * width + x) + 2];
		}
	}
		
	cImage.erode(6, 6);

	/// Powrotne kopiowanie zmodyfikowanego juz zdjecia do obiektu wxImage
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			imgData[3 * (y * width + x) + 0] = cImage(x, y, 0);
			imgData[3 * (y * width + x) + 1] = cImage(x, y, 1);
			imgData[3 * (y * width + x) + 2] = cImage(x, y, 2);
		}
	}
	refresh(dc);
}

void GUIMyFrame::animationHandler( wxCommandEvent& event ) {
	if (!m_original_image->IsOk() || !m_checkBox1->IsChecked())
		return;

	// na wiecej nie wystarczylo sil
}

void GUIMyFrame::refresh(wxClientDC& dc) const {
	wxBufferedDC buff(&dc);
	if (m_image->Ok()) {
		m_image->Rescale(dc.GetSize().x, dc.GetSize().y);
		const wxBitmap bitmap(*m_image);
		buff.DrawBitmap(bitmap, 0, 0);
	}
}

GUIMyFrame::~GUIMyFrame() {
	delete m_image;
	delete m_original_image;
}



wxString GetMetadata(FIBITMAP* bitmap) {
	FITAG* tag = nullptr;
	FIMETADATA* metadata = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, bitmap, &tag);
	wxString metadataString = "";
	
	metadataString << "Rozmiar obrazka: " << FreeImage_GetWidth(bitmap) << "x" << FreeImage_GetHeight(bitmap) << "\n";
	metadataString << "EXIF Info:" << "\r\n";


	if (metadata) {
		/// petla pobierajaca metadane typu EXIF do momentu ich wyczerpania
		do {
			metadataString << FreeImage_GetTagKey(tag) << ": " << FreeImage_TagToString(FIMD_EXIF_MAIN, tag) << "\n";
		} while (FreeImage_FindNextMetadata(metadata, &tag));

		FreeImage_FindCloseMetadata(metadata);
	}
	return metadataString;
}