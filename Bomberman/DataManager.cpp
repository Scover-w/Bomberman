#include "DataManager.h"

DataManager* DataManager::dataManager;

DataManager::DataManager()
{
	dataManager = this;

}

DataManager::~DataManager()
{

}

void DataManager::SetCurrentPage(Page page)
{
	currentPage = page;
}

int DataManager::GetCurrentPage()
{
	return currentPage;
}