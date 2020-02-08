#pragma once

#include "Menu.h"
#include "IDocument.h"
#include "Document.h"

using namespace std;

class CEditor
{
public:
	CEditor(istream& inStrm = cin, ostream& outStrm = cout)
		: m_menu(inStrm, outStrm)
		, m_outStrm(outStrm)
		, m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });

		AddMenuItem("insertParagraph", "Inserts paragraph. Args: <position>|end <text>", &CEditor::InsertParagraph);
		AddMenuItem("insertImage", "Inserts image. Args: <position>|end <width> <height> <path>", &CEditor::InsertImage);
		AddMenuItem("setTitle", "Changes title. Args: <title>", &CEditor::SetTitle);
		AddMenuItem("list", "Show document", &CEditor::List);
		AddMenuItem("replaceText", "Replaces text of paragraph. Args: <position> <text>", &CEditor::ReplaceText);
		AddMenuItem("resizeImage", "Resizes image. Args: <position> <width> <height>", &CEditor::ResizeImage);
		AddMenuItem("deleteItem", "Deletes document item. Args: <position>", &CEditor::DeleteItem);
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
		AddMenuItem("save", "Saves document. Args: <path>", &CEditor::Save);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	typedef void (CEditor::*MenuHandler)(std::istream& in);

	CMenu m_menu;
	std::ostream& m_outStrm;
	std::unique_ptr<IDocument> m_document;

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, placeholders::_1));
	}

	void InsertParagraph(istream& in)
	{
		try
		{
			optional<size_t> position = ReadOptionalPosition(in);
			string text = ReadLine(in);
			m_document->InsertParagraph(text, position);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;
		}
	}
	void InsertImage(istream& in)
	{
		try
		{
			optional<size_t> position = ReadOptionalPosition(in);

			int width;
			int height;
			ReadSizes(in, width, height);

			string path = ReadLine(in);

			m_document->InsertImage(path, width, height, position);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;
		}
	}
	void SetTitle(istream& in)
	{
		string title = ReadLine(in);
		m_document->SetTitle(title);
	}
	void List(istream&)
	{
		m_outStrm << "-------------" << endl;
		m_outStrm << "Title: " << m_document->GetTitle() << endl;
		for (size_t i = 0; i < m_document->GetItemsCount(); i++)
		{
			shared_ptr<IImage> image = m_document->GetItem(i).GetImage();
			if (image == nullptr)
			{
				m_outStrm << i << ". Paragraph: " << m_document->GetItem(i).GetParagraph()->GetText() << endl;
			}
			else
			{
				m_outStrm << i << ". Image: " << image->GetWidth() << ' ' << image->GetHeight() << ' ' << image->GetPath() << endl;
			}
		}
		m_outStrm << "-------------" << endl;
	}
	void ReplaceText(istream& in)
	{
		try
		{
			size_t index = ReadPosition(in);
			string text = ReadLine(in);
			m_document->ReplaceText(text, index);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;
		}
	}
	void ResizeImage(istream& in)
	{
		try
		{
			size_t index = ReadPosition(in);

			int width;
			int height;
			ReadSizes(in, width, height);

			m_document->ResizeImage(width, height, index);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;
		}
	}
	void DeleteItem(istream& in)
	{
		try
		{
			size_t index = ReadPosition(in);
			m_document->DeleteItem(index);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;
		}
	}
	void Undo(istream&)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
		}
		else
		{
			m_outStrm << "Can't undo" << endl;
		}
	}
	void Redo(istream&)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
		}
		else
		{
			m_outStrm << "Can't redo" << endl;
		}
	}
	void Save(istream& in)
	{
		string path = ReadLine(in);
		try
		{
			m_document->Save(path);
		}
		catch (runtime_error& exc)
		{
			m_outStrm << exc.what() << endl;;
		}
	}

	string ReadLine(istream& in) const
	{
		string head;
		string tail;
		if (in >> head)
		{
			getline(in, tail);
		}
		return head + tail;
	}
	void ReadSizes(istream& in, int& width, int& height) const
	{
		string str1;
		string str2;
		in >> str1 >> str2;

		if (!in)
		{
			throw runtime_error("Not specified sizes of image");
		}

		int tmpWidth;
		int tmpHeight;
		try
		{
			tmpWidth = stoi(str1);
			tmpHeight = stoi(str2);
		}
		catch (...)
		{
			throw runtime_error("Not specified sizes of image");
		}

		width = tmpWidth;
		height = tmpHeight;
	}
	size_t ReadPosition(istream& in) const
	{
		string str;
		in >> str;

		if (!in)
		{
			throw runtime_error("Not specified position of the document");
		}

		return StringToUnsigned(str);
	}
	optional<size_t> ReadOptionalPosition(istream& in) const
	{
		string str;
		in >> str;

		if (!in)
		{
			throw runtime_error("Not specified position of the document");
		}

		optional<size_t> position;
		if (str != "end")
		{
			position = StringToUnsigned(str);
		}

		return position;
	}

	size_t StringToUnsigned(const string& str) const
	{
		int result;
		try
		{
			result = stoi(str);
		}
		catch (...)
		{
			throw runtime_error("Not specified position of the document");
		}

		if (result < 0)
		{
			throw runtime_error("Position cannot be a negative number");
		}

		return (size_t)result;
	}
};
