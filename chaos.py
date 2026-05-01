# A wrapper to make g++ *worse*, because we and society needed this.
import subprocess
import sys
import keyboard
import random

KEY_AMOUNT = 10

# Singleton state obj because I can't be bothered making another python script
class State:
    def __init__(self):
        self.keys_pressed = 0
        self.designated_key = random.choice("abcdefghijklmnopqrstuvwxyz")
    
    def upd_keys_pressed(self):
        self.keys_pressed += 1
    
    def get_keys_pressed(self):
        return self.keys_pressed

    def get_designated_key(self):
        return self.designated_key

state = State()

def on_key_press(event: keyboard.KeyboardEvent):
    if event.event_type == "down" and event.name == state.get_designated_key():
        state.upd_keys_pressed()

command = ["g++"] + sys.argv[1:]
result = subprocess.run(command, text=True, capture_output=True)

if result.returncode == 0:
    print("\033[92mCOMPILATION SUCCESSFUL\033[0m")
    sys.exit()

print("Your spaghetti code has resulted in a \033[1;37mcompilation error!\033[0m")
print(f"Press the {state.get_designated_key()} key {KEY_AMOUNT} times to continue!")
keyboard.hook(on_key_press)
while True:
    if state.get_keys_pressed() >= KEY_AMOUNT:
        break
processed = result.stderr.replace("error", "fumble")
processed = processed.replace("No such file or directory", "You tried to include a file that doesn't exist, genius.")
processed = processed.replace("compilation terminated.", "fix your code then compile it again\n(tip: don't compile the exact same code again expecting it to work)")
processed = processed.replace("expected ';'", "expected ';' and braincells")
print(f"\033[91m{processed}\033[0m")
