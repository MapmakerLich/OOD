#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../lw5/ChangeStringCommand.h"
#include "../lw5/InsertItemCommand.h"
#include "../lw5/ReplaceTextCommand.h"
#include "../lw5/ResizeImageCommand.h"
#include "../lw5/DeleteItemCommand.h"
#include "../lw5/Paragraph.h"
#include "../lw5/Image.h"
#include "../lw5/Document.h"
#include "../lw5/Editor.h"
#include "../lw5/History.h"
#include "../lw5/Menu.h"
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

TEST_CASE("Change string command tests")
{
	string str = "first";
	CChangeStringCommand command(str, "second");
	CHECK(str == "first");

	command.Unexecute();
	CHECK(str == "first");

	command.Execute();
	CHECK(str == "second");

	command.Execute();
	CHECK(str == "second");

	command.Unexecute();
	CHECK(str == "first");
}

TEST_CASE("Insert item command tests")
{
	vector<CDocumentItem> items;
	CDocumentItem item1(make_shared<CParagraph>("first"));

	CHECK_THROWS_AS(CInsertItemCommand(items, item1, 1), runtime_error);

	CInsertItemCommand command1(items, item1, nullopt);
	CHECK(items.empty());

	command1.Execute();
	CHECK(items.size() == 1);
	CHECK(items[0].GetParagraph()->GetText() == "first");

	command1.Unexecute();
	CHECK(items.empty());

	CDocumentItem item2(make_shared<CParagraph>("second"));
	CInsertItemCommand command2(items, item2, 0);

	command2.Execute();
	CHECK(items.size() == 1);
	CHECK(items[0].GetParagraph()->GetText() == "second");

	CDocumentItem item3(make_shared<CParagraph>("third"));
	CInsertItemCommand command3(items, item3, 0);

	command3.Execute();
	CHECK(items.size() == 2);
	CHECK(items[0].GetParagraph()->GetText() == "third");
	CHECK(items[1].GetParagraph()->GetText() == "second");

	command3.Unexecute();
	CHECK(items.size() == 1);
	CHECK(items[0].GetParagraph()->GetText() == "second");

	command2.Unexecute();
	CHECK(items.empty());
}

TEST_CASE("Replace paragraph text command tests")
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>("first");
	CReplaceTextCommand command(paragraph, "second");

	command.Execute();
	CHECK(paragraph->GetText() == "second");

	command.Unexecute();
	CHECK(paragraph->GetText() == "first");
}

TEST_CASE("Resize image command tests")
{
	shared_ptr<IImage> image = make_shared<CImage>("TestResources/fox.jpg", 200, 150);
	CResizeImageCommand command(image, 300, 200);

	command.Execute();
	CHECK(image->GetWidth() == 300);
	CHECK(image->GetHeight() == 200);

	command.Unexecute();
	CHECK(image->GetWidth() == 200);
	CHECK(image->GetHeight() == 150);
}

TEST_CASE("Delete item command tests")
{
	vector<CDocumentItem> items;

	CHECK_THROWS_AS(CDeleteItemCommand(items, 0), runtime_error);

	items.push_back(CDocumentItem(make_shared<CParagraph>("first")));
	items.push_back(CDocumentItem(make_shared<CParagraph>("second")));

	CDeleteItemCommand command1(items, 0);
	CHECK(items.size() == 2);
	CHECK(items[0].GetParagraph()->GetText() == "first");
	CHECK(items[1].GetParagraph()->GetText() == "second");

	command1.Execute();
	CHECK(items.size() == 1);
	CHECK(items[0].GetParagraph()->GetText() == "second");

	command1.Unexecute();
	CHECK(items.size() == 2);
	CHECK(items[0].GetParagraph()->GetText() == "first");
	CHECK(items[1].GetParagraph()->GetText() == "second");

	CDeleteItemCommand command2(items, 1);
	command2.Execute();
	CHECK(items.size() == 1);
	CHECK(items[0].GetParagraph()->GetText() == "first");

	command2.Unexecute();
	CHECK(items.size() == 2);
	CHECK(items[0].GetParagraph()->GetText() == "first");
	CHECK(items[1].GetParagraph()->GetText() == "second");
}

TEST_CASE("Paragraph tests")
{
	CParagraph paragraph("first");
	CHECK(paragraph.GetText() == "first");

	paragraph.SetText("second");
	CHECK(paragraph.GetText() == "second");
}

