#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textFile.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include "project.h"

bool MainFrame::__is_wx = false;


TEST_CASE("Test AddCheckboxButtonClickedIfIsEmpty") {

	MainFrame mf("");
	wxString exp_err{ "Ќазвание чек-бокса не может быть пустым" },
			 curr_err{};
	wxCommandEvent evt;
	CHECK_THROWS_AS(mf.AddCheckboxButtonClicked(evt), std::runtime_error);

	try { mf.AddCheckboxButtonClicked(evt); }
	catch (std::runtime_error& err) { curr_err = err.what(); }

	CHECK(curr_err == exp_err);
}


TEST_CASE("Test AddNoteButtonClicked") {

	MainFrame mf("");
	wxString exp_err{ "Ќазвание заметки не может быть пустым" },
		curr_err{};
	wxCommandEvent evt;
	CHECK_THROWS_AS(mf.AddNoteButtonClicked(evt), std::runtime_error);

	try { mf.AddNoteButtonClicked(evt); }
	catch (std::runtime_error& err) { curr_err = err.what(); }

	CHECK(curr_err == exp_err);
}

TEST_CASE("Test SearchButtonClicked") {

	MainFrame mf("");
	wxString exp_err{ "¬ведите название заметки, которую хотите найти." },
		curr_err{};
	wxCommandEvent evt;
	CHECK_THROWS_AS(mf.SearchButtonClicked(evt), std::runtime_error);

	try { mf.SearchButtonClicked(evt); }
	catch (std::runtime_error& err) { curr_err = err.what(); }

	CHECK(curr_err == exp_err);
}


TEST_CASE("Test AddCheckboxButtonClickedIsNotEmpty") {

	MainFrame mf("");

	mf.CheckBoxName->SetValue("somethingwaswritten");

	wxCommandEvent evt;
	mf.AddCheckboxButtonClicked(evt);

	CHECK(mf.CheckListBox->GetCount() == 1);
}



