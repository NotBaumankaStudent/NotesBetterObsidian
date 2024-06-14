
#include "project.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textFile.h>
#include <wx/filename.h>
#include <wx/dir.h>

bool MainFrame::__is_wx = true;

//заимствование; развёртка макроса
int main(int argc, char* argv[]) {
	wxApp::SetInstance(new App());
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();

	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
	return 0;
}
//