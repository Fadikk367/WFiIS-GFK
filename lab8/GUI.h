///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
	private:

	protected:
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		wxCheckBox* m_checkBox1;
		wxGauge* m_gauge1;
		wxTextCtrl* m_textCtrl1;
		wxPanel* m_panel1;

		// Virtual event handlers, overide them in your derived class
		virtual void onUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
		virtual void loadImageHandler( wxCommandEvent& event ) { event.Skip(); }
		virtual void putCenzureHandler( wxCommandEvent& event ) { event.Skip(); }
		virtual void erodeHandler( wxCommandEvent& event ) { event.Skip(); }
		virtual void animationHandler( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxString("GFK lab 8"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1120,606 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame();

};

