LOCAL_CPP_SRCS := $(wildcard libs/*/*.cpp) $(wildcard src/*/*.cpp)
CPPFLAGS += -Ilibs/LiquidCrystal_I2C/
include /usr/share/arduino/Arduino.mk
