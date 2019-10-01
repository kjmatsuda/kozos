	.h8300h  // TODO これは何か？CPUアーキテクチャか？消したらビルドできるか？
	.section .text // TODO この命令で何が起こる？テキストセクションに入る指示？例えば.dataにしたら実行できずエラーになるのか？
	.global	_start  // TODO globalは何を表す？
#	.type	_start,@function 
_start:
	mov.l	#0xffff00,sp
	jsr	@_main

1:
	bra	1b
