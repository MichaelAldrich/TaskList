// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TaskListSettings.generated.h"

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
	UPROPERTY(config, EditAnywhere, Category = "Task List")
	TArray<FName> TaskPrefixes = { FName("dragons"), FName("todo"), FName("lions") };

	/** Top level directory of search. If blank searches entire content directory. */
	UPROPERTY(config, EditAnywhere, Category = "Task List", meta = (ContentDir))
	FDirectoryPath SearchScope;

	//Graph types to search
	/** Include Blueprint graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchBlueprints = true;

	/** Include Sound Cue graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchSoundCues = true;

	/** Include Material graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchMaterials = true;

	/** Include Widget Blueprint graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchWidgetBlueprints = true;

	/** Include Animation Blueprint graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchAnimationBlueprints = true;

	/** Include Material Function graphs in search.*/
	UPROPERTY(config, EditAnywhere, Category = "Asset Types to Search")
	bool SearchMaterialFunctions = true;
};
