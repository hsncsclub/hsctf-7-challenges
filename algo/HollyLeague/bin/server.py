import os
import sys
import random
import signal

cases = [os.listdir(f"saved/case{i}/") for i in range(1, 16)]

def handler(signum, frame):
    print("TLE. Good night.")
    sys.exit(0)

signal.signal(signal.SIGALRM, handler)
signal.alarm(120)

for i in range(15):
    case = open(f"saved/case{i+1}/{random.choice(cases[i])}").read()
    send, expect = case.split("\n\n")
    print(f"Here's case {i+1}!")
    print(send)
    s = input() + "\n"
    if s == expect:
        print("Congrats, that's right!")
    else:
        print("No, you're wrong, get out!")
        sys.exit(0)

print("Wow, you really know your matchings!")
print("Take this flag and get the heck out.")
print(open("flag.txt").read())
