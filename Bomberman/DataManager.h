#pragma once
#include "Page.h"
class DataManager
{
private:
	Page currentPage;
	bool isFirstLoad;
public:
	DataManager();
	~DataManager();
	static DataManager* instance;
	void SetCurrentPage(Page);
	int GetCurrentPage();
	bool IsFirstLoad();
	void NoFirstLoad();
};

