#pragma once
#include"libOne.h"
class KUKAKU
{
	float PosX, PosY, Len;
	bool SirabeZumi;
	bool UnkoToMinasu;
	bool UnkoAri;
	int MawariNoUnkoSu;
public:
	void tsukuru(float posX, float posY, float len) {
		PosX = posX; PosY = posY; Len = len;
		SirabeZumi = false;
		UnkoToMinasu = false;
		if (random() % 10 == 0) {
			UnkoAri = true;
		}
		else {
			UnkoAri = false;
		}
		MawariNoUnkoSu = 0;
	}
	void setMawarinoUnkoSu(int su) {
		MawariNoUnkoSu = su;
	}
	bool mawariNiUnkoNasi() {
		return MawariNoUnkoSu == 0;
	}
	void siraberu() {
		SirabeZumi = true;
	}
	bool sirabeteNai() {
		return !SirabeZumi;
	}
	void unkoToMinasu() {
		UnkoToMinasu = true;
	}
	bool unkoAri() {
		return UnkoAri;
	}
	void miseru() {
		stroke(128);
		strokeWeight(3);
		rectMode(CENTER);
		if (SirabeZumi) {
			fill(120, 240, 120);
			rect(PosX, PosY, Len, Len);
			if (UnkoAri) {
				imageColor(120, 60, 0);
				image(UnkoImg, PosX, PosY, 0, Len / 100);
			}
			else if(MawariNoUnkoSu>0) {
				fill(128);
				textSize(Len);
				textMode(BCENTER);
				text(MawariNoUnkoSu, PosX, PosY);
			}
		}
		else if (UnkoToMinasu) {
			fill(120, 60, 0);
			rect(PosX, PosY, Len, Len);
		}
		else {
			fill(0, 60, 0);
			rect(PosX, PosY, Len, Len);
		}
	}
private:
	static int UnkoImg;
public:
	static void loadUnkoImg() {
		UnkoImg = loadImage("unko.png");
	}
};

int KUKAKU::UnkoImg=0;