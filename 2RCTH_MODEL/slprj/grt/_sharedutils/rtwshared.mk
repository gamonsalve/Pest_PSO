###########################################################################
## Makefile generated for component 'rtwshared'. 
## 
## Makefile     : rtwshared.mk
## Generated on : Mon Sep 11 15:27:22 2023
## Final product: ./rtwshared.lib
## Product type : static library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = rtwshared
MAKEFILE                  = rtwshared.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2022b
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/monsalve/ONEDRI~1/SOC_ES~3/Pest_PSO/2RCTH_~1
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = ISO_C
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
COMPILER_COMMAND_FILE     = rtwshared_comp.rsp
CMD_FILE                  = rtwshared.rsp
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
MODELLIB                  = rtwshared.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          MinGW64 | gmake (64-bit Windows)
# Supported Version(s):    6.x
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS
# MINGW_ROOT
# MINGW_C_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS            = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX        = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS        = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX    = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow
MW_EXTERNLIB_DIR      = $(MATLAB_ROOT)/extern/lib/win64/mingw64
SHELL                 = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lws2_32

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC_PATH = $(MINGW_ROOT)
CC = "$(CC_PATH)/gcc"

# Linker: GNU Linker
LD_PATH = $(MINGW_ROOT)
LD = "$(LD_PATH)/g++"

# C++ Compiler: GNU C++ Compiler
CPP_PATH = $(MINGW_ROOT)
CPP = "$(CPP_PATH)/g++"

# C++ Linker: GNU C++ Linker
CPP_LD_PATH = $(MINGW_ROOT)
CPP_LD = "$(CPP_LD_PATH)/g++"

# Archiver: GNU Archiver
AR_PATH = $(MINGW_ROOT)
AR = "$(AR_PATH)/ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(MINGW_C_STANDARD_OPTS) -m64 \
                       -O0
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -m64 \
                       -O0
CPP_LDFLAGS          =  -static -m64
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined \
                         -Wl,--out-implib,$(notdir $(basename $(PRODUCT))).lib
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =  -static -m64
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined \
                       -Wl,--out-implib,$(notdir $(basename $(PRODUCT))).lib



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./rtwshared.lib
PRODUCT_TYPE = "static library"
BUILD_TYPE = "Model Reference Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_BUILD_ARGS = -DINTEGER_CODE=0
DEFINES_CUSTOM = 
DEFINES_STANDARD = -DNRT -DUSE_RTMODEL

DEFINES = $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/slprj/grt/_sharedutils/div_nde_s32_floor.c $(START_DIR)/slprj/grt/_sharedutils/look1_binlxpw.c $(START_DIR)/slprj/grt/_sharedutils/qr_cqxNMU1I.c $(START_DIR)/slprj/grt/_sharedutils/rotate_3AIOL9tK.c $(START_DIR)/slprj/grt/_sharedutils/rtGetInf.c $(START_DIR)/slprj/grt/_sharedutils/rtGetNaN.c $(START_DIR)/slprj/grt/_sharedutils/rt_hypotd_snf.c $(START_DIR)/slprj/grt/_sharedutils/rt_nonfinite.c $(START_DIR)/slprj/grt/_sharedutils/svd_OY2AbR3b.c $(START_DIR)/slprj/grt/_sharedutils/trisolve_7ekc8URj.c $(START_DIR)/slprj/grt/_sharedutils/xaxpy_2XzzEcAx.c $(START_DIR)/slprj/grt/_sharedutils/xaxpy_73DBh0ev.c $(START_DIR)/slprj/grt/_sharedutils/xaxpy_Z0aVBByk.c $(START_DIR)/slprj/grt/_sharedutils/xdotc_6O0r46Vz.c $(START_DIR)/slprj/grt/_sharedutils/xgemv_QDh8c9kG.c $(START_DIR)/slprj/grt/_sharedutils/xgemv_W2hZyGQZ.c $(START_DIR)/slprj/grt/_sharedutils/xgerc_iRBGkROB.c $(START_DIR)/slprj/grt/_sharedutils/xgerc_kAS2vIrq.c $(START_DIR)/slprj/grt/_sharedutils/xnrm2_0XtxOmV3.c $(START_DIR)/slprj/grt/_sharedutils/xnrm2_VmvcPHhE.c $(START_DIR)/slprj/grt/_sharedutils/xnrm2_v4pHr6JM.c $(START_DIR)/slprj/grt/_sharedutils/xrot_miKOw6Cs.c $(START_DIR)/slprj/grt/_sharedutils/xrotg_B2eK2SzN.c $(START_DIR)/slprj/grt/_sharedutils/xswap_U9h3dV3C.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = div_nde_s32_floor.obj look1_binlxpw.obj qr_cqxNMU1I.obj rotate_3AIOL9tK.obj rtGetInf.obj rtGetNaN.obj rt_hypotd_snf.obj rt_nonfinite.obj svd_OY2AbR3b.obj trisolve_7ekc8URj.obj xaxpy_2XzzEcAx.obj xaxpy_73DBh0ev.obj xaxpy_Z0aVBByk.obj xdotc_6O0r46Vz.obj xgemv_QDh8c9kG.obj xgemv_W2hZyGQZ.obj xgerc_iRBGkROB.obj xgerc_kAS2vIrq.obj xnrm2_0XtxOmV3.obj xnrm2_VmvcPHhE.obj xnrm2_v4pHr6JM.obj xrot_miKOw6Cs.obj xrotg_B2eK2SzN.obj xswap_U9h3dV3C.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS += $(CPPFLAGS_BASIC)

