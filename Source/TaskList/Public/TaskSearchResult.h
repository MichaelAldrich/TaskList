// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"

class UEdGraph;
class UEdGraphNode_Comment;

/**
*
*/
class FTaskSearchResult
{
public:

	UObject * TargetObject = nullptr;
	UEdGraph * TargetGraph = nullptr;
	UEdGraphNode_Comment * TargetCommentNode = nullptr;
	FString CategoryID = "none";
	bool bIsCategory = false;

public:

	FTaskSearchResult(FString InCategoryID);
	FTaskSearchResult(UObject * InTargetObject, UEdGraph * InTargetGraph, UEdGraphNode_Comment * InTargetCommentNode, FString InCategoryID);

	bool AddChild(TSharedRef<FTaskSearchResult> InChild);
	bool AddChild(UObject * InTargetObject, UEdGraph * InTargetGraph, UEdGraphNode_Comment * InTargetCommentNode);

	void GetChildren(TArray< TSharedPtr<FTaskSearchResult> >& OutChildren);

private:
	TArray< TSharedPtr<FTaskSearchResult> > Children;
};