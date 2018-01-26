// Copyright (c) 2018 Michael Aldrich. MIT License. See https://github.com/MichaelAldrich/TaskList/blob/427d8aa03cf453857881ac1947aa9a7803c44070/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

#include "DataTest.h"

class UDDEdEngine;


typedef STreeView< FDDFileTreeItemPtr > SDDFileTreeView;

/**
* File Tree View
*/
class SDDFileTree : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SDDFileTree)
	{}

	SLATE_END_ARGS()


		//~~~~~~~~
		//		DDEdEngine
		//~~~~~~~~
public:
	//owns this
	TWeakObjectPtr<class UDDEdEngine> DDEdEngine;


	/** Refresh the Tree */
	//bool DoRefresh;


	//~~~
public:
	/** Widget constructor */
	void Construct(const FArguments& Args, TWeakObjectPtr<class UDDEdEngine> IN_DDEdEngine);

	/** Destructor */
	~SDDFileTree();

	/** @return Returns the currently selected category item */
	FDDFileTreeItemPtr GetSelectedDirectory() const;

	/** Selects the specified category */
	void SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect);

	/** @return Returns true if the specified item is currently expanded in the tree */
	bool IsItemExpanded(const FDDFileTreeItemPtr Item) const;

private:

	/** Called to generate a widget for the specified tree item */
	TSharedRef<ITableRow> DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** Given a tree item, fills an array of child items */
	void DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren);

	/** Called when the user clicks on an  item, or when selection changes by some other means */
	void DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo);

	/** Rebuilds the category tree from scratch */
	void RebuildFileTree();

	/** SWidget overrides */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) OVERRIDE;


private:


	/** The tree view widget*/
	TSharedPtr< SDDFileTreeView > DDFileTreeView;

	/** The Core Data for the Tree Viewer! */
	TArray< FDDFileTreeItemPtr > Directories;
};