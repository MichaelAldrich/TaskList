// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#include "TaskSearchResult.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"

FTaskSearchResult::FTaskSearchResult()
{
	TaskID = "";
	ParentObject = nullptr;
	ParentGraph = nullptr;
	Node = nullptr;
}

FTaskSearchResult::FTaskSearchResult(FString InTaskID, UObject * InParentObject, UEdGraph * InParentGraph, UEdGraphNode * InNode)
{
	TaskID = InTaskID;
	ParentObject = InParentObject;
	ParentGraph = InParentGraph;
	Node = InNode;
}

FString FTaskSearchResult::ToString() const
{
	FString ParentObjectString = "";
	FString ParentGraphString = "";
	FString NodeString = "";
	if (ParentObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got a parent object"))
		ParentObjectString = ParentObject->GetName();
	}
	if (ParentGraph)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got a parent graph"))
		ParentGraphString = ParentGraph->GetName();
	}
	if (Node)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got a node"))
		NodeString = Node->GetNodeTitle((ENodeTitleType::FullTitle)).ToString();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Task: %s|Object: %s|Graph: %s|Node: %s"), TaskID, ParentObjectString, ParentGraphString, NodeString)
	//return FString("Tings");
	return FString::Printf(TEXT("Task: %s|Object: %s|Graph: %s|Node: %s"), *TaskID, *ParentObjectString, *ParentGraphString, *NodeString);
}

FText FTaskSearchResult::ToText() const
{
	return FText::AsCultureInvariant(ToString());
}
