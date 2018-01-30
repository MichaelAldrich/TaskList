// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "SlateBasics.h"

class UEdgraph;
class UEdgraphNode;
class FAssetRegistryModule;
class FTaskSearchResult;

typedef TSharedPtr<FTaskSearchResult> TaskSearchResultSharedPtr;

class STaskListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskListWidget)
	{}
	SLATE_END_ARGS()

		void Construct(const FArguments& Args);

	TSharedRef<ITableRow> OnGenerateRow(TaskSearchResultSharedPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildren(TaskSearchResultSharedPtr Item, TArray<TaskSearchResultSharedPtr>& OutChildren);

	TArray<TaskSearchResultSharedPtr> ActiveResults;
	//TArray<TMap<FString, TArray<TMap<UObject*, TArray<TMap<UEdgraph*, TArray<UEdGraphNode*>>>>>>> ActiveResults;

	FReply ButtonPressed();

	TSharedPtr <SListView <TaskSearchResultSharedPtr> > ListViewWidget;

private:
	TArray<FString> TaskPrefixes = { "Dragons", "TODO", "Lions" }; //TODO figure out configuration
	FAssetRegistryModule& ActiveAssetRegistryModule;

private:
	void UpdateActiveResults();

};
