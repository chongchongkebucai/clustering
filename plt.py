import matplotlib.pyplot as plt

indexs = []
coords_x = []
coords_y = []

# read date from file
file_name = "/home/congxiang/work/clustering/build/itdp_clusters.dot"
with open(file_name) as file_obj:
    lines = file_obj.readlines()

for line in lines:
    if line == '\n':
        continue
    coord_str = line.strip().split(" ")
    
    index = int(coord_str[0])
    coord_x = int(coord_str[1])
    coord_y = int(coord_str[2])

    indexs.append(index)
    coords_x.append(coord_x)
    coords_y.append(coord_y)

# set color table
colors = []
color_table = ["#000000", "#6495ED", "#8470FF", "#0000CD", "#00BFFF", "#00FF7F", "#7CFC00", "#32CD32", "#FFFF00", 
          "#B8860B", "#BC8F8F", "#B22222", "#FF0000", "#FF69B4", "#FF1493", "#9400D3", "#0000FF", "#5CACEE"]
color_table_len = len(color_table)
for index in indexs:
    color = color_table[index % color_table_len]
    colors.append(color)

# print point into picture
plt.figure(dpi=3000)
plt.title("clustering", fontsize=14)
plt.xlabel("x", fontsize=14)
plt.ylabel("y", fontsize=14)
plt.tick_params(axis="both", which="major", labelsize=7)

plt.scatter(coords_x, coords_y, c=colors, edgecolor="none", s=0.2)
plt.savefig("coord.png")

