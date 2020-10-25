#include "defines.h"

extern void start(void);				/* スタート・アップ */
extern void intr_softerr(void); /* ソフトウエア・エラー */
extern void intr_syscall(void); /* システム・コール */
extern void intr_serintr(void); /* シリアル割込み */
extern void intr_timer(void);	/* タイマー割込み */

/*
 * 割込みベクタの設定．
 * リンカ・スクリプトの定義により，先頭番地に配置される．
 */
void (*vectors[])(void) = {
	start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 		// 0-7
	intr_syscall, intr_softerr, intr_softerr, intr_softerr, NULL, NULL, NULL, NULL, 	// 8-15
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 		// 16-23
	intr_timer, intr_timer, intr_timer, NULL, intr_timer, intr_timer, intr_timer, NULL,			// 24-31
	intr_timer, intr_timer, intr_timer, NULL, NULL, NULL, NULL, NULL, 		// 32-39
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,			// 40-47
	NULL, NULL, NULL, NULL, intr_serintr, intr_serintr, intr_serintr, intr_serintr,		// 48-55
	intr_serintr, intr_serintr, intr_serintr, intr_serintr,	intr_serintr, intr_serintr, intr_serintr, intr_serintr, // 56-63
};
