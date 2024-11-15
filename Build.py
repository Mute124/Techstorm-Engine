import os
import subprocess
if __name__ == "__main__":
    # If windows, then call build-windows.bat. Otherwise, call build-linux.sh
    if (os.name == "nt"):
        subprocess.call('build-windows.bat')
    else:
        subprocess.call('chmod +x build-linux.sh')
        subprocess.call('./build-linux.sh') 