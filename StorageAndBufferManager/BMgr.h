#pragma once
#include<iostream>
#include"BCB.h"
#include"DSMgr.h"
#include"LRU.h"
using std::cout; using std::endl;
const int BUFSIZE = 1024;
class BMgr {
public:
	BMgr() { 
		hit = 0; io = 0; blockNums =0; 
		for (int i = 0;i < BUFSIZE;i++)
			ptof[i] = nullptr;
	}
	//interface functions
	int fixPage(int page_id);
	//NewPage fixNewPage();
	//int unfixPage(int page_id);   //return a frame_id
	int numFreeFrames();
	int getHit() const { return hit; }
	int getIO()const { return io; }
	//internal functions
	int selectVictim();
	int hash(int page_id);
	void removeBCB(int page_id);
	//void removeLRUEle(int frid);
	void setDirty(int frame_id);
	void unsetDirty(int frame_id);
	void writeDirtys();
	void printFrame(int frame_id);
	void addBuffer(int page,int frame);
	void update(int page, int frame,bFrame* b);
private:
	int ftop[BUFSIZE];
	BCB* ptof[BUFSIZE];
	int hit, io,blockNums;
	DSMgr* storageMgr=new DSMgr();
	LRU* lru=new LRU();
	bFrame buffer[BUFSIZE];
};