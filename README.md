# MoJoCo仪表盘

##  **项目信息** 
- 学号：232011144

- 姓名：从德俊

- 班级：计科2304班

- 完成日期：2025年12月26日

##  **项目概述** 
本项目基于 **MuJoCo物理引擎**和**MPC（模型预测控制技术）**，实现了一个汽车仪表盘可视化系统。系统通过读取仿真中的车辆物理数据（速度、位置、转速等），使用OpenGL实时渲染2D仪表盘覆盖层，包括速度表、转速表、油量、温度显示等功能。该项目综合运用了C++编程、物理仿真、实时渲染等技术，展示了物理引擎与图形界面的集成应用。

##  **环境要求** 
-  **操作系统：** Ubuntu 22.04 LTS（推荐）

-  **编译器：** gcc 11.3.0+

-  **构建工具：** CMake 3.22.1+

-  **显卡：** 支持OpenGL 3.3+

-  **内存：** 8GB+（推荐16GB）

-  **硬盘空间：** 至少10GB可用空间

##  **依赖库** 
- MuJoCo物理引擎

- GLFW（窗口管理）

- GLEW（OpenGL扩展）

- Eigen3（线性代数）

- OpenBLAS（数学计算）

##  **编译和运行** 
### 1. 安装依赖（Ubuntu）
bash
sudo apt update
sudo apt install -y build-essential cmake git libgl1-mesa-dev libglfw3-dev libglew-dev libeigen3-dev libopenblas-dev
### 2. 获取源码
bash
mkdir -p ~/mujoco_projects
cd ~/mujoco_projects
git clone https://github.com/google-deepmind/mujoco_mpc.git
cd mujoco_mpc
### 3. 集成仪表盘代码
将本项目的代码文件复制到相应位置：

bash
 假设本项目的code目录在~/MuJoCo_Dashboard/code/

cp ~/MuJoCo_Dashboard/code/dashboard_data.h mjpc/

cp ~/MuJoCo_Dashboard/code/dashboard_render.h mjpc/

cp ~/MuJoCo_Dashboard/code/dashboard_render.cc mjpc/

cp ~/MuJoCo_Dashboard/scenes/car_simple.xml mjpc/tasks/car/

### 4. 修改主程序
根据第五部分的指导，修改mjpc/app.cc文件，添加：

- #include "dashboard_data.h"

- #include "dashboard_render.h"

- 仪表盘数据提取和渲染的调用

### 5. 编译项目

mkdir -p build

cd build

cmake .. -DCMAKE_BUILD_TYPE=Release

cmake --build . -j4


### 6. 运行程序

./bin/mjpc --mjcf=../mjpc/tasks/car/car_simple.xml

##  **功能说明** 
###  **已实现功能** 
 - **环境配置：** 成功编译并运行MuJoCo MPC

 - **场景创建：** 创建自定义车辆场景（MJCF格式）

 - **数据获取：** 实时获取车辆速度、位置、转速等数据

 - **速度表：** 圆形仪表盘，范围0-200 km/h

 - **转速表：** 圆形仪表盘，范围0-8000 RPM，含红区提示

 - **数字显示：** 油量、温度进度条显示

 - **实时更新：** 数据与界面动态绑定

###  **进阶功能（可选）** 
-  **UI美化：** 纹理贴图、平滑动画

-  **小地图：** 显示车辆位置与轨迹

-  **碰撞检测：** 接近障碍物时警告提示

-  **档位显示：** 自动/手动档位指示

-  **驾驶模式：** 运动/舒适/经济模式切换

##  **文件说明** 
###  **核心代码文件** 
- dashboard_data.h：数据提取模块头文件

--- 定义DashboardData数据结构

--- 实现DashboardDataExtractor类

- dashboard_render.h：仪表盘渲染模块头文件

--- 定义DashboardRenderer类

--- 包含速度表、转速表、数字显示的渲染函数

- dashboard_render.cc：渲染模块实现

--- OpenGL 2D渲染的具体实现

###  **场景文件** 
* car_simple.xml：简单车辆场景

--- 包含车身、四轮、自由关节

--- 定义执行器和传感器

###  **配置文件** 
* CMakeLists.txt：CMake构建配置（已修改，添加仪表盘模块）

###  **文档文件** 
* README.md：项目说明文档（本文件）

* report.md：详细作业报告

* screenshots/：项目运行截图

* videos/demo.mp4：功能演示视频

##  **项目结构** 

MuJoCo_Dashboard/

├── code/

│   ├── dashboard_data.h

│   ├── dashboard_render.h

│   └── dashboard_render.cc

├── scenes/

│   ├── car_simple.xml

│   └── car_advanced.xml

├── docs/

│   ├── report.md

│   ├── screenshots/

│   └── demo.mp4

└── README.md

##  **使用说明** 

###  **基本操作** 
1. **启动程序：** 运行上述编译命令

2. **车辆控制：** 

* W/S：前进/后退

* A/D：左转/右转

* 鼠标：旋转视角

3. **仪表盘观察：** 观察左下角的速度表、转速表和右下角的数字显示

##  **数据说明** 
* 速度：基于车辆X、Y方向速度计算的总速度

* 转速：模拟值，与速度成正比（速度 × 40）

* 油量：模拟值，随时间递减

* 温度：模拟值，与转速相关（60°C + 转速比例 × 60°C）

##已知问题
1. **指针跳动：** 高速时指针可能有轻微跳动（可通过插值平滑优化）

2. **OpenGL兼容性：** 某些集成显卡可能支持不完全

3. **内存泄漏：** 长时间运行可能有轻微内存增长（需进一步优化资源管理）

##  **调试建议** 
###  **编译问题** 

 如果编译失败，清理后重新编译

cd ~/mujoco_projects/mujoco_mpc

rm -rf build

mkdir build && cd build

cmake .. -DCMAKE_BUILD_TYPE=Release

cmake --build . -j4

###  **运行时问题** 

 如果找不到库文件

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/mujoco_projects/mujoco_mpc/build/lib

###  **仪表盘不显示** 
1.检查app.cc中是否正确调用了渲染函数

2.检查OpenGL错误：glGetError()

3.确认数据提取函数被正确调用

###  **性能优化** 
* 渲染优化：预计算圆形顶点，使用VBO（Vertex Buffer Objects）

* 数据缓存：缓存不变的ID和几何数据

* 更新频率：限制数据更新频率，避免不必要的计算

###  **扩展开发** 
####  **添加新功能** 
1. **修改数据提取：** 在DashboardDataExtractor::update()中添加新数据

2. **扩展渲染：** 在DashboardRenderer中添加新的绘制函数

3. **更新界面：** 在render()函数中调用新的绘制函数

####  **集成第三方库** 
* ImGui：用于更复杂的UI界面

* FreeType：用于高质量字体渲染

* GLM：用于数学计算

## **参考资料** 
1.MuJoCo官方文档

2.MuJoCo MPC GitHub

3.OpenGL教程

4.MJCF格式参考

5.C++课程讲义和相关教程




