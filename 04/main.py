range_bottom = 357253
range_top = 892942

def check_password(password):
    one_pair = False
    increase = True
    digit_count = {'0': 0, '1': 0, '2': 0, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0, '8': 0, '9': 0}
    if(len(str(password)) == 6):
        if(password >= range_bottom & password <= range_top):
            prev = str(password)[0]
            digit_count[prev] += 1
            for c in str(password)[1:6]:
                digit_count[c] += 1
                if(c < prev):
                    increase = False
                prev = c
    for value in digit_count.values():
        if(value == 2):
            one_pair = True
    return (increase & one_pair)

def main():
    #do something
    print(check_password(111111))
    print(check_password(223454))
    print(check_password(123788))
    print(check_password(112233))
    print(check_password(103344))
    print(check_password(111122))


    count = 0
    for password in range(range_bottom, range_top + 1):
        valid = check_password(password)
        if(valid):
            count += 1

    print(count)

main()
