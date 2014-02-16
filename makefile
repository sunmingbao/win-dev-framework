# 
# 本软件为免费、开源软件。
# 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
# 您可以自由使用、传播本软件。
# 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
# =====================
# 作者: 孙明保
# 邮箱: sunmingbao@126.com
# 

BUILD_TIME:=$(shell echo %date:~0,10%) $(shell echo %time:~0,8%)

CC := gcc

CFLAG := -Wall -O2  -DBUILD_TIME='"$(BUILD_TIME)"' -D_WIN32_IE=0x0501 -D_WIN32_WINNT=0x0502 -DWINVER=0x0501 

# 如果要编译_UNICODE版本，则放开下面的注释
#CFLAG := $(CFLAG) -D_UNICODE

LDFLAG := -mwindows  -s  -lkernel32 -luser32 -lgdi32 -lcomctl32 -lws2_32 


PRJ_DIR := .
RES_DIR := $(PRJ_DIR)\res
INC_RES_DIRS := --include-dir $(RES_DIR)
INC_DIRS := -I$(PRJ_DIR)\inc -I$(RES_DIR)
OBJ_DIR:=$(PRJ_DIR)\obj

CFLAG := $(CFLAG) $(INC_DIRS)
WINDRES_FLAG := --use-temp-file $(INC_RES_DIRS)
# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Targets: ###
target := $(OBJ_DIR)\win-dev-framework.exe

OBJECTS :=  \
	$(OBJ_DIR)\main.o \
	$(OBJ_DIR)\frame_window.o \
	$(OBJ_DIR)\toolbar.o \
	$(OBJ_DIR)\statusbar.o \
	$(OBJ_DIR)\env.o \
	$(OBJ_DIR)\about_dlg.o \
	$(OBJ_DIR)\app_property.o \
	$(OBJ_DIR)\common.o \
	$(OBJ_DIR)\utils.o \
	$(OBJ_DIR)\res.orc


default: prepare  clean  $(target)


$(target): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)  $(LDFLAG)

$(OBJ_DIR)\res.orc: $(PRJ_DIR)\res\resource.rc
	windres $(WINDRES_FLAG) -i $< -o $@   

$(OBJ_DIR)\main.o: $(PRJ_DIR)\src\main.c
	$(CC) -c $(CFLAG)  -o $@  $<
	
$(OBJ_DIR)\frame_window.o: $(PRJ_DIR)\src\frame_window.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\toolbar.o: $(PRJ_DIR)\src\toolbar.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\statusbar.o: $(PRJ_DIR)\src\statusbar.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\about_dlg.o: $(PRJ_DIR)\src\about_dlg.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\app_property.o: $(PRJ_DIR)\src\app_property.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\env.o: $(PRJ_DIR)\src\env.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\tip_window.o: $(PRJ_DIR)\src\tip_window.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\common.o: $(PRJ_DIR)\src\common.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\utils.o: $(PRJ_DIR)\src\utils.c
	$(CC) -c $(CFLAG)  -o $@  $<

installer:
	makensis $(PRJ_DIR)\package.nsi
	
clean:
	-cmd.exe /c del /F /Q  $(OBJ_DIR)\\*

prepare:
	-cmd.exe /c mkdir  $(OBJ_DIR)
	
all: default installer

.PHONY: all prepare default installer clean



