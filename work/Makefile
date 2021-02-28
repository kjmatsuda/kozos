#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outkz_puts ----#
COMPONENT_NAME = kozos_work
#Set this to @ to keep the makefile quiet
SILENCE = @

#--- Inkz_puts ----#
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc

SRC_DIRS = \
    os\
    os/*

# to pick specific files (rather than directories) use this:    
SRC_FILES = 

TEST_SRC_DIRS = \
    tests \
    tests/*

MOCKS_SRC_DIRS = \
    mocks \

INCLUDE_DIRS =\
  .\
  include \
  include/* \
  $(CPPUTEST_HOME)/include/ \
  $(CPPUTEST_HOME)/include/Platforms/Gcc\
  mocks

CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -fno-builtin
CPPUTEST_WARNINGFLAGS += -Wconversion -Wswitch-enum 
# 2021/02/28 K.Matsuda ソースコード上で ifndefで切り分けられるように以下を追加
CPPUTEST_WARNINGFLAGS += -DCPPUTEST

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

