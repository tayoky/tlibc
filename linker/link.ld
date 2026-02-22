/*thank sasdallas for this awsome idea ...*/

SECTIONS {
	. = 0x3F000000;
	.text : ALIGN(4K) {
		*(.text .text.*)
	}
	.data : ALIGN(4K) {
		*(.data .data.*)
	}
	.bss : ALIGN(4K) {
		*(COMMON)
		*(.bss .bss.*)
	}

	/DISCARD/ : {
		*(.comment)
	}
}
