################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Aspect.cpp \
../src/Command.cpp \
../src/DebugDrawer.cpp \
../src/Engine.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp \
../src/GameMgr.cpp \
../src/GfxMgr.cpp \
../src/InputMgr.cpp \
../src/Mgr.cpp \
../src/Physics3D.cpp \
../src/Physics3Dq.cpp \
../src/UnitAI.cpp \
../src/Utils.cpp \
../src/main.cpp 

OBJS += \
./src/Aspect.o \
./src/Command.o \
./src/DebugDrawer.o \
./src/Engine.o \
./src/Entity381.o \
./src/EntityMgr.o \
./src/GameMgr.o \
./src/GfxMgr.o \
./src/InputMgr.o \
./src/Mgr.o \
./src/Physics3D.o \
./src/Physics3Dq.o \
./src/UnitAI.o \
./src/Utils.o \
./src/main.o 

CPP_DEPS += \
./src/Aspect.d \
./src/Command.d \
./src/DebugDrawer.d \
./src/Engine.d \
./src/Entity381.d \
./src/EntityMgr.d \
./src/GameMgr.d \
./src/GfxMgr.d \
./src/InputMgr.d \
./src/Mgr.d \
./src/Physics3D.d \
./src/Physics3Dq.d \
./src/UnitAI.d \
./src/Utils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jsiao/workspace/Caelestion/inc" -I/usr/local/include/OGRE/Overlay -I/usr/include/OIS -I/usr/local/include/OGRE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


