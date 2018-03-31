#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"bFrame.h"
using std::string;
const int MAXPAGES =500000;
const int PAGESIZE = 1024;
class DSMgr {                //Data Storage Manager
public:
	DSMgr()=default;
	void createFile(bFrame* ppages);
	int openFile();
	int closeFile();
	bFrame readPage(int page_id);
	int writePage(int frame_id, bFrame frm);
	int seek(int offset, int pos);
	FILE* getFile();
	void incNumPages();
	int getNumPages();
	//void setUse(int index, int use_bit);
	//int getUse(int index);
private:
	FILE *currFile;
	int numPages;
	bFrame pages[MAXPAGES];
};