#ifndef _DEFINES_H_INCLUDED_
#define _DEFINES_H_INCLUDED_

#define NULL ((void *)0)
#define SERIAL_DEFAULT_DEVICE 1

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

// DONE このtypedefは何の型？
// -> スレッドポインタ(スレッドIDと参考書には記載)。用途が分かるように型を定義している。
typedef uint32 kz_thread_id_t;
// DONE このtypedefは何の型？
// -> スレッドのメイン関数の型
typedef int (*kz_func_t)(int argc, char *argv[]);
// DONE このtypedefは何の型？
// -> 割り込みハンドラの型
typedef void (*kz_handler_t)(void);

#endif

