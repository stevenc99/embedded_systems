LOCAL_CPP_SRCS := $(wildcard libs/*/*.cpp) $(wildcard src/*/*.cpp)
CPPFLAGS += -Ilibs/LiquidCrystal_I2C/ -I/usr/share/arduino/libraries/EEPROM/
include /usr/share/arduino/Arduino.mk
