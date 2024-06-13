
#include "project.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textFile.h>
#include <wx/filename.h>
#include <wx/dir.h>
//wxIMPLEMENT_APP(App);

bool MainFrame::__is_wx = true;


int main(int argc, char* argv[]) {
	wxApp::SetInstance(new App());
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();

	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
	return 0;
}