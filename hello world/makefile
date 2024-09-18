# 指定编译器  
CXX=g++  
  
# 指定编译选项，-g 添加调试信息  
CXXFLAGS=-g  
  
# 目标文件  
TARGET=hello  
  
# 构建目标  
all: $(TARGET)  
  
# 规则：如何从 hello.cpp 生成可执行文件 hello  
$(TARGET): hello.cpp  
    $(CXX) $(CXXFLAGS) hello.cpp -o $(TARGET)  
  
# 清理编译生成的文件  
clean:  
    rm -f $(TARGET)  