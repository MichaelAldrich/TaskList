// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TaskListStyle.h"

class FTaskListCommands : public TCommands<FTaskListCommands>
{
public:

	FTaskListCommands()
		: TCommands<FTaskListCommands>(TEXT("TaskList"), NSLOCTEXT("Contexts", "TaskList", "TaskList Plugin"), NAME_None, FTaskListStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};