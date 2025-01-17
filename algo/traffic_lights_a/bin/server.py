import os
import sys
import random
import signal
from threading import Timer, Event

cases = [os.listdir(f"saved/case{i}/") for i in range(1, 11)]

answered = Event()

def handler(signum, frame):
    if not answered.is_set():
        print("TLE. Good night.")
        sys.exit(0)

signal.signal(signal.SIGALRM, handler)
signal.alarm(120)

print("Welcome! Good luck :D")
print("You have 120 seconds to solve all ten cases")

for i in range(10):
    case = open(f"saved/case{i+1}/{random.choice(cases[i])}").read()
    answered.clear()
    send, expect = case.split("\n\n")
    print(f"Here's case {i+1}!")
    print(send)
    s = input() + "\n"
    if s == expect:
        print("Congrats, that's right!")
        answered.set()
    else:
        print("No, you're wrong, get out!")
        sys.exit(0)

print("Wow, you really know your flow!")
print("Take this flag and get the heck out.")
print(open("flag.txt").read())
