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
	ActiveAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	this->ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(LOCTEXT("AddSomethingText", "Add something."))
		.OnClicked(this, &STaskListWidget::ButtonPressed)
		]
	+ SScrollBox::Slot()
		[
			SAssignNew(ListViewWidget, STreeView<TaskSearchResultSharedPtr>)
			.ItemHeight(24)
		.TreeItemsSource(&ActiveResults)
		.OnGenerateRow(this, &STaskListWidget::OnGenerateRow)
		.OnGetChildren(this, &STaskListWidget::OnGetChildren)
		]
		];
	UpdateActiveResults();
}

TSharedRef<ITableRow> STaskListWidget::OnGenerateRow(TaskSearchResultSharedPtr Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	/*
	if (Item->StartsWith("A"))
	{
	return
	SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	.Padding(2.0f)
	[
	SNew(STextBlock).Text(FText::FromString(*Item.Get()))
	];
	}
	else
	{
	*/
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable);
	/*
	[
	SNew(STextBlock).Text(FText::FromString("THIS WAS NULL SOMEHOW"))
	];
	}
	*/
	
}

void STaskListWidget::OnGetChildren(TaskSearchResultSharedPtr Item, TArray<TaskSearchResultSharedPtr>& OutChildren)
{
	//FString OutString = FString(*Item + " child");
	//TSharedPtr<FString> OutPtr =
	//auto New = MakeShareable(new FString(*Item + " child"));
	//Items.Add(New);
	//OutChildren.Add(New);
	/*
	for (auto& Item : Items)
	{

	if (Item->StartsWith("B"))
	{
	OutChildren.Add(Item);
	}
	};
	*/
}

FReply STaskListWidget::ButtonPressed()
{
	ListViewWidget->RequestListRefresh();
	return FReply::Handled();
}

void STaskListWidget::UpdateActiveResults()
{
	TArray<FAssetData> AssetData;
	ActiveAssetRegistryModule.Get().GetAssetsByClass(FName("Blueprint"), AssetData);
	TArray<FTaskSearchResult> CurrentResults;

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
				for (auto& ActiveTaskPrefix : TaskPrefixes)
				{
					if (ActiveCommentNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString().StartsWith(ActiveTaskPrefix))
					{
						//CurrentResults.Add(FTaskSearchResult(ActiveTaskPrefix, ActiveBlueprint, ActiveGraph, ActiveCommentNode));
					}
				}
			}
		}
	}
	//DisplayedResults = CurrentResults;

	ListViewWidget->RequestListRefresh();
}
