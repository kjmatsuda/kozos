#include "defines.h"

extern void start(void);        /* スタート・アップ */
extern void intr_softerr(void); /* ソフトウエア・エラー */
extern void intr_syscall(void); /* システム・コール */
extern void intr_serintr(void); /* シリアル割込み */

/*
 * 割込みベクタの設定．
 * リンカ・スクリプトの定義により，先頭番地に配置される．
 */
void (*vectors[])(void) = {
  start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
  intr_syscall, intr_softerr, intr_softerr, intr_softerr,   // トラップ割込みのベクタに、システムコール、ソフトウェアエラーを設定
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  intr_serintr, intr_serintr, intr_serintr, intr_serintr, // SCI0の割込みベクタ
  intr_serintr, intr_serintr, intr_serintr, intr_serintr, // SCI1の割込みベクタ
  intr_serintr, intr_serintr, intr_serintr, intr_serintr, // SCI2の割込みベクタ
};
