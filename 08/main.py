
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

def decode_image(image):
    result =[]
    result_string = ""
    for i in range(height):
        row = []
        for j in range(width):
            for layer in image:
                if(layer[i][j] != 2):
                    row.append(layer[i][j])
                    result_string += str(layer[i][j])
                    break
        result.append(row)
    print(result_string)
    print(len(result_string))
    return result

def print_result(result):
    for row in result:
        line = ""
        for num in row:
            if(num == 0):
                line += 'O'
            else:
                line += '.'
        print(line)

def main():
    file = open('input.txt')
    position = 0
    input = file.read()
    image = []

    print('Length : ', len(input))
    print('# Layers: ', int(len(input)/ ( width * height)))
    for i in range(int(len(input)/ ( width * height))):
        file.seek(i * ( width * height))
        image.append(read_layer(file, position))

    print(image)
    layer = find_layer_fewest_0(image)

    print('fewest: ', layer)

    print('Num 0s: ', find_num_of_x(layer, 0))
    print('Num 1s: ', find_num_of_x(layer, 1))
    print('Num 2s: ', find_num_of_x(layer, 2))
    print('Output: ', find_num_of_x(layer, 1) * find_num_of_x(layer, 2))


    print_result(decode_image(image))

main()
