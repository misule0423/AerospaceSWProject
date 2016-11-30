# AerospaceSWProject

프로젝트 내용
Pixhawk, ROS를 활용한 장애물 회피 드론 

프로젝트 설명
노트북에 연결된 아두이노 프로 미니에서 IR센서를 통해서 거리값을 읽고 이를 PID제어를 통해 적절한 roll, pitch 값을 rosserial 통신을 통해 ros로 전달한다.
그리고 ros에서 받은 roll, pitch 값을 topic을 통해서 mavros 통신을 통해 pixhawk에 전달한다. 전달 받은 topic을 통해 픽스호크가 OFFBOARD mode일 때 장애물이 있을때 반대로 비행하도록 제어한다.

ros intall
http://wiki.ros.org/

rosserial_arduino install
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup#Introduction

mavros install
http://dev.px4.io/ros-mavros-installation.html