TEST_CASE("Image invalid arguments tests")
{
	CHECK_THROWS_AS(CImage("nonexistentFile", 200, 150), runtime_error);
	CHECK_THROWS_AS(CImage("TestResources/text.txt", 200, 150), runtime_error);
	CHECK_THROWS_AS(CImage("TestResources/fox.jpg", 0, 150), runtime_error);
	CHECK_THROWS_AS(CImage("TestResources/fox.jpg", 200, 10001), runtime_error);
}

TEST_CASE("Image tests")
{
	SECTION("Work with images")
	{
		CImage image1("TestResources/fox.jpg", 200, 150);

		CHECK(image1.GetPath() == "2.jpg");
		CHECK(image1.GetWidth() == 200);
		CHECK(image1.GetHeight() == 150);

		CHECK(filesystem::exists(image1.GetPath()));

		image1.Resize(1, 10000);

		CHECK(image1.GetWidth() == 1);
		CHECK(image1.GetHeight() == 10000);

		CImage image2("TestResources/fox.jpg", 200, 150);

		CHECK(image2.GetPath() == "3.jpg");
		CHECK(filesystem::exists(image2.GetPath()));
	}

	SECTION("Check delete images")
	{
		CHECK_FALSE(filesystem::exists("2.jpg"));
		CHECK_FALSE(filesystem::exists("3.jpg"));
	}
}

TEST_CASE("Document item tests")
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>("text");
	CConstDocumentItem constDocumentItem(paragraph);

	CHECK(constDocumentItem.GetImage() == nullptr);

	shared_ptr<const IParagraph> constParagraph = constDocumentItem.GetParagraph();
	CHECK(constParagraph->GetText() == "text");

	CDocumentItem documentItem(paragraph);

	CHECK(documentItem.GetImage() == nullptr);

	paragraph = documentItem.GetParagraph();
	CHECK(paragraph->GetText() == "text");
}

TEST_CASE("Document set title tests")
{
	CDocument document;

	CHECK(document.GetItemsCount() == 0);
	CHECK(document.GetTitle() == "");
	CHECK_FALSE(document.CanUndo());
	CHECK_FALSE(document.CanRedo());

	document.SetTitle("first");

	CHECK(document.GetTitle() == "first");
	CHECK(document.CanUndo());
	CHECK_FALSE(document.CanRedo());

	document.Undo();

	CHECK(document.GetTitle() == "");
	CHECK_FALSE(document.CanUndo());
	CHECK(document.CanRedo());

	document.Redo();

	CHECK(document.GetTitle() == "first");
	CHECK(document.CanUndo());
	CHECK_FALSE(document.CanRedo());
}

TEST_CASE("Document insert paragraph tests")
{
	CDocument document;
	document.InsertParagraph("first");

	CHECK(document.GetItemsCount() == 1);
	CHECK(document.GetItem(0).GetParagraph()->GetText() == "first");

	document.InsertParagraph("second", 0);

	CHECK(document.GetItemsCount() == 2);
	CHECK(document.GetItem(0).GetParagraph()->GetText() == "second");
	CHECK(document.GetItem(1).GetParagraph()->GetText() == "first");
}

TEST_CASE("Document insert image tests")
{
	CDocument document;
	document.InsertImage("TestResources/fox.jpg", 200, 150);

	CHECK(document.GetItemsCount() == 1);
	CHECK(document.GetItem(0).GetImage()->GetPath() == "4.jpg");
	CHECK(document.GetItem(0).GetImage()->GetWidth() == 200);
	CHECK(document.GetItem(0).GetImage()->GetHeight() == 150);
}

TEST_CASE("Document replace text of paragraph tests")
{
	CDocument document;
	document.InsertParagraph("first");

	CHECK_THROWS_AS(document.ReplaceText("second", 1), runtime_error);

	document.ReplaceText("second", 0);
	CHECK(document.GetItem(0).GetParagraph()->GetText() == "second");
}

TEST_CASE("Document resize image tests")
{
	CDocument document;
	document.InsertParagraph("first");
	document.InsertImage("TestResources/fox.jpg", 200, 150);

	CHECK_THROWS_AS(document.ResizeImage(300, 200, 0), runtime_error);

	document.ResizeImage(300, 200, 1);
	CHECK(document.GetItem(1).GetImage()->GetWidth() == 300);
	CHECK(document.GetItem(1).GetImage()->GetHeight() == 200);
}

