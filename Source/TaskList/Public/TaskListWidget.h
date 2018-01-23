// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"


struct FTaskSearchResult;
/**
 * 
 */
class STaskListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskListWidget)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	TSharedRef<ITableRow> OnGenerateRow(FTaskSearchResult* InItem, const TSharedRef<STableViewBase>& OwnerTable);
};
