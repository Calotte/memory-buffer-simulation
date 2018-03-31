#include<iostream>
#include<fstream>
#include"BMgr.h"
#include"DSMgr.h"
using std::ifstream;
using std::cout; using std::endl;
int main() {
	BMgr* bufferMgr=new BMgr();
	int dirty = 0, page_id,frame_id,count=0;
	char c;
	int cnt = 0;
	ifstream in("data.txt");
	if (!in) std::cerr << "open file error" << endl;
	while (in >> dirty >>c>>page_id) {
		frame_id = bufferMgr->fixPage(page_id);
		if (dirty == 1) {
			bufferMgr->setDirty(frame_id);
			cnt++;
		}
		else
			bufferMgr->unsetDirty(frame_id);
	}
	cout << "before write dirtys:" << endl;
	cout << "hit:  " << bufferMgr->getHit() << "\n"
		<< "IO: " << bufferMgr->getIO() << endl;
	bufferMgr->writeDirtys();
	cout << "after write dirtys:" << endl;
	cout << "hit:  " << bufferMgr->getHit() << "\n" 
		    << "IO: " << bufferMgr->getIO() << endl;
	cout << "dirty="<<cnt << endl;
	return 0;
}