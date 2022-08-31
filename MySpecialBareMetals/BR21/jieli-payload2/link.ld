MEMORY {
	RAM0(rwx): ORIGIN = 0x10000, LENGTH = 64k
}

ENTRY(_start);

SECTIONS {
	.text : {
		*(.text.startup)
		*(.text)
		*(.text.*)
	} >RAM0
	
	.rodata : {
		*(.rodata)
		*(.rodata.*)
	} >RAM0
	
	.data : {
		*(.data)
		*(.data.*)
		*(.sdata)
		*(.sdata.*)
	} >RAM0
	
	.bss : {
		_sbss = .;
		*(.sbss)
		*(.sbss.*)
		*(.scommon)
		*(.bss)
		*(.bss.*)
		*(COMMON)
		_ebss = .;
	} >RAM0
	
	.stack : {
		. = . + 4096;
		. = ALIGN(8);
	} >RAM0

	end = .;
};