TEST_CASE("Document delete item tests")
{
	CDocument document;
	document.InsertParagraph("first");

	document.DeleteItem(0);

	CHECK(document.GetItemsCount() == 0);
}

TEST_CASE("Document save tests")
{
	CDocument document;
	document.SetTitle("<title>");
	document.InsertParagraph("\"first\"");
	document.InsertParagraph("&'second'");
	document.InsertImage("TestResources/fox.jpg", 200, 150);

	CHECK_THROWS_AS(document.Save("nonexistentFolder"), runtime_error);

	filesystem::create_directory("TestResults");
	document.Save("TestResults");

	CHECK(filesystem::exists("TestResults/images/6.jpg"));

	ifstream fIn("TestResults/index.html");
	string str;

	getline(fIn, str);
	CHECK("<!DOCTYPE html>");
	getline(fIn, str);
	CHECK("<html>");
	getline(fIn, str);
	CHECK("  <head>");
	getline(fIn, str);
	CHECK("    <title>&lt;title&gt;</title>");
	getline(fIn, str);
	CHECK("  </head>");
	getline(fIn, str);
	CHECK("  <body>");
	getline(fIn, str);
	CHECK("    <h1>&lt;title&gt;</h1>");
	getline(fIn, str);
	CHECK("    <p>&quot;first&quot;</p>");
	getline(fIn, str);
	CHECK("    <p>&amp;&apos;second&apos;</p>");
	getline(fIn, str);
	CHECK("    <img src=\"images/6.jpg\" width=\"200\" height=\"150\">");
	getline(fIn, str);
	CHECK("  </body>");
	getline(fIn, str);
	CHECK("</html>");

	CHECK_FALSE(getline(fIn, str));
}

TEST_CASE("Editor tests")
{
	istringstream inStrm("list\nundo\nredo\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "Commands list:");
	getline(result, str);
	CHECK(str == "  help: Help");
	getline(result, str);
	CHECK(str == "  exit: Exit");
	getline(result, str);
	CHECK(str == "  insertParagraph: Inserts paragraph. Args: <position>|end <text>");
	getline(result, str);
	CHECK(str == "  insertImage: Inserts image. Args: <position>|end <width> <height> <path>");
	getline(result, str);
	CHECK(str == "  setTitle: Changes title. Args: <title>");
	getline(result, str);
	CHECK(str == "  list: Show document");
	getline(result, str);
	CHECK(str == "  replaceText: Replaces text of paragraph. Args: <position> <text>");
	getline(result, str);
	CHECK(str == "  resizeImage: Resizes image. Args: <position> <width> <height>");
	getline(result, str);
	CHECK(str == "  deleteItem: Deletes document item. Args: <position>");
	getline(result, str);
	CHECK(str == "  undo: Undo command");
	getline(result, str);
	CHECK(str == "  redo: Redo undone command");
	getline(result, str);
	CHECK(str == "  save: Saves document. Args: <path>");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "-------------");

	getline(result, str);
	CHECK(str == "Can't undo");

	getline(result, str);
	CHECK(str == "Can't redo");

	CHECK_FALSE(getline(result, str));
}

TEST_CASE("Editor set title tests")
{
	istringstream inStrm("setTitle word1 word2\nlist\nundo\nlist\nredo\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: word1 word2");
	getline(result, str);
	CHECK(str == "-------------");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "-------------");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: word1 word2");
	getline(result, str);
	CHECK(str == "-------------");

	CHECK_FALSE(getline(result, str));
}

TEST_CASE("Editor insert paragraph tests")
{
	istringstream inStrm("insertParagraph\ninsertParagraph word\ninsertParagraph end word1 word2\ninsertParagraph 0 word3\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "Not specified position of the document");
	getline(result, str);
	CHECK(str == "Not specified position of the document");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "0. Paragraph: word3");
	getline(result, str);
	CHECK(str == "1. Paragraph: word1 word2");
	getline(result, str);
	CHECK(str == "-------------");
}

