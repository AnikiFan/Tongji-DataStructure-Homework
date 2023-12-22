import os

# 待测试程序的路径
待测试程序路径 = "C:\\Users\\15800\\Desktop\\homework_for_data_structure\\查找\\a.exe"

# 生成测试文件和正确答案的程序的路径
生成测试程序路径 = "C:\\Users\\15800\\Desktop\\homework_for_data_structure\\查找\\p90_data.exe"

# 测试的轮数
测试轮数 = 1000000000
sun = 0
# 循环测试
for i in range(1, 测试轮数 + 1):
    # 生成测试文件和正确答案
    os.system(生成测试程序路径)

    # 获取当前测试文件和正确答案的文件名
    测试文件 = f"input{i%2+1}.txt"
    正确答案文件 = f"output{i%2+1}.txt"

    # 运行待测试程序，将测试文件输入，获取输出结果
    命令 = f"{待测试程序路径} < {测试文件} > test.txt"
    os.system(命令)

    # 比较待测试程序的输出与正确答案
    比较命令 = f"fc output{i%2+1}.txt test.txt"
    差异 = os.system(比较命令)

    if 差异 != 0:
        sun+=1
        print(f"第 {i} 轮测试结果不一致！")
        # 保存不一致的测试文件和正确答案
        os.rename(测试文件, f"failed_input_{i}.txt")
        os.rename(正确答案文件, f"failed_expected_output_{i}.txt")
        # 删除临时文件

print("测试结束")
print(sun)