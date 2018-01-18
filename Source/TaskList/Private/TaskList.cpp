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

static const FName TaskListTabName("Task List");

#define LOCTEXT_NAMESPACE "FTaskListModule"

void FTaskListModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
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
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTaskListStyle::Shutdown();

	FTaskListCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TaskListTabName);
}

TSharedRef<SDockTab> FTaskListModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//FText WidgetText = LOCTEXT("WindowWidgetText","I can use built in example plugins. I can even change their icon. Someday some code will run.");
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
				.OnClicked_Raw(this, &FTaskListModule::UpdateTaskList)
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

FReply FTaskListModule::UpdateTaskList()
{
	//TODO only get blueprints in content folder, ignore all blueprints in engine folder. Futhermore, allow user to constrain their search to within a specific directory, default to content.
	//TODO allow for many different prefixes, or "tokens" as VS calls them
	//TODO visual studio allows for the creation of "shortcuts" basically things to showup in the task list iwthout being a comment
	//TODO visual stuio allows for arbitrary white space before the token, should we care about that?
	//TODO consider supporting comments in other graphs, like materials, sound cues, animation bps/graphs and others I'm sure I'm forgetting. Probably should allow users to select the classes they want to search.
	//TODO allow users to optionally remove the prefix from the display of the item
	
	//NextList
	//Need to layout the UI, build a method to retun SBox, or Sbutton, or some other slate object when given a TTaskSearchResult
	//	FPropertyEditorModule maybe can show a TMap of keys "ActualTokens" and values "Display Names"
	//Need to Update list when SWindow::OnIsActiveChanged is called, need to figure out how to bind to that.
	//In the mean time, we can keep using the button to do that, after formatting the UI.
	/*
	Replace updateTaskList with 2 method calls array of TTaskSearchResult ParseProjectForTaskList() and void RefreshTaskDisplay(array of TTaskSearchResults)
	This will allow us to insert fake results if necessary(either for testing or for "found nothing" results.)
	*/
	//FKismetEditorUtilities::BringKismetToFocusAttentionOnObject
	//UE_LOG(LogTemp, Warning, TEXT("We do a thing when we hit the buton."))
	
	FString TaskPrefix = FString("Dragons"); //TODO promote this to property of the class, transform into array, and figure out configuration
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByClass(FName("Blueprint"), AssetData);
	
	TArray<UEdGraphNode_Comment*> ResultCommentNodes;
	
	for (auto& ActiveBPAssetData : AssetData)
	{
		UBlueprint* ActiveBlueprint = Cast<UBlueprint>(ActiveBPAssetData.GetAsset());
		
		TArray<UEdGraph*> AllActiveGraphs;
		ActiveBlueprint->GetAllGraphs(AllActiveGraphs);

		for (auto& ActiveGraph : AllActiveGraphs)
		{
			TArray<UEdGraphNode_Comment*> AllActiveCommentNodes;
			ActiveGraph->GetNodesOfClass(AllActiveCommentNodes);
			for (auto& ActiveCommentNode : AllActiveCommentNodes)
			{
				if (ActiveCommentNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString().StartsWith(TaskPrefix))
				{
					ResultCommentNodes.AddUnique(ActiveCommentNode);
					//ResultCommentNodes.Add(ActiveCommentNode);
				}
			}
		}

		for (auto& ActiveResultNode : ResultCommentNodes)
		{
			UE_LOG(LogTemp, Warning, TEXT("Comment: %s"), *ActiveResultNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString())
		}
		//UE_LOG(LogTemp, Warning, TEXT("Blueprint: %s, Comments: %i"), *ActiveBPAssetData.AssetName.ToString(), ResultCommentNodes.Num())
	}

	return FReply::Handled();
}

void FTaskListModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTaskListCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTaskListModule, TaskList)