TEST_CASE("Editor insert image tests")
{
	istringstream inStrm("insertImage 0 TestResources/fox.jpg\ninsertImage 0 5 a TestResources/fox.jpg\ninsertImage 0 20 15 TestResources/fox.jpg\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "Not specified sizes of image");
	getline(result, str);
	CHECK(str == "Not specified sizes of image");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "0. Image: 20 15 7.jpg");
	getline(result, str);
	CHECK(str == "-------------");
}

TEST_CASE("Editor replace text of paragraph tests")
{
	istringstream inStrm("insertParagraph end word1\nreplaceText\nreplaceText word2\nreplaceText 0 word2\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "Not specified position of the document");
	getline(result, str);
	CHECK(str == "Not specified position of the document");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "0. Paragraph: word2");
	getline(result, str);
	CHECK(str == "-------------");
}

TEST_CASE("Editor resize image tests")
{
	istringstream inStrm("insertImage 0 200 150 TestResources/fox.jpg\nresizeImage 0 300 200\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "0. Image: 300 200 8.jpg");
	getline(result, str);
	CHECK(str == "-------------");
}

TEST_CASE("Editor delete item tests")
{
	istringstream inStrm("insertParagraph end word\ndeleteItem\ndeleteItem abc\ndeleteItem 0\nlist\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);
	getline(result, str);

	getline(result, str);
	CHECK(str == "Not specified position of the document");
	getline(result, str);
	CHECK(str == "Not specified position of the document");

	getline(result, str);
	CHECK(str == "-------------");
	getline(result, str);
	CHECK(str == "Title: ");
	getline(result, str);
	CHECK(str == "-------------");
}

TEST_CASE("Editor save tests")
{
	istringstream inStrm("save TestResults\nexit");
	ostringstream outStrm;
	CEditor editor(inStrm, outStrm);

	editor.Start();

	ifstream fIn("TestResults/index.html");
	string str;

	getline(fIn, str);
	CHECK("<!DOCTYPE html>");
	getline(fIn, str);
	CHECK("<html>");
	getline(fIn, str);
	CHECK("  <head>");
	getline(fIn, str);
	CHECK("    <title></title>");
	getline(fIn, str);
	CHECK("  </head>");
	getline(fIn, str);
	CHECK("  <body>");
	getline(fIn, str);
	CHECK("    <h1></h1>");
	getline(fIn, str);
	CHECK("  </body>");
	getline(fIn, str);
	CHECK("</html>");
}

TEST_CASE("History tests")
{
	CHistory history;
	CHECK_FALSE(history.CanUndo());
	CHECK_FALSE(history.CanRedo());

	string str;

	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "first"));

	CHECK(str == "first");
	CHECK(history.CanUndo());
	CHECK_FALSE(history.CanRedo());

	history.Undo();

	CHECK(str == "");
	CHECK_FALSE(history.CanUndo());
	CHECK(history.CanRedo());

	history.Redo();

	CHECK(str == "first");
	CHECK(history.CanUndo());
	CHECK_FALSE(history.CanRedo());

	history.Undo();
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "second"));

	CHECK(str == "second");
	CHECK(history.CanUndo());
	CHECK_FALSE(history.CanRedo());

	history.Undo();

	CHECK(str == "");
	CHECK_FALSE(history.CanUndo());
	CHECK(history.CanRedo());
}

TEST_CASE("10 commands tests")
{
	CHistory history;
	string str;

	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "1"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "2"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "3"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "4"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "5"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "6"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "7"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "8"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "9"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "10"));
	history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(str, "11"));

	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();

	CHECK(history.CanUndo());

	history.Undo();

	CHECK_FALSE(history.CanUndo());
	CHECK(str == "1");
}

TEST_CASE("Menu tests")
{
	istringstream inStrm("help\nUnknownCommand\nexit\nhelp");
	ostringstream outStrm;
	CMenu menu(inStrm, outStrm);

	menu.AddItem("help", "Help", [&](istream&) { menu.ShowInstructions(); });
	menu.AddItem("exit", "Exit", [&](istream&) { menu.Exit(); });

	menu.Run();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "Commands list:");
	getline(result, str);
	CHECK(str == "  help: Help");
	getline(result, str);
	CHECK(str == "  exit: Exit");

	getline(result, str);
	CHECK(str == "Commands list:");
	getline(result, str);
	CHECK(str == "  help: Help");
	getline(result, str);
	CHECK(str == "  exit: Exit");

	getline(result, str);
	CHECK(str == "Unknown command");

	CHECK_FALSE(getline(result, str));
}