// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DataTest
{
public:

	UObject * TargetObject;
	FString CategoryID;
	bool bIsCategory;

public:

	DataTest(UObject * InTargetObject, bool InbIsCategory, FString InCategoryID);
	DataTest(UObject * InTargetObject);
	FString ToString();

};