import math

result = r""

for x in range(-10, 10, 2):
    for y in range(-10, 10, 2):
        result += "glm::vec2{" + f'{x/10}f' + ',' + f'{y/10}f' + "},\n"

print(result)
# print(len(list(range(-10, 10, 2)))**2)
