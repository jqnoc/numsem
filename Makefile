SRCS := main.cpp NumericalSemigroup.cpp
SRCDIR := src
BUILD := build
BIN := bin
EXE := numsem
OBJS := $(addprefix $(BUILD)/,$(SRCS:.cpp=.o))

CPP := g++
CFLAGS := -O3 -std=c++11
LFLAGS := -std=c++11

.PHONY: all clean

all: $(EXE)

$(BUILD):
	mkdir -p $@

$(BIN):
	mkdir -p $@

numsem: $(OBJS) |  $(BIN)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CPP) -o $(BIN)/$(EXE) $(OBJS) $(LFLAGS)
	@echo 'Finished building target: $@'
	@echo ' '

$(BUILD)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h |  $(BUILD)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD)/main.o: $(SRCDIR)/main.cpp |  $(BUILD)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean:
	rm -rf $(BUILD)/*
