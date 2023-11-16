## 三维CAD建模 2023年秋学期作业程序 
- 定义了半边数据结构
- 可以实现五个基本的欧拉操作
- 使用欧拉操作和平移扫掠构建了一个“八字”B-rep实体模型
- 能力有限，程序无法完成对模型的表面渲染，这里只给出了一个线框显示

### 运行环境：
- 程序运行环境：x86 Ubuntu2204-Desktop
```shell
# 从apt包管理安装 opengl 依赖：glew、glfw、freeglut
sudo apt update
sudo apt install libglew-dev libglfw3-dev freeglut3-dev
# 或手动安装glew、glfw、freeglut
# ......
```

### Usage
```shell
mkdir build
cd build
cmake ..
make
./euler_operator_modeling
```