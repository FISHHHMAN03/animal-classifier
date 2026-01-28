from binary_forest_swimmer_classifier import Features,classify


f = Features()
f.height = 183.0
f.weight = 90.0
f.arm_length = 195.0

print(classify(f))