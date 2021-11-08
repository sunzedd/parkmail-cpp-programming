import sys
import random
import string
import math

PARTY_OF_DIGRAPHS_IN_TEXT = 0.2

def generate_random_string(size: int):
    letters = string.ascii_letters
    rs = ''.join(random.choice(letters) for i in range(size))
    return rs

def pick_mood_digraphs_cout(text_size: int, mood: int):
    digraphs_count = math.floor(text_size * PARTY_OF_DIGRAPHS_IN_TEXT)

    positive_count = 0
    negative_count = 0

    if mood == 0:
        positive_count = math.floor(digraphs_count * 0.5)
        negative_count = math.floor(digraphs_count * 0.5)
    elif mood == 1:
        positive_count = math.floor(digraphs_count * 0.7)
        negative_count = math.floor(digraphs_count * 0.3)
    elif mood == -1:
        positive_count = math.floor(digraphs_count * 0.3)
        negative_count = math.floor(digraphs_count * 0.7)

    return (positive_count, negative_count)


def add_mood_digraphs_randomly(s: str, positive_count: int, negative_count: int):
    max_pos = len(s) - 2
    min_pos = 0

    modified = []

    chars = list(s)

    positive_added_count = 0
    while positive_added_count < positive_count:
        pos = random.choice(range(min_pos, max_pos))
        if pos in modified or pos+1 in modified or pos-1 in modified:
            continue
        else:
            chars[pos] = ':'
            chars[pos+1] = ')'
            modified.append(pos)
            positive_added_count += 1

    negative_added_count = 0
    while negative_added_count < negative_count:
        pos = random.choice(range(min_pos, max_pos))
        if pos in modified or pos+1 in modified or pos-1 in modified:
            continue
        else:
            chars[pos] = ':'
            chars[pos+1] = '('
            modified.append(pos)
            negative_added_count += 1

    return "".join(chars)

def generate_text_file(mood: int, filesize: int, filename: str):
    text = generate_random_string(filesize)
    positive_count, negative_count = pick_mood_digraphs_cout(filesize, mood)
    text = add_mood_digraphs_randomly(text, positive_count, negative_count)
    if len(text) > 0:
        output_file = open(filename, "w")
        output_file.write(text)
        output_file.close()

def print_usage():
    print("usage:")
    print("\tdatagen.py <mood> <filesize in mb> <filename>")
    print("\tparameter mood: [negative | neutral | positive]\n")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print_usage()
        exit()

    if sys.argv[1] == 'negative':
        mood = -1
    elif sys.argv[1] == 'neutral':
        mood = 0
    elif sys.argv[1] == 'positive':
        mood = 1
    else:
        print('invalid mood parameter passed')
        print_usage()
        exit()

    generate_text_file(mood, int(sys.argv[2]) * 1024, sys.argv[3])
    print('generated file ' + sys.argv[3] + " size: " + str(sys.argv[2]) + " mb")
