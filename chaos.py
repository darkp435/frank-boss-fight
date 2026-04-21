# A wrapper to make g++ *worse*, because we and society needed this.
import subprocess
import sys

result = subprocess.run(["g++", "game.cpp", "-IC:/SFML/include", "-LC:/SFML/lib", "-lsfml-graphics", "-lsfml-window", "-lsfml-system", "-o", "app"], text=True, capture_output=True)

if result.returncode == 0:
    print("\033[92mCOMPILATION SUCCESSFUL\033[0m")
    sys.exit()
print(f"\033[91m{result.stderr}\033[0m")