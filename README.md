# deep-learning-strong-part
Deep Learning Strong Parts for Pedestrian Detection


rectangle_one _image:读取ground truth txt和 ldcf .txt 根据IOU，判断negative ,positive, not detected，并把相应的LDCF的四个信息输出， not detected情况下输出ground truth 信息.
 得到ground truth 1.1 对应 proposal 1.1的 iou，得到所有iou 的如果大于0.5则为positive，小于0.5，则为negative，如果全都是neGative，则为no detect

***compute_files_iou ：positive,height>50 positive,negative,height>50 negative, ground truth 안에서 사람이 있어요,근데 LDCF 인식 못해서..이런 것 NOTdetect 설정한다.
test, train04 모두 file 결과 나와다. check 수량
可具体分为几类：positive_large, negative_large , nodetected,实际上取得pos,neg进行训练的是 positive_large， nodetected。

change_Image_size：正规化图片为64*128大小。。。。手动法
先读取图片，再读取相应（ground truth）的txt，得到txt中坐标和长宽，进行画矩形框，把矩形框里的图片抠出来，再重新定义抠出来的矩形框的大小，统一变成64*128->保存该图片到新的文件夹里

Normalization: 自动化处理图片，变为64*128大小
先读取图片，再读取相应（ground truth）的txt，得到txt中坐标和长宽，进行画矩形框，把矩形框里的图片抠出来，再重新定义抠出来的矩形框的大小，统一变成64*128->保存该图片到新的文件夹里

part_pool：一张64*128 大小的图片的45种 part pool，最终选已知的6种
negative_positive_ratio：positive 16个negative 48个，共64个一起，循环放到一起
