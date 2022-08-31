MEMORY {
	RAM (rwx): ORIGIN = 0x2000, LENGTH = 64k+64k-0x2000
}

ENTRY(_start);

SECTIONS {
	.text : {
		*(.text.startup)
		*(.text)
		*(.text.*)
	} >RAM
	
	.rodata : {
		*(.rodata)
		*(.rodata.*)
	} >RAM
	
	.data : {
		*(.data)
		*(.data.*)
		*(.sdata)
		*(.sdata.*)
	} >RAM
	
	.bss : {
		_sbss = .;
		*(.sbss)
		*(.sbss.*)
		*(.scommon)
		*(.bss)
		*(.bss.*)
		*(COMMON)
		_ebss = .;
	} >RAM
	
	.stack : {
		. = . + 4096;
		. = ALIGN(8);
		__usp = .;
	} >RAM

	end = .;
};
