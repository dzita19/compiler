PROGRAM = compiler
SPEC_DIR = spec
BUILD_DIR = build

DEBUG_ENABLED = 1

FLEX_SPEC = lexer_spec.l
BISON_SPEC = parser_spec.y

FLEX_OUTFILE = lex.yy.c
BISON_OUTFILE = y.tab.c

C_SOURCE_LIST = src/yy/$(FLEX_OUTFILE) \
	src/yy/$(BISON_OUTFILE) \
	src/compiler.c \
	src/ast/tree.c \
	src/ast/production.c \
	src/util/stack.c \
	src/util/linked_list.c 

CPP_SOURCE_LIST = 

C_OBJECT_LIST = 
C_OBJECT_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCE_LIST:.c=.o)))
C_OBJECT_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(CPP_SOURCE_LIST:.cpp=.o)))

vpath %.c $(sort $(dir $(C_SOURCE_LIST)))
vpath %.cpp $(sort $(dir $(CPP_SOURCE_LIST)))

INCLUDE = -I src
FLAGS_DEBUG = -g
FLAGS_DEPS = -MMD -MP

FLAGS =
FLAGS += $(INCLUDE)
FLAGS += $(FLAGS_DEBUG)
FLAGS += $(FLAGS_DEPS)

ifeq ($(FLAGS_DEBUG), 1)
FLAGS += $(FLAGS_DEBUG)
endif

all: parser_gen lexer_gen $(BUILD_DIR)/$(PROGRAM)
	$(info BUILT WITHOUT ERRORS)

parser_gen: $(SPEC_DIR)/$(BISON_SPEC) makefile
	bison -d -o src/yy/$(BISON_OUTFILE) $(SPEC_DIR)/$(BISON_SPEC)

lexer_gen: $(SPEC_DIR)/$(FLEX_SPEC) makefile
	flex --outfile=src/yy/$(FLEX_OUTFILE) $(SPEC_DIR)/$(FLEX_SPEC)

$(BUILD_DIR)/$(PROGRAM) : $(C_OBJECT_LIST) makefile | $(BUILD_DIR)
	g++ -o $(@) $(C_OBJECT_LIST)

$(BUILD_DIR)/%.o : %.c makefile | $(BUILD_DIR)
	gcc -c -o $(@) $(<) $(FLAGS)

$(BUILD_DIR)/%.o : %.cpp makefile | $(BUILD_DIR)
	g++ -c -o $(@) $(<) $(FLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)