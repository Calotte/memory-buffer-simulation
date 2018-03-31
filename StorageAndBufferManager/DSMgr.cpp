#include "DSMgr.h"

void DSMgr::createFile(bFrame * ppages)
{
	if (openFile()) {
		bFrame* ps[MAXPAGES];
		for (int i = 0;i < MAXPAGES;i++)
			ps[i] = &pages[i];
		for (int i = 0;i < MAXPAGES;i++)
			fwrite(ps, sizeof(bFrame*), 1, currFile);
		closeFile();
	}
	else
		std::cerr << "open file failed!" << std::endl;
}

int DSMgr::openFile()
{
	if (currFile = fopen("data.dbf", "ab+"))
		return 1;
	else return 0;
}

int DSMgr::closeFile()
{
	return fclose(currFile);
}

bFrame DSMgr::readPage(int page_id)
{ 
	 openFile();
		seek(page_id, SEEK_SET);
		bFrame* p = new bFrame();
		bFrame* bfp = p;
		fread(bfp, sizeof(bFrame*), 1, currFile);
		delete p;
		closeFile();
		return *bfp;	
}

int DSMgr::writePage(int page_id, bFrame frm)
{
	FILE* pos=currFile;
	seek(page_id, SEEK_SET);
	bFrame* bfp=new bFrame();
	bFrame* p = bfp;
	int err=fread(bfp, sizeof(bFrame*), 1, currFile);
	*bfp = frm;
	delete p;
	closeFile();
	return err;
}

int DSMgr::seek(int page_id, int start)
{
	return fseek(currFile, page_id * sizeof(bFrame*), start);
}

FILE * DSMgr::getFile()
{
	return currFile;
}

void DSMgr::incNumPages()
{
	numPages++;
}

int DSMgr::getNumPages()
{
	return numPages;
}
