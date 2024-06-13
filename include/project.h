#pragma once

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textFile.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <fstream>
#include <iostream>
#include <vector>

/**
* реализует окно
* ...
* что-то ещё
*/
class MainFrame : public wxFrame
{
	void print_error(wxString msg); //< значение поля
public:
	static bool __is_wx;  //< значение поля
	wxTextCtrl* TitleOfNote;  //< значение поля
	wxTextCtrl* DescriptionOfNote;
	wxListBox* NotesArea;
	wxTextCtrl* NoteTitleDisplay;
	wxTextCtrl* NoteTextDisplay;
	wxButton* SaveNoteButton;
	wxTextCtrl* SearchField;
	wxButton* SearchButton;
	wxButton* AddNoteButton;
	wxButton* DeleteNoteButton;
	wxButton* SeeNoteButton;
	wxCheckListBox* CheckListBox; // пошла возня с чекбоксами
	wxTextCtrl* CheckBoxName; // поле для названия чек-бокса
	wxButton* AddCheckBox; // добавить чек-бокс
	wxCheckListBox* CompletedTasksList;
	wxCheckListBox* UncompletedTasksList;
	/**
	* что делает
	* \param title значение парамтра
	*/
	MainFrame(const wxString& title);
	/**
	* что делает
	* \param title значение парамтра
	*/
	void AddCheckboxButtonClicked(wxCommandEvent& evt);
	/**
	* что делает
	* \param title значение парамтра
	*/
	void AddNoteButtonClicked(wxCommandEvent& evt);
	void LoadNotes();
	void DeleteNoteButtonClicked(wxCommandEvent& evt);
	void SeeNoteButtonClicked(wxCommandEvent& evt);				
	void SaveNoteButtonClicked(wxCommandEvent& evt);
	void SearchButtonClicked(wxCommandEvent& evt);
};

class App : public wxApp
{
public:
	bool OnInit();
};
