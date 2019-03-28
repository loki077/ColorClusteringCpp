all:
	g++ Main.cpp List2Dynamic.cpp List1Dynamic.cpp ColorClustering.cpp -o output

output: Main.o List1Dynamic.o List2Dynamic.o ColorClustering.o
	g++ Main.o List1Dynamic.o List2Dynamic.o ColorClustering.o -o bin/output

Main.o: Main.cpp
	g++ -c Main.cpp

List1Dynamic.o: src/List1Dynamic.cpp src/List1Dynamic.cpp
	g++ -c src/List1Dynamic.cpp


List2Dynamic.o: src/List2Dynamic.cpp src/List2Dynamic.cpp
	g++ -c src/List2Dynamic.cpp


ColorClustering.o: src/ColorClustering.cpp src/ColorClustering.cpp
	g++ -c include/ColorClustering.cpp

clean:
	rm *.o bin/output

# TARGET_EXEC ?= a.out

# BUILD_DIR ?= ./build
# SRC_DIRS ?= ./src
# INC ?= ./include

# SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(INC) -name *.cpp)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# # c++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	$(MKDIR_P) $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


# .PHONY: clean

# clean:
# 	$(RM) -r $(BUILD_DIR)

# -include $(DEPS)

# MKDIR_P ?= mkdir -p
