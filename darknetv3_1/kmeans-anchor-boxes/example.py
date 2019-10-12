# https://blog.csdn.net/zuliang001/article/details/90551798#examplepyload_dataset_18
# https://github.com/lars76/kmeans-anchor-boxes
import glob
import xml.etree.ElementTree as ET

import numpy as np

from kmeans import kmeans, avg_iou

# ANNOTATIONS_PATH = "Annotations"
ANNOTATIONS_PATH = "/home/xx/cv_xx/darknetv3_2/VOCdevkit/VOC2007/Annotations"
CLUSTERS = 6

def load_dataset(path):
	dataset = []
	for xml_file in glob.glob("{}/*xml".format(path)):
		tree = ET.parse(xml_file)

		height = int(tree.findtext("./size/height"))
		width = int(tree.findtext("./size/width"))

		for obj in tree.iter("object"):
			xmin = int(obj.findtext("bndbox/xmin")) 
			ymin = int(obj.findtext("bndbox/ymin")) 
			xmax = int(obj.findtext("bndbox/xmax")) 
			ymax = int(obj.findtext("bndbox/ymax")) 

			dataset.append([xmax - xmin, ymax - ymin])

	return np.array(dataset)


data = load_dataset(ANNOTATIONS_PATH)
print(data)
out = kmeans(data, k=CLUSTERS)
print("Accuracy: {:.2f}%".format(avg_iou(data, out) * 100))
print("Boxes:\n {}".format(out))

ratios = np.around(out[:, 0] / out[:, 1], decimals=2).tolist() # box的长宽比
print("Ratios:\n {}".format(sorted(ratios)))
