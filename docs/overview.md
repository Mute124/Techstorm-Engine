## What is Techstorm {#what-is-techstorm}

---

Techstorm is the response to the lack of a free game engine that is built for large open worlds. 

If you are looking for a hello world application, please see \ref hello-world-example

## Architecture {#architecture}

---

Due to the inherent nature of Techstorm, the architecture can be complex. In terms of building, there are a few things that are required to understand how Techstorm works. There are 4 groups that are used to build the engine, as outlined below:
- Application
- Engine
- Project
- Tools
The Application is responsible for loading the engine and handling the project, as seen below. 

![Game Engine Application Flow Chart](flowchart.png "Techstorm's high level flow chart")

### File System Architecture {#file-system-architecture}

---

**The design of the file system is complex and it is highly encouraged that this is read very carefully. **

As of now, the file system works by recursively searching the "game" folder in the root directory (Techstorm-v5). The folder will contain the "assets" and "data" sub-directories, wherein you will put assets and data files.  

### Graphics Architecture {#graphics-architecture}

---

#### Graphics Introduction {#graphics-introduction}

---

Despite the fact Techstorm tries to make graphics easier, it can become complex due to the nature of 3D graphics. For this reason, it is imperative that you read this carefully in order to reduce future headache. In addition, if you are not well versed in how OpenGL and Raylib works, please read the online book/tutorial [Learn OpenGL](https://learnopengl.com/) and \ref using-raylib respectably.  


#### How Cameras Work {#how-cameras-work}

---

##### Graphics Terminology {#graphics-terminology}

---


## Dependencies {#dependencies}

---

As it is a game engine, Techstorm has alot of dependencies and can be found within the conanfile.txt in the same folder as the main CMakeLists.txt file. In addition to this, the current dependencies are listed as listed below with it's basic purpose. 

* Jolt Physics
	* Handle Techstorm's physics. 
	* [Online Documentation](https://jrouwe.github.io/JoltPhysics/index.html)
	* [Github](https://github.com/jrouwe/JoltPhysics/tree/master)
* Libconfig
	* Handle configuration file read/write.
	* [Online Documentation](http://hyperrealm.github.io/libconfig/libconfig_manual.html)
	* [Github](https://github.com/hyperrealm/libconfig)
	* [Website](http://hyperrealm.github.io/libconfig/)
* RmlUi
	* Handle Techstorm's UI with HTML/CSS.
	* [Online Documentation](https://mikke89.github.io/RmlUiDoc/)
	* [Github](https://github.com/mikke89/RmlUi)
* Asio
	* Provides Techstorm's networking functionality
	* [Online Documentation](https://think-async.com/Asio/asio-1.30.2/doc/)
	* [Website](https://think-async.com/Asio/)
* Argh
	* Command line parsing library that is mainly used by tools. 
	* [Online Documentation](https://github.com/adishavit/argh/blob/master/README.md)
	* [Github](https://github.com/adishavit/argh)
* Dear ImGUI
	* Provides an in-game debug UI for developers.
	* [Online Documentation](https://github.com/ocornut/imgui/wiki)
	* [Github](https://github.com/ocornut/imgui)
* Sol2
	* Provides Lua scripting and modding support.
	* [Online Documentation](https://sol2.readthedocs.io/en/latest/)
	* [Github](https://github.com/ThePhD/sol2)
* Angel Script
	* Provides a more advanced form of modding and scripting support.
	* [Online Documentation](https://www.angelcode.com/angelscript/documentation.html)
	* [Website](https://www.angelcode.com/angelscript/)

If you want an indepth explanation of these dependencies and their implementation status, see \ref detailed-analysis-of-dependencies. 

## Code Conventions {#code-conventions}

---

Techstorm tries to be as easy to read as possible by making the code read similarly to English (This is mandatory for engine contributions!). In addition, Techstorm tries to be intuitive and understandable at a quick glance, hence it uses PascalCase and CamelCase. As such, the code conventions are simple and intuitive. The only exception is with broad cases. 

Broad cases should only be used as long as there are no other applicable cases. For example, a private static variable. This variable would look like a static type variable rather than a private variable. That means it should be named with a prefix of "s" rather than a 'm'. However, please note that this only applies when the "Notes" section contains "Broad case". Additionally, There are some other important distinctions, definitions, and use cases that must be followed to stay compliant, as seen below.

### Important Convention Use Cases {#important-convention-use-cases}

---


| Case                                                                                                             | Distinction |
| ---------------------------------------------------------------------------------------------------------------- | ----------- |
| Preprocessors Unless there are multiple logical inputs, avoid using `#if defined()` and use `#ifdef` instead.  . |             |


### Variables {#variables}

---

| Case                  | Format                       | Example                                            | Notes                                                               |
| --------------------- | ---------------------------- | -------------------------------------------------- | ------------------------------------------------------------------- |
| Private Variables     | mPrivateVariable             | `int mPrivateVariable = 7;`                        |                                                                     |
| Protected Variables   | mProtectedVariable           | `int mProtectedVariable = 4;`                      |                                                                     |
| Static Type Variables | sStaticTypeVariable          | `static inline float sStaticVariable = 3.14f;`     |                                                                     |
| Static Variable       | StaticVariable               | `static inline int StaticVariable = 72;`           |                                                                     |
| Constant Variable     | cConstantVariable            | `const double cConstantVariable = 3.14;`           |                                                                     |
| Constant Expression   | CONSTANT_EXPRESSION_VARIABLE | `constexpr int CONSTANT_EXPRESSION_VARIABLE = 45;` |                                                                     |
| Constant Global       | CONSTANT_GLOBAL_VARIABLE     | `const int GLOBAL_VARIABLE;`                       | A constant global is a variable that is not declared inside a type. |
| Macro                 | MACRO_VARIABLE               | `#define MACRO_VARIABLE 8`                         |                                                                     |
| Local Variable        | localVariable                | `int localVariable = 34;`                          |                                                                     |
| Parameter Variable    | parameterVariable            | `int parameterVariable`                            |                                                                     |
| Public Variable       | publicVariable               | `int publicVariable = 3;`                          |                                                                     |



### Functions {#functions}

---

Functions are simple, any that are not bound to a specific object will have the first letter lowercase. If it is a static, namespace, or global function, then it will have the first letter capitalized instead. When it comes to Preprocessor functions, it will follow the same rules as Constant Global variables, as seen below:

