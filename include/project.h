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
* ��������� ����
* ...
* ���-�� ���
*/
class MainFrame : public wxFrame
{
	void print_error(wxString msg); //< �������� ����
public:
	static bool __is_wx;  //< �������� ����
	wxTextCtrl* TitleOfNote;  //< �������� ����
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
	wxCheckListBox* CheckListBox; // ����� ����� � ����������
	wxTextCtrl* CheckBoxName; // ���� ��� �������� ���-�����
	wxButton* AddCheckBox; // �������� ���-����
	wxCheckListBox* CompletedTasksList;
	wxCheckListBox* UncompletedTasksList;
	/**
	* ��� ������
	* \param title �������� ��������
	*/
	MainFrame(const wxString& title);
	/**
	* ��� ������
	* \param title �������� ��������
	*/
	void AddCheckboxButtonClicked(wxCommandEvent& evt);
	/**
	* ��� ������
	* \param title �������� ��������
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
