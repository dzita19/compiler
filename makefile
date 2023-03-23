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
	src/util/stack.c \
	src/util/queue.c \
	src/util/linked_list.c \
	src/util/memory_safety.c \
	src/util/vector.c \
	src/symtab/obj.c \
	src/symtab/scope.c \
	src/symtab/struct.c \
	src/symtab/symtab.c \
	src/decl/declarations.c \
	src/decl/specifiers.c \
	src/decl/declarators.c \
	src/decl/indirections.c \
	src/decl/const_expr.c \
	src/stmt/tree.c \
	src/stmt/literals.c \
	src/stmt/stmt.c \
	src/stmt/expr/expr.c \
	src/stmt/expr/arithm.c \
	src/stmt/expr/bitwise.c \
	src/stmt/expr/logic.c \
	src/stmt/expr/postfix.c \
	src/stmt/expr/prefix.c \
	src/stmt/expr/primary.c 

C_OBJECT_LIST = 
C_OBJECT_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCE_LIST:.c=.o)))

vpath %.c $(sort $(dir $(C_SOURCE_LIST)))

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

clean:
	rm -rf build

$(BUILD_DIR)/$(PROGRAM) : $(C_OBJECT_LIST) makefile | $(BUILD_DIR)
	g++ -o $(@) $(C_OBJECT_LIST)

$(BUILD_DIR)/%.o : %.c makefile | $(BUILD_DIR)
	gcc -c -o $(@) $(<) $(FLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)