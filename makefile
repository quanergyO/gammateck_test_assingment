CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include $(shell pkg-config --cflags Qt5Widgets Qt5Network)
LDFLAGS = $(shell pkg-config --libs Qt5Widgets Qt5Network)

SRC_DIR = src
INCLUDE_DIR = include
UI_DIR = ui
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
UI_FILES = $(wildcard $(UI_DIR)/*.ui)

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BUILD_DIR)/myapp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/moc_%.cpp: $(INCLUDE_DIR)/%.h
	@mkdir -p $(BUILD_DIR)
	moc $< -o $@

$(INCLUDE_DIR)/ui_%.h: $(UI_DIR)/%.ui
	@mkdir -p $(INCLUDE_DIR)
	uic $< -o $@

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all clean rebuild
