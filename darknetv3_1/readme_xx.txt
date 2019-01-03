


make clean


训练
./darknet detector train cfg/voc_xx.data cfg/yolov3-voc_xx.cfg   
./darknet detector train cfg/voc_xx.data cfg/yolov3-voc_xx.cfg   darknet53.conv.74  
./darknet detector train cfg/voc_xx.data cfg/yolov3-voc_xx.cfg   darknet53.conv.74  -gpus 0,1

./darknet detector train cfg/voc_xx.data cfg/yolov3-tiny_xx.cfg   darknet53.conv.74  -gpus 0,1

测试
./darknet detector test cfg/voc_xx.data cfg/yolov3-voc_xx.cfg backup/yolov3-voc_xx_300.weights   3.jpg 


./darknet detector demo cfg/voc_xx.data cfg/yolov3-voc_xx.cfg backup/yolov3-voc_xx_900.weights live.avi 

./darknet detector demo cfg/voc_xx.data cfg/yolov3-voc_xx.cfg backup/yolov3-voc_xx_400.weights  /home/xx/video_xx/1.avi 


./darknet detector demo cfg/voc_xx.data cfg/yolov3-tiny_xx.cfg backup/yolov3-voc_xx_400.weights  /home/xx/video_xx/1.avi 


