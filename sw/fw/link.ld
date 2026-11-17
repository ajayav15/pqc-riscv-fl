MEMORY { RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 256K }
SECTIONS {
  .text : { *(.text.start) *(.text*) } > RAM
  .rodata : { *(.rodata*) *(.srodata*) } > RAM
  .data : { *(.data*) *(.sdata*) } > RAM
  .bss : { _bss_start = .; *(.bss*) *(.sbss*) *(COMMON) . = ALIGN(4); _bss_end = .; } > RAM
  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
