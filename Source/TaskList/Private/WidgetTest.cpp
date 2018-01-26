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
				SAssignNew(ListViewWidget, SListView<TSharedPtr<FString>>)
				.ItemHeight(24)
				.ListItemsSource(&Items)
				.OnGenerateRow(this, &STestListWidget::OnGenerateRow)
			]
		];
}

TSharedRef<ITableRow> STestListWidget::OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
		SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
		.Padding(2.0f)
		[
			SNew(STextBlock).Text(FText::FromString(*Item.Get()))
		];
}

FReply STestListWidget::ButtonPressed()
{
	Items.Add(MakeShareable(new FString("Take a break")));
	ListViewWidget->RequestListRefresh();
	return FReply::Handled();
}
