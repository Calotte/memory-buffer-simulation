#pragma once
struct LRUEle {
public:
	LRUEle(int p, int f, int d) :page_id(p), frame_id(f), dirty(d) { next = nullptr; }
	int page_id;
	int frame_id;
	int dirty;
	LRUEle* next;
};
class LRU {
public:
	LRU() { most ->next= nullptr; least = nullptr; }
	void manageLRU(int frame_id,int page_id);
	LRUEle* getLeast() const { return least; }
	void setDirty(int frame);
	void unSetDirty(int frame);
	LRUEle* getFirst()const { return most->next; }
	LRUEle* getNext(LRUEle* p) const { return p->next; }
	void removeLRUEle(int frame_id);
private:
	LRUEle* findLRUEle(int frame_id);
	LRUEle* most=new LRUEle(-1,-1,-1);
	LRUEle* least;
};