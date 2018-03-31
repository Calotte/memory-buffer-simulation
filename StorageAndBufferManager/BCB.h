#pragma once
struct BCB {
	BCB()=default;
	BCB(int page, int frame) :
		page_id(page), frame_id(frame) {
		next = nullptr; dirty = 0;
	}
	int page_id;
	int frame_id;
	//int latch;
	//int count;
	int dirty;
	BCB* next;
};