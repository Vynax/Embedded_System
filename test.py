# shopping_list_diff.py
from pprint import pprint
import difflib
import sys

text1 = open("my_shopping_list.txt").readlines()
text2 = open("friends_shopping_list.txt").readlines()

file1 = open("my_shopping_list.txt").read()
file2 = open("friends_shopping_list.txt").read()

delta = difflib.context_diff(
    text1, text2, "my_shopping_list.txt", "friends_shopping_list.txt")
sys.stdout.writelines(delta)

d = difflib.Differ()
alpha = difflib.unified_diff(
    text1, text2, "my_shopping_list.txt", "friends_shopping_list.txt")
print("")
#alpha = list(d.compare(file1,file2))
sys.stdout.writelines(alpha)

m = difflib.SequenceMatcher(None, file1, file2)
print("")
print(m.ratio())

m = difflib.SequenceMatcher(lambda x: x == " ", file1, file2)
print("")
print(m.ratio())
