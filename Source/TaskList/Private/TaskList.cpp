// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TaskList.h"
#include "TaskListStyle.h"
#include "TaskListCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName TaskListTabName("TaskList");

#define LOCTEXT_NAMESPACE "FTaskListModule"

void FTaskListModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// Novelty comit
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
		.SetDisplayName(LOCTEXT("FTaskListTabTitle", "TaskList"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTaskListModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTaskListStyle::Shutdown();

	FTaskListCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TaskListTabName);
}

TSharedRef<SDockTab> FTaskListModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = LOCTEXT("WindowWidgetText","I can use built in example plugins. I can even change their icon. Someday some code will run.");
	//FText::FromString(TEXT("FTaskListModule::OnSpawnPluginTab")),
	//FText::FromString(TEXT("TaskList.cpp"))

	/*
	Need to create an FStreamSearch(const FString& InSearchValue) Defined in "FindInBlueprintManager"
	Novelty commiut
	Need to create a delegate(perhaps with 1 param) see FindInBlueprints.h line 28
	*/


	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(LOCTEXT("Super Special Button", "Super Special Button"))
				//.OnClicked(this, &FTaskListModule::UpdateTaskList)
				//SNew(SButton)
				//.Text(LOCTEXT("DisplayTextureAtlases", "Display Texture Atlases"))
				//.OnClicked(this, &SWidgetReflector::HandleDisplayTextureAtlases)
	
				//.OnClicked(this, &SWidgetReflector::HandleDisplayTextureAtlases)
				//SNew(STextBlock)
				//.Text(WidgetText)
			]
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
