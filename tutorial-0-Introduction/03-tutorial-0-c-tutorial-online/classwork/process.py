import matplotlib.pyplot as plt

img = plt.imread('../images/cw4_pic.png')

print("{")
for i in range(0, 15):
    print("{", end="")
    for j in range(0, 15):
        print("{", end="")
        print("{: <3}, {: <3}, {: <3}".format(int(img[i][j][0]*255), int(img[i][j][1]*255), int(img[i][j][2]*255)), end="")
        print("}", end="")
        if(j!=14):
            print(", ", end="")
    print("}", end="")
    if(i!=14):
        print(",")
print("}")

plt.imshow(img)
