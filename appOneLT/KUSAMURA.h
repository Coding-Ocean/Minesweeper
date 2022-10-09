#pragma once
#include"KUKAKU.h"
class KUSAMURA
{
	float Len;
	int Col;
	int Row;
	//区画の２次元配列
	KUKAKU** Kukaku;
	//ゲームオーバー用
	bool UnkoNiSawatta;
	//ゲームクリア用
	int SouUnkoSu;
	int SirabeteNaiSu;
	bool NinmuKanryo;
public:
	KUSAMURA() {
		KUKAKU::loadUnkoImg();

		Len = 100;
		Col = width / Len;
		Row = height / Len;
		//２次元配列の動的確保
		Kukaku = new KUKAKU* [Col];
		for (int col = 0; col < Col; col++) {
			Kukaku[col] = new KUKAKU[Row];
		}

		tsukuru();
	}
	~KUSAMURA() {
		for (int col = 0; col < Col; col++) {
			delete[]Kukaku[col];
		}
		delete[] Kukaku;
	}
	void tsukuru() {
		//区画を作って、総うんこ数を求めておく
		SouUnkoSu = 0;
		for (int col = 0; col < Col; col++) {
			for (int row = 0; row < Row; row++) {
				float posX = Len*0.5f + Len * col;
				float posY = Len*0.5f + Len * row;
				Kukaku[col][row].tsukuru(posX, posY, Len);
				if (Kukaku[col][row].unkoAri()) {
					SouUnkoSu++;
				}
			}
		}
		//ゲームオーバー
		UnkoNiSawatta = false;
		//ゲームクリア
		NinmuKanryo = false;
		SirabeteNaiSu = Col * Row;
		//各区画のまわりのうんこの数をかぞえる
		for (int col = 0; col < Col; col++) {
			for (int row = 0; row < Row; row++) {
				//周囲をチェックしていく
				int mawariNoUnkoSu = 0;
				for (int i = -1; i <= 1; i++) {
					if (col + i < 0 || col+i>=Col)continue;
					for (int j = -1; j <= 1; j++) {
						if (row + j < 0 || row + j >= Row)continue;
						if (Kukaku[col+i][row+j].unkoAri()) {
							mawariNoUnkoSu++;
						}
					}
				}
				Kukaku[col][row].setMawarinoUnkoSu(mawariNoUnkoSu);
			}
		}
	}
	void siraberu(int col, int row) {
		if (Kukaku[col][row].sirabeteNai()) {
			Kukaku[col][row].siraberu();
			SirabeteNaiSu--;
			if (Kukaku[col][row].mawariNiUnkoNasi()) {
				mawariWoSiraberu(col,row);
			}
		}
	}
	void mawariWoSiraberu(int col, int row) {
		for (int i = -1; i <= 1; i++) {
			if (col + i < 0 || col + i >= Col)continue;
			for (int j = -1; j <= 1; j++) {
				if (row + j < 0 || row + j >= Row)continue;
				siraberu(col + i, row + j);
			}
		}
	}
	void chousa() {
		if (!UnkoNiSawatta && !NinmuKanryo) {
			int col = mouseX / Len;
			int row = mouseY / Len;
			//調べる
			if (isTrigger(MOUSE_LBUTTON)) {
				siraberu(col, row);
				if (Kukaku[col][row].unkoAri()) {
					UnkoNiSawatta = true;
				}
				if (SouUnkoSu == SirabeteNaiSu) {
					NinmuKanryo = true;
				}
			}
			//うんことみなす
			if (isTrigger(MOUSE_RBUTTON)) {
				Kukaku[col][row].unkoToMinasu();
			}
		}
		//いつでもリセット
		if (isTrigger(KEY_SPACE)) {
			tsukuru();
		}
	}
	void miseru() {
		for (int col = 0; col < Col; col++) {
			for (int row = 0; row < Row; row++) {
				Kukaku[col][row].miseru();
			}
		}
		if (UnkoNiSawatta) {
			fill(255, 0, 0);
			textMode(TOP);
			textSize(width / 8);
			text("うんこにさわった", 0, (height-Len) / 2);
		}
		if (NinmuKanryo) {
			fill(255, 255, 0);
			textMode(TOP);
			textSize(width / 8);
			text("うんこしらべ成功", 0, (height-Len) / 2);
		}
	}
};

