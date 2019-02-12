#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"


//  最初のスレッド
//  - start_threadsを引数にkz_startを実行
//    - start_threadsを引数にthread_runを実行
//      - タスクコントロールブロックの空きを探す
//      - スレッドを生成(thp->init.funcにstart_threadsを設定)。(これをスレッドAとする)
//      - スレッドAのコンテキストを設定thp->context.sp = (uint32)sp
//      - スレッドAをカレントスレッドに設定し、レディキューの末尾に設定
//    - dispatch(&current->context)を実行
//      - 「mov.l	@er0,er7で」でスタックポインタにスレッドAのスタックを指定
//      - 汎用レジスタER0~ER6を復元
//      - rte (CCR←@SP+, PC←@SP+)でプログラムカウンタにthread_initが設定されて、thread_initが呼ばれる
//   
//  スレッドA
//  - thread_init

/* システム・タスクとユーザ・スレッドの起動 */
static int start_threads(int argc, char *argv[])
{
  kz_run(test08_1_main, "command", 0x100, 0, NULL);
  return 0;
}
// TODO プログラムの開始から終了まで、各スレッドの生成、終了をおっかける
// TODO スレッドのハンドラへの引数の渡し方など理解する
// TODO スタックポインタの退避、復旧。レジスタの退避、復旧について理解する
int main(void)
{
  INTR_DISABLE; /* 割込み無効にする */

  puts("kozos boot succeed!\n");
  // TODO なぜ直接start_threadsを呼び出してはいけない？
  /* OSの動作開始 */
  kz_start(start_threads, "start", 0x100, 0, NULL);
  // TODO 「ここには戻ってこない」と書いてるが、なぜか、理解する
  /* ここには戻ってこない */

  return 0;
}





