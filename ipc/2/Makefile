CC  =  gcc
CXX =  g++
AR  =  ar

MAKECMDGOALS ?= debug

ifeq ($(MAKECMDGOALS),release)
	BUILD=RELEASE
else
	BUILD=DEBUG
endif

PATH_PROJECT = /home/sean/gitdir/code/
PATH_SRC = $(PATH_PROJECT)/ipc/2
PATH_OBJ = $(PATH_PROJECT)/objs/2
PATH_LIB = $(PATH_PROJECT)/lib/
PATH_BIN = $(PATH_PROJECT)/bin/

### 64bit for OSVERSION_64 ###
OS_VERSION = OSVERSION_64
ASYNOP     = NASYN_TRIGGER

### C flags define ###
ifeq ($(BUILD), BUILD)
	C_FLAGS = -Wall -D_GNU_SOURCE -Wno-deprecated -fPIC -g -O0 -pipe -DDEBUG
	cxx_FLAGS = -Wall -D_GNU_SOURCE -Wno-deprecated -fPIC -g -O0 -pipe -DDEBUG -Woverloaded-virtual -D__cplusplus
else
	C_FLAGS = -Wall -D_GNU_SOURCE -Wno-deprecated -fPIC -g -O0 -pipe -DNDEBUG
	cxx_FLAGS = -Wall -D_GNU_SOURCE -Wno-deprecated -fPIC -g -O0 -pipe -DNDEBUG -Woverloaded-virtual -D__cplusplus
endif

ifeq ($(ASYNOP), ASYN_TRIGGER)
	C_FLAGS += -DASYN_TRIGGER
	Cxx_FLAGS += -DASYN_TRIGGER
endif

### include dir ###
INC_INCLUDE = -I$(PATH_PROJECT)/util/

INC = $(INC_INCLUDE)

SRC_DIR = $(PATH_SRC)
OBJ_DIR = $(PATH_OBJ)

SOURCE=$(wildcard *.c)
SRC=$(notdir $(SOURCE))
SRCOBJ=$(patsubst %.c,%.o,$(SRC))
OBJS=$(addprefix $(OBJ_DIR), $(SRCOBJ))

TARGET=$(PATH_BIN)pipetest2 
all:$(OBJS)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(INC) $(C_FLAGS) -c $< -o $@
	@echo compile $(BUILD) $@

$(TARGET):$(OBJS)
	@$(CC) $(C_FLAGS) $^ -o $@
	@echo -e "Create $@"
	@echo $(CC) $(C_FLAGS) $^ -o $@ 

debug:all
release:all
all:$(TARGET)

clean:
	@rm -f $(TARGET) $(OBJS)
	@echo rm *.o $(TARGET)

.PHONY:all clean debug release

