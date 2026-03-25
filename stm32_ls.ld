ENTRY(Reset_Handler)

MEMORY {
FLASH(rx):ORIGIN =0x08000000,LENGTH =1024K
SRAM(rwx):ORIGIN =0X20000000,LENGTH =128K
}
SECTIONS 
{
	.text : 
	{
  		*(.isr_vector)
		*(.text)
		*(.text.*) 
		*(.rodata)
		*(.rodata.*)
		*(.init)
		*(.fini)
		. = ALIGN(4);
		_etext = .;
	}>FLASH AT>FLASH

	_la_data =  LOADADDR(.data);

	.data :
	{
	_sdata = .;
		*(.data)
		*(.data.*)
	_edata = .;
	. = ALIGN(4);
	}>SRAM AT>FLASH

	.bss :
	{
	_sbss = .;
	__bss_start__ = _sbss;
	*(.bss)
	*(.bss.*)	
	_ebss = .;
	__bss_end__ = _ebss;
	. = ALIGN(4);
	__end__ = .; 
	end = .;
	}>SRAM

}
