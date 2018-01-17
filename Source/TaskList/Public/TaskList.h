// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

struct TTaskSearchResult
{
	UObject * ParentObject;
	UEdGraph * ParentGraph;
	UEdGraphNode * Node;
	FString TaskID;

	TTaskSearchResult()
	{
		TaskID = "";
		ParentObject = nullptr;
		ParentGraph = nullptr;
		Node = nullptr;
	}
	
	TTaskSearchResult(FString InTaskID, UObject * InParentObject, UEdGraph * InParentGraph, UEdGraphNode * InNode)
	{
		TaskID = InTaskID;
		ParentObject = InParentObject;
		ParentGraph = InParentGraph;
		Node = InNode;
	}

	FString ToString()
	{
		FString ParentObjectString = "";
		FString ParentGraphString = "";
		FString NodeString = "";

		if (ParentObject)
		{
			ParentObjectString = ParentObject->GetName();
		}
		if (ParentGraph)
		{
			ParentGraphString = ParentGraph->GetName();
		}
		if (Node)
		{
			NodeString = Node->GetName();
		}
		return FString((TEXT("Task: %s|Object: %s|Graph: %s|Node: %s"), TaskID, ParentObjectString, ParentGraphString, NodeString));
	}
};


class FToolBarBuilder;
class FMenuBuilder;

class FTaskListModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:
	FReply UpdateTaskList();

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);



	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};