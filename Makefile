#############################################################################
# Makefile for building: Compile
# Generated by qmake (2.01a) (Qt 4.8.4) on: ?? ?? 1 22:29:59 2013
# Project:  Compile.pro
# Template: app
# Command: d:\Qt\4.8.4\bin\qmake.exe -spec d:\Qt\4.8.4\mkspecs\win32-g++ CONFIG+=declarative_debug -o Makefile Compile.pro
#############################################################################

first: debug
install: debug-install
uninstall: debug-uninstall
MAKEFILE      = Makefile
QMAKE         = d:\Qt\4.8.4\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
SUBTARGETS    =  \
		debug \
		release

debug: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: Compile.pro  d:/Qt/4.8.4/mkspecs/win32-g++/qmake.conf d:/Qt/4.8.4/mkspecs/features/device_config.prf \
		d:/Qt/4.8.4/mkspecs/qconfig.pri \
		d:/Qt/4.8.4/mkspecs/modules/qt_webkit_version.pri \
		d:/Qt/4.8.4/mkspecs/features/qt_functions.prf \
		d:/Qt/4.8.4/mkspecs/features/qt_config.prf \
		d:/Qt/4.8.4/mkspecs/features/exclusive_builds.prf \
		d:/Qt/4.8.4/mkspecs/features/default_pre.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/default_pre.prf \
		d:/Qt/4.8.4/mkspecs/features/debug.prf \
		d:/Qt/4.8.4/mkspecs/features/debug_and_release.prf \
		d:/Qt/4.8.4/mkspecs/features/default_post.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/default_post.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/console.prf \
		d:/Qt/4.8.4/mkspecs/features/declarative_debug.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/rtti.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/exceptions.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/stl.prf \
		d:/Qt/4.8.4/mkspecs/features/shared.prf \
		d:/Qt/4.8.4/mkspecs/features/warn_on.prf \
		d:/Qt/4.8.4/mkspecs/features/win32/thread_off.prf \
		d:/Qt/4.8.4/mkspecs/features/resources.prf \
		d:/Qt/4.8.4/mkspecs/features/uic.prf \
		d:/Qt/4.8.4/mkspecs/features/yacc.prf \
		d:/Qt/4.8.4/mkspecs/features/lex.prf \
		d:/Qt/4.8.4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec d:\Qt\4.8.4\mkspecs\win32-g++ CONFIG+=declarative_debug -o Makefile Compile.pro
d:\Qt\4.8.4\mkspecs\features\device_config.prf:
d:\Qt\4.8.4\mkspecs\qconfig.pri:
d:\Qt\4.8.4\mkspecs\modules\qt_webkit_version.pri:
d:\Qt\4.8.4\mkspecs\features\qt_functions.prf:
d:\Qt\4.8.4\mkspecs\features\qt_config.prf:
d:\Qt\4.8.4\mkspecs\features\exclusive_builds.prf:
d:\Qt\4.8.4\mkspecs\features\default_pre.prf:
d:\Qt\4.8.4\mkspecs\features\win32\default_pre.prf:
d:\Qt\4.8.4\mkspecs\features\debug.prf:
d:\Qt\4.8.4\mkspecs\features\debug_and_release.prf:
d:\Qt\4.8.4\mkspecs\features\default_post.prf:
d:\Qt\4.8.4\mkspecs\features\win32\default_post.prf:
d:\Qt\4.8.4\mkspecs\features\win32\console.prf:
d:\Qt\4.8.4\mkspecs\features\declarative_debug.prf:
d:\Qt\4.8.4\mkspecs\features\win32\rtti.prf:
d:\Qt\4.8.4\mkspecs\features\win32\exceptions.prf:
d:\Qt\4.8.4\mkspecs\features\win32\stl.prf:
d:\Qt\4.8.4\mkspecs\features\shared.prf:
d:\Qt\4.8.4\mkspecs\features\warn_on.prf:
d:\Qt\4.8.4\mkspecs\features\win32\thread_off.prf:
d:\Qt\4.8.4\mkspecs\features\resources.prf:
d:\Qt\4.8.4\mkspecs\features\uic.prf:
d:\Qt\4.8.4\mkspecs\features\yacc.prf:
d:\Qt\4.8.4\mkspecs\features\lex.prf:
d:\Qt\4.8.4\mkspecs\features\include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec d:\Qt\4.8.4\mkspecs\win32-g++ CONFIG+=declarative_debug -o Makefile Compile.pro

qmake_all: FORCE

make_default: debug-make_default release-make_default FORCE
make_first: debug-make_first release-make_first FORCE
all: debug-all release-all FORCE
clean: debug-clean release-clean FORCE
distclean: debug-distclean release-distclean FORCE
	-$(DEL_FILE) Makefile

check: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
