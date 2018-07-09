// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskListWidget.h"
#include "TaskSearchResult.h"
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "Editor/UnrealEd/Public/EdGraphNode_Comment.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "TaskListSettings.h"

#define LOCTEXT_NAMESPACE "FTaskListModule"

void STaskListWidget::Construct(const FArguments& Args)
{
	this->ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SAssignNew(TreeViewWidget, STreeView<TSharedPtr<FTaskSearchResult>>)
				.ItemHeight(24)
				.TreeItemsSource(&FoundTasks)
				.OnGenerateRow(this, &STaskListWidget::OnGenerateRow)
				.OnGetChildren(this, &STaskListWidget::OnGetChildren)
				.OnMouseButtonDoubleClick(this, &STaskListWidget::OnItemDoubleClicked)
			]
		];
	UpdateActiveResults();
}

TSharedRef<ITableRow> STaskListWidget::OnGenerateRow(TSharedPtr<FTaskSearchResult> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	FText RowTitle = FText::FromString("No Title Found");
	if (Item->bIsCategory)
	{
		RowTitle = FText::FromName(Item->CategoryID);
	}
	else
	{
		if (Item->TargetCommentNode)
		{
			RowTitle = Item->TargetCommentNode->GetNodeTitle(ENodeTitleType::FullTitle);
		}
	}

	return
		/*
		SNew(STableRow<TSharedPtr<FTaskSearchResult>>, OwnerTable)
		.Padding(2.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(Item->CategoryID)
			]
			/*
			+ SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(RowTitle)
			]
			
		];
		*/
	SNew(STableRow<TSharedPtr<FTaskSearchResult>>, OwnerTable)
		.Padding(2.f)
		[
			SNew(STextBlock)
			.Text(RowTitle)
		];
	
}

void STaskListWidget::OnGetChildren(TSharedPtr<FTaskSearchResult> Item, TArray<TSharedPtr<FTaskSearchResult>>& OutChildren)
{
	if (Item->bIsCategory)
	{
		Item->GetChildren(OutChildren);
	}
}

void STaskListWidget::OnItemDoubleClicked(TSharedPtr<FTaskSearchResult> Item)
{
	if (Item->TargetCommentNode)
	{
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(Item->TargetCommentNode);
	}
	else if (Item->TargetGraph)
	{
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(Item->TargetGraph);
	}
	else if (Item->TargetObject)
	{
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(Item->TargetObject);
	}
}

void STaskListWidget::UpdateActiveResults()
{
	FAssetRegistryModule& ActiveAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	ActiveAssetRegistryModule.Get().GetAssetsByClass(FName("Blueprint"), AssetData);
	
	//TODO there is a way to make filters for the asset registry. Should assemble a filter based on the config settings for what graphs to serach.
	TArray<FAssetData> TestData;
	ActiveAssetRegistryModule.Get().GetAssetsByPath(FName("/Game"), TestData, true);
	UE_LOG(LogTemp, Warning, TEXT("Sup"));
	UE_LOG(LogTemp, Warning, TEXT("Count: %i"), TestData.Num());
	for (auto& TestItem : TestData)
	{
		FString ActiveName = TestItem.GetFullName();
		UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *ActiveName);
	}

	TArray<FName> ActivePrefixes = GetPrefixesFromUserConfig();

	FoundTasks.Empty();
	for (auto& ActiveBPAssetData : AssetData)
	{
		TArray<UEdGraph*> AllActiveGraphs;
		
		UBlueprint* ActiveBlueprint = Cast<UBlueprint>(ActiveBPAssetData.GetAsset());
		ActiveBlueprint->GetAllGraphs(AllActiveGraphs);
		
		FName ActiveClass = ActiveBPAssetData.AssetClass;
		//if (ActiveClass == FName("Blueprint"))

		for (auto& ActiveGraph : AllActiveGraphs)
		{
			TArray<UEdGraphNode_Comment*> AllActiveCommentNodes;
			ActiveGraph->GetNodesOfClass(AllActiveCommentNodes);

			for (auto& ActiveCommentNode : AllActiveCommentNodes)
			{
				for (auto& ActiveTaskPrefix : ActivePrefixes)
				{
					if (ActiveCommentNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString().StartsWith(ActiveTaskPrefix.ToString()))
					{
						FoundTasks.Add(MakeShareable(new FTaskSearchResult(ActiveBlueprint, ActiveGraph, ActiveCommentNode, ActiveTaskPrefix)));
					}
				}
			}
		}
	}
	TreeViewWidget->RequestListRefresh();
}

TArray<FName> STaskListWidget::GetPrefixesFromUserConfig()
{
	const UTaskListSettings * ActiveSettings = GetDefault<UTaskListSettings>();
	return ActiveSettings->TaskPrefixes;
}