#---------------------
# MEX C++ Compiler
#---------------------

MEX_CPP_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CPPFLAGS += $(MEX_CPP_Compiler_BASIC)

#-----------------
# MEX Compiler
#-----------------

MEX_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CFLAGS += $(MEX_Compiler_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


MINGW_C_STANDARD_OPTS = $(C_STANDARD_OPTS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


div_nde_s32_floor.obj : $(START_DIR)/slprj/grt/_sharedutils/div_nde_s32_floor.c
	$(CC) $(CFLAGS) -o "$@" "$<"


look1_binlxpw.obj : $(START_DIR)/slprj/grt/_sharedutils/look1_binlxpw.c
	$(CC) $(CFLAGS) -o "$@" "$<"


qr_cqxNMU1I.obj : $(START_DIR)/slprj/grt/_sharedutils/qr_cqxNMU1I.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rotate_3AIOL9tK.obj : $(START_DIR)/slprj/grt/_sharedutils/rotate_3AIOL9tK.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.obj : $(START_DIR)/slprj/grt/_sharedutils/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.obj : $(START_DIR)/slprj/grt/_sharedutils/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_hypotd_snf.obj : $(START_DIR)/slprj/grt/_sharedutils/rt_hypotd_snf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.obj : $(START_DIR)/slprj/grt/_sharedutils/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


svd_OY2AbR3b.obj : $(START_DIR)/slprj/grt/_sharedutils/svd_OY2AbR3b.c
	$(CC) $(CFLAGS) -o "$@" "$<"


trisolve_7ekc8URj.obj : $(START_DIR)/slprj/grt/_sharedutils/trisolve_7ekc8URj.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xaxpy_2XzzEcAx.obj : $(START_DIR)/slprj/grt/_sharedutils/xaxpy_2XzzEcAx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xaxpy_73DBh0ev.obj : $(START_DIR)/slprj/grt/_sharedutils/xaxpy_73DBh0ev.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xaxpy_Z0aVBByk.obj : $(START_DIR)/slprj/grt/_sharedutils/xaxpy_Z0aVBByk.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdotc_6O0r46Vz.obj : $(START_DIR)/slprj/grt/_sharedutils/xdotc_6O0r46Vz.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemv_QDh8c9kG.obj : $(START_DIR)/slprj/grt/_sharedutils/xgemv_QDh8c9kG.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemv_W2hZyGQZ.obj : $(START_DIR)/slprj/grt/_sharedutils/xgemv_W2hZyGQZ.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgerc_iRBGkROB.obj : $(START_DIR)/slprj/grt/_sharedutils/xgerc_iRBGkROB.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgerc_kAS2vIrq.obj : $(START_DIR)/slprj/grt/_sharedutils/xgerc_kAS2vIrq.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2_0XtxOmV3.obj : $(START_DIR)/slprj/grt/_sharedutils/xnrm2_0XtxOmV3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2_VmvcPHhE.obj : $(START_DIR)/slprj/grt/_sharedutils/xnrm2_VmvcPHhE.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2_v4pHr6JM.obj : $(START_DIR)/slprj/grt/_sharedutils/xnrm2_v4pHr6JM.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrot_miKOw6Cs.obj : $(START_DIR)/slprj/grt/_sharedutils/xrot_miKOw6Cs.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg_B2eK2SzN.obj : $(START_DIR)/slprj/grt/_sharedutils/xrotg_B2eK2SzN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xswap_U9h3dV3C.obj : $(START_DIR)/slprj/grt/_sharedutils/xswap_U9h3dV3C.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


