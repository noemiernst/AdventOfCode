
width = 25
height = 6

def read_layer(file, position):
    layer = []
    for i in range(height):
        row = []
        for j in range(width):
            row.append(int(file.read(1)))
            position += 1
        layer.append(row)
    return layer

def find_num_of_x(layer, x):
    count = 0
    for row in layer:
        for entry in row:
            if(entry == x):
                count += 1
    return count

def find_layer_fewest_0(image):
    fewest0 = width * height #maximum
    layer_fewest0 = image[0]

    for layer in image:
        num = find_num_of_x(layer, 0)
        if(num < fewest0):
            fewest0 = num
            layer_fewest0 = layer
    return layer_fewest0

def main():
    file = open('input.txt')
    position = 0
    input = file.read()
    image = []

    print('Length : ', len(input))
    print('# Layers: ', int(len(input)/ ( 25 * 6)))
    for i in range(int(len(input)/ ( 25 * 6))):
        file.seek(i * 25 * 6)
        image.append(read_layer(file, position))

    layer = find_layer_fewest_0(image)

    print('fewest: ', layer)

    print('Num 0s: ', find_num_of_x(layer, 0))
    print('Num 1s: ', find_num_of_x(layer, 1))
    print('Num 2s: ', find_num_of_x(layer, 2))
    print('Output: ', find_num_of_x(layer, 1) * find_num_of_x(layer, 2))


main()
