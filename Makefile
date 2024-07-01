# Source directories separated by space
# Example ./ src1/ src2/
SRCDIR   =  src/ src/network/ src/packet/ src/packet/handler/ src/packet/packets/ src/util/ src/helpers/ src/headers/ \
			src/minecraft/ src/minecraft/entity/ src/minecraft/entity/player/ src/minecraft/logic/ src/minecraft/world/ \
			src/minecraft/world/worldgen/ src/minecraft/server/ src/minecraft/logic/events/
OBJDIR   = target/objects/
# Include directories separated by space
INCDIR   = include/
BINDIR   = target/
TARGET   = main
# Compiler
CXX      = g++

# Retrive list of the source files
SRC      = $(wildcard $(addsuffix *.cpp,$(SRCDIR)))
# Generate list of the object files
OBJ      = $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))
VPATH    = $(SRCDIR)

# Compilation flags
CXXFLAGS = -std=c++23 -O1 -fsanitize=address -g

$(TARGET) : $(OBJ)
	@echo Linking...
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)$@ $(OBJ)

$(OBJDIR)%.o : %.cpp
	@echo Compiling $< in $@...
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCDIR)) -c -o $@ $<

clean:
	rm ./target/objects/ -rf
	rm ./logs/ -rf
	mkdir logs
	touch server_prefs.txt
settingstest:
	g++ -std=c++23 src/util/miscutil.cpp test/settingsmain.cpp ./src/helpers/server_settings.cpp -o target/settingstest

loggertest:
	g++ -std=c++23 test/loggermain.cpp ./src/helpers/loggerhandler.cpp ./src/helpers/logger.cpp -o target/loggertest

distancetest:
	g++ -std=c++23 test/distancecalc.cpp ./src/minecraft/world/vector.cpp -o target/distancetest

ticktest:
	g++ -std=c++23 test/ticks.cpp -o target/ticktest