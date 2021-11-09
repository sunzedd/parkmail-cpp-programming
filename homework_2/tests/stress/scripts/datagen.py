import sys
import random
import string
import math

PART_OF_DIGRAPHS_IN_TEXT = 0.2

def generate_random_string(size: int):
    letters = string.ascii_letters
    rs = ''.join(random.choice(letters) for i in range(size))
    return rs

def pick_mood_digraphs_cout(text_size: int, mood: int):
    digraphs_count = math.floor(text_size * PART_OF_DIGRAPHS_IN_TEXT)

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

def generate_text_with_digraphs(mood: int, filesize: int):
    text = generate_random_string(filesize)
    positive_count, negative_count = pick_mood_digraphs_cout(filesize, mood)
    text = add_mood_digraphs_randomly(text, positive_count, negative_count)
    return text

def print_usage():
    print("usage:")
    print("\tdatagen.py <mood> <filesize in mb> <filename>")
    print("\tparameter mood: [negative | neutral | positive]\n")

def write_generated_text_into_file(text: str, filename: str, filesize_mbytes: int):
    with open(filename, "w") as f:
        f.write(text)
        print("File succesfully generated")

if __name__ == "__main__":
    if len(sys.argv) == 4:
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

        filesize_mbytes = int(sys.argv[2])
        filesize_bytes = filesize_mbytes * 1024
        filename = sys.argv[3]

        print("Generating file: " + filename + "\tSize: " + str(filesize_bytes // 1024) + " Mb")
                
        if filesize_mbytes <= 100:
            text = generate_text_with_digraphs(mood, filesize_bytes)
        else:
            text = generate_text_with_digraphs(mood, 100 * 1024)
            text_scale_factor = filesize_mbytes // 100
            text = "" + text * text_scale_factor
            
        write_generated_text_into_file(text, filename, filesize_mbytes)
        print()
    else:
        print_usage()
        exit()