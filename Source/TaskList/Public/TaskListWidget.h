// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STaskListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskListWidget)
		: _bIsSearchWindow(true)
		, _bHideSearchBar(false)
		, _ContainingTab()
	{}
	SLATE_ARGUMENT(bool, bIsSearchWindow)
	SLATE_ARGUMENT(bool, bHideSearchBar)
	SLATE_ARGUMENT(TSharedPtr<SDockTab>, ContainingTab)
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, TSharedPtr<class FBlueprintEditor> InBlueprintEditor = nullptr);
class TASKLIST_API TaskListWidget
{
public:
	TaskListWidget();
	~TaskListWidget();
};
