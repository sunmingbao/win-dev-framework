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

USE_AV=0
ifeq ($(USE_AV),1)
    CFLAG :=  $(CFLAG) -D_USE_AV 
    LDFLAG := $(LDFLAG) -lavformat.dll 
endif


PRJ_DIR := .
RES_DIR := $(PRJ_DIR)\res
INC_RES_DIRS := --include-dir $(RES_DIR)
INC_DIRS := -I$(PRJ_DIR)\inc -I$(RES_DIR)
OBJ_DIR:=$(PRJ_DIR)\obj

CAUSE_MK_OBJ_DIR:=$(shell mkdir $(OBJ_DIR))


SRC_FILES_BASE_NAMES:=$(shell tools\get_src_files.bat)
OBJ_FILES:=$(addprefix $(OBJ_DIR)\, $(addsuffix .o, $(SRC_FILES_BASE_NAMES)))

RES_OBJS := $(OBJ_DIR)\res.orc
ALL_OBJS := $(OBJ_FILES) $(RES_OBJS) 

CAUSE_GEN_RULES:=$(shell tools\gen_rules.bat)

VPATH := $(PRJ_DIR)\src

CFLAG := $(CFLAG) $(INC_DIRS)
WINDRES_FLAG := --use-temp-file $(INC_RES_DIRS)
# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Targets: ###
target := $(OBJ_DIR)\win-dev-framework.exe

RES_OBJS := $(OBJ_DIR)\res.orc



default: clean  $(target)


$(target): $(ALL_OBJS)
	$(CC) -o $@ $(ALL_OBJS)  $(LDFLAG)
	-cmd.exe /c del c:\rules.txt

$(OBJ_DIR)\res.orc: $(PRJ_DIR)\res\resource.rc
	windres $(WINDRES_FLAG) -i $< -o $@   


-include c:\rules.txt

installer:
	makensis $(PRJ_DIR)\package.nsi
	
clean:
	-cmd.exe /c del /F /Q  $(OBJ_DIR)\\*

all: default installer

.PHONY: all default installer clean



