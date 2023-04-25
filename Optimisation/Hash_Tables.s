	.file	"Hash_Tables.cpp"
	.text
	.globl	_Z15Hash_Table_CtormP4TextPFlPK4WordE
	.type	_Z15Hash_Table_CtormP4TextPFlPK4WordE, @function
_Z15Hash_Table_CtormP4TextPFlPK4WordE:
.LFB4513:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$24, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	$0, -16(%rbp)
	jmp	.L2
.L3:
	movq	-32(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rax
	salq	$4, %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z16Add_Node_To_ListP10Hash_TableP4Word
	addq	$1, -16(%rbp)
.L2:
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jl	.L3
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4513:
	.size	_Z15Hash_Table_CtormP4TextPFlPK4WordE, .-_Z15Hash_Table_CtormP4TextPFlPK4WordE
	.globl	_Z16Add_Node_To_ListP10Hash_TableP4Word
	.type	_Z16Add_Node_To_ListP10Hash_TableP4Word, @function
_Z16Add_Node_To_ListP10Hash_TableP4Word:
.LFB4514:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-56(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rcx
	movq	%rdx, %rax
	movl	$0, %edx
	divq	%rcx
	movq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movb	$0, -41(%rbp)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L6
	movb	$1, -41(%rbp)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	leaq	(%rdx,%rax), %rbx
	movl	$16, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, 8(%rbx)
.L6:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L7
.L10:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L8
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rcx
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	je	.L12
.L8:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -40(%rbp)
.L7:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L10
	movzbl	-41(%rbp), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L11
	movl	$16, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -40(%rbp)
.L11:
	movq	-40(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	addq	$1, %rdx
	movq	%rdx, (%rax)
	jmp	.L5
.L12:
	nop
.L5:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4514:
	.size	_Z16Add_Node_To_ListP10Hash_TableP4Word, .-_Z16Add_Node_To_ListP10Hash_TableP4Word
	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"index;list_len\n"
.LC2:
	.string	"%ld;%ld\n"
	.text
	.globl	_Z24Save_Table_Lists_LengthsP10Hash_TablePKc
	.type	_Z24Save_Table_Lists_LengthsP10Hash_TablePKc, @function
_Z24Save_Table_Lists_LengthsP10Hash_TablePKc:
.LFB4515:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	leaq	.LC0(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	movl	$15, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	$0, -16(%rbp)
	jmp	.L14
.L15:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$1, -16(%rbp)
.L14:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L15
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4515:
	.size	_Z24Save_Table_Lists_LengthsP10Hash_TablePKc, .-_Z24Save_Table_Lists_LengthsP10Hash_TablePKc
	.globl	_Z11Check_EntryPK10Hash_TablePKc
	.type	_Z11Check_EntryPK10Hash_TablePKc, @function
_Z11Check_EntryPK10Hash_TablePKc:
.LFB4516:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -24(%rbp)
	movq	-72(%rbp), %rax
	movq	16(%rax), %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	movq	(%rax), %rcx
	movq	%rdx, %rax
	movl	$0, %edx
	divq	%rcx
	movq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movb	$0, -57(%rbp)
	movq	-72(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	$0, -48(%rbp)
	jmp	.L17
.L20:
	movq	-24(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L18
	movq	-24(%rbp), %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	jne	.L18
	movb	$1, -57(%rbp)
	jmp	.L19
.L18:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	addq	$1, -48(%rbp)
.L17:
	movq	-72(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	cmpq	%rax, -48(%rbp)
	jb	.L20
.L19:
	movzbl	-57(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L22
	call	__stack_chk_fail@PLT
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4516:
	.size	_Z11Check_EntryPK10Hash_TablePKc, .-_Z11Check_EntryPK10Hash_TablePKc
	.globl	_Z15Check_Entry_AVXPK10Hash_TablePPKc
	.type	_Z15Check_Entry_AVXPK10Hash_TablePPKc, @function
_Z15Check_Entry_AVXPK10Hash_TablePPKc:
.LFB4517:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movl	$0, -84(%rbp)
	jmp	.L24
.L25:
	movl	-84(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movl	-84(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$72, %rax
	movq	%rdx, (%rax)
	movl	-84(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-84(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	subq	$80, %rdx
	movq	%rax, (%rdx)
	addl	$1, -84(%rbp)
.L24:
	cmpl	$3, -84(%rbp)
	jle	.L25
	nop
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4517:
	.size	_Z15Check_Entry_AVXPK10Hash_TablePPKc, .-_Z15Check_Entry_AVXPK10Hash_TablePPKc
	.globl	_Z16Hash_Polynom_AVXPK4Word
	.type	_Z16Hash_Polynom_AVXPK4Word, @function
_Z16Hash_Polynom_AVXPK4Word:
.LFB4518:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	nop
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4518:
	.size	_Z16Hash_Polynom_AVXPK4Word, .-_Z16Hash_Polynom_AVXPK4Word
	.globl	_Z15Hash_Table_DtorP10Hash_Table
	.type	_Z15Hash_Table_DtorP10Hash_Table, @function
_Z15Hash_Table_DtorP10Hash_Table:
.LFB4519:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L29
.L32:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	$0, -16(%rbp)
	jmp	.L30
.L31:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	$0, (%rax)
	movq	-24(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	addq	$1, -16(%rbp)
.L30:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	salq	$4, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jb	.L31
	addq	$1, -32(%rbp)
.L29:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -32(%rbp)
	jbe	.L32
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-40(%rbp), %rax
	movq	$0, (%rax)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4519:
	.size	_Z15Hash_Table_DtorP10Hash_Table, .-_Z15Hash_Table_DtorP10Hash_Table
	.globl	_Z13Hash_Just_OnePK4Word
	.type	_Z13Hash_Just_OnePK4Word, @function
_Z13Hash_Just_OnePK4Word:
.LFB4520:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4520:
	.size	_Z13Hash_Just_OnePK4Word, .-_Z13Hash_Just_OnePK4Word
	.globl	_Z10Hash_AsciiPK4Word
	.type	_Z10Hash_AsciiPK4Word, @function
_Z10Hash_AsciiPK4Word:
.LFB4521:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4521:
	.size	_Z10Hash_AsciiPK4Word, .-_Z10Hash_AsciiPK4Word
	.globl	_Z11Hash_StrlenPK4Word
	.type	_Z11Hash_StrlenPK4Word, @function
_Z11Hash_StrlenPK4Word:
.LFB4522:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4522:
	.size	_Z11Hash_StrlenPK4Word, .-_Z11Hash_StrlenPK4Word
	.globl	_Z14Hash_Ascii_SumPK4Word
	.type	_Z14Hash_Ascii_SumPK4Word, @function
_Z14Hash_Ascii_SumPK4Word:
.LFB4523:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L40
.L41:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rax, -16(%rbp)
	addq	$1, -8(%rbp)
.L40:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -8(%rbp)
	jl	.L41
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4523:
	.size	_Z14Hash_Ascii_SumPK4Word, .-_Z14Hash_Ascii_SumPK4Word
	.globl	_Z3ROLli
	.type	_Z3ROLli, @function
_Z3ROLli:
.LFB4524:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %ecx
	salq	%cl, %rsi
	movl	-12(%rbp), %edx
	movl	$8, %eax
	subl	%edx, %eax
	movq	-8(%rbp), %rdx
	movl	%eax, %ecx
	sarq	%cl, %rdx
	movq	%rdx, %rax
	orq	%rsi, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4524:
	.size	_Z3ROLli, .-_Z3ROLli
	.globl	_Z8Hash_RolPK4Word
	.type	_Z8Hash_RolPK4Word, @function
_Z8Hash_RolPK4Word:
.LFB4525:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L46
.L47:
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_Z3ROLli
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-12(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	xorq	%rdx, %rax
	movq	%rax, -8(%rbp)
	addl	$1, -12(%rbp)
.L46:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jl	.L47
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4525:
	.size	_Z8Hash_RolPK4Word, .-_Z8Hash_RolPK4Word
	.globl	_Z3RORli
	.type	_Z3RORli, @function
_Z3RORli:
.LFB4526:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %ecx
	sarq	%cl, %rsi
	movl	-12(%rbp), %edx
	movl	$8, %eax
	subl	%edx, %eax
	movq	-8(%rbp), %rdx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	orq	%rsi, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4526:
	.size	_Z3RORli, .-_Z3RORli
	.globl	_Z8Hash_RorPK4Word
	.type	_Z8Hash_RorPK4Word, @function
_Z8Hash_RorPK4Word:
.LFB4527:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L52
.L53:
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_Z3ROLli
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-12(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	xorq	%rdx, %rax
	movq	%rax, -8(%rbp)
	addl	$1, -12(%rbp)
.L52:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jl	.L53
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4527:
	.size	_Z8Hash_RorPK4Word, .-_Z8Hash_RorPK4Word
	.globl	_Z12Hash_PolynomPK4Word
	.type	_Z12Hash_PolynomPK4Word, @function
_Z12Hash_PolynomPK4Word:
.LFB4528:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	$31, -8(%rbp)
	movq	$1, -24(%rbp)
	movq	$0, -16(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L56
.L57:
	movq	-40(%rbp), %rax
	movq	(%rax), %rdx
	movl	-28(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	imulq	-24(%rbp), %rax
	addq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	imulq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	addl	$1, -28(%rbp)
.L56:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jl	.L57
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4528:
	.size	_Z12Hash_PolynomPK4Word, .-_Z12Hash_PolynomPK4Word
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
