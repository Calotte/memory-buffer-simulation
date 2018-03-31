#include"BMgr.h"
int BMgr::fixPage(int page_id) {     //return a frame_id
	int index = hash(page_id);
	auto b = ptof[index];
	while (b != nullptr) {
		if (b->page_id == page_id) {
			hit++;
			//命中，只需更新lru
			lru->manageLRU(b->frame_id, b->page_id);
			return b->frame_id;
		}
		else
			b = b->next;
	}	
	bFrame bf=storageMgr->readPage(page_id);
	io++;
	if (numFreeFrames() > 0) {		
		update(page_id, blockNums, &bf);   //更新ftop, buffer, ptof, lru
		blockNums++;
		return blockNums-1;
}
	else {
		int frame_id = selectVictim(); //selects a frame to replace
		update(page_id, frame_id, &bf);
		return frame_id;
	}
}

int BMgr::numFreeFrames()
{
	return BUFSIZE - blockNums;
}



int BMgr::selectVictim()
{
	LRUEle* victim = lru->getLeast();
	int frame_id = victim->frame_id;
	int page_id = victim->page_id;
	if (victim->dirty == 1) {
		storageMgr->writePage(frame_id, buffer[frame_id]);		
	}
	removeBCB(page_id);
	lru->removeLRUEle(frame_id);
	return frame_id;
}

int BMgr::hash(int page_id)
{
	return page_id%BUFSIZE;
}

void BMgr::removeBCB(int page_id)
{
	int index = hash(page_id);
	auto pre = ptof[index];
	if (pre->page_id == page_id) {
		ptof[index] = pre->next;
		delete pre;
	}
	else {
		while (pre->next != nullptr) {
			if (pre->next->page_id == page_id) {
				auto pb = pre->next;
				pre->next = pb->next;
				delete pb;
			}
			else
				pre = pre->next;
		}
	}
}

void BMgr::setDirty(int frame_id)
{
	int pid = ftop[frame_id];
	int index = hash(pid);
	BCB* b = ptof[index];
	while (b != nullptr) {
		if (b->page_id == pid) {
			b->dirty = 1;
			break;
		}
		else
			b = b->next;
	}
	lru->setDirty(frame_id); //更新lru
}

void BMgr::unsetDirty(int frame_id)
{
	int pid = ftop[frame_id];
	int index = hash(pid);
	BCB* b = ptof[index];
	while (b != nullptr) {
		if (b->page_id == pid) {
			b->dirty = 0; break;
		}
		else
			b = b->next;
	}
	lru->unSetDirty(frame_id); //更新lru
}

void BMgr::writeDirtys()
{
	LRUEle* p = lru->getFirst();
	while (p != nullptr) {
		if (p->dirty == 1) {
			storageMgr->writePage(p->page_id, buffer[p->frame_id]);
			io++;
		}
		p = lru->getNext(p);
	}
}

void BMgr::printFrame(int frame_id)
{
	for (int i = 0;i < FRAMESIZE;i++)
		cout << buffer[frame_id].field[i] << " ";
	cout << endl;
}




void BMgr::addBuffer(int page, int frame) {
	int index = hash(page);
	BCB* newBCB = new BCB(page, frame);
	if (ptof[index] == nullptr)
		ptof[index] = newBCB;
	else {
		newBCB->next = ptof[index];
		ptof[index]= newBCB;
	}
}

void BMgr::update(int page, int frame, bFrame* bframe)
{
	ftop[frame] = page;
	buffer[frame] = *bframe;
	//下句将新page添加到btop中，同时返回其BCB*
	addBuffer(page, frame);  
	lru->manageLRU(frame,page);
}
