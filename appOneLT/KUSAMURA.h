#pragma once
#include"KUKAKU.h"
class KUSAMURA
{
	float Len;
	int Col;
	int Row;
	//���̂Q�����z��
	KUKAKU** Kukaku;
	//�Q�[���I�[�o�[�p
	bool UnkoNiSawatta;
	//�Q�[���N���A�p
	int SouUnkoSu;
	int SirabeteNaiSu;
	bool NinmuKanryo;
public:
	KUSAMURA() {
		KUKAKU::loadUnkoImg();

		Len = 100;
		Col = width / Len;
		Row = height / Len;
		//�Q�����z��̓��I�m��
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
		//��������āA�����񂱐������߂Ă���
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
		//�Q�[���I�[�o�[
		UnkoNiSawatta = false;
		//�Q�[���N���A
		NinmuKanryo = false;
		SirabeteNaiSu = Col * Row;
		//�e���̂܂��̂��񂱂̐�����������
		for (int col = 0; col < Col; col++) {
			for (int row = 0; row < Row; row++) {
				//���͂��`�F�b�N���Ă���
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
			//���ׂ�
			if (isTrigger(MOUSE_LBUTTON)) {
				siraberu(col, row);
				if (Kukaku[col][row].unkoAri()) {
					UnkoNiSawatta = true;
				}
				if (SouUnkoSu == SirabeteNaiSu) {
					NinmuKanryo = true;
				}
			}
			//���񂱂Ƃ݂Ȃ�
			if (isTrigger(MOUSE_RBUTTON)) {
				Kukaku[col][row].unkoToMinasu();
			}
		}
		//���ł����Z�b�g
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
			text("���񂱂ɂ������", 0, (height-Len) / 2);
		}
		if (NinmuKanryo) {
			fill(255, 255, 0);
			textMode(TOP);
			textSize(width / 8);
			text("���񂱂���א���", 0, (height-Len) / 2);
		}
	}
};

