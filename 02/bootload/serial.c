#include "defines.h"
#include "serial.h"

#define SERIAL_SCI_NUM 3

#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

struct h8_3069f_sci {
  volatile uint8 smr;
  volatile uint8 brr;
  volatile uint8 scr;
  volatile uint8 tdr;
  volatile uint8 ssr;
  volatile uint8 rdr;
  volatile uint8 scmr;
};

#define H8_3069F_SCI_SMR_CKS_PER1  (0<<0)
#define H8_3069F_SCI_SMR_CKS_PER4  (1<<0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2<<0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3<<0)
#define H8_3069F_SCI_SMR_MP     (1<<2)
#define H8_3069F_SCI_SMR_STOP   (1<<3)
#define H8_3069F_SCI_SMR_OE     (1<<4)
#define H8_3069F_SCI_SMR_PE     (1<<5)
#define H8_3069F_SCI_SMR_CHR    (1<<6)
#define H8_3069F_SCI_SMR_CA     (1<<7)

#define H8_3069F_SCI_SCR_CKE0   (1<<0)
#define H8_3069F_SCI_SCR_CKE1   (1<<1)
#define H8_3069F_SCI_SCR_TEIE   (1<<2)
#define H8_3069F_SCI_SCR_MPIE   (1<<3)
#define H8_3069F_SCI_SCR_RE     (1<<4) /* 受信有効 */
#define H8_3069F_SCI_SCR_TE     (1<<5) /* 送信有効 */
#define H8_3069F_SCI_SCR_RIE    (1<<6) /* 受信割込み有効 */
#define H8_3069F_SCI_SCR_TIE    (1<<7) /* 送信割込み有効 */

#define H8_3069F_SCI_SSR_MPBT   (1<<0)
#define H8_3069F_SCI_SSR_MPB    (1<<1)
#define H8_3069F_SCI_SSR_TEND   (1<<2)
#define H8_3069F_SCI_SSR_PER    (1<<3)
#define H8_3069F_SCI_SSR_FERERS (1<<4)
#define H8_3069F_SCI_SSR_ORER   (1<<5)
#define H8_3069F_SCI_SSR_RDRF   (1<<6) /* 受信完了 */
#define H8_3069F_SCI_SSR_TDRE   (1<<7) /* 送信完了 */

// SCIのレジスタの先頭アドレスの配列
static struct {
  volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
  { H8_3069F_SCI0 }, 
  { H8_3069F_SCI1 }, 
  { H8_3069F_SCI2 }, 
};

/* デバイス初期化 */
int serial_init(int index)
{
  // H8/3069Fのマニュアル 13節を参照
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  /* SCR(シリアルコントロールレジスタ)は送受信動作や送受信に関わる割り込みの許可、禁止を設定する。0が禁止で1が許可 */
  sci->scr = 0;
  /* SMR(シリアルモードレジスタ)ではシリアル通信フォーマット(ストップビット、パリティetc)と、ボーレートジェネレータの
   クロックソースを選択する */
  sci->smr = 0;
  // BRRはマニュアルの13.2.8節を参照 (p535 ビットレート 9600bpsの行)
  sci->brr = 64; /* 20MHzのクロックから9600bpsを生成(25MHzの場合は80にする) */
  /*
    ビット4のレシーブイネーブル(受信許可)、ビット5のトランスミットイネーブル(送信許可)を1にしている。
    ビット2のトランスミットエンドインタラプト(送信終了割り込み)、ビット7のトランスミット(送信データエンプティ割り込み)も
    1にするのかなと思いきや、そうでもないようだ。よく分からない。
  */
  sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE; /* 送受信可能 */
  /* SSR(シリアルステータスレジスタ)はSCIの動作状態を示すステータスフラグと、マルチプロセッサビットを内蔵 */
  sci->ssr = 0;

  return 0;
}

/* 送信可能か？ */
int serial_is_send_enable(int index)
{
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

/* １文字送信 */
int serial_send_byte(int index, unsigned char c)
{
  volatile struct h8_3069f_sci *sci = regs[index].sci;

  /* 送信可能になるまで待つ */
  while (!serial_is_send_enable(index))
    ;
  sci->tdr = c;
  sci->ssr &= ~H8_3069F_SCI_SSR_TDRE; /* 送信開始 */

  return 0;
}

