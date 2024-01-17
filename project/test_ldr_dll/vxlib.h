#pragma once

#ifdef USE_VL_MACRO
#ifdef _WIN64
#pragma comment(lib, "../../externals/vxlang/lib/vxlib64.lib")
#else
#pragma comment(lib, "../../externals/vxlang/lib/vxlib32.lib")
#endif

void __stdcall VxVirtualizationBegin();
void __stdcall VxVirtualizationEnd();

void __stdcall VxObfuscationBegin();
void __stdcall VxObfuscationEnd();

void __stdcall VxCodeFlatteningBegin();
void __stdcall VxCodeFlatteningEnd();

void __stdcall VxCodeFlatteningType2Begin();
void __stdcall VxCodeFlatteningType2End();

//

void __stdcall VxCodeFlatteningLv1Begin();
void __stdcall VxCodeFlatteningLv1End();

void __stdcall VxCodeFlatteningLv2Begin();
void __stdcall VxCodeFlatteningLv2End();

void __stdcall VxCodeFlatteningLv3Begin();
void __stdcall VxCodeFlatteningLv3End();

void __stdcall VxCodeFlatteningLv4Begin();
void __stdcall VxCodeFlatteningLv4End();

void __stdcall VxCodeFlatteningLv5Begin();
void __stdcall VxCodeFlatteningLv5End();

//

#define VL_OBFUSCATION_BEGIN               VxObfuscationBegin()
#define VL_OBFUSCATION_END                 VxObfuscationEnd()

#define VL_CODE_FLATTENING_BEGIN           VxCodeFlatteningBegin()
#define VL_CODE_FLATTENING_END             VxCodeFlatteningEnd()

#define VL_CODE_FLATTENING_TYPE2_BEGIN     VxCodeFlatteningType2Begin()
#define VL_CODE_FLATTENING_TYPE2_END       VxCodeFlatteningType2End()

#define VL_VIRTUALIZATION_BEGIN            VxVirtualizationBegin()
#define VL_VIRTUALIZATION_END              VxVirtualizationEnd()

//

#define VL_CODE_FLATTENING_LV_BEGIN(lv)     VxCodeFlatteningLv##lv##Begin()
#define VL_CODE_FLATTENING_LV_END(lv)       VxCodeFlatteningLv##lv##End()
#else
#define VL_OBFUSCATION_BEGIN            
#define VL_OBFUSCATION_END              

#define VL_CODE_FLATTENING_BEGIN        
#define VL_CODE_FLATTENING_END          

#define VL_CODE_FLATTENING_TYPE2_BEGIN  
#define VL_CODE_FLATTENING_TYPE2_END    

#define VL_VIRTUALIZATION_BEGIN         
#define VL_VIRTUALIZATION_END           

//

#define VL_CODE_FLATTENING_LV_BEGIN(lv) 
#define VL_CODE_FLATTENING_LV_END(lv)   
#endif
