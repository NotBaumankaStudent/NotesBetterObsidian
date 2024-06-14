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
* @class MainFrame
* @brief Realizes the main application window.
*/
class MainFrame : public wxFrame
{
	/**
	 * @brief Displays an error message.
	 * @param msg Error message.
	 */
	void print_error(wxString msg); 
public:
	static bool __is_wx;  ///< Indicates where to output errors.
	wxTextCtrl* TitleOfNote;  ///< Text Field For Input Title Of Note
	wxTextCtrl* DescriptionOfNote; ///< Text field for entering a description of the note
	wxListBox* NotesArea; ///< A field for displaying all user notes
	wxTextCtrl* NoteTitleDisplay; ///< Field for displaying the note title
	wxTextCtrl* NoteTextDisplay; ///< A field for displaying the text of the note content
	wxButton* SaveNoteButton; ///< Button to save the viewed note
	wxTextCtrl* SearchField; ///< The field for the note to be searched
	wxButton* SearchButton;  ///< Button to search for a note
	wxButton* AddNoteButton; ///< Button to add a note
	wxButton* DeleteNoteButton; ///< Creating a button to delete a note
	wxButton* SeeNoteButton; ///< Button to view the contents of the note
	wxCheckListBox* CheckListBox; ///< A list showing the checkboxes that the user adds to the note
	wxTextCtrl* CheckBoxName; ///< Field for entering the checkbox name
	wxButton* AddCheckBox;  ///< Button for adding a checkbox
	wxCheckListBox* CompletedTasksList; ///< A list displaying completed checkboxes
	wxCheckListBox* UncompletedTasksList; ///< List showing uncompleted checkboxes
	/**
	* @brief MainFrame class constructor.
	* \param title The title of main window.
	*/
	MainFrame(const wxString& title);
	/**
	* @brief Add Checkbox in the note.
	* 
	* This method adds the checkbox entered by the user to the CheckListBox list. 
	* After the checkbox is added to the list, the CheckBoxName input field is cleared.
	* 
	* \param evt Event(button click)
	*/
	void AddCheckboxButtonClicked(wxCommandEvent& evt);
	/**
	* @brief Add note.
	* 
	* This method saves the new note to a file.
	* After saving the note to a file, the CheckListBox, TitleOfNote and DescriptionOfNote input fields are cleared.
	* 
	* \param evt Event(button click)
	*/
	void AddNoteButtonClicked(wxCommandEvent& evt);
	/**
	* @brief Load Notes from directory.
	* 
	* This method scans the "NotesBase" folder for files with the ".txt" extension.
	* If the directory is successfully opened and files are found, the method adds their names to the notes list.
	*/
	void LoadNotes();
	/**
	* @brief Delete choosen note.
	* 
	* The method removes the selected note from the notes list and folder. In case of an error, an error or warning is displayed.
	* 
	* \param evt Event(button click)
	*/
	void DeleteNoteButtonClicked(wxCommandEvent& evt);
	/**
	* @brief Check choosen Note.
	* 
	* This method shows the content of the selected note from a file. The "delete note" and "view note" buttons become inactive to avoid conflicts.
	* 
	* \param evt Event(button click)
	*/
	void SeeNoteButtonClicked(wxCommandEvent& evt);		
	/**
	* @brief Save Note that is checking.
	* 
	* This method saves changes to the selected note, including the note text and checkbox state.
	* After saving the note, the method clears the note's display fields and makes them inactive. 
	* The View Note and Delete Note buttons become active.

	* \param evt Event(button click)
	*/
	void SaveNoteButtonClicked(wxCommandEvent& evt);
	/**
	* @brief Search Note.
	* 
	* This method searches for a note. The note title is taken from the search field. 
	* The method goes through the list of notes and selects the note.
	* 
	* \param evt Event(button click)
	*/
	void SearchButtonClicked(wxCommandEvent& evt);
};
/**
* @class App
* @brief Realizes the application.
*/
class App : public wxApp
{
public:
	/**
	 * @brief Initializes the application.
	 * @return true if initialization is successful, false if not.
	 */
	bool OnInit();
};
