CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = serializer
OBJS = main.o Serializer.o Deserializer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) inlet.in outlet.out

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
