import subprocess
import os
import sys

def IsConanInstalled():
    try:
        subprocess.check_call(['conan', '--version'])
        print("Conan is already installed\n")
        return True
    except:
        print("Conan is not installed\n")
        return False

def InstallConan():
    print("Installing Conan...")
    subprocess.check_call(['pip', 'install', 'conan'])
    print("Conan is now installed.\n")

def DoesBuildFolderExist():
    return os.path.exists("build")

def RemoveBuildFolder():
    os.rmdir("build")

def CheckConanStep():
    print("Checking for Conan...")

    if IsConanInstalled() == False:
        InstallConan()

    print("Done checking for Conan.\n")

def InstallPackagesStep():
    print("Installing packages...")

    packageConfigsInstalled = [False, False, False]
    removeBuildDir = False
    

    for i in range(len(sys.argv)):
        if sys.argv[i] == "--debug":
            packageConfigsInstalled[0] = True
        elif sys.argv[i] == "--release":
            packageConfigsInstalled[1] = True
        elif sys.argv[i] == "--distribution":
            packageConfigsInstalled[2] = True
        elif sys.argv[i] == "--remove-build-folder":
            removeBuildDir = True

    if DoesBuildFolderExist() == True and removeBuildDir == True:
        print("Removing build folder...")
        RemoveBuildFolder()
        print("Done removing build folder.\n")


    if packageConfigsInstalled[0] == True:
        print("Installing debug packages...")
        subprocess.check_call(['conan', 'install', '.', '--output-folder=build', '--build=missing', '-s', 'build_type=Debug'])

        print("Done installing debug packages.\n")



    if packageConfigsInstalled[1] == True:
        print("Installing release packages...")
        subprocess.check_call(['conan', 'install', '.', '--output-folder=build', '--build=missing', '-s', 'build_type=Release'])

        print("Done installing release packages.\n")


    if packageConfigsInstalled[2] == True:
        print("Installing distribution packages...")
        subprocess.check_call(['conan', 'install', '.', '--output-folder=build', '--build=missing', '-s', 'build_type=Distribution'])

        print("Done installing distribution packages.\n")

    print("Done installing packages.\n")
    return packageConfigsInstalled

def GenerateProjectStep():
    print("Generating project...")
    os.chdir("build")
    subprocess.check_call(['cmake', '..', '-G', 'Visual Studio 17 2022', '-DCMAKE_TOOLCHAIN_FILE=build\conan_toolchain.cmake'])
    print("Done generating project.\n")

def BuildProject(type):
    print("Building project of type " + type + "...")
    subprocess.check_call(['cmake', '--build', '.', '--config=' + type])
    print("Done building project.\n")

print("Configuring Techstorm...")

os.chdir("../")

CheckConanStep()
conf = InstallPackagesStep()
GenerateProjectStep()

print("Building project...")

installedDebug = conf[0]
installedRelease = conf[1]
installedDistribution = conf[2]

if installedDebug == True:
    print("Building debug packages and project...")
    BuildProject("Debug")
    print("Done building debug packages and project.\n")

if installedRelease == True:
    print("Building release packages and project...")
    BuildProject("Release")
    print("Done building release packages and project.\n")

if installedDistribution == True:
    print("Building distribution packages and project...")
    BuildProject("Distribution")
    print("Done building distribution packages and project.\n")

print("Done building project.\n")
    
os.chdir("..")

print("Techstorm is now configured and built. Go to the build folder, and click on the Techstorm.sln solution to begin working. Happy coding, you magnificent developer! :)")