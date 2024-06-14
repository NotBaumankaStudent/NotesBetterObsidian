#include "project.h"



	void MainFrame::print_error(wxString msg) {
		if (__is_wx)
			wxMessageBox(msg, wxString("Ошибка"), wxOK | wxICON_WARNING);
		else
			throw std::runtime_error {msg};
	}
	
	MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
	{
		SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)); // заимствование, делает окно нерастяжимым и блокирует развёртку 
		wxPanel* panel = new wxPanel(this, wxID_ANY);
		wxStaticText* LabelApp = new wxStaticText(panel, wxID_ANY, "NOTES", wxPoint(390, 0), wxDefaultSize);
		wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
		LabelApp->SetFont(font);
		wxFont fontother(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
		wxStaticText* LabelAddTitle = new wxStaticText(panel, wxID_ANY, "Note Title:", wxPoint(5, 60), wxDefaultSize);
		LabelAddTitle->SetFont(fontother);
		wxStaticText* DescriptionLabel = new wxStaticText(panel, wxID_ANY, "Add Description:", wxPoint(5, 115), wxDefaultSize);
		DescriptionLabel->SetFont(fontother);
		wxStaticText* YourNotesLabel = new wxStaticText(panel, wxID_ANY, "Your Notes:", wxPoint(500, 60), wxDefaultSize);
		YourNotesLabel->SetFont(fontother);
		wxStaticText* SearchNoteLabel = new wxStaticText(panel, wxID_ANY, "Search Note:", wxPoint(720, 60), wxDefaultSize);
		SearchNoteLabel->SetFont(fontother);
		wxStaticText* CurrentNote = new wxStaticText(panel, wxID_ANY, "Current Note:", wxPoint(5, 390), wxDefaultSize);
		CurrentNote->SetFont(fontother);
		wxStaticText* CompletedTasks = new wxStaticText(panel, wxID_ANY, "Completed Tasks:", wxPoint(510, 420), wxDefaultSize);
		CompletedTasks->SetFont(fontother);
		wxStaticText* UncompletedTasks = new wxStaticText(panel, wxID_ANY, "Uncompleted Tasks:", wxPoint(510, 550), wxDefaultSize);
		UncompletedTasks->SetFont(fontother);
		TitleOfNote = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(5, 85), wxSize(250, 25));
		DescriptionOfNote = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(5, 140), wxSize(430, 100), wxTE_MULTILINE);
		NotesArea = new wxListBox(panel, wxID_ANY, wxPoint(500, 85), wxSize(220, 255), {});
		AddNoteButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(332, 340), wxSize(100, 33));
		DeleteNoteButton = new wxButton(panel, wxID_ANY, "Delete Note", wxPoint(625, 340), wxSize(96, 32));
		SeeNoteButton = new wxButton(panel, wxID_ANY, "See Note", wxPoint(530, 340), wxSize(96, 32));
		NoteTitleDisplay = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(5, 420), wxSize(200, 29), wxTE_READONLY);
		NoteTextDisplay = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(5, 450), wxSize(500, 250), wxTE_MULTILINE);
		SearchField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(720, 85), wxSize(160, 25));
		SearchButton = new wxButton(panel, wxID_ANY, "Search", wxPoint(720, 115), wxSize(92, 29));
		AddNoteButton->Bind(wxEVT_BUTTON, &MainFrame::AddNoteButtonClicked, this);
		DeleteNoteButton->Bind(wxEVT_BUTTON, &MainFrame::DeleteNoteButtonClicked, this);
		SeeNoteButton->Bind(wxEVT_BUTTON, &MainFrame::SeeNoteButtonClicked, this);
		SaveNoteButton = new wxButton(panel, wxID_ANY, "Save Note", wxPoint(200, 418), wxSize(96, 32));
		SaveNoteButton->Bind(wxEVT_BUTTON, &MainFrame::SaveNoteButtonClicked, this);
		SearchButton->Bind(wxEVT_BUTTON, &MainFrame::SearchButtonClicked, this);
		SaveNoteButton->Disable();
		NoteTextDisplay->Disable();
		NoteTitleDisplay->Disable();
		CheckListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(5, 240), wxSize(150, 150)); 
		CheckBoxName = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(155, 240), wxSize(150, 25)); 
		AddCheckBox = new wxButton(panel, wxID_ANY, "Add CheckBox", wxPoint(320, 240), wxSize(96, 32)); 
		AddCheckBox->Bind(wxEVT_BUTTON, &MainFrame::AddCheckboxButtonClicked, this); 
		CompletedTasksList = new wxCheckListBox(panel, wxID_ANY, wxPoint(510, 450), wxSize(200, 100));
		UncompletedTasksList = new wxCheckListBox(panel, wxID_ANY, wxPoint(510, 580), wxSize(200, 100));
		CompletedTasksList->Disable();
		UncompletedTasksList->Disable();
		CheckListBox->Disable();
		LoadNotes();
	}

	void MainFrame::AddCheckboxButtonClicked(wxCommandEvent& evt) 
	{
		wxString CheckBoxHead = CheckBoxName->GetValue();
		if (CheckBoxHead.IsEmpty())
		{
			print_error("Название чек-бокса не может быть пустым");
			return;
		}
		CheckListBox->Append(CheckBoxHead);
		this->CheckBoxName->Clear();
		CheckListBox->Enable();
	}


	void MainFrame::AddNoteButtonClicked(wxCommandEvent& evt) 
	{
		wxString DescriptionText = DescriptionOfNote->GetValue();
		wxString TitleText = TitleOfNote->GetValue();
		if (TitleText.IsEmpty())
		{
			print_error("Название заметки не может быть пустым");
			return; 
		}
		std::string basePath = "NotesBase/";
		std::string filename = basePath + TitleText.ToStdString() + ".txt";
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << DescriptionText.ToStdString();
			file << "\n";
			for (unsigned int i = 0; i < CheckListBox->GetCount(); ++i)
			{
				wxString itemText = CheckListBox->GetString(i);
				bool isChecked = CheckListBox->IsChecked(i);
				file << itemText.mb_str() << ": " << (isChecked ? "Checked 1" : "Unchecked 0") << std::endl;
			}
			NotesArea->Append(TitleText);
			this->TitleOfNote->Clear();
			this->DescriptionOfNote->Clear();
			this->CheckListBox->Clear(); 
			CheckListBox->Disable();
			file.close();
			wxMessageBox("Текст сохранен в файл '" + TitleText + ".txt'.", "Информация", wxOK | wxICON_INFORMATION);
		}
		else
		{
			wxMessageBox("Ошибка при сохранении файла '" + TitleText + ".txt'.", "Ошибка", wxOK | wxICON_ERROR);
		}
	}


	void MainFrame::LoadNotes()
	{

		wxString basePath = "NotesBase/";
		NotesArea->Clear();
		wxDir dir(basePath);
		if (dir.IsOpened())
		{
			wxString filename;
			bool cont = dir.GetFirst(&filename, "*.txt", wxDIR_FILES);
			while (cont)
			{
				if (wxFileName::FileExists(basePath + filename) && wxFileName(filename).GetExt().Lower() == "txt")
				{
					wxString note = wxFileName(filename).GetName();
					NotesArea->Append(note);
				}
				cont = dir.GetNext(&filename);
			}
		}
		else
		{
			wxMessageBox("Ошибка при открытии папки 'NotesBase'.", "Ошибка", wxOK | wxICON_ERROR);
		}
	}


	
	void MainFrame::DeleteNoteButtonClicked(wxCommandEvent& evt)
	{
		int selectedIndex = NotesArea->GetSelection();
		if (selectedIndex != wxNOT_FOUND)
		{
			wxString noteName = NotesArea->GetString(selectedIndex);
			NotesArea->Delete(selectedIndex);
			std::string basePath = "NotesBase/";
			std::string filename = basePath + noteName.ToStdString() + ".txt";
			if (wxRemoveFile(wxString(filename.c_str())))
			{
				wxMessageBox("Файл '" + wxString(filename.c_str()) + "' удален успешно.", "Информация", wxOK | wxICON_INFORMATION);
			}
			else
			{
				wxMessageBox("Ошибка при удалении файла '" + wxString(filename.c_str()) + "'.", "Ошибка", wxOK | wxICON_ERROR);
			}
		}
		else
		{
			wxMessageBox("Пожалуйста, выберите заметку для удаления.", "Предупреждение", wxOK | wxICON_WARNING);
		}
	}



	void MainFrame::SeeNoteButtonClicked(wxCommandEvent& evt)
	{
		int selectedIndex = NotesArea->GetSelection();
		if (selectedIndex != wxNOT_FOUND)
		{
			wxString noteName = NotesArea->GetString(selectedIndex);
			NoteTitleDisplay->SetValue(noteName);
			std::string basePath = "NotesBase/";
			std::string filename = basePath + noteName.ToStdString() + ".txt";
			std::ifstream file(filename);
			if (file.is_open())
			{
				std::string line;
				std::string noteText;
				std::vector<std::string> unchecked0Block;
				std::vector<std::string> checked1Block;
				while (std::getline(file, line))
				{
					
					size_t pos = line.find(":");
					if (pos != std::string::npos)
					{
						std::string checkboxName = line.substr(0, pos); 
						std::string status = line.substr(pos + 2); 

						
						if (status == "Unchecked 0")
						{
							unchecked0Block.push_back(checkboxName);
						}
						else if (status == "Checked 1")
						{
							checked1Block.push_back(checkboxName);
						}
						else
						{
							noteText += line + "\n";
						}
					}
					else
					{
						noteText += line + "\n";
					}
				}
				file.close();
				for (const auto& str : unchecked0Block)
				{
					UncompletedTasksList->Append(wxString(str));
				}
				for (const auto& str : checked1Block)
				{
					CompletedTasksList->Append(wxString(str));
				}
				for (unsigned int i = 0; i < CompletedTasksList->GetCount(); ++i)
				{
					CompletedTasksList->Check(i, true);
				}
				NoteTextDisplay->SetValue(wxString(noteText));
				NoteTextDisplay->Enable();
				SaveNoteButton->Enable();
				CompletedTasksList->Enable();
				UncompletedTasksList->Enable();
				SeeNoteButton->Disable();
				DeleteNoteButton->Disable();
			}
			else
			{
				wxMessageBox("Ошибка при чтении файла '" + wxString(filename.c_str()) + "'.", "Ошибка", wxOK | wxICON_ERROR);
			}
		}
		else
		{
			wxMessageBox("Пожалуйста, выберите заметку для просмотра.", "Предупреждение", wxOK | wxICON_WARNING);
		}
	}



	void MainFrame::SaveNoteButtonClicked(wxCommandEvent& evt)
	{
		int selectedIndex = NotesArea->GetSelection();
		if (selectedIndex != wxNOT_FOUND)
		{
			wxString noteName = NotesArea->GetString(selectedIndex);
			std::string basePath = "NotesBase/";
			std::string filename = basePath + noteName.ToStdString() + ".txt";
			std::ofstream file(filename);
			if (file.is_open())
			{
				file << NoteTextDisplay->GetValue().ToStdString();
				file << "\n";
				for (unsigned int i = 0; i < CompletedTasksList->GetCount(); ++i)
				{
					wxString itemText = CompletedTasksList->GetString(i);
					bool isChecked = CompletedTasksList->IsChecked(i);
					file << itemText.mb_str() << ": " << (isChecked ? "Checked 1" : "Unchecked 0") << std::endl;
				}
				for (unsigned int i = 0; i < UncompletedTasksList->GetCount(); ++i)
				{
					wxString itemText = UncompletedTasksList->GetString(i);
					bool isChecked = UncompletedTasksList->IsChecked(i);
					file << itemText.mb_str() << ": " << (isChecked ? "Checked 1" : "Unchecked 0") << std::endl;
				}

				file.close();
				wxMessageBox("Изменения сохранены.", "Информация", wxOK | wxICON_INFORMATION);
				NoteTitleDisplay->Clear();
				NoteTextDisplay->Clear();
				NoteTextDisplay->Disable();
				NoteTitleDisplay->Disable();
				SaveNoteButton->Disable();
				CompletedTasksList->Clear();
				UncompletedTasksList->Clear();
				CompletedTasksList->Disable();
				UncompletedTasksList->Disable();
				SeeNoteButton->Enable();
				DeleteNoteButton->Enable();
			}
			else
			{
				wxMessageBox("Ошибка при сохранении файла '" + wxString(filename.c_str()) + "'.", "Ошибка", wxOK | wxICON_ERROR);
			}
		}
		else
		{
			wxMessageBox("Пожалуйста, выберите заметку для сохранения.", "Предупреждение", wxOK | wxICON_WARNING);
		}
	}
	
	
	void MainFrame::SearchButtonClicked(wxCommandEvent& evt)
	{
		wxString searching = SearchField->GetValue();
		if (!searching.IsEmpty())
		{
			NotesArea->DeselectAll();
			for (unsigned long i = 0; i < NotesArea->GetCount(); ++i)
			{
				wxString noteName = NotesArea->GetString(i);
				if (noteName.Lower().Find(searching.Lower()) != wxNOT_FOUND)
				{
					NotesArea->SetSelection(i);
				}
			}
		}
		else
		{
			print_error("Введите название заметки, которую хотите найти.");
		}
	}
	
	bool App::OnInit()
	{
		MainFrame* mainFrame = new MainFrame("Notes");
		mainFrame->Show();
		mainFrame->SetClientSize(900, 720);
		mainFrame->Center();
		mainFrame->SetFocus();
		return true;
	}

