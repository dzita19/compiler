PROGRAM   = compiler
WRAPPER   = cc
SPEC_DIR  = spec
BUILD_DIR = build

DEBUG_ENABLED = 1

FLEX_SPEC  = lexer_spec.l
BISON_SPEC = parser_spec.y

FLEX_OUTFILE  = lex.yy.c
BISON_OUTFILE = y.tab.c
BISON_SYMBOLS = y.tab.h

C_SOURCE_LIST = src/yy/$(BISON_OUTFILE) \
	src/yy/$(FLEX_OUTFILE) \
	src/compiler_main.c \
	src/util/array.c \
	src/util/linked_list.c \
	src/util/logger.c \
	src/util/memory_safety.c \
	src/util/queue.c \
	src/util/stack.c \
	src/util/vector.c \
	src/symtab/obj.c \
	src/symtab/scope.c \
	src/symtab/struct.c \
	src/symtab/symtab.c \
	src/decl/declarations.c \
	src/decl/declarators.c \
	src/decl/indirections.c \
	src/decl/initializer.c \
	src/decl/specifiers.c \
	src/stmt/fold.c \
	src/stmt/literals.c \
	src/stmt/stmt.c \
	src/stmt/tree.c \
	src/stmt/expr/arithm.c \
	src/stmt/expr/bitwise.c \
	src/stmt/expr/expr.c \
	src/stmt/flow/iteration.c \
	src/stmt/flow/jump.c \
	src/stmt/expr/logic.c \
	src/stmt/expr/postfix.c \
	src/stmt/expr/prefix.c \
	src/stmt/expr/primary.c \
	src/stmt/flow/selection.c \
	src/gen/abi.c \
	src/gen/architecture.c \
	src/gen/assembler.c \
	src/gen/generator.c \
	src/gen/ir_gen.c \
	src/gen/ir_opt.c \
	src/gen/ir_to_asm.c \
	src/gen/intermediate.c \
	src/gen/link_flow.c \
	src/gen/resources.c

C_OBJECT_LIST = 
C_OBJECT_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCE_LIST:.c=.o)))

vpath %.c $(sort $(dir $(C_SOURCE_LIST)))

CC_PATH     = gcc
FLEX_PATH   = flex
BISON_PATH  = bison

INCLUDE     = -I src
WARNINGS    = -Wall
FLAGS_DEBUG = -g
FLAGS_DEPS  = -MMD -MP

FLAGS =
FLAGS += $(INCLUDE)
FLAGS += $(FLAGS_DEPS)
FLAGS += $(WARNINGS)

ifeq ($(DEBUG_ENABLED), 1)
FLAGS += $(FLAGS_DEBUG)
endif

all: src/yy/$(BISON_OUTFILE) src/yy/$(FLEX_OUTFILE) $(BUILD_DIR)/$(PROGRAM) $(BUILD_DIR)/$(WRAPPER)

src/yy/$(BISON_OUTFILE): $(SPEC_DIR)/$(BISON_SPEC) makefile
	$(BISON_PATH) -d -o src/yy/$(BISON_OUTFILE) $(SPEC_DIR)/$(BISON_SPEC)

src/yy/$(FLEX_OUTFILE): $(SPEC_DIR)/$(FLEX_SPEC) src/yy/$(BISON_SYMBOLS) makefile
	$(FLEX_PATH) --outfile=src/yy/$(FLEX_OUTFILE) $(SPEC_DIR)/$(FLEX_SPEC)

clean:
	rm -rf build
	rm src/yy/$(BISON_OUTFILE)
	rm src/yy/$(BISON_SYMBOLS)
	rm src/yy/$(FLEX_OUTFILE)

$(BUILD_DIR)/$(PROGRAM) : $(C_OBJECT_LIST) makefile | $(BUILD_DIR)
	$(CC_PATH) -o $(@) $(C_OBJECT_LIST)

$(BUILD_DIR)/$(WRAPPER) : src/compiler_wrapper.c makefile | $(BUILD_DIR)
	$(CC_PATH) -o $(@) src/compiler_wrapper.c $(FLAGS)

$(BUILD_DIR)/%.o : %.c makefile | $(BUILD_DIR)
	$(CC_PATH) -c -o $(@) $(<) $(FLAGS)

line_count:
	wc -l $(C_SOURCE_LIST) $(SPEC_DIR)/$(FLEX_SPEC) $(SPEC_DIR)/$(BISON_SPEC)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)