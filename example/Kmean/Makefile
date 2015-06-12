# NEED : export LD_LIBRARY_PATH=/Developer/NVIDIA/CUDA-7.0/lib


LIB_NAME = SimpleExample

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

CC = clang++
CC_FLAGS = -std=c++11 -DNDEBUG  -fPIC  -Wall -mtune=core2 -g -O2 

CUDA_CC = nvcc
CUDA_CC_FLAGS = -std=c++11 



LIB_DIR = lib
OBJ_DIR = build
SRC_DIR = source
INC_DIR = include

DYN_LIB_NAME = $(LIB_NAME).so

# Use all .cpp files in SRC_DIR folder.
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

CUDA_FILES := $(wildcard $(SRC_DIR)/*.cu)

# All object file are gonna be in OBJ_DIR folder.
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
CU_OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CUDA_FILES:.cu=.o)))

# Source include.
# Comming from "R RHOME" command.
R_SRC_INCLUDE = -I/Library/Frameworks/R.framework/Resources/include 
INCLUDE_SRC = -I$(INC_DIR) $(R_SRC_INCLUDE) -I/usr/local/include -I/usr/local/include/freetype2 -I/opt/X11/include

# Linker commands.
LD_INCLUDE = -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/lib
LD_FLAGS = -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress
LD_LIB = -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation

CUDA_LIB = -L/Developer/NVIDIA/CUDA-7.0/lib/ -lcudart
CUDA_INCLUDE = -I/Developer/NVIDIA/CUDA-7.0/include/

all: createDir $(OBJ_FILES) $(CU_OBJ_FILES)
	$(CC) $(LD_FLAGS) $(LD_INCLUDE) $(CUDA_LIB) $(OBJ_FILES) $(CU_OBJ_FILES) $(LD_LIB) -o $(LIB_DIR)/$(DYN_LIB_NAME)
	# $(CC) $(CC_FLAGS) $(CUDA_LIB) $(OBJ_FILES) $(CU_OBJ_FILES) -o main

createDir:
	@mkdir -p build lib

$(OBJ_DIR)/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

$(OBJ_DIR)/%.o: source/%.cu
	$(CUDA_CC) $(CUDA_CC_FLAGS) $(INCLUDE_SRC) $(CUDA_INCLUDE) $(CUDA_LIB) -c -o $@ $<

test:
	@R --slave -f main.R

clean: 
	rm -f $(OBJ_FILES)
	rm -f $(CU_OBJ_FILES)
	rm -f $(LIB_DIR)/$(DYN_LIB_NAME)
