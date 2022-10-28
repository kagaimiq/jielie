/*------------------ MaskROM exports ---------------------*/
local_irq_enable				= 0x117d40;
local_irq_disable				= 0x117d44;

p33_buf						= 0x117d48;
p33_xor_1byte					= 0x117d4c;
p33_and_1byte					= 0x117d50;
p33_or_1byte					= 0x117d54;
p33_tx_1byte					= 0x117d58;
p33_rx_1byte					= 0x117d5c;
P33_CON_SET					= 0x117d60;

os_init						= 0x117d64;
os_start					= 0x117d68;
os_get_curr_tcb_var				= 0x117d6c;
os_task_create					= 0x117d70;
os_current_task_rom				= 0x117d74;
os_time_dly					= 0x117d78;
os_time_get					= 0x117d7c;
os_task_del_req					= 0x117d80;
os_task_del_res					= 0x117d84;
os_task_del					= 0x117d88;
__os_taskq_pend					= 0x117d8c;
os_taskq_pend					= 0x117d90;
os_task_pend					= 0x117d94;
__os_taskq_post_rom				= 0x117d98;
os_taskq_post					= 0x117d9c;
os_taskq_post_type				= 0x117da0;
os_taskq_flush_rom				= 0x117da4;
task_queue_post_event				= 0x117da8;
os_taskq_post_msg				= 0x117dac;
os_taskq_post_event				= 0x117db0;
os_taskq_accept					= 0x117db4;
os_taskq_del_rom				= 0x117db8;
os_taskq_del_type				= 0x117dbc;
os_sem_create					= 0x117dc0;
os_sem_del					= 0x117dc4;
os_sem_pend_rom					= 0x117dc8;
os_sem_post					= 0x117dcc;
os_sem_set					= 0x117dd0;
os_sem_valid					= 0x117dd4;
os_sem_query					= 0x117dd8;
os_mutex_create					= 0x117ddc;
os_mutex_del					= 0x117de0;
os_mutex_pend_rom				= 0x117de4;
os_mutex_post					= 0x117de8;
os_mutex_valid					= 0x117dec;

xTaskCreate					= 0x117df0;
xTaskGetCurrentTaskHandle			= 0x117df4;
xTaskGetTickCount				= 0x117df8;
xTaskGetHandle					= 0x117dfc;
vTaskDelete					= 0x117e00;
xTaskGetApplicationTaskTag			= 0x117e04;
vTaskSetApplicationTaskTag			= 0x117e08;
xQueueGenericCreateStatic			= 0x117e0c;
xQueueGenericReset				= 0x117e10;
xQueueGenericSend				= 0x117e14;
xQueueGenericSendFromISR			= 0x117e18;
xQueueGenericReceive				= 0x117e1c;
xQueueReceiveFromISR				= 0x117e20;
vQueueDelete					= 0x117e24;
uxQueueMessagesWaiting				= 0x117e28;
uxQueueMessagesWaitingFromISR			= 0x117e2c;
uxQueueSpacesAvailable				= 0x117e30;
pcTaskGetName					= 0x117e34;
prvGetExpectedIdleTime				= 0x117e38;
eTaskConfirmSleepModeStatus			= 0x117e3c;
vTaskStepTick					= 0x117e40;
pxPortInitialiseStack				= 0x117e44;
xPortStartScheduler				= 0x117e48;
vPortEndScheduler				= 0x117e4c;
vPortYield					= 0x117e50;
vPortExitCritical				= 0x117e54;
OS_ClrPending					= 0x117e58;
vTickISR					= 0x117e5c;

pmalloc_init					= 0x117e60;
pmalloc						= 0x117e64;
pfree						= 0x117e68;
pmalloc_get_unused_pages			= 0x117e6c;
get_physic_address				= 0x117e70;
pmm_get_var					= 0x117e74;
vmm_init_					= 0x117e78;
vmalloc_					= 0x117e7c;
vfree_						= 0x117e80;
vmem_get_phy_adr				= 0x117e84;
vmem_start					= 0x117e88;
vmem_end					= 0x117e8c;
vmm_get_var					= 0x117e90;
vmalloc_v2					= 0x117e94;
vfree_v2					= 0x117e98;
vcopy_						= 0x117e9c;

get_cvsd_codec_ops				= 0x117ea0;

VecPlus_fix_r_r_r				= 0x117ea4;
VecMinus_fix_r_r_r				= 0x117ea8;
VecDiv_fix_r_r_r				= 0x117eac;
VelEleMul_fix_r_r_r				= 0x117eb0;
VecEleMul_fix_c_r_c				= 0x117eb4;
VecMagAndDiv_fix				= 0x117eb8;
VecCopy_fix_r_r					= 0x117ebc;
VecConjEleMulAndDiv_fix				= 0x117ec0;
VecRecurAvg_fix					= 0x117ec4;
VecConjRecurAvg_ix				= 0x117ec8;
VecMagRecurAvg_fix				= 0x117ecc;
VecPlusMulScalar_fix				= 0x117ed0;
VecGetMag_fix					= 0x117ed4;
VecMax_fix_v_s					= 0x117ed8;
VecMin_fix_v_s					= 0x117edc;
VecOppos_fix					= 0x117ee0;
VecMean_fix					= 0x117ee4;
VecMeanSq_fix_c					= 0x117ee8;
VecRequanByMax_fix_r				= 0x117eec;
VecRequanByMax_fix_c				= 0x117ef0;
VecEleShift_fix_c				= 0x117ef4;
VecOvShift_fix					= 0x117ef8;
VecCopy_fix_r_c					= 0x117efc;
VecMeanSq_fix_r					= 0x117f00;
VecEleShift_fix_r				= 0x117f04;
logAprx_fix					= 0x117f08;
expAprx_fix					= 0x117f0c;
sqrtAprx_fix					= 0x117f10;
VecEleMul_s16_s16_s32				= 0x117f14;
VecEleMul_s16_s32_s16				= 0x117f18;
VecEleMul_s32_s16_s32				= 0x117f1c;
VecOfShift_s16_s16				= 0x117f20;
VecOvShift_s16_s32				= 0x117f24;
VecCopy_s16_s32					= 0x117f28;
VecCopy_s32_s16					= 0x117f2c;
VecMinus_s16_s32_s32				= 0x117f30;
VecMeanSq_s16_s32				= 0x117f34;
CircVecArrEwMulAndSum_fix			= 0x117f38;

B_fir_cal_s					= 0x117f3c;
B_array_vol					= 0x117f40;
B_Syn_filt					= 0x117f44;
B_Residu					= 0x117f48;
B_comput_correlationS				= 0x117f4c;
B_iircal					= 0x117f50;

repair_corefun_corr				= 0x117f54;
repair_corefun_mixdata				= 0x117f58;
get_repair_api					= 0x117f5c;

firfft						= 0x117f60;
firifft						= 0x117f64;
_rfifft_wrap					= 0x117f68;
_rififft_wrap					= 0x117f6c;

memmem						= 0x117f70;
memcpy						= 0x117f74;
memmove						= 0x117f78;
memcmp						= 0x117f7c;
memset						= 0x117f80;
strcmp						= 0x117f84;
strcpy						= 0x117f88;
strlen						= 0x117f8c;
strncmp						= 0x117f90;
strstr						= 0x117f94;
strchr						= 0x117f98;

__fixdfsi					= 0x117f9c;
__fixsfsi					= 0x117fa0;

spi_get_port					= 0x117fa4;
spi_set_port					= 0x117fa8;
sfc_suspend					= 0x117fac;
sfc_resume					= 0x117fb0;
sfc_drop_cache					= 0x117fb4;

chip_crc16					= 0x117fb8;
CrcDecode					= 0x117fbc;
mask_init					= 0x117fc0;
wdt_clr						= 0x117fc4;
nvram_set_boot_state				= 0x117fc8;
chip_reset					= 0x117fcc;
the_debug_isr					= 0x117fd0;
flash_poweron					= 0x117fd4;
exception_irq_handler				= 0x117fd8;

print						= 0x117fdc;
sprintf						= 0x117fe0;
printf						= 0x117fe4;
puts						= 0x117fe8;

doe						= 0x117fec;

LZ4_setStreamDecode				= 0x117ff0;
LZ4_decompress_safe_continue			= 0x117ff4;
LZ4_decompress_generic				= 0x117ff8;
LZ4_decompress_safe_usingDict			= 0x117ffc;

/*-------------------- MaskROM data ----------------------*/
WOLA_ANA_128					= 0x110060;
WOLA_ANA_64					= 0x110460;
WOLA_SYN_128					= 0x110660;
WOLA_SYN_64					= 0x110a60;
ans_win						= 0x110c60;
nlp_win						= 0x110d60;
bsinc_tab_6					= 0x110f60;
bsinc_tab_6_l					= 0x1111a4;
iCos_Tab					= 0x115f48;

/*--------------------------------------------------------*/
/*
boot_arg_list					= 0x31bfc;

_pll_init					= 0x116fce;

_IRQ_MEM_ADDR					= 0x31f00;
_MASK_MEM_BEGIN					= 0x31b60;
_MASK_MEM_END					= _MASK_MEM_BEGIN + 0x318;
*/
