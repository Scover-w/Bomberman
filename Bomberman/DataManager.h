#pragma once
#include "Page.h"
class DataManager
{
private:
	Page currentPage;

public:
	DataManager();
	~DataManager();
	static DataManager* dataManager;
	void SetCurrentPage(Page);
	int GetCurrentPage();
};

