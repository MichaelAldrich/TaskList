// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskListWidget.h"
#include "TaskSearchResult.h"

void STaskListWidget::Construct(const FArguments & Args)
{
}

TSharedRef<ITableRow> STaskListWidget::OnGenerateRow(FTaskSearchResult* InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	//return TSharedRef<ITableRow>();
	return SNew(STableRow< TSharedPtr<FTaskSearchResult> >, OwnerTable)
		[
			SNew(SBorder)
			.VAlign(VAlign_Center)
			.Padding(FMargin(2.0f))
			[
				SNew(STextBlock)
				.Text(LOCTEXT("TestKey", InItem->ToString()))
				.ToolTipText(LOCTEXT("BlueprintCatSearchToolTip", "Blueprint"))
			]
		];
}
