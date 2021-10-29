#pragma once
#include "Page.h"
class DataManager
{
private:
	Page currentPage;
	bool isFirstLoad;
	bool hasWin;
public:
	DataManager();
	~DataManager();
	static DataManager* instance;
	void SetCurrentPage(Page);
	int GetCurrentPage();
	bool IsFirstLoad();
	void NoFirstLoad();
	void SetWinValue(bool);
	bool AskWin();
};

