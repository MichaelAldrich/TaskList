// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskSearchResult.h"

FTaskSearchResult::FTaskSearchResult(FName InCategoryID)
{
	CategoryID = InCategoryID;
	bIsCategory = true;
}

FTaskSearchResult::FTaskSearchResult(UObject * InTargetObject, UEdGraph * InTargetGraph, UEdGraphNode_Comment * InTargetCommentNode, FName InCategoryID)
{
	TargetObject = InTargetObject;
	TargetGraph = InTargetGraph;
	TargetCommentNode = InTargetCommentNode;
	CategoryID = InCategoryID;
}

bool FTaskSearchResult::AddChild(TSharedRef<FTaskSearchResult> InChild)
{
	Children.Add(InChild);
	return true;
}

bool FTaskSearchResult::AddChild(UObject * InTargetObject, UEdGraph * InTargetGraph, UEdGraphNode_Comment * InTargetCommentNode)
{
	if (TargetCommentNode) { return false; }
	if (TargetGraph)
	{
		if (InTargetCommentNode && (TargetObject == InTargetObject) && (TargetGraph==InTargetGraph))
		{
			Children.Add(MakeShareable(new FTaskSearchResult(InTargetObject, InTargetGraph, InTargetCommentNode, CategoryID)));
			return true;
		}
		else { return false; }
	}
	if (TargetObject)
	{
		if (InTargetGraph && (TargetObject == InTargetObject))
		{
			if (InTargetCommentNode)
			{
				for (auto& child : Children)
				{
					if (child->TargetGraph == InTargetGraph)
					{
						return child->AddChild(InTargetObject, InTargetGraph, InTargetCommentNode);
					}
				}

				TSharedRef<FTaskSearchResult> NewChild = MakeShareable(new FTaskSearchResult(InTargetObject, InTargetGraph, nullptr, CategoryID));
				NewChild->AddChild(InTargetObject, InTargetGraph, InTargetCommentNode);
				return AddChild(NewChild);
			}
			else
			{
				return AddChild(MakeShareable(new FTaskSearchResult(InTargetObject, InTargetGraph, nullptr, CategoryID)));
			}
		}
		else { return false; }
	}
	else
	{
		if (InTargetObject)
		{
			for (auto& child : Children)
			{
				if (child->TargetObject == InTargetObject)
				{
					return child->AddChild(InTargetObject, InTargetGraph, InTargetCommentNode);
				}
			}

			TSharedRef<FTaskSearchResult> NewChild = MakeShareable(new FTaskSearchResult(InTargetObject, nullptr, nullptr, CategoryID));
			NewChild->AddChild(InTargetObject, InTargetGraph, InTargetCommentNode);
			return AddChild(NewChild);
		}
		else { return false; }
	}
}

void FTaskSearchResult::GetChildren(TArray<TSharedPtr<FTaskSearchResult>>& OutChildren)
{
	OutChildren += Children;
}
