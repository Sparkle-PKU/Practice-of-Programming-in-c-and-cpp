'''TaggedList 表示元素带标签的列表。每个元素都有不同标签，标签是字符串。元素可以用整数做下标访问，也可以用标签做下标访问。请给出该类的实现'''
exit = None
class TaggedList:
    def __init__(self,nums,subjects):
        self.count=0
        self.nums=nums
        self.subjects=subjects
        self.dict1=dict()
        self.dict2=dict()
        while self.count<len(nums):
            self.dict1[self.count]=nums[self.count]
            self.dict2[subjects[self.count]]=self.count
            self.count+=1
    def __str__(self):
        res=[]
        for label in self.subjects:
            idx=self.dict2[label]
            res.append(f"{label}:{self.nums[idx]}")
        return ",".join(res) + ","
    def __len__(self):
        return self.count
    def __contains__(self,item):
        return item in self.nums
    def __getitem__(self,item):#获取a[something]
        if(isinstance(item,int)):
            return self.dict1[item]
        else:
            index=self.dict2[item]
            return self.dict1[index]
    def __setitem__(self,key,value):#设置a[something]=value
        if isinstance(key,int):
            self.nums[key]=value
            self.dict1[key]=value
        elif isinstance(key,str):
            index=self.dict2[key]
            self.nums[index]=value
            self.dict1[index]=value   
 
a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
print(len(a),78 in a, 80 in a) #>>4 False True
print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
a[1] = a['物理'] = 85
print(a) #>>语文:70,数学:85,英语:90,物理:85,