# ISP

The ISP (In-System Programmer) protocol was used to burn the OTP PROM in early JieLi chips, like AC209N, AC309N, AC109N, etc.

But in the current flash-based chips, this protocol is merely used to upload a special UART bootloader that is used for the rest of the work. Another use of this protocol in such chips is the [ISP_KEY](isp-key.md) bootloader enter method.
