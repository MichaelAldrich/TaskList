#pragma once
typedef TSharedPtr< class FDDFileTreeItem > FDDFileTreeItemPtr;
/**
* The Data for a single node in the Directory Tree
*/
class FDDFileTreeItem
{

public:

	/** @return Returns the parent or NULL if this is a root */
	const FDDFileTreeItemPtr GetParentCategory() const
	{
		return ParentDir.Pin();
	}

	/** @return the path on hard disk, read-only */
	const FString& GetDirectoryPath() const
	{
		return DirectoryPath;
	}

	/** @return name to display in file tree view! read-only */
	const FString& GetDisplayName() const
	{
		return DisplayName;
	}

	/** @return Returns all subdirectories, read-only */
	const TArray< FDDFileTreeItemPtr >& GetSubDirectories() const
	{
		return SubDirectories;
	}

	/** @return Returns all subdirectories, read or write */
	TArray< FDDFileTreeItemPtr >& AccessSubDirectories()
	{
		return SubDirectories;
	}

	/** Add a subdirectory to this node in the tree! */
	void AddSubDirectory(const FDDFileTreeItemPtr NewSubDir)
	{
		SubDirectories.Add(NewSubDir);
	}

public:

	/** Constructor for FDDFileTreeItem */
	FDDFileTreeItem(const FDDFileTreeItemPtr IN_ParentDir, const FString& IN_DirectoryPath, const FString& IN_DisplayName)
		: ParentDir(IN_ParentDir)
		, DirectoryPath(IN_DirectoryPath)
		, DisplayName(IN_DisplayName)
	{
	}


private:

	/** Parent item or NULL if this is a root  */
	TWeakPtr< FDDFileTreeItem > ParentDir;

	/** Full path of this directory in the tree */
	FString DirectoryPath;

	/** Display name of the category */
	FString DisplayName;

	/** Child categories */
	TArray< FDDFileTreeItemPtr > SubDirectories;
};