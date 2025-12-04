#说明：本程序是魔兽世界系列作业的辅助比对程序，类似于文本比对软件。
#使用方法是把你程序输出的答案和标准答案分别粘贴到text1与text2中，即可看到有哪些差别（顺序差别也会报）。其中从第7个开始，文本的输出长度就超出了终端显示范围。
#此时应该使用如下命令运行程序：g++ yourProgrammName.cpp -o yourProgrammName && ./yourProgrammName > out.txt把输出写到out.txt中。之后再粘贴到本程序中。
#当然你也可以改造本程序，使text1、text2可以从文件中直接读取。
#注意：一般跑通第1、3、4、5、7、8、9个test case后就能AC（这几个具有代表性）。
#如果你遇到了segmentation fault，请利用clab.pku.edu.cn上提供的Linux虚拟机进行gdb调试，你可以很清楚地看到哪里导致了segmentation fault。
import os
import difflib
import re
def normalize_spaces(text):
    return "\n".join([" ".join(re.split(r'\s+', line.strip())) for line in text.splitlines()])

#初始化两段文字,1=my_output,2=std_output
text1=''''''

text2=''''''

differ=difflib.Differ()
diff=list(differ.compare(normalize_spaces(text1).splitlines(),normalize_spaces(text2).splitlines()))
diff_lines=[line for line in diff if line.startswith('+ ') or line.startswith('- ')]
print(diff_lines)
