from numpy import *
import json


# 加载数据，分割标签和文本
def load_message():
    content = []
    label = []
    lines =[]

    with open('Data/labeled.txt') as fr:
        for i in range(10000):
            line = fr.readline()
            lines.append(line)
        num = len(lines)
        for i in range(num):
            message = lines[i].split('\t')
            label.append(message[0])
            content.append(message[1])
    return num, content, label


# 保存
def data_storage(content, label):
    with open('Data/train_content.json', 'w') as f:
        json.dump(content, f)
    with open('Data/train_label.json', 'w') as f:
        json.dump(label, f)


if '__main__' == __name__:
    num, content, label = load_message()
    data_storage(content, label)
