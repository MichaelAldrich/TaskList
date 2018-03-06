// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskList.h"
#include "TaskListStyle.h"
#include "TaskListCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "Editor/UnrealEd/Public/EdGraphNode_Comment.h"
#include "TaskSearchResult.h"
#include "TaskListWidget.h"

static const FName TaskListTabName("Task List");

#define LOCTEXT_NAMESPACE "FTaskListModule"

void FTaskListModule::StartupModule()
{
	FTaskListStyle::Initialize();
	FTaskListStyle::ReloadTextures();

	FTaskListCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTaskListCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTaskListModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTaskListModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Compile", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTaskListModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TaskListTabName, FOnSpawnTab::CreateRaw(this, &FTaskListModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTaskListTabTitle", "Task List"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTaskListModule::ShutdownModule()
{
	FTaskListStyle::Shutdown();

	FTaskListCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TaskListTabName);
}

TSharedRef<SDockTab> FTaskListModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(STaskListWidget)
		];
}

void FTaskListModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(TaskListTabName);
}

void FTaskListModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FTaskListCommands::Get().OpenPluginWindow);
}

void FTaskListModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTaskListCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTaskListModule, TaskList)
