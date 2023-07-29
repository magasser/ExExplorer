#include "eepch.h"
#include "ExExplorerApp.h"

#include "Core.h"
#include <vector>

void ExExplorerApp::OnUpdateCore()
{
	if (m_HasUpdated)
	{
		m_Explorer.SetCurrentPath(m_NewPath);
	}
}

void ExExplorerApp::OnUIRenderCore()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New");
			ImGui::Separator();
			ImGui::MenuItem("Exit");

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	uint32_t dockspaceId = ImGui::GetID("Dockspace");
	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	ImGui::Begin("Explorer");

	static ImGuiTableFlags tableFlags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
		| ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
		| ImGuiTableFlags_SizingFixedFit;

	if (ImGui::BeginTable("explorer_table", 4, tableFlags))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_NoHide);
		ImGui::TableSetupColumn("Last modified", ImGuiTableColumnFlags_NoHide);
		ImGui::TableSetupColumn("Type");
		ImGui::TableSetupColumn("Size");
		ImGui::TableSetupScrollFreeze(1, 1);
		ImGui::TableHeadersRow();

		if (!m_Explorer.HasCurrentPath())
		{
			for (const Drive& drive : m_Explorer.GetCurrentDrives())
			{
				auto test = std::format("##Drive {}", drive.GetRoot());
				const char* id = test.c_str();
				ImGui::PushID(id);


				ImGui::TableNextRow(ImGuiTableRowFlags_None);
				ImGui::TableSetColumnIndex(0);

				std::string t = std::format("{0} ({1})", drive.GetName(), drive.GetRoot());
				const char* driveLabel = t.c_str();

				if (drive.IsExplorable())
				{
					bool selected = false;
					if (ImGui::Selectable(driveLabel, &selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap))
					{
						m_NewPath = drive.GetRoot();
						m_HasUpdated = true;
					}

				}
				else
				{
					ImGui::TextUnformatted(driveLabel);
				}

				ImGui::PopID();
			}
		}
		else
		{
			for (const Entry& entry : m_Explorer.GetCurrentEntries())
			{
				ImGui::PushID(entry.GetName().c_str());

				ImGui::TableNextRow(ImGuiTableRowFlags_None);

				ImGui::TableSetColumnIndex(0);
				bool selected = false;
				if (ImGui::Selectable(entry.GetName().c_str(), &selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap))
				{
					m_NewPath = entry.GetPath();
					m_HasUpdated = true;
				}
				ImGui::TableSetColumnIndex(1);
				ImGui::TextUnformatted(std::format("{}", entry.GetLastModified()).c_str());
				ImGui::TableSetColumnIndex(2);
				ImGui::TextUnformatted(entry.GetExtension().c_str());
				ImGui::TableSetColumnIndex(3);
				ImGui::TextUnformatted(std::format("{} KB", (uintmax_t)entry.GetSize().GetKilobytes()).c_str());


				ImGui::PopID();
			}
			
		}

		ImGui::EndTable();
	}

	ImGui::End();

	ImGui::ShowDemoWindow();
}
