#pragma once
const int FRAMESIZE = 1024;
struct bFrame {
	bFrame() {
		for (int i = 0;i < FRAMESIZE;i++)
			field[i] = '#';
	}
	char field[FRAMESIZE];
};