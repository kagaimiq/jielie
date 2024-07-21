# BR25 MaskROM

- Size: 32 KiB
- Base address: 0x110000
- [Dump](br25_110000.bin)
- [Listing (external link)](https://github.com/jiang20082233/AC6966B-JBD/blob/696X/SDK/cpu/br25/tools/rom.lst)

## Contents

- System boot code
- USB "UBOOT" bootloader
- UART bootloader
- ...

## Function stubs

| Address  | Name                            |
|----------|---------------------------------|
| 0x117D40 | `local_irq_enable`              |
| 0x117D44 | `local_irq_disable`             |
| 0x117D48 | `p33_buf`                       |
| 0x117D4C | `p33_xor_1byte`                 |
| 0x117D50 | `p33_and_1byte`                 |
| 0x117D54 | `p33_or_1byte`                  |
| 0x117D58 | `p33_tx_1byte`                  |
| 0x117D5C | `p33_rx_1byte`                  |
| 0x117D60 | `P33_CON_SET`                   |
| 0x117D64 | `os_init`                       |
| 0x117D68 | `os_start`                      |
| 0x117D6C | `os_get_curr_tcb_var`           |
| 0x117D70 | `os_task_create`                |
| 0x117D74 | `os_current_task`               |
| 0x117D78 | `os_time_dly`                   |
| 0x117D7C | `os_time_get`                   |
| 0x117D80 | `os_task_del_req`               |
| 0x117D84 | `os_task_del_res`               |
| 0x117D88 | `os_task_del`                   |
| 0x117D8C | `__os_taskq_pend`               |
| 0x117D90 | `os_taskq_pend`                 |
| 0x117D94 | `os_task_pend`                  |
| 0x117D98 | `__os_taskq_post`               |
| 0x117D9C | `os_taskq_post`                 |
| 0x117DA0 | `os_taskq_post_type`            |
| 0x117DA4 | `os_taskq_flush`                |
| 0x117DA8 | `task_queue_post_event`         |
| 0x117DAC | `os_taskq_post_msg`             |
| 0x117DB0 | `os_taskq_post_event`           |
| 0x117DB4 | `os_taskq_accept`               |
| 0x117DB8 | `os_taskq_del`                  |
| 0x117DBC | `os_taskq_del_type`             |
| 0x117DC0 | `os_sem_create`                 |
| 0x117DC4 | `os_sem_del`                    |
| 0x117DC8 | `os_sem_pend`                   |
| 0x117DCC | `os_sem_post`                   |
| 0x117DD0 | `os_sem_set`                    |
| 0x117DD4 | `os_sem_valid`                  |
| 0x117DD8 | `os_sem_query`                  |
| 0x117DDC | `os_mutex_create`               |
| 0x117DE0 | `os_mutex_del`                  |
| 0x117DE4 | `os_mutex_pend`                 |
| 0x117DE8 | `os_mutex_post`                 |
| 0x117DEC | `os_mutex_valid`                |
| 0x117DF0 | `xTaskCreate`                   |
| 0x117DF4 | `xTaskGetCurrentTaskHandle`     |
| 0x117DF8 | `xTaskGetTickCount`             |
| 0x117DFC | `xTaskGetHandle`                |
| 0x117E00 | `vTaskDelete`                   |
| 0x117E04 | `xTaskGetApplicationTaskFlag`   |
| 0x117E08 | `vTaskSetApplicationTaskTag`    |
| 0x117E0C | `xQueueGenericCreateStatic`     |
| 0x117E10 | `xQueueGenericReset`            |
| 0x117E14 | `xQueueGenericSend`             |
| 0x117E18 | `xQueueGenericSendFromISR`      |
| 0x117E1C | `xQueueGenericReceive`          |
| 0x117E20 | `xQueueReceiveFromISR`          |
| 0x117E24 | `vQueueDelete`                  |
| 0x117E28 | `uxQueueMessagesWaiting`        |
| 0x117E2C | `uxQueueMessagesWaitingFromISR` |
| 0x117E30 | `uxQueueSpacesAvailable`        |
| 0x117E34 | `pcTaskGetName`                 |
| 0x117E38 | `prvGetExpectedIdleTime`        |
| 0x117E3C | `eTaskConfirmSleepModeStatus`   |
| 0x117E40 | `vTaskStepTick`                 |
| 0x117E44 | `pxPortInitializeStack`         |
| 0x117E48 | `xPortStartScheduler`           |
| 0x117E4C | `vPortEndScheduler`             |
| 0x117E50 | `vPortYield`                    |
| 0x117E54 | `vPortExitCritical`             |
| 0x117E58 | `OS_ClrPending`                 |
| 0x117E5C | `vTickISR`                      |
| 0x117E60 | `pmalloc_init`                  |
| 0x117E64 | `pmalloc`                       |
| 0x117E68 | `pfree`                         |
| 0x117E6C | `pmalloc_get_unused_pages`      |
| 0x117E70 | `get_physic_address`            |
| 0x117E74 | `pmm_get_var`                   |
| 0x117E78 | `vmm_init_`                     |
| 0x117E7C | `vmalloc_`                      |
| 0x117E80 | `vfree_`                        |
| 0x117E84 | `vmem_get_phy_adr`              |
| 0x117E88 | `vmem_start`                    |
| 0x117E8C | `vmem_end`                      |
| 0x117E90 | `vmm_get_var`                   |
| 0x117E94 | `vmalloc_v2`                    |
| 0x117E98 | `vfree_v2`                      |
| 0x117E9C | `vcopy_`                        |
| 0x117EA0 | `get_cvsd_codec_ops`            |
| 0x117EA4 | `VecPlus_fix_r_r_r`             |
| 0x117EA8 | and so on...                    |
| 0x117EAC |                                 |
| 0x117EB0 |                                 |
| 0x117EB4 |                                 |
| 0x117EB8 |                                 |
| 0x117EBC |                                 |
| 0x117EC0 |                                 |
| 0x117EC4 |                                 |
| 0x117EC8 |                                 |
| 0x117ECC |                                 |
| 0x117ED0 |                                 |
| 0x117ED4 |                                 |
| 0x117ED8 |                                 |
| 0x117EDC |                                 |
| 0x117EE0 |                                 |
| 0x117EE4 |                                 |
| 0x117EE8 |                                 |
| 0x117EEC |                                 |
| 0x117EF0 |                                 |
| 0x117EF4 |                                 |
| 0x117EF8 |                                 |
| 0x117EFC |                                 |
| 0x117F00 |                                 |
| 0x117F04 |                                 |
| 0x117F08 |                                 |
| 0x117F0C |                                 |
| 0x117F10 |                                 |
| 0x117F14 |                                 |
| 0x117F18 |                                 |
| 0x117F1C |                                 |
| 0x117F20 |                                 |
| 0x117F24 |                                 |
| 0x117F28 |                                 |
| 0x117F2C |                                 |
| 0x117F30 |                                 |
| 0x117F34 |                                 |
| 0x117F38 |                                 |
| 0x117F3C |                                 |
| 0x117F40 |                                 |
| 0x117F44 |                                 |
| 0x117F48 |                                 |
| 0x117F4C |                                 |
| 0x117F50 |                                 |
| 0x117F54 |                                 |
| 0x117F58 |                                 |
| 0x117F5C |                                 |
| 0x117F60 | `firfft`                        |
| 0x117F64 | `firifft`                       |
| 0x117F68 | `_rfifft_wrap`                  |
| 0x117F6C | `_rififft_wrap`                 |
| 0x117F70 | `memmem`                        |
| 0x117F74 | `memcpy`                        |
| 0x117F78 | `memmove`                       |
| 0x117F7C | `memcmp`                        |
| 0x117F80 | `memset`                        |
| 0x117F84 | `strcmp`                        |
| 0x117F88 | `strcpy`                        |
| 0x117F8C | `strlen`                        |
| 0x117F90 | `strncmp`                       |
| 0x117F94 | `strstr`                        |
| 0x117F98 | `strchr`                        |
| 0x117F9C | `__fixdfsi`                     |
| 0x117FA0 | `__fixsfsi`                     |
| 0x117FA4 | `spi_get_port`                  |
| 0x117FA8 | `spi_set_port`                  |
| 0x117FAC | `sfc_suspend`                   |
| 0x117FB0 | `sfc_resume`                    |
| 0x117FB4 | `sfc_drop_cache`                |
| 0x117FB8 | `chip_crc16`                    |
| 0x117FBC | `CrcDecode`                     |
| 0x117FC0 | `mask_init`                     |
| 0x117FC4 | `wdt_clr`                       |
| 0x117FC8 | `nvram_set_boot_state`          |
| 0x117FCC | `chip_reset`                    |
| 0x117FD0 | `the_debug_isr`                 |
| 0x117FD4 | `flash_poweron`                 |
| 0x117FD8 | `exception_irq_handler`         |
| 0x117FDC | `print`                         |
| 0x117FE0 | `sprintf`                       |
| 0x117FE4 | `printf`                        |
| 0x117FE8 | `puts`                          |
| 0x117FEC | `doe`                           |
| 0x117FF0 | `LZ4_setStreamDecode`           |
| 0x117FF4 | `LZ4_decompress_safe_continue`  |
| 0x117FF8 | `LZ4_decompress_generic`        |
| 0x117FFC | `LZ4_decompress_safe_usingDict` |

### CrcDecode

Implements the ["mengli" / "crc"](../../misc/cipher.md#crcdecode-cipher) cipher.
The 'key' is fixed to 0xFFFFFFFF.

```c
void CrcDecode(
	void *buffer,	/* Buffer */
	int size	/* Size in bytes */
);
```

### doe

Implements the ["ENC"](../../misc/cipher.md#enc-chiper) cipher.

```c
void doe(
	uint16_t key,	/* Key */
	void *data,	/* Buffer */
	int size,	/* Size in bytes */
	uint32_t adr	/* key ^= (adr >> 2) */
);
```

### exception_irq_handler

Default exception vector handler that is set up by the Mask ROM automatically.

When it's called, it will push registers `r0-r15` and `reti,rete,retx,rets,psr,icfg,usp,ssp` into the stack and then
call the `exception_irq_hook` (that can be set up with the `mask_init` function) with the pointer to the stack frame provided in the stack frame.
If the hook hasn't been set up (it being `NULL`), then it will simply reset the chip.

### mask_init

Intializes the MaskROM enviroment for use by the application.

```c
void mask_init(
	/* Heap free */
	void	(*free)(void *),
	/* Heap memory allocation */
	void *	(*malloc)(int),
	/* Free memory of the task's stack */
	void	(*stack_free)(void *),
	/* Allocate memory for task's stack */
	void *	(*stack_malloc)(int),
	/* suppress ticks and enter sleep mode (FreeRTOS) */
	void	(*portSUPPRESS_TICKS_AND_SLEEP)(),
	/* start the first task (FreeRTOS) */
	void	(*vPortStartFirstTask)(),
	/* Exception hook */
	void	(*exception_irq_hook)(void),
	/* Idle task hook */
	void	(*idle_hook)(void),
	/* MaskROM putchar */
	void	(*putchar)(int chr),
	/* MaskROM error message output */
	void	(*log_e)(const char *fmt, ...)
);
```

### nvram_set_boot_state

Set up a special magic value in the "NVRAM" to trigger a USB or UART bootloader
instead of going through the normal boot process.

```c
enum nvram_boot_state {
	NVRAM_BOOT_STATE_USB_BOOT	= 2,	/* enter USB bootloader */
	NVRAM_BOOT_STATE_UART_BOOT	= 3,	/* enter UART bootloader */
};

void nvram_set_boot_state(
	enum nvram_boot_state	state;
);
```

### the_debug_isr

An emulation vector handler.

When this is entered, it will switch the stack to a special debug stack,
and push all general and special registers onto this stack.

The pointer of the stack frame is then written into `JL_CPU->BSP` (at 0x10F084),
the bit 31 of `JL_CPU->BPCON` is cleared and it is polled until it sets.
After that it restores the stack frame, switches stack back to normal and returns to normal execution.
