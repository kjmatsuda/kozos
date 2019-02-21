#include "intr.h"
	.h8300h
	.section .text

	.global	_intr_softerr
#	.type	_intr_softerr,@function
_intr_softerr:
;;; 汎用レジスタを割込み前のスタックに退避
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
;;; 割込み前のスタックポインタをer1に設定(interruptの第2引数として渡る)
	mov.l	er7,er1
;;; スタックを割込み用のスタックに切り替え
	mov.l	#_intrstack,sp
;;; 割込み前のスタックポインタを割込み用スタックに積む
	mov.l	er1,@-er7
	mov.w	#SOFTVEC_TYPE_SOFTERR,r0
	jsr	@_interrupt
	mov.l	@er7+,er1
	mov.l	er1,er7
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte
    
	.global	_intr_syscall
#	.type	_intr_syscall,@function
_intr_syscall:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.l	#_intrstack,sp
	mov.l	er1,@-er7
	mov.w	#SOFTVEC_TYPE_SYSCALL,r0
	jsr	@_interrupt
	mov.l	@er7+,er1
	mov.l	er1,er7
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte

	.global	_intr_serintr
#	.type	_intr_serintr,@function
_intr_serintr:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.l	#_intrstack,sp
	mov.l	er1,@-er7
	mov.w	#SOFTVEC_TYPE_SERINTR,r0
	jsr	@_interrupt
	mov.l	@er7+,er1
	mov.l	er1,er7
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte
