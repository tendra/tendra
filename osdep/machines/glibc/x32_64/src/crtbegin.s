
	.global __dso_handle
	.type __dso_handle,@object
	.size __dso_handle,8
	.section .sbss
	.align 8
__dso_handle:
	.long __dso_handle
	.hidden __dso_handle
