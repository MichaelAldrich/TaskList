// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "WidgetTest.h"

#define LOCTEXT_NAMESPACE "FTaskListModule"

void STestListWidget::Construct(const FArguments& Args)
{
	this->ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[	
				SNew(SButton)
				.Text(LOCTEXT("AddSomethingText", "Add something."))
				.OnClicked(this, &STestListWidget::ButtonPressed)
			]
			+ SScrollBox::Slot()
			[
				SAssignNew(ListViewWidget, STreeView<TSharedPtr<FString>>)
				.ItemHeight(24)
				.TreeItemsSource(&Items)
				.OnGenerateRow(this, &STestListWidget::OnGenerateRow)
				.OnGetChildren(this, &STestListWidget::OnGetChildren)
			]
		];
}

TSharedRef<ITableRow> STestListWidget::OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (Item->StartsWith("A"))
	{
		return
			SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
			.Padding(2.0f)
			[
				SNew(STextBlock).Text(FText::FromString(*Item.Get()))
			];
	}
}

void STestListWidget::OnGetChildren(TSharedPtr<FString> Item, TArray<TSharedPtr<FString>>& OutChildren)
{
	FString OutString = FString(*Item + " child");
	TSharedPtr<FString> OutPtr = 
	OutChildren.Append(TSharedPtr<OutString>);
	/*
	return
		SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
		.Padding(2.0f)
		[
			SNew(STextBlock).Text(FText::FromString(*Item.Get() + "deeper"))
		];
	*/
}

FReply STestListWidget::ButtonPressed()
{
	Items.Add(MakeShareable(new FString("AGood Grief")));
	Items.Add(MakeShareable(new FString("BTake Care")));
	ListViewWidget->RequestListRefresh();
	return FReply::Handled();
}
