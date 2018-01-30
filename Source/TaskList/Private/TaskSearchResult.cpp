// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskSearchResult.h"

FTaskSearchResult::FTaskSearchResult(UObject * InTargetObject, bool InbIsCategory, FString InCategoryID)
{
	if (InTargetObject) { TargetObject = InTargetObject; }
	bIsCategory = InbIsCategory;
	CategoryID = InCategoryID;
}

FTaskSearchResult::FTaskSearchResult(UObject * InTargetObject)
{
	bIsCategory = false;
	if (InTargetObject) { TargetObject = InTargetObject; }
}
