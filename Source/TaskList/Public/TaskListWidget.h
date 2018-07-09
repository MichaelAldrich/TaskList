// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "SlateBasics.h"

class UEdgraph;
class UEdgraphNode;
class FAssetRegistryModule;
class FTaskSearchResult;

class STaskListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskListWidget)
	{}
	SLATE_END_ARGS()

	TArray<TSharedPtr<FTaskSearchResult>> FoundTasks;
	TArray<TSharedPtr<FTaskSearchResult>> ActiveResults;
	TSharedPtr <SListView <TSharedPtr<FTaskSearchResult>> > TreeViewWidget;

public:
	void Construct(const FArguments& Args);
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FTaskSearchResult> Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildren(TSharedPtr<FTaskSearchResult> Item, TArray<TSharedPtr<FTaskSearchResult>>& OutChildren);
	void OnItemDoubleClicked(TSharedPtr<FTaskSearchResult> Item);

private:
	void UpdateActiveResults();
	TArray<FName> GetPrefixesFromUserConfig();
};
