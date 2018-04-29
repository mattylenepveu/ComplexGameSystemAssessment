#include "Window.h"

Window::Window()
{
	boxSize = ImVec2(90, 90);
}

Window::~Window()
{
}

bool Window::ConsoleWindow(char* filename, bool open)
{
	ImGui::SetNextWindowSize(ImVec2(900.0f, 500.0f));
	ImGui::Begin(filename, &open, ImGuiWindowFlags_NoResize);

	ImGui::BeginMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("New Project");

		if (ImGui::MenuItem("Load Audio"))
		{
			ImGui::OpenPopup(filename);
		}

		bool result = false;

		ImGui::MenuItem("Save Audio");
		ImGui::MenuItem("Save Audio As");
		ImGui::EndMenu();
	}

	int verticalSpacing = 70;
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(300.0f);
	ImGui::Button("PAUSE", ImVec2(50, 20));

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	ImGui::Button("PLAY", ImVec2(50, 20));

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	ImGui::Button("STOP", ImVec2(50, 20));

	ImGui::Unindent(513.0f);
	verticalSpacing = 5;
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(120.0f);
	ImGui::TextWrapped("FREQUENCY"),

		ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("PITCH");

	ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("SPEED");

	ImGui::Spacing();
	ImGui::Unindent(612.0f);

	ImGui::ListBoxHeader("", boxSize);
	ImGui::Selectable("Very Low", false);
	ImGui::Selectable("Low", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("High", false);
	ImGui::Selectable("Very High", false);
	ImGui::ListBoxFooter();

	ImGui::SameLine();
	ImGui::Indent(285.0f);

	ImGui::ListBoxHeader(" ", boxSize);
	ImGui::Selectable("Very Low", false);
	ImGui::Selectable("Low", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("High", false);
	ImGui::Selectable("Very High", false);
	ImGui::ListBoxFooter();

	ImGui::SameLine();
	ImGui::Indent(300.0f);

	ImGui::ListBoxHeader("  ", boxSize);
	ImGui::Selectable("Very Slow", false);
	ImGui::Selectable("Slow", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("Fast", false);
	ImGui::Selectable("Very Fast", false);
	ImGui::ListBoxFooter();

	ImGui::End();

	return false;
}

//--------------------------------------------------------------------------------
// https://github.com/mellinoe/synthapp/blob/master/src/synthapp/Widgets/FilePicker.cs
//--------------------------------------------------------------------------------

//bool Window::DrawFolder(char* selected, bool returnOnSelection = false)
//{
//	ImGui::Text("Current Folder: " + *(CurrentFolder));
//	bool result = false;
//
//	if (ImGui::BeginChildFrame(1, ImVec2(0, 600), 0))
//	{
//		DirectoryInfo di = new DirectoryInfo(CurrentFolder);
//		if (di.Exists)
//		{
//			if (di.Parent != null)
//			{
//				ImGui.PushStyleColor(ColorTarget.Text, RgbaFloat.Yellow.ToVector4());
//				if (ImGui.Selectable("../", false, SelectableFlags.DontClosePopups))
//				{
//					CurrentFolder = di.Parent.FullName;
//				}
//				ImGui.PopStyleColor();
//			}
//
//			foreach(var fse in Directory.EnumerateFileSystemEntries(di.FullName))
//			{
//				if (Directory.Exists(fse))
//				{
//					string name = Path.GetFileName(fse);
//					ImGui.PushStyleColor(ColorTarget.Text, RgbaFloat.Yellow.ToVector4());
//					if (ImGui.Selectable(name + "/", false, SelectableFlags.DontClosePopups))
//					{
//						CurrentFolder = fse;
//					}
//					ImGui.PopStyleColor();
//				}
//				else
//				{
//					string name = Path.GetFileName(fse);
//					bool isSelected = SelectedFile == fse;
//					if (ImGui.Selectable(name, isSelected, SelectableFlags.DontClosePopups))
//					{
//						SelectedFile = fse;
//						if (returnOnSelection)
//						{
//							result = true;
//							selected = SelectedFile;
//						}
//					}
//					if (ImGui.IsMouseDoubleClicked(0))
//					{
//						result = true;
//						selected = SelectedFile;
//						ImGui.CloseCurrentPopup();
//					}
//				}
//			}
//		}
//
//	}
//	ImGui::EndChildFrame();
//
//	if (ImGui.Button("Cancel"))
//	{
//		result = false;
//		ImGui.CloseCurrentPopup();
//	}
//
//	if (SelectedFile != null)
//	{
//		ImGui.SameLine();
//		if (ImGui.Button("Open"))
//		{
//			result = true;
//			selected = SelectedFile;
//			ImGui.CloseCurrentPopup();
//		}
//	}
//
//	return result;
//}

void Window::SetCurrentFolder(char* pCurrentFolder)
{
	CurrentFolder = pCurrentFolder;
}

char* Window::GetCurrentFolder()
{
	return CurrentFolder;
}
