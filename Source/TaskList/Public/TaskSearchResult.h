// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UEdGraph;
class UEdGraphNode;

class FTaskSearchResult
{
public:

	UObject * ParentObject;
	UEdGraph * ParentGraph;
	UEdGraphNode * Node;
	FString TaskID;

public:

	FTaskSearchResult();
	FTaskSearchResult(FString InTaskID, UObject * InParntObject, UEdGraph * InParentGraph, UEdGraphNode * InNode);

	FString ToString();
};