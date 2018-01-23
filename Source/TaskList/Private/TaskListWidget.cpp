// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskListWidget.h"
#include "TaskSearchResult.h"
#include "Widgets/Views/STreeView.h"

void STaskListWidget::Construct(const FArguments & Args)
{
	this->ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STreeView<FTaskSearchResult>)
				.TreeItemsSource(Args._ActiveResults)
				.OnGenerateRow(this, &STaskListWidget::OnGenerateRow)
				//.OnGenerateRow_Raw(this, &STaskListWidget::OnGenerateRow)
			]
		];
}

TSharedRef<ITableRow> STaskListWidget::OnGenerateRow(FTaskSearchResult* InResult, const TSharedRef<STableViewBase>& OwnerTable)
{
	//return TSharedRef<ITableRow>();

	FString DisplayText = InResult->ToString();
	return SNew(STableRow< TSharedPtr<FTaskSearchResult> >, OwnerTable)
		[
			SNew(SBorder)
			.VAlign(VAlign_Center)
			.Padding(FMargin(2.0f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(DisplayText))
				.ToolTipText(FText(FText::FromString("Touch my tooltips")))
			]
		];
}
