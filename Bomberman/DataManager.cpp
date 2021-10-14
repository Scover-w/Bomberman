#include "DataManager.h"

DataManager* DataManager::instance;

DataManager::DataManager()
{
	instance = this;

}

DataManager::~DataManager()
{

}

void DataManager::SetCurrentPage(Page page)
{
	isFirstLoad = true;
	currentPage = page;
}

int DataManager::GetCurrentPage()
{
	return currentPage;
}

bool DataManager::IsFirstLoad()
{
	return isFirstLoad;
}

void DataManager::NoFirstLoad()
{
	isFirstLoad = false;
}