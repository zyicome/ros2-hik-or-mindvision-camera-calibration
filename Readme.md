该功能包用于一键标定相机内参，适用于hik相机以及mindvision相机。
本功能包采用ros2标定程序以及hik和mindvision的ros2启动程序，感谢所有为这些功能包作出贡献的人。

使用方法：
驱动安装：
	mindvision相机驱动安装参考MDVISION_driver的readme.pdf，按操作进行安装测试.
	hik相机驱动安装参考HIK_driver的doc/USB.pdf文档
	
hik相机标定：
	ros2 launch hik_camera hik_camera.launch.py  //hik相机启动
	ros2 run camera_calibration cameracalibrator --size 7x9 --square 0.02 --ros-args -r image:=/image_raw -p camera:=/hik           // 开启标定程序 
	                                         //参数说明: --size 每次标定取的角点数，理论上越多标定越准确，但是棋盘图不清晰之类原因会导致无法一次识别到太多角点，根据实际调整即可
	                                         -- square 每个棋格的边长大小（m）
	                                        
mindvision相机标定:
        ros2 launch mindvision_camera mv_launch.py //mindvision相机启动
        ros2 run camera_calibration cameracalibrator --size 7x9 --square 0.02 --ros-args -r image:=/image_raw -p camera:=/my_camera
        
自己用可视化工具进行亮度调节(foxglove或rqt)，亮度过低标定效果不好.
