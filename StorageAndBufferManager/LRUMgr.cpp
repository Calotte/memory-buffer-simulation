#include "LRU.h"

void LRU::manageLRU(int frame_id,int page_id)
{
	if (most->next == nullptr) {
		LRUEle* b = new LRUEle(page_id, frame_id, 0);
		b->next = most->next;
		most->next = b;
		least = b;
	}
	else {
		LRUEle* preBCB = findLRUEle(frame_id);
		if (preBCB== nullptr) {
			LRUEle* b = new LRUEle(page_id, frame_id, 0);
			b->next = most->next;
			most->next = b;
		}
		else {
			LRUEle* lb = preBCB->next;
			preBCB->next = lb->next;
			if (preBCB->next == nullptr)
				least = preBCB;
			lb->next = most->next;
			most->next = lb;
		}
	}
}

void LRU::setDirty(int frame)
{
	LRUEle* p = most->next;
	while (p) {
		if (p->frame_id == frame) {
			p->dirty = 1;
			break;
		}
		else
			p = p->next;
	}
}

void LRU::unSetDirty(int frame)
{
	LRUEle* p = most->next;
	while (p) {
		if (p->frame_id == frame) {
			p->dirty = 0; break;
		}
		else
			p = p->next;
	}
}


void LRU::removeLRUEle(int frame_id)
{
	LRUEle* pre = findLRUEle(frame_id);
	LRUEle* p = pre->next;
	pre->next = p->next;
	if (pre->next == nullptr)
		least = pre;
	delete p;
}

LRUEle * LRU::findLRUEle(int frame_id)
{
	LRUEle* pre = most;
	while (pre->next != nullptr) {
		if (pre->next->frame_id==frame_id)
			return pre;
		else
		pre = pre->next;
	}
	return nullptr;
}