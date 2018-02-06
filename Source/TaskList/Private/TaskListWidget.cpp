// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskListWidget.h"
#include "TaskSearchResult.h"
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "Editor/UnrealEd/Public/EdGraphNode_Comment.h"

#define LOCTEXT_NAMESPACE "FTaskListModule"

void STaskListWidget::Construct(const FArguments& Args)
{
	this->ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				//SNew(SButton)
				SAssignNew(TreeViewWidget, STreeView<TaskSearchResultSharedPtr>)
				.ItemHeight(24)
				.TreeItemsSource(&FoundTasks)
				.OnGenerateRow(this, &STaskListWidget::OnGenerateRow)
				.OnGetChildren(this, &STaskListWidget::OnGetChildren)
			]
		];
	UpdateActiveResults();
}

TSharedRef<ITableRow> STaskListWidget::OnGenerateRow(TaskSearchResultSharedPtr Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	FString RowTitle = "No Title Found";
	/*
	if (Item->bIsCategory)
	{
		RowTitle = Item->CategoryID;
	}
	
	else
	{
		if (Item->TargetCommentNode)
		{
			RowTitle = Item->TargetCommentNode->GetFullName();
		}
	}
	*/
	return
		SNew(STableRow<TaskSearchResultSharedPtr>, OwnerTable)
		.Padding(2.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(RowTitle))
		];	
}

void STaskListWidget::OnGetChildren(TaskSearchResultSharedPtr Item, TArray<TaskSearchResultSharedPtr>& OutChildren)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Trying to get children"))
	Item->GetChildren(OutChildren);
	/*
	if (!Item->TargetCommentNode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to return children"))
		Item->GetChildren(OutChildren);
	}
	*/
}

void STaskListWidget::UpdateActiveResults()
{
	FAssetRegistryModule& ActiveAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	
	TArray<FAssetData> AssetData;
	ActiveAssetRegistryModule.Get().GetAssetsByClass(FName("Blueprint"), AssetData);
	
	TSet<FString> ActiveFoundTasks;

	TMap<FString, FTaskSearchResult> TaskResultsMap;
	for (auto& ActiveTaskPrefix : TaskPrefixes)
	{
		TaskResultsMap.Add(ActiveTaskPrefix, FTaskSearchResult(ActiveTaskPrefix));
	}

	for (auto& ActiveBPAssetData : AssetData)
	{
		TArray<UEdGraph*> AllActiveGraphs;
		
		UBlueprint* ActiveBlueprint = Cast<UBlueprint>(ActiveBPAssetData.GetAsset());
		ActiveBlueprint->GetAllGraphs(AllActiveGraphs);

		for (auto& ActiveGraph : AllActiveGraphs)
		{
			TArray<UEdGraphNode_Comment*> AllActiveCommentNodes;
			ActiveGraph->GetNodesOfClass(AllActiveCommentNodes);

			for (auto& ActiveCommentNode : AllActiveCommentNodes)
			{
				for (auto& ActiveTaskPrefix : TaskPrefixes)
				{
					if (ActiveCommentNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString().StartsWith(ActiveTaskPrefix))
					{
						TaskResultsMap.Find(ActiveTaskPrefix)->AddChild(MakeShareable(new FTaskSearchResult(ActiveBlueprint, ActiveGraph, ActiveCommentNode, ActiveTaskPrefix)));
						//UE_LOG(LogTemp, Warning, TEXT("Found Child for %s"), *ActiveTaskPrefix)
						ActiveFoundTasks.Add(ActiveTaskPrefix);
					}
				}
			}
		}
	}
	
	for (auto& ActiveTaskPrefix : ActiveFoundTasks)
	{
		FoundTasks.Add(MakeShareable(TaskResultsMap.Find(ActiveTaskPrefix)));
	}

	TreeViewWidget->RequestListRefresh();
}
