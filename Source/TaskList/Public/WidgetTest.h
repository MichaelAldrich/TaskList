// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "SlateBasics.h"

class STestListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STestListWidget)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildren(TSharedPtr<FString> Item, TArray<TSharedPtr<FString>>& OutChildren);

	TArray<TSharedPtr<FString>> Items;

	FReply ButtonPressed();

	TSharedPtr <SListView <TSharedPtr <FString> > > ListViewWidget;
};
