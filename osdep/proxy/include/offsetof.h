#ifndef __PROXY_OFFSETOF_H
#define __PROXY_OFFSETOF_H

#pragma TenDRA begin
#pragma TenDRA keyword __literal for keyword literal
#pragma TenDRA conversion analysis (pointer-int) off
#define offsetof(__s, __m) (__literal (size_t) &(((__s *) 0)->__m))
#pragma TenDRA end

#endif

