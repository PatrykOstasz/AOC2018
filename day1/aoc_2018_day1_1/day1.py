def find_duplicates(frequencies):
    sum = 0
    duplicates = set()
    while True:
        for x in frequencies:
            sum += x
            if sum not in duplicates:
                duplicates.add(sum)
            else:
                return sum

def solution(filename):
    frequencies = [int(line) for line in open(filename)]
    freq_sum = sum(frequencies)
    duplicate = find_duplicates(frequencies)
    return freq_sum, duplicate

print(solution("input.txt"))
