MEMORY {
	RAM (rwx): ORIGIN = 0x12000, LENGTH = 0x10000-0x2000
}

ENTRY(_start);

irqvectors = 0x32000 - 0x100;

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

	/*.stack : {
		. = . + 4096;
		. = ALIGN(8);
		__usp = .;
	} >RAM*/

	end = .;
};
