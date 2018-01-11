// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TaskListCommands.h"

#define LOCTEXT_NAMESPACE "FTaskListModule"

void FTaskListCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TaskList", "Bring up TaskList window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
