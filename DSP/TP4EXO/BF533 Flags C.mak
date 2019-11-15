# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     BF533 Flags C_Debug
#     BF533 Flags C_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files\Analog Devices\VisualDSP 5.0


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "BF533 Flags C_Debug" configuration
#

ifeq ($(MAKECMDGOALS),BF533 Flags C_Debug)

BF533\ Flags\ C_Debug : ./Debug/BF533\ Flags\ C.dxe 

Debug/Initialization.doj :Initialization.c BF533\ Flags.h $(VDSP)/Blackfin/include/sys/exception.h $(VDSP)/Blackfin/include/cdefBF533.h $(VDSP)/Blackfin/include/cdefBF532.h $(VDSP)/Blackfin/include/defBF532.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/sys/05000311.h $(VDSP)/Blackfin/include/sys/platform.h $(VDSP)/Blackfin/include/sys/_adi_platform.h 
	@echo ".\Initialization.c"
	$(VDSP)/ccblkfn.exe -c .\Initialization.c -file-attr ProjectName=BF533\ Flags\ C -g -no-annotate -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -flags-compiler --diag_warning,implicit_func_decl -warn-protos -proc ADSP-BF533 -o .\Debug\Initialization.doj -MM

Debug/ISRs.doj :ISRs.c BF533\ Flags.h $(VDSP)/Blackfin/include/sys/exception.h $(VDSP)/Blackfin/include/cdefBF533.h $(VDSP)/Blackfin/include/cdefBF532.h $(VDSP)/Blackfin/include/defBF532.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/sys/05000311.h $(VDSP)/Blackfin/include/sys/platform.h $(VDSP)/Blackfin/include/sys/_adi_platform.h 
	@echo ".\ISRs.c"
	$(VDSP)/ccblkfn.exe -c .\ISRs.c -file-attr ProjectName=BF533\ Flags\ C -g -no-annotate -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -flags-compiler --diag_warning,implicit_func_decl -warn-protos -proc ADSP-BF533 -o .\Debug\ISRs.doj -MM

Debug/main.doj :main.c BF533\ Flags.h $(VDSP)/Blackfin/include/sys/exception.h $(VDSP)/Blackfin/include/cdefBF533.h $(VDSP)/Blackfin/include/cdefBF532.h $(VDSP)/Blackfin/include/defBF532.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/sys/05000311.h $(VDSP)/Blackfin/include/sys/platform.h $(VDSP)/Blackfin/include/sys/_adi_platform.h $(VDSP)/Blackfin/include/sysreg.h 
	@echo ".\main.c"
	$(VDSP)/ccblkfn.exe -c .\main.c -file-attr ProjectName=BF533\ Flags\ C -g -no-annotate -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -flags-compiler --diag_warning,implicit_func_decl -warn-protos -proc ADSP-BF533 -o .\Debug\main.doj -MM

./Debug/BF533\ Flags\ C.dxe :$(VDSP)/Blackfin/ldf/adsp-BF533.ldf $(VDSP)/Blackfin/lib/bf532_rev_0.5/crtsf532y.doj ./Debug/Initialization.doj ./Debug/ISRs.doj ./Debug/main.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/__initsbsz532.doj $(VDSP)/Blackfin/lib/cplbtab533.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/crtn532y.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/libsmall532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libio532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libc532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/librt_fileio532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libevent532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libcpp532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libf64ieee532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libdsp532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libsftflt532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libetsi532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libssl532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libdrv532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libusb532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libprofile532y.dlb 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\Initialization.doj .\Debug\ISRs.doj .\Debug\main.doj -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\BF533\ Flags\ C.dxe -proc ADSP-BF533 -MM

endif

ifeq ($(MAKECMDGOALS),BF533 Flags C_Debug_clean)

BF533\ Flags\ C_Debug_clean:
	-$(RM) "Debug\Initialization.doj"
	-$(RM) "Debug\ISRs.doj"
	-$(RM) "Debug\main.doj"
	-$(RM) ".\Debug\BF533 Flags C.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


