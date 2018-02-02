// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskSearchResult.h"

FTaskSearchResult::FTaskSearchResult(FString InCategoryID)
{
	CategoryID = InCategoryID;
	bIsCategory = true;
}

FTaskSearchResult::FTaskSearchResult(UObject * InTargetObject, UEdGraph * InTargetGraph, UEdGraphNode_Comment * InTargetCommentNode, FString InCategoryID)
{
	TargetObject = InTargetObject;
	TargetGraph = InTargetGraph;
	TargetCommentNode = InTargetCommentNode;
	FString CategoryID = InCategoryID;
}

void FTaskSearchResult::AddChild(TSharedRef<FTaskSearchResult> InChild)
{
	Children.Add(InChild);
}

void FTaskSearchResult::GetChildren(TArray<TSharedPtr<FTaskSearchResult>>& OutChildren)
{
	OutChildren = Children;
}
