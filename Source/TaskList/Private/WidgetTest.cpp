// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "WidgetTest.h"

#define LOCTEXT_NAMESPACE "FTaskListModule"

void STestListWidget::Construct(const FArguments& Args)
{
	Items.Add(MakeShareable(new FString("AGood Grief")));
	Items.Add(MakeShareable(new FString("BSad Trees")));
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
	else
	{
		return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
			[
				SNew(STextBlock).Text(FText::FromString("THIS WAS NULL SOMEHOW"))
			];
	}
}

void STestListWidget::OnGetChildren(TSharedPtr<FString> Item, TArray<TSharedPtr<FString>>& OutChildren)
{
	//FString OutString = FString(*Item + " child");
	//TSharedPtr<FString> OutPtr =
	//auto New = MakeShareable(new FString(*Item + " child"));
	//Items.Add(New);
	//OutChildren.Add(New);
	for (auto& Item : Items)
	{

		if (Item->StartsWith("B"))
		{
			OutChildren.Add(Item);
		}
	};
}

FReply STestListWidget::ButtonPressed()
{
	Items.Add(MakeShareable(new FString("AGood Grief")));
	Items.Add(MakeShareable(new FString("BSad Trees")));
	ListViewWidget->RequestListRefresh();
	return FReply::Handled();
}
