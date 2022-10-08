MEMORY {
	RAM  (rwx): ORIGIN = 0x10000, LENGTH = 136k
	FLASH (rx): ORIGIN = 0x1000000, LENGTH = 16M
}

ENTRY(_start)

SECTIONS {
	.text : {
		*(.text.startup)
		*(.text)
		*(.text.*)
	} >FLASH

	.rodata : {
		*(.rodata)
		*(.rodata.*)
	} >FLASH

	.data : {
		_sdata = .;
		*(.data)
		*(.data.*)
		_edata = .;
	} >RAM AT >FLASH
	_ldata = LOADADDR(.data);

	.bss : {
		_sbss = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		_ebss = .;
	} >RAM

	.stack : {
		. = . + 4096;
		. = ALIGN(8);
		__sp = .;
	} >RAM

	end = .;
}
