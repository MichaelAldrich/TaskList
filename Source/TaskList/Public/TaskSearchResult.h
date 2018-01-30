// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"

/**
*
*/
class FTaskSearchResult
{
public:

	UObject * TargetObject = nullptr;
	FString CategoryID = "none";
	bool bIsCategory = false;

public:

	FTaskSearchResult(UObject * InTargetObject, bool InbIsCategory, FString InCategoryID);
	FTaskSearchResult(UObject * InTargetObject);

	void AddChild(TSharedRef<FTaskSearchResult> InChild);
	void GetChildren(TArray< TSharedPtr<FTaskSearchResult> >& OutChildren);

private:
	TArray< TSharedPtr<FTaskSearchResult> > Children;

};