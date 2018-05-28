// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TaskListSettings.generated.h"

/**
 * 
 */
//, defaultconfig
UCLASS(config = TaskList)
class TASKLIST_API UTaskListSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UTaskListSettings(const FObjectInitializer& ObjectInitializer);

	/** 
	*List of prefixes to search the comments for. Each entry here will effect performance.
	*See TaskListWidget::UpdateActiveResults
	*/
	UPROPERTY(config, EditAnywhere, Category = General)
	TArray<FName> TaskPrefixes = { FName("dragons"), FName("todo"), FName("lions") };

};
