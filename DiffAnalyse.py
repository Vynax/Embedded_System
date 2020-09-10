import difflib
import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()
file_path = filedialog.askopenfilenames()

fileX = ["", ""]
fileY = ["", ""]

fileX[0] = open("my_shopping_list.txt").read()
fileX[1] = open("friends_shopping_list.txt").read()

for x in range(2):
    fileY[x] = fileX[x].replace(" ", "").replace("\n", "")

m = difflib.SequenceMatcher( None, fileY[0], fileY[1] )
print("")
print(m.ratio())