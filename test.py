# shopping_list_diff.py
from pprint import pprint
import difflib
import sys

text1 = open("my_shopping_list.txt").readlines()
text2 = open("friends_shopping_list.txt").readlines()
fileX = ["", ""]
fileY = ["", ""]
fileX[0] = open("my_shopping_list.txt").read()
fileX[1] = open("friends_shopping_list.txt").read()

delta = difflib.context_diff(
    text1, text2, "my_shopping_list.txt", "friends_shopping_list.txt")
sys.stdout.writelines(delta)

d = difflib.Differ()
alpha = difflib.unified_diff(
    text1, text2, "my_shopping_list.txt", "friends_shopping_list.txt")
print("")
#alpha = list(d.compare(file1,file2))
sys.stdout.writelines(alpha)

k = difflib.SequenceMatcher(None, fileX[0], fileX[1])
print("")
print(k.ratio())

for x in range(2):
    fileY[x] = fileX[x].replace(" ", "").replace("\n", "")
    #fileY[x] = fileY[x].replace("\n", "")


#fileY[1] = fileX[1].replace(" ", "")
m = difflib.SequenceMatcher(lambda x: x ==" ", fileY[0], fileY[1])
print("")
print(m.ratio())